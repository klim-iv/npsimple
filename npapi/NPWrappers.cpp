#include "NPWrappers.h"
#include "npfunctions.h"

void
NPObjectWrapper::Invalidate()
{
}

bool
NPObjectWrapper::HasMethod(NPIdentifier name)
{
  return false;
}

bool
NPObjectWrapper::Invoke(NPIdentifier name, const NPVariant *args,
                        uint32_t argCount, NPVariant *result)
{
  return false;
}

bool
NPObjectWrapper::InvokeDefault(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
  return false;
}

bool
NPObjectWrapper::HasProperty(NPIdentifier name)
{
  return false;
}

bool
NPObjectWrapper::GetProperty(NPIdentifier name, NPVariant *result)
{
  return false;
}

bool
NPObjectWrapper::SetProperty(NPIdentifier name, const NPVariant *value)
{
  return false;
}

bool
NPObjectWrapper::RemoveProperty(NPIdentifier name)
{
  return false;
}

bool
NPObjectWrapper::Enumerate(NPIdentifier **identifier, uint32_t *count)
{
  return false;
}

bool
NPObjectWrapper::Construct(const NPVariant *args, uint32_t argCount,
                           NPVariant *result)
{
  return false;
}

void
NPObjectWrapper::_Deallocate(NPObject *npobj)
{
  delete (NPObjectWrapper*)npobj;
}

void
NPObjectWrapper::_Invalidate(NPObject *npobj)
{
  ((NPObjectWrapper*)npobj)->Invalidate();
}

bool
NPObjectWrapper::_HasMethod(NPObject *npobj, NPIdentifier name)
{
  return ((NPObjectWrapper*)npobj)->HasMethod(name);
}

bool
NPObjectWrapper::_Invoke(NPObject *npobj, NPIdentifier name,
                                    const NPVariant *args, uint32_t argCount,
                                    NPVariant *result)
{
  return ((NPObjectWrapper*)npobj)->Invoke(name, args, argCount, result);
}

bool
NPObjectWrapper::_InvokeDefault(NPObject *npobj, const NPVariant *args,
                                uint32_t argCount, NPVariant *result)
{
  return ((NPObjectWrapper*)npobj)->InvokeDefault(args, argCount, result);
}

bool
NPObjectWrapper::_HasProperty(NPObject * npobj, NPIdentifier name)
{
  return ((NPObjectWrapper*)npobj)->HasProperty(name);
}

bool
NPObjectWrapper::_GetProperty(NPObject *npobj, NPIdentifier name,
                              NPVariant *result)
{
  return ((NPObjectWrapper*)npobj)->GetProperty(name, result);
}

bool
NPObjectWrapper::_SetProperty(NPObject *npobj, NPIdentifier name,
                              const NPVariant *value)
{
  return ((NPObjectWrapper*)npobj)->SetProperty(name, value);
}

bool
NPObjectWrapper::_RemoveProperty(NPObject *npobj, NPIdentifier name)
{
  return ((NPObjectWrapper*)npobj)->RemoveProperty(name);
}

bool
NPObjectWrapper::_Enumerate(NPObject *npobj, NPIdentifier **identifier, uint32_t *count)
{
  return ((NPObjectWrapper*)npobj)->Enumerate(identifier, count);
}

bool
NPObjectWrapper::_Construct(NPObject *npobj, const NPVariant *args,
                                       uint32_t argCount, NPVariant *result)
{
  return ((NPObjectWrapper*)npobj)->Construct(args, argCount, result);
}

/***********************************************************************
 *
 * Wrapper functions : plugin calling Netscape Navigator
 *
 * These functions let the plugin developer just call the APIs
 * as documented and defined in npapi.h, without needing to know
 * about the function table and call macros in npupp.h.
 *
 ***********************************************************************/

static NPNetscapeFuncs gNetscapeFuncs;    /* Netscape Function table */

void
NPN_Version(int* plugin_major, int* plugin_minor,
         int* netscape_major, int* netscape_minor)
{
    *plugin_major = NP_VERSION_MAJOR;
    *plugin_minor = NP_VERSION_MINOR;

    /* Major version is in high byte */
    *netscape_major = gNetscapeFuncs.version >> 8;
    /* Minor version is in low byte */
    *netscape_minor = gNetscapeFuncs.version & 0xFF;
}

NPError
NPN_GetValue(NPP instance, NPNVariable variable, void *r_value)
{
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
    return CallNPN_GetValueProc(gNetscapeFuncs.getvalue,
                    instance, variable, r_value);
#else
    return (*gNetscapeFuncs.getvalue)(instance, variable, r_value);
#endif
}

