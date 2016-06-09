//
// Created by Matthias Büchi on 17.09.15.
//
#include <string.h>

#include "XPlugin.h"
#include "XPLMDefs.h"

/*
 *  The XPluginStart function is called by X-Plane right after the plugin's DLL is loaded.
 */
PLUGIN_API int XPluginStart(char *outName, char *outSig, char *outDesc) {
    strcpy(outName, "XPlane Plugin Template");
    strcpy(outSig, "com.something.xplane.template");
    strcpy(outDesc, "Template to implement a XPlane Plugin");

    return 1;
}

/*
 *  The XPluginStop function is called by X-Plane right before the DLL is unloaded.
 *  The plugin will be disabled (if it was enabled) before this routine is called.
 */
PLUGIN_API void XPluginStop(void) {

}

/*
 *  The XPluginEnable function is called by X-Plane right before the plugin is enabled.
 *  Until the plugin is enabled, it will not receive any other callbacks and its UI will be hidden and/or disabled.
 */
PLUGIN_API int XPluginEnable(void) {
    return 1;
}

/*
 *  The XPluginDisable function is called by X-Plane right before the plugin is disabled. When the plugin is disabled,
 *  it will not receive any other callbacks and its UI will be hidden and/or disabled.
 */
PLUGIN_API void XPluginDisable(void) {

}

