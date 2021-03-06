#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <npapi.h>
#include <npfunctions.h>
#include <npruntime.h>

/*-----------------------------------------------------------------*/
#if defined(ANDROID)

#undef HAVE_LONG_LONG
#include <jni.h>
#define OSCALL

#define NPP_WRITE_TYPE (NPP_WriteProcPtr)
#define NPStringText UTF8Characters
#define NPStringLen  UTF8Length
extern JNIEnv *pluginJniEnv;

/*-----------------------------------------------------------------*/
#elif defined(WEBKIT_DARWIN_SDK)

#include <Webkit/npapi.h>
#include <WebKit/npfunctions.h>
#include <WebKit/npruntime.h>
#define OSCALL

#endif

static NPObject        *so       = NULL;
static NPNetscapeFuncs *npnfuncs = NULL;
static NPP              inst     = NULL;

/*windowless plugin*/
int bWindowed = 0;


/* NPN */

static void logmsg(const char *msg) {
#if defined(ANDROID)
	FILE *out = fopen("/sdcard/npsimple.log", "a");
	if(out) {
		fputs(msg, out);
		fclose(out);
	}
#elif !defined(_WINDOWS)
	fputs(msg, stderr);
	FILE *out = fopen("/tmp/npsimple.log", "a");
	if(out) {
		fputs(msg, out);
		fclose(out);
	}
#else
	FILE *out = fopen("\\npsimple.log", "a");
	if(out) {
		fputs(msg, out);
		fclose(out);
	}
#endif
}

static bool
hasMethod(NPObject* obj, NPIdentifier methodName) {
	logmsg("npsimple: hasMethod\n");
	return true;
}

static bool
invokeDefault(NPObject *obj, const NPVariant *args, uint32_t argCount, NPVariant *result) {
	logmsg("npsimple: invokeDefault\n");
	result->type = NPVariantType_Int32;
	result->value.intValue = 42;
	return true;
}

static bool
invoke(NPObject* obj, NPIdentifier methodName, const NPVariant *args, uint32_t argCount, NPVariant *result) {
	logmsg("npsimple: invoke\n");
	int error = 1;
	char *name = npnfuncs->utf8fromidentifier(methodName);
	if(name) {
		if(!strcmp(name, "foo")) {
			logmsg("npsimple: invoke foo\n");
			return invokeDefault(obj, args, argCount, result);
		}
		if(!strcmp(name, "quit")) {
			logmsg("npsimple: invoke quit\n");
			exit(0);
			return invokeDefault(obj, args, argCount, result);
		}
		else if(!strcmp(name, "callback")) {
			if(argCount == 1 && args[0].type == NPVariantType_Object) {
				static NPVariant v, r;
				const char kHello[] = "Hello";
				char *txt = (char *)npnfuncs->memalloc(strlen(kHello));

				logmsg("npsimple: invoke callback function\n");
				memcpy(txt, kHello, strlen(kHello));
				STRINGN_TO_NPVARIANT(txt, strlen(kHello), v);

				if(npnfuncs->invokeDefault(inst, NPVARIANT_TO_OBJECT(args[0]), &v, 1, &r))
					return invokeDefault(obj, args, argCount, result);
			}
		}
	}
	// aim exception handling
	npnfuncs->setexception(obj, "exception during invocation");
	return false;
}

static bool
hasProperty(NPObject *obj, NPIdentifier propertyName) {
	logmsg("npsimple: hasProperty\n");
	return false;
}

static bool
getProperty(NPObject *obj, NPIdentifier propertyName, NPVariant *result) {
	logmsg("npsimple: getProperty\n");
	return false;
}

static NPClass npcRefObject = {
	NP_CLASS_STRUCT_VERSION,
	NULL,
	NULL,
	NULL,
	hasMethod,
	invoke,
	invokeDefault,
	hasProperty,
	getProperty,
	NULL,
	NULL,
};

/* NPP */

static NPError
create(NPMIMEType pluginType, NPP instance, uint16_t mode, int16_t argc, char *argn[], char *argv[], NPSavedData *saved) {
	inst = instance;
	logmsg("npsimple: create\n");
	npnfuncs->setvalue(instance, NPPVpluginWindowBool, (void *)bWindowed);

	return NPERR_NO_ERROR;
}

