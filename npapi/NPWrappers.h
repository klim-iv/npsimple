#ifndef __NP_OBJET_WRAPPER_H__
#define __NP_OBJET_WRAPPER_H__

#include "npapi.h"
#include "npruntime.h"
#include "nptypes.h"

/*****************************************************************************
* Macros to be used to generate Plug-in module functions implementation
*****************************************************************************/

#define DECLARE_PLUGIN_INTERFACE(plugin_name, plugin_description, plugin_mimetypes, plugin_object) \
    class plugin_object##_PluginHelper \
    { \
    public: \
        plugin_object##_PluginHelper(NPP instance) : mScriptableObject(NULL), mBrowser(instance) { } \
        virtual ~plugin_object##_PluginHelper() { if (mScriptableObject) NPN_ReleaseObject(mScriptableObject); } \
        NPObject* getScriptableObject() \
        { \
            if (!mScriptableObject) mScriptableObject = NPN_CreateObject(mBrowser, GET_NPOBJECT_CLASS(plugin_object)); \
            if (mScriptableObject) NPN_RetainObject(mScriptableObject); \
            return mScriptableObject; \
        } \
    private: \
        NPObject*   mScriptableObject; \
        NPP         mBrowser; \
    }; \
    char* NPP_GetMIMEDescription() { static char mimetype[] = plugin_mimetypes; return mimetype; } \
    NPError NPP_GetValue(NPP instance, NPPVariable variable, void* value) \
    { \
        static char psz_name[] = plugin_name; \
        static char psz_desc[] = plugin_description; \
        switch (variable) { \
            case NPPVpluginNameString: *((char**)value) = psz_name; return NPERR_NO_ERROR; \
            case NPPVpluginDescriptionString: *((char**)value) = psz_desc; return NPERR_NO_ERROR; \
        } \
        if (instance == NULL) return NPERR_INVALID_INSTANCE_ERROR; \
        plugin_object##_PluginHelper* p_plugin = reinterpret_cast<plugin_object##_PluginHelper*>(instance->pdata); \
        if (p_plugin == NULL) return NPERR_INVALID_INSTANCE_ERROR; \
        if (variable == NPPVpluginScriptableNPObject) { \
            NPObject* obj = p_plugin->getScriptableObject(); \
            if (obj) { \
                *(NPObject**)value = obj; \
                return NPERR_NO_ERROR; \
            } \
        } \
        return NPERR_GENERIC_ERROR; \
    } \
    NPError NPP_SetValue(NPP instance, NPNVariable variable, void* value) { return NPERR_GENERIC_ERROR; } \
    NPError NPP_Initialize() { return NPERR_NO_ERROR; } \
    void NPP_Shutdown() { } \
    NPError NPP_New(NPMIMEType pluginType, NPP instance, uint16_t mode, int16_t argc, \
                    char* argn[], char* argv[], NPSavedData* saved) \
    { \
        if (instance == NULL) return NPERR_INVALID_INSTANCE_ERROR; \
        plugin_object##_PluginHelper* p_plugin = new plugin_object##_PluginHelper(instance); \
        if (p_plugin == NULL) return NPERR_OUT_OF_MEMORY_ERROR; \
        instance->pdata = reinterpret_cast<void*>(p_plugin); \
        return NPERR_NO_ERROR; \
    } \
    NPError NPP_Destroy(NPP instance, NPSavedData** save) \
    { \
        if (instance == NULL) return NPERR_INVALID_INSTANCE_ERROR; \
        plugin_object##_PluginHelper* p_plugin = reinterpret_cast<plugin_object##_PluginHelper*>(instance->pdata); \
        if (p_plugin == NULL) return NPERR_NO_ERROR; \
        instance->pdata = NULL; \
        delete p_plugin; \
        return NPERR_NO_ERROR; \
    } \
    NPError NPP_SetWindow( NPP instance, NPWindow* window) \
    { \
        if (!instance) return NPERR_INVALID_INSTANCE_ERROR; \
        return NPERR_NO_ERROR; \
    } \
    NPError NPP_NewStream(NPP instance, NPMIMEType type, NPStream* stream, NPBool seekable, uint16_t* stype) \
    { \
        NPN_DestroyStream(instance, stream, NPRES_DONE); \
        return NPERR_NO_ERROR; \
    } \
    int32_t NPP_WriteReady(NPP instance, NPStream* stream) { return 8 * 1024; } \
    int32_t NPP_Write(NPP instance, NPStream* stream, int32_t offset, int32_t len, void* buffer) { return len; } \
    NPError NPP_DestroyStream(NPP instance, NPStream* stream, NPError reason) \
    { \
        if (instance == NULL) return NPERR_INVALID_INSTANCE_ERROR; \
        return NPERR_NO_ERROR; \
    } \
    void NPP_StreamAsFile(NPP instance, NPStream* stream, const char* fname) { } \
    void NPP_URLNotify(NPP instance, const char* url, NPReason reason, void* notifyData) { } \
    void NPP_Print(NPP instance, NPPrint* printInfo) { }

