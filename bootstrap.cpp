#include "bootstrap.h"

#include <stdlib.h>

#include "ts3_functions.h"
#include "plugin_definitions.h"


static struct TS3Functions funcs;


const char* ts3plugin_name() {
  return "pyTSon Bootstrap";
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
  return 0;
}

void ts3plugin_shutdown() {

}

int ts3plugin_offersConfigure() {
  return PLUGIN_OFFERS_NO_CONFIGURE;
}