NPError
NPN_SetValue(NPP instance, NPPVariable variable, void *value)
{
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
    return CallNPN_SetValueProc(gNetscapeFuncs.setvalue,
                    instance, variable, value);
#else
    return (*gNetscapeFuncs.setvalue)(instance, variable, value);
#endif
}

NPError
NPN_GetURL(NPP instance, const char* url, const char* window)
{
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
    return CallNPN_GetURLProc(gNetscapeFuncs.geturl, instance, url, window);
#else
    return (*gNetscapeFuncs.geturl)(instance, url, window);
#endif
}

NPError
NPN_GetURLNotify(NPP instance, const char* url, const char* window, void* notifyData)
{
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
    return CallNPN_GetURLNotifyProc(gNetscapeFuncs.geturlnotify, instance, url, window, notifyData);
#else
    return (*gNetscapeFuncs.geturlnotify)(instance, url, window, notifyData);
#endif
}

NPError
NPN_PostURL(NPP instance, const char* url, const char* window,
         uint32_t len, const char* buf, NPBool file)
{
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
    return CallNPN_PostURLProc(gNetscapeFuncs.posturl, instance,
                    url, window, len, buf, file);
#else
    return (*gNetscapeFuncs.posturl)(instance, url, window, len, buf, file);
#endif
}

NPError
NPN_PostURLNotify(NPP instance, const char* url, const char* window, uint32_t len,
                  const char* buf, NPBool file, void* notifyData)
{
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
    return CallNPN_PostURLNotifyProc(gNetscapeFuncs.posturlnotify,
            instance, url, window, len, buf, file, notifyData);
#else
    return (*gNetscapeFuncs.posturlnotify)(instance, url, window, len, buf, file, notifyData);

#endif
}

NPError
NPN_RequestRead(NPStream* stream, NPByteRange* rangeList)
{
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
    return CallNPN_RequestReadProc(gNetscapeFuncs.requestread,
                    stream, rangeList);
#else
    return (*gNetscapeFuncs.requestread)(stream, rangeList);
#endif
}

NPError
NPN_NewStream(NPP instance, NPMIMEType type, const char *window,
          NPStream** stream_ptr)
{
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
    return CallNPN_NewStreamProc(gNetscapeFuncs.newstream, instance,
                    type, window, stream_ptr);
#else
    return (*gNetscapeFuncs.newstream)(instance, type, window, stream_ptr);
#endif
}

int32_t
NPN_Write(NPP instance, NPStream* stream, int32_t len, void* buffer)
{
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
    return CallNPN_WriteProc(gNetscapeFuncs.write, instance,
                    stream, len, buffer);
#else
    return (*gNetscapeFuncs.write)(instance, stream, len, buffer);
#endif
}

NPError
NPN_DestroyStream(NPP instance, NPStream* stream, NPError reason)
{
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
    return CallNPN_DestroyStreamProc(gNetscapeFuncs.destroystream,
                        instance, stream, reason);
#else
    return (*gNetscapeFuncs.destroystream)(instance, stream, reason);
#endif
}

void
NPN_Status(NPP instance, const char* message)
{
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
    CallNPN_StatusProc(gNetscapeFuncs.status, instance, message);
#else
    (*gNetscapeFuncs.status)(instance, message);
#endif
}

const char*
NPN_UserAgent(NPP instance)
{
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
    return CallNPN_UserAgentProc(gNetscapeFuncs.uagent, instance);
#else
    return (*gNetscapeFuncs.uagent)(instance);
#endif
}

void *NPN_MemAlloc(uint32_t size)
{
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
    return CallNPN_MemAllocProc(gNetscapeFuncs.memalloc, size);
#else
    return (*gNetscapeFuncs.memalloc)(size);
#endif
}

void NPN_MemFree(void* ptr)
{
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
    CallNPN_MemFreeProc(gNetscapeFuncs.memfree, ptr);
#else
    (*gNetscapeFuncs.memfree)(ptr);
#endif
}

uint32_t NPN_MemFlush(uint32_t size)
{
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
    return CallNPN_MemFlushProc(gNetscapeFuncs.memflush, size);
#else
    return (*gNetscapeFuncs.memflush)(size);
#endif
}

void NPN_ReloadPlugins(NPBool reloadPages)
{
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
    CallNPN_ReloadPluginsProc(gNetscapeFuncs.reloadplugins, reloadPages);
#else
    (*gNetscapeFuncs.reloadplugins)(reloadPages);
#endif
}

void
NPN_InvalidateRect(NPP instance, NPRect *invalidRect)
{
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
    CallNPN_InvalidateRectProc(gNetscapeFuncs.invalidaterect, instance,
        invalidRect);
#else
    (*gNetscapeFuncs.invalidaterect)(instance, invalidRect);
#endif
}

