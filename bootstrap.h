#ifndef BOOTSTRAP_H__
#define BOOTSTRAP_H__


#ifdef WIN32
#define EXPORT_SYMBOL __declspec(dllexport)
#else
#define EXPORT_SYMBOL __attribute__ ((visibility("default")))
#endif

#ifdef __cplusplus
extern "C" {
#endif


EXPORT_SYMBOL const char* ts3plugin_name();
EXPORT_SYMBOL const char* ts3plugin_version();
EXPORT_SYMBOL int ts3plugin_apiVersion();
EXPORT_SYMBOL const char* ts3plugin_author();
EXPORT_SYMBOL const char* ts3plugin_description();
EXPORT_SYMBOL int ts3plugin_requestAutoload();
EXPORT_SYMBOL void ts3plugin_setFunctionPointers(const struct TS3Functions functions);
EXPORT_SYMBOL void ts3plugin_freeMemory(void* data);
EXPORT_SYMBOL int ts3plugin_init();
EXPORT_SYMBOL void ts3plugin_shutdown();
EXPORT_SYMBOL int ts3plugin_offersConfigure();


#ifdef __cplusplus
}
#endif

#endif

