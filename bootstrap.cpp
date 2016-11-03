#include "bootstrap.h"

#include <stdlib.h>
#include <Windows.h>

#include <stdio.h>

#include "ts3_functions.h"
#include "plugin_definitions.h"


static struct TS3Functions funcs;


const char* ts3plugin_name() {
  return "Bootstrap pyTSon";
}

const char* ts3plugin_version() {
  return "1.0.0";
}

int ts3plugin_apiVersion() {
  return 21;
}

const char* ts3plugin_author() {
  return "Thomas \"PLuS\" Pathmann";
}

const char* ts3plugin_description() {
  return "This plugin is used to bootstrap pyTSon. Moving python35.dll to your TeamSpeak install directory makes this plugin obsolete.";
}

int ts3plugin_requestAutoload() {
  return 1;
}

void ts3plugin_setFunctionPointers(const struct TS3Functions functions) {
  funcs = functions;
}

void ts3plugin_freeMemory(void* data) {
  free(data);
}

int ts3plugin_init() {
  char confpath[256];
  const char* plname = "plugins\\pyTSon\\";
  funcs.getConfigPath(confpath, 256 - strlen(plname));
  
  char fullpath[256];
  if (snprintf(fullpath, 256, "%s%s", confpath, plname) < 0) {
	funcs.logMessage("Error constructing pythonlibpath", LogLevel_ERROR, "pyTSon.bootstrap", 0);
    return 1;
  }
  
  wchar_t wbuf[256];
  if (mbstowcs(wbuf, fullpath, 256) == -1) {
    funcs.logMessage("Error converting pythonlibpath", LogLevel_ERROR, "pyTSon.bootstrap", 0);
    return 1;
  }
  
  if (SetDllDirectory(wbuf) == 0) {
    funcs.logMessage("Error setting pythonlibpath", LogLevel_ERROR, "pyTSon.bootstrap", GetLastError());
	return 1;
  }
  
  return 0;
} 

void ts3plugin_shutdown() {

}

int ts3plugin_offersConfigure() {
  return PLUGIN_OFFERS_NO_CONFIGURE;
}