/*****************************************************************************
* Wrapper class to be used to map calls to the NPObject into virtual methods
*****************************************************************************/

class NPObjectWrapper : public NPObject
{
public:
    NPObjectWrapper(NPP npp)
        : mNpp(npp)
    {
    }

    virtual ~NPObjectWrapper()
    {
    }

    // Virtual NPObject hooks called through this base class. Override
    // as you see fit.
    virtual void Invalidate();
    virtual bool HasMethod(NPIdentifier name);
    virtual bool Invoke(NPIdentifier name, const NPVariant *args,
                        uint32_t argCount, NPVariant *result);
    virtual bool InvokeDefault(const NPVariant *args, uint32_t argCount,
                               NPVariant *result);
    virtual bool HasProperty(NPIdentifier name);
    virtual bool GetProperty(NPIdentifier name, NPVariant *result);
    virtual bool SetProperty(NPIdentifier name, const NPVariant *value);
    virtual bool RemoveProperty(NPIdentifier name);
    virtual bool Enumerate(NPIdentifier **identifier, uint32_t *count);
    virtual bool Construct(const NPVariant *args, uint32_t argCount,
                           NPVariant *result);

public:
    static void _Deallocate(NPObject *npobj);
    static void _Invalidate(NPObject *npobj);
    static bool _HasMethod(NPObject *npobj, NPIdentifier name);
    static bool _Invoke(NPObject *npobj, NPIdentifier name,
                        const NPVariant *args, uint32_t argCount,
                        NPVariant *result);
    static bool _InvokeDefault(NPObject *npobj, const NPVariant *args,
                               uint32_t argCount, NPVariant *result);
    static bool _HasProperty(NPObject * npobj, NPIdentifier name);
    static bool _GetProperty(NPObject *npobj, NPIdentifier name,
                             NPVariant *result);
    static bool _SetProperty(NPObject *npobj, NPIdentifier name,
                             const NPVariant *value);
    static bool _RemoveProperty(NPObject *npobj, NPIdentifier name);
    static bool _Enumerate(NPObject *npobj, NPIdentifier **identifier,
                           uint32_t *count);
    static bool _Construct(NPObject *npobj, const NPVariant *args,
                           uint32_t argCount, NPVariant *result);

protected:
    NPP mNpp;
};

#define DECLARE_NPOBJECT_CLASS_WITH_BASE(_class, ctor)  \
    static NPClass s##_class##_NPClass = {              \
    NP_CLASS_STRUCT_VERSION_CTOR,                       \
    ctor,                                               \
    NPObjectWrapper::_Deallocate,            \
    NPObjectWrapper::_Invalidate,            \
    NPObjectWrapper::_HasMethod,             \
    NPObjectWrapper::_Invoke,                \
    NPObjectWrapper::_InvokeDefault,         \
    NPObjectWrapper::_HasProperty,           \
    NPObjectWrapper::_GetProperty,           \
    NPObjectWrapper::_SetProperty,           \
    NPObjectWrapper::_RemoveProperty,        \
    NPObjectWrapper::_Enumerate,             \
    NPObjectWrapper::_Construct              \
}

#define GET_NPOBJECT_CLASS(_class) &s##_class##_NPClass 

#endif