void
NPN_InvalidateRegion(NPP instance, NPRegion invalidRegion)
{
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
    CallNPN_InvalidateRegionProc(gNetscapeFuncs.invalidateregion, instance,
        invalidRegion);
#else
    (*gNetscapeFuncs.invalidateregion)(instance, invalidRegion);
#endif
}

void
NPN_ForceRedraw(NPP instance)
{
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
    CallNPN_ForceRedrawProc(gNetscapeFuncs.forceredraw, instance);
#else
    (*gNetscapeFuncs.forceredraw)(instance);
#endif
}

void NPN_PushPopupsEnabledState(NPP instance, NPBool enabled)
{
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
    CallNPN_PushPopupsEnabledStateProc(gNetscapeFuncs.pushpopupsenabledstate,
        instance, enabled);
#else
    (*gNetscapeFuncs.pushpopupsenabledstate)(instance, enabled);
#endif
}

void NPN_PopPopupsEnabledState(NPP instance)
{
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
    CallNPN_PopPopupsEnabledStateProc(gNetscapeFuncs.poppopupsenabledstate,
        instance);
#else
    (*gNetscapeFuncs.poppopupsenabledstate)(instance);
#endif
}

NPIdentifier NPN_GetStringIdentifier(const NPUTF8 *name)
{
    int minor = gNetscapeFuncs.version & 0xFF;
    if( minor >= 14 )
    {
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
        return CallNPN_GetStringIdentifierProc(
                        gNetscapeFuncs.getstringidentifier, name);
#else
        return (*gNetscapeFuncs.getstringidentifier)(name);
#endif
    }
    return NULL;
}

void NPN_GetStringIdentifiers(const NPUTF8 **names, int32_t nameCount,
                              NPIdentifier *identifiers)
{
    int minor = gNetscapeFuncs.version & 0xFF;
    if( minor >= 14 )
    {
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
        CallNPN_GetStringIdentifiersProc(gNetscapeFuncs.getstringidentifiers,
                                         names, nameCount, identifiers);
#else
        (*gNetscapeFuncs.getstringidentifiers)(names, nameCount, identifiers);
#endif
    }
}

NPIdentifier NPN_GetIntIdentifier(int32_t intid)
{
    int minor = gNetscapeFuncs.version & 0xFF;
    if( minor >= 14 )
    {
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
        return CallNPN_GetIntIdentifierProc(gNetscapeFuncs.getintidentifier, intid);
#else
        return (*gNetscapeFuncs.getintidentifier)(intid);
#endif
    }
    return NULL;
}

bool NPN_IdentifierIsString(NPIdentifier identifier)
{
    int minor = gNetscapeFuncs.version & 0xFF;
    if( minor >= 14 )
    {
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
        return CallNPN_IdentifierIsStringProc(
                        gNetscapeFuncs.identifierisstring,
                        identifier);
#else
        return (*gNetscapeFuncs.identifierisstring)(identifier);
#endif
    }
    return false;
}

NPUTF8 *NPN_UTF8FromIdentifier(NPIdentifier identifier)
{
    int minor = gNetscapeFuncs.version & 0xFF;
    if( minor >= 14 )
    {
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
        return CallNPN_UTF8FromIdentifierProc(
                            gNetscapeFuncs.utf8fromidentifier,
                            identifier);
#else
        return (*gNetscapeFuncs.utf8fromidentifier)(identifier);
#endif
    }
    return NULL;
}

int32_t NPN_IntFromIdentifier(NPIdentifier identifier)
{
    int minor = gNetscapeFuncs.version & 0xFF;
    if( minor >= 14 )
    {
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
        return CallNPN_IntFromIdentifierProc(
                        gNetscapeFuncs.intfromidentifier,
                        identifier);
#else
        return (*gNetscapeFuncs.intfromidentifier)(identifier);
#endif
    }
    return 0;
}

NPObject *NPN_CreateObject(NPP npp, NPClass *aClass)
{
    int minor = gNetscapeFuncs.version & 0xFF;
    if( minor >= 14 )
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
        return CallNPN_CreateObjectProc(gNetscapeFuncs.createobject, npp, aClass);
#else
        return (*gNetscapeFuncs.createobject)(npp, aClass);
#endif
    return NULL;
}

NPObject *NPN_RetainObject(NPObject *obj)
{
    int minor = gNetscapeFuncs.version & 0xFF;
    if( minor >= 14 )
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
        return CallNPN_RetainObjectProc(gNetscapeFuncs.retainobject, obj);
#else
        return (*gNetscapeFuncs.retainobject)(obj);
#endif
    return NULL;
}

