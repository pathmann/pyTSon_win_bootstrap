#include "bootstrap.h"

#include <stdlib.h>
#include <Windows.h>
#include <memory.h> 

#include <stdio.h>

#include "ts3_functions.h"
#include "plugin_definitions.h"

#define PATH_LEN 256

static HANDLE memhandle = NULL;
static void* shmem = NULL;

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
  wchar_t curpath[PATH_LEN];
  bool gotpath = false;
  DWORD res = GetDllDirectory(PATH_LEN, curpath);
  if (res == 0)
    funcs.logMessage("Error getting DLL directory, ignoring", LogLevel_WARNING, "pyTSon.bootstrap", GetLastError());
  else if (res > PATH_LEN)
    funcs.logMessage("Error getting DLL directory (path too long), ignoring", LogLevel_WARNING, "pyTSon.bootstrap", GetLastError());
  else gotpath = true;
  
  char confpath[PATH_LEN];
  const char* plname = "plugins\\pyTSon\\";
  funcs.getConfigPath(confpath, PATH_LEN - strlen(plname));
  
  char fullpath[PATH_LEN];
  if (snprintf(fullpath, PATH_LEN, "%s%s", confpath, plname) < 0) {
	funcs.logMessage("Error constructing pythonlibpath", LogLevel_ERROR, "pyTSon.bootstrap", 0);
    return 1;
  }
  
  wchar_t wbuf[PATH_LEN];
  if (mbstowcs(wbuf, fullpath, PATH_LEN) == -1) {
    funcs.logMessage("Error converting pythonlibpath", LogLevel_ERROR, "pyTSon.bootstrap", 0);
    return 1;
  }
  
  if (SetDllDirectory(wbuf) == 0) {
    funcs.logMessage("Error setting pythonlibpath", LogLevel_ERROR, "pyTSon.bootstrap", GetLastError());
	return 1;
  }
  
  if (gotpath) {
    /* if the host or some other plugin did set the dll search path, we want to set the former value back. So we use shared memory to inform pyTSon about the former path. pyTSon will then set it back (if pyTSon is loaded, we don't need the path anymore */
    memhandle = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, PATH_LEN, TEXT("pyTSondllpath"));
    if (memhandle != NULL) {
      shmem = MapViewOfFile(memhandle, FILE_MAP_WRITE, 0, 0, 0);
      if (shmem == NULL)
        funcs.logMessage("Error accessing shared memory object", LogLevel_WARNING, "pyTSon.bootstrap", GetLastError());
      else {
        memset(shmem, '\0', PATH_LEN);
        
        memcpy(shmem, curpath, PATH_LEN);
      }
    }
    else funcs.logMessage("Error creating shared memory object", LogLevel_WARNING, "pyTSon.bootstrap", GetLastError());
  }
  
  return 0;
} 

void ts3plugin_shutdown() {
  if (shmem)
    UnmapViewOfFile(shmem);
  
  if (memhandle)      
    CloseHandle(memhandle);
}

int ts3plugin_offersConfigure() {
  return PLUGIN_OFFERS_NO_CONFIGURE;
}