static NPError
destroy(NPP instance, NPSavedData **save) {
	if(so)
		npnfuncs->releaseobject(so);
	so = NULL;
	logmsg("npsimple: destroy\n");
	return NPERR_NO_ERROR;
}

static NPError
setValue(NPP instance, NPNVariable variable, void* value)
{
	return NPERR_GENERIC_ERROR;
}

static NPError
getValue(NPP instance, NPPVariable variable, void *value) {
	inst = instance;

	switch(variable) {
	default:
		logmsg("npsimple: getvalue - default\n");
		return NPERR_GENERIC_ERROR;
	case NPPVpluginNameString:
		logmsg("npsimple: getvalue - name string\n");
		*((char **)value) = "testAgent";
		break;
	case NPPVpluginDescriptionString:
		logmsg("npsimple: getvalue - description string\n");
		*((char **)value) = "testAgent plugin.";
		break;
	case NPPVpluginScriptableNPObject:
		logmsg("npsimple: getvalue - scriptable object\n");
		if(!so)
			so = npnfuncs->createobject(instance, &npcRefObject);
		npnfuncs->retainobject(so);
		*(NPObject **)value = so;
		break;
	case NPPVpluginNeedsXEmbed:
		logmsg("npsimple: getvalue - xembed\n");
		*((int *)value) = 1;
		break;
	}
	return NPERR_NO_ERROR;
}

static NPError /* expected by Safari on Darwin */
handleEvent(NPP instance, void *ev) {
	inst = instance;
	logmsg("npsimple: handleEvent\n");
	return NPERR_NO_ERROR;
}

static NPError /* expected by Opera */
setWindow(NPP instance, NPWindow* pNPWindow) {
	inst = instance;
	logmsg("npsimple: setWindow\n");
	return NPERR_NO_ERROR;
}

/* EXPORT */
#ifdef __cplusplus
extern "C" {
#endif

NPError OSCALL
NP_GetEntryPoints(NPPluginFuncs *nppfuncs) {
	logmsg("npsimple: NP_GetEntryPoints\n");
	nppfuncs->version       = (NP_VERSION_MAJOR << 8) | NP_VERSION_MINOR;
	nppfuncs->newp          = create;
	nppfuncs->destroy       = destroy;
	nppfuncs->getvalue      = getValue;
	nppfuncs->setvalue      = setValue;
	nppfuncs->event         = handleEvent;
	nppfuncs->setwindow     = setWindow;
	nppfuncs->size = sizeof(NPPluginFuncs);

	return NPERR_NO_ERROR;
}

#ifndef HIBYTE
#define HIBYTE(x) ((((uint32_t)(x)) & 0xff00) >> 8)
#endif

NPError OSCALL
NP_Initialize(NPNetscapeFuncs *npnf
#if defined(ANDROID)
			, NPPluginFuncs *nppfuncs, JNIEnv *env, jobject plugin_object
#elif !defined(_WINDOWS) && !defined(WEBKIT_DARWIN_SDK)
			, NPPluginFuncs *nppfuncs
#endif
			) {
	logmsg("npsimple: NP_Initialize\n");
	if(npnf == NULL)
		return NPERR_INVALID_FUNCTABLE_ERROR;

	if(HIBYTE(npnf->version) > NP_VERSION_MAJOR)
		return NPERR_INCOMPATIBLE_VERSION_ERROR;

	npnfuncs = npnf;
#if !defined(_WINDOWS) && !defined(WEBKIT_DARWIN_SDK)
	NP_GetEntryPoints(nppfuncs);
#endif
	return NPERR_NO_ERROR;
}

NPError
OSCALL NP_Shutdown() {
	logmsg("npsimple: NP_Shutdown\n");
	return NPERR_NO_ERROR;
}

char *
NP_GetMIMEDescription(void) {
	logmsg("npsimple: NP_GetMIMEDescription\n");
	return "application/x-test-agent::;";
}

NPError OSCALL /* needs to be present for WebKit based browsers */
NP_GetValue(void *npp, NPPVariable variable, void *value) {
	inst = (NPP)npp;
	return getValue((NPP)npp, variable, value);
}

#ifdef __cplusplus
}
#endif