void NPN_ReleaseObject(NPObject *obj)
{
    int minor = gNetscapeFuncs.version & 0xFF;
    if( minor >= 14 )
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
        CallNPN_ReleaseObjectProc(gNetscapeFuncs.releaseobject, obj);
#else
        (*gNetscapeFuncs.releaseobject)(obj);
#endif
}

bool NPN_Invoke(NPP npp, NPObject* obj, NPIdentifier methodName,
                const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    int minor = gNetscapeFuncs.version & 0xFF;
    if( minor >= 14 )
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
        return CallNPN_InvokeProc(gNetscapeFuncs.invoke, npp, obj, methodName,
                                  args, argCount, result);
#else
        return (*gNetscapeFuncs.invoke)(npp, obj, methodName, args, argCount, result);
#endif
    return false;
}

bool NPN_InvokeDefault(NPP npp, NPObject* obj, const NPVariant *args,
                       uint32_t argCount, NPVariant *result)
{
    int minor = gNetscapeFuncs.version & 0xFF;
    if( minor >= 14 )
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
        return CallNPN_InvokeDefaultProc(gNetscapeFuncs.invokeDefault, npp, obj,
                                         args, argCount, result);
#else
        return (*gNetscapeFuncs.invokeDefault)(npp, obj, args, argCount, result);
#endif
    return false;
}

bool NPN_Evaluate(NPP npp, NPObject* obj, NPString *script,
                  NPVariant *result)
{
    int minor = gNetscapeFuncs.version & 0xFF;
    if( minor >= 14 )
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
        return CallNPN_EvaluateProc(gNetscapeFuncs.evaluate, npp, obj,
                                    script, result);
#else
        return (*gNetscapeFuncs.evaluate)(npp, obj, script, result);
#endif
    return false;
}

bool NPN_GetProperty(NPP npp, NPObject* obj, NPIdentifier propertyName,
                     NPVariant *result)
{
    int minor = gNetscapeFuncs.version & 0xFF;
    if( minor >= 14 )
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
        return CallNPN_GetPropertyProc(gNetscapeFuncs.getproperty, npp, obj,
                                       propertyName, result);
#else
        return (*gNetscapeFuncs.getproperty)(npp, obj, propertyName, result);
#endif
    return false;
}

bool NPN_SetProperty(NPP npp, NPObject* obj, NPIdentifier propertyName,
                     const NPVariant *value)
{
    int minor = gNetscapeFuncs.version & 0xFF;
    if( minor >= 14 )
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
        return CallNPN_SetPropertyProc(gNetscapeFuncs.setproperty, npp, obj,
                                       propertyName, value);
#else
        return (*gNetscapeFuncs.setproperty)(npp, obj, propertyName, value);
#endif
    return false;
}

bool NPN_RemoveProperty(NPP npp, NPObject* obj, NPIdentifier propertyName)
{
    int minor = gNetscapeFuncs.version & 0xFF;
    if( minor >= 14 )
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
        return CallNPN_RemovePropertyProc(gNetscapeFuncs.removeproperty, npp, obj,
                                          propertyName);
#else
        return (*gNetscapeFuncs.removeproperty)(npp, obj, propertyName);
#endif
    return false;
}

bool NPN_HasProperty(NPP npp, NPObject* obj, NPIdentifier propertyName)
{
    int minor = gNetscapeFuncs.version & 0xFF;
    if( minor >= 14 )
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
        return CallNPN_HasPropertyProc(gNetscapeFuncs.hasproperty, npp, obj,
                                       propertyName);
#else
        return (*gNetscapeFuncs.hasproperty)(npp, obj, propertyName);
#endif
    return false;
}

bool NPN_HasMethod(NPP npp, NPObject* obj, NPIdentifier methodName)
{
    int minor = gNetscapeFuncs.version & 0xFF;
    if( minor >= 14 )
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
        return CallNPN_HasMethodProc(gNetscapeFuncs.hasmethod, npp,
                                     obj, methodName);
#else
        return (*gNetscapeFuncs.hasmethod)(npp, obj, methodName);
#endif
    return false;
}

void NPN_ReleaseVariantValue(NPVariant *variant)
{
    int minor = gNetscapeFuncs.version & 0xFF;
    if( minor >= 14 )
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
        CallNPN_ReleaseVariantValueProc(gNetscapeFuncs.releasevariantvalue, variant);
#else
        (*gNetscapeFuncs.releasevariantvalue)(variant);
#endif
}

void NPN_SetException(NPObject* obj, const NPUTF8 *message)
{
    int minor = gNetscapeFuncs.version & 0xFF;
    if( minor >= 14 )
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
        CallNPN_SetExceptionProc(gNetscapeFuncs.setexception, obj, message);
#else
        (*gNetscapeFuncs.setexception)(obj, message);
#endif
}

/***********************************************************************
 *
 * Wrapper functions : Netscape Navigator -> plugin
 *
 * These functions let the plugin developer just create the APIs
 * as documented and defined in npapi.h, without needing to 
 * install those functions in the function table or worry about
 * setting up globals for 68K plugins.
 *
 ***********************************************************************/

/* Function prototypes */
NPError Private_New(NPMIMEType pluginType, NPP instance, uint16_t mode,
        int16_t argc, char* argn[], char* argv[], NPSavedData* saved);
NPError Private_Destroy(NPP instance, NPSavedData** save);
NPError Private_SetWindow(NPP instance, NPWindow* window);
NPError Private_NewStream(NPP instance, NPMIMEType type, NPStream* stream,
                          NPBool seekable, uint16_t* stype);
int32_t Private_WriteReady(NPP instance, NPStream* stream);
int32_t Private_Write(NPP instance, NPStream* stream, int32_t offset,
                    int32_t len, void* buffer);
void Private_StreamAsFile(NPP instance, NPStream* stream, const char* fname);
NPError Private_DestroyStream(NPP instance, NPStream* stream, NPError reason);
void Private_URLNotify(NPP instance, const char* url,
                       NPReason reason, void* notifyData);
void Private_Print(NPP instance, NPPrint* platformPrint);
NPError Private_GetValue(NPP instance, NPPVariable variable, void *r_value);
NPError Private_SetValue(NPP instance, NPNVariable variable, void *r_value);

/* function implementations */
NPError
Private_New(NPMIMEType pluginType, NPP instance, uint16_t mode,
        int16_t argc, char* argn[], char* argv[], NPSavedData* saved)
{
    NPError ret;
    ret = NPP_New(pluginType, instance, mode, argc, argn, argv, saved);
    return ret; 
}

NPError
Private_Destroy(NPP instance, NPSavedData** save)
{
    return NPP_Destroy(instance, save);
}

NPError
Private_SetWindow(NPP instance, NPWindow* window)
{
    NPError err;
    err = NPP_SetWindow(instance, window);
    return err;
}

NPError
Private_NewStream(NPP instance, NPMIMEType type, NPStream* stream,
            NPBool seekable, uint16_t* stype)
{
    NPError err;
    err = NPP_NewStream(instance, type, stream, seekable, stype);
    return err;
}

int32_t
Private_WriteReady(NPP instance, NPStream* stream)
{
    unsigned int result;
    result = NPP_WriteReady(instance, stream);
    return result;
}

int32_t
Private_Write(NPP instance, NPStream* stream, int32_t offset, int32_t len,
        void* buffer)
{
    unsigned int result;
    result = NPP_Write(instance, stream, offset, len, buffer);
    return result;
}

void
Private_StreamAsFile(NPP instance, NPStream* stream, const char* fname)
{
    NPP_StreamAsFile(instance, stream, fname);
}


NPError
Private_DestroyStream(NPP instance, NPStream* stream, NPError reason)
{
    NPError err;
    err = NPP_DestroyStream(instance, stream, reason);
    return err;
}

void
Private_URLNotify(NPP instance, const char* url,
                NPReason reason, void* notifyData)
{
    NPP_URLNotify(instance, url, reason, notifyData);
}

void
Private_Print(NPP instance, NPPrint* platformPrint)
{
    NPP_Print(instance, platformPrint);
}

NPError
Private_GetValue(NPP instance, NPPVariable variable, void *r_value)
{
    return NPP_GetValue(instance, variable, r_value);
}

NPError
Private_SetValue(NPP instance, NPNVariable variable, void *r_value)
{
    return NPP_SetValue(instance, variable, r_value);
}

/*********************************************************************** 
 *
 * These functions are located automagically by netscape.
 *
 ***********************************************************************/

/* EXPORT */
#ifdef __cplusplus
extern "C" {
#endif

/*
 * NP_GetMIMEDescription
 *  - Netscape needs to know about this symbol
 *  - Netscape uses the return value to identify when an object instance
 *    of this plugin should be created.
 */
char *
NP_GetMIMEDescription(void)
{
#ifdef _WINDOWS
	return NULL;
#else
    return NPP_GetMIMEDescription();
#endif
}

/*
 * NP_GetValue [optional]
 *  - Netscape needs to know about this symbol.
 *  - Interfaces with plugin to get values for predefined variables
 *    that the navigator needs.
 */
NPError
NP_GetValue(void* future, NPPVariable variable, void *value)
{
    return NPP_GetValue((NPP_t*)future, variable, value);
}

/*
 * NP_Initialize
 *  - Netscape needs to know about this symbol.
 *  - It calls this function after looking up its symbol before it
 *    is about to create the first ever object of this kind.
 *
 * PARAMETERS
 *    nsTable   - The netscape function table. If developers just use these
 *        wrappers, they don't need to worry about all these function
 *        tables.
 * RETURN
 *    pluginFuncs
 *      - This functions needs to fill the plugin function table
 *        pluginFuncs and return it. Netscape Navigator plugin
 *        library will use this function table to call the plugin.
 *
 */
NPError OSCALL
#ifndef _WINDOWS
NP_Initialize(NPNetscapeFuncs* nsTable, NPPluginFuncs* pluginFuncs)
#else
NP_Initialize(NPNetscapeFuncs* nsTable)
#endif
{
    NPError err = NPERR_NO_ERROR;

    /* validate input parameters */
    if (( nsTable == NULL))
		err = NPERR_INVALID_FUNCTABLE_ERROR;

    /*
     * Check the major version passed in Netscape's function table.
     * We won't load if the major version is newer than what we expect.
     * Also check that the function tables passed in are big enough for
     * all the functions we need (they could be bigger, if Netscape added
     * new APIs, but that's OK with us -- we'll just ignore them).
     *
     */
    if (err == NPERR_NO_ERROR) {
        if ((nsTable->version >> 8) > NP_VERSION_MAJOR)
            err = NPERR_INCOMPATIBLE_VERSION_ERROR;
        if (nsTable->size < ((char *)&nsTable->posturlnotify - (char *)nsTable))
            err = NPERR_INVALID_FUNCTABLE_ERROR;
    }

    int minor;
    if (err == NPERR_NO_ERROR)
    {
        /*
         * Copy all the fields of Netscape function table into our
         * copy so we can call back into Netscape later.  Note that
         * we need to copy the fields one by one, rather than assigning
         * the whole structure, because the Netscape function table
         * could actually be bigger than what we expect.
         */
		minor = nsTable->version & 0xFF;

        gNetscapeFuncs.version       = nsTable->version;
        gNetscapeFuncs.size          = nsTable->size;
        gNetscapeFuncs.posturl       = nsTable->posturl;
        gNetscapeFuncs.geturl        = nsTable->geturl;
        gNetscapeFuncs.requestread   = nsTable->requestread;
        gNetscapeFuncs.newstream     = nsTable->newstream;
        gNetscapeFuncs.write         = nsTable->write;
        gNetscapeFuncs.destroystream = nsTable->destroystream;
        gNetscapeFuncs.status        = nsTable->status;
        gNetscapeFuncs.uagent        = nsTable->uagent;
        gNetscapeFuncs.memalloc      = nsTable->memalloc;
        gNetscapeFuncs.memfree       = nsTable->memfree;
        gNetscapeFuncs.memflush      = nsTable->memflush;
        gNetscapeFuncs.reloadplugins = nsTable->reloadplugins;

        gNetscapeFuncs.getvalue      = nsTable->getvalue;
        gNetscapeFuncs.setvalue      = nsTable->setvalue;

        if( minor >= NPVERS_HAS_NOTIFICATION )
        {
            gNetscapeFuncs.geturlnotify  = nsTable->geturlnotify;
            gNetscapeFuncs.posturlnotify = nsTable->posturlnotify;
        }

        if (nsTable->size >= ((char *)&nsTable->setexception - (char *)nsTable))
        {
            gNetscapeFuncs.invalidaterect = nsTable->invalidaterect;
            gNetscapeFuncs.invalidateregion = nsTable->invalidateregion;
            gNetscapeFuncs.forceredraw = nsTable->forceredraw;
            /* npruntime support */
            if (minor >= 14)
            {
                gNetscapeFuncs.getstringidentifier = nsTable->getstringidentifier;
                gNetscapeFuncs.getstringidentifiers = nsTable->getstringidentifiers;
                gNetscapeFuncs.getintidentifier = nsTable->getintidentifier;
                gNetscapeFuncs.identifierisstring = nsTable->identifierisstring;
                gNetscapeFuncs.utf8fromidentifier = nsTable->utf8fromidentifier;
                gNetscapeFuncs.intfromidentifier = nsTable->intfromidentifier;
                gNetscapeFuncs.createobject = nsTable->createobject;
                gNetscapeFuncs.retainobject = nsTable->retainobject;
                gNetscapeFuncs.releaseobject = nsTable->releaseobject;
                gNetscapeFuncs.invoke = nsTable->invoke;
                gNetscapeFuncs.invokeDefault = nsTable->invokeDefault;
                gNetscapeFuncs.evaluate = nsTable->evaluate;
                gNetscapeFuncs.getproperty = nsTable->getproperty;
                gNetscapeFuncs.setproperty = nsTable->setproperty;
                gNetscapeFuncs.removeproperty = nsTable->removeproperty;
                gNetscapeFuncs.hasproperty = nsTable->hasproperty;
                gNetscapeFuncs.hasmethod = nsTable->hasmethod;
                gNetscapeFuncs.releasevariantvalue = nsTable->releasevariantvalue;
                gNetscapeFuncs.setexception = nsTable->setexception;
            }
        }
        else
        {
            gNetscapeFuncs.invalidaterect = NULL;
            gNetscapeFuncs.invalidateregion = NULL;
            gNetscapeFuncs.forceredraw = NULL;
            gNetscapeFuncs.getstringidentifier = NULL;
            gNetscapeFuncs.getstringidentifiers = NULL;
            gNetscapeFuncs.getintidentifier = NULL;
            gNetscapeFuncs.identifierisstring = NULL;
            gNetscapeFuncs.utf8fromidentifier = NULL;
            gNetscapeFuncs.intfromidentifier = NULL;
            gNetscapeFuncs.createobject = NULL;
            gNetscapeFuncs.retainobject = NULL;
            gNetscapeFuncs.releaseobject = NULL;
            gNetscapeFuncs.invoke = NULL;
            gNetscapeFuncs.invokeDefault = NULL;
            gNetscapeFuncs.evaluate = NULL;
            gNetscapeFuncs.getproperty = NULL;
            gNetscapeFuncs.setproperty = NULL;
            gNetscapeFuncs.removeproperty = NULL;
            gNetscapeFuncs.hasproperty = NULL;
            gNetscapeFuncs.releasevariantvalue = NULL;
            gNetscapeFuncs.setexception = NULL;
        }
        if (nsTable->size >=
            ((char *)&nsTable->poppopupsenabledstate - (char *)nsTable))
        {
            gNetscapeFuncs.pushpopupsenabledstate = nsTable->pushpopupsenabledstate;
            gNetscapeFuncs.poppopupsenabledstate  = nsTable->poppopupsenabledstate;
        }
        else
        {
            gNetscapeFuncs.pushpopupsenabledstate = NULL;
            gNetscapeFuncs.poppopupsenabledstate  = NULL;
        }
	}
#ifndef _WINDOWS
    /*
     * Set up the plugin function table that Netscape will use to
     * call us.  Netscape needs to know about our version and size
     * and have a UniversalProcPointer for every function we
     * implement.
     */
    if ((pluginFuncs == NULL))
		err = NPERR_INVALID_FUNCTABLE_ERROR;

    if (pluginFuncs->size < sizeof(NPPluginFuncs))
        err = NPERR_INVALID_FUNCTABLE_ERROR;


    if (err == NPERR_NO_ERROR)
    {
        pluginFuncs->version    = (NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR;
        pluginFuncs->size       = sizeof(NPPluginFuncs);
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
        pluginFuncs->newp       = NewNPP_NewProc(Private_New);
        pluginFuncs->destroy    = NewNPP_DestroyProc(Private_Destroy);
        pluginFuncs->setwindow  = NewNPP_SetWindowProc(Private_SetWindow);
        pluginFuncs->newstream  = NewNPP_NewStreamProc(Private_NewStream);
        pluginFuncs->destroystream = NewNPP_DestroyStreamProc(Private_DestroyStream);
        pluginFuncs->asfile     = NewNPP_StreamAsFileProc(Private_StreamAsFile);
        pluginFuncs->writeready = NewNPP_WriteReadyProc(Private_WriteReady);
        pluginFuncs->write      = NewNPP_WriteProc(Private_Write);
        pluginFuncs->print      = NewNPP_PrintProc(Private_Print);
        pluginFuncs->getvalue   = NewNPP_GetValueProc(Private_GetValue);
        pluginFuncs->setvalue   = NewNPP_SetValueProc(Private_SetValue);
#else
        pluginFuncs->newp       = (NPP_NewProcPtr)(Private_New);
        pluginFuncs->destroy    = (NPP_DestroyProcPtr)(Private_Destroy);
        pluginFuncs->setwindow  = (NPP_SetWindowProcPtr)(Private_SetWindow);
        pluginFuncs->newstream  = (NPP_NewStreamProcPtr)(Private_NewStream);
        pluginFuncs->destroystream = (NPP_DestroyStreamProcPtr)(Private_DestroyStream);
        pluginFuncs->asfile     = (NPP_StreamAsFileProcPtr)(Private_StreamAsFile);
        pluginFuncs->writeready = (NPP_WriteReadyProcPtr)(Private_WriteReady);
        pluginFuncs->write      = (NPP_WriteProcPtr)(Private_Write);
        pluginFuncs->print      = (NPP_PrintProcPtr)(Private_Print);
        pluginFuncs->getvalue   = (NPP_GetValueProcPtr)(Private_GetValue);
        pluginFuncs->setvalue   = (NPP_SetValueProcPtr)(Private_SetValue);
#endif
        pluginFuncs->event      = NULL;
        if( minor >= NPVERS_HAS_NOTIFICATION )
        {
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
            pluginFuncs->urlnotify = NewNPP_URLNotifyProc(Private_URLNotify);
#else
            pluginFuncs->urlnotify = (NPP_URLNotifyProcPtr)(Private_URLNotify);
#endif
        }
        pluginFuncs->javaClass = NULL;

        err = NPP_Initialize();
    }
#endif
    return err;
}

/*
 * NP_Shutdown [optional]
 *  - Netscape needs to know about this symbol.
 *  - It calls this function after looking up its symbol after
 *    the last object of this kind has been destroyed.
 *
 */
NPError OSCALL
NP_Shutdown(void)
{
    NPP_Shutdown();
    return NPERR_NO_ERROR;
}


#ifdef _WINDOWS
/*
 * NP_GetEntryPoints [mandatory in Windows]
 *  - Netscape needs to know about this symbol.
 *  - It calls this function after looking up its symbol before it
 *    is about to create the first ever object of this kind.
 * RETURN
 *    pluginFuncs
 *      - This functions needs to fill the plugin function table
 *        pluginFuncs and return it. Netscape Navigator plugin
 *        library will use this function table to call the plugin.
 */
NPError OSCALL
NP_GetEntryPoints(NPPluginFuncs* pluginFuncs)
{
    NPError err = NPERR_NO_ERROR;

    if ((pluginFuncs == NULL))
		err = NPERR_INVALID_FUNCTABLE_ERROR;

    if (pluginFuncs->size < sizeof(NPPluginFuncs))
        err = NPERR_INVALID_FUNCTABLE_ERROR;


    if (err == NPERR_NO_ERROR)
    {
        pluginFuncs->version    = (NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR;
        pluginFuncs->size       = sizeof(NPPluginFuncs);
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
        pluginFuncs->newp       = NewNPP_NewProc(Private_New);
        pluginFuncs->destroy    = NewNPP_DestroyProc(Private_Destroy);
        pluginFuncs->setwindow  = NewNPP_SetWindowProc(Private_SetWindow);
        pluginFuncs->newstream  = NewNPP_NewStreamProc(Private_NewStream);
        pluginFuncs->destroystream = NewNPP_DestroyStreamProc(Private_DestroyStream);
        pluginFuncs->asfile     = NewNPP_StreamAsFileProc(Private_StreamAsFile);
        pluginFuncs->writeready = NewNPP_WriteReadyProc(Private_WriteReady);
        pluginFuncs->write      = NewNPP_WriteProc(Private_Write);
        pluginFuncs->print      = NewNPP_PrintProc(Private_Print);
        pluginFuncs->getvalue   = NewNPP_GetValueProc(Private_GetValue);
        pluginFuncs->setvalue   = NewNPP_SetValueProc(Private_SetValue);
#else
        pluginFuncs->newp       = (NPP_NewProcPtr)(Private_New);
        pluginFuncs->destroy    = (NPP_DestroyProcPtr)(Private_Destroy);
        pluginFuncs->setwindow  = (NPP_SetWindowProcPtr)(Private_SetWindow);
        pluginFuncs->newstream  = (NPP_NewStreamProcPtr)(Private_NewStream);
        pluginFuncs->destroystream = (NPP_DestroyStreamProcPtr)(Private_DestroyStream);
        pluginFuncs->asfile     = (NPP_StreamAsFileProcPtr)(Private_StreamAsFile);
        pluginFuncs->writeready = (NPP_WriteReadyProcPtr)(Private_WriteReady);
        pluginFuncs->write      = (NPP_WriteProcPtr)(Private_Write);
        pluginFuncs->print      = (NPP_PrintProcPtr)(Private_Print);
        pluginFuncs->getvalue   = (NPP_GetValueProcPtr)(Private_GetValue);
        pluginFuncs->setvalue   = (NPP_SetValueProcPtr)(Private_SetValue);
#endif
        pluginFuncs->event      = NULL;
#if (((NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR) < 20)
        pluginFuncs->urlnotify = NewNPP_URLNotifyProc(Private_URLNotify);
#else
        pluginFuncs->urlnotify = (NPP_URLNotifyProcPtr)(Private_URLNotify);
#endif
        pluginFuncs->javaClass = NULL;

		err = NPP_Initialize();
    }

    return err;
}
#endif

#ifdef __cplusplus
}
#endif
