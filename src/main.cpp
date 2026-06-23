#include <dlfcn.h>
#include <android/log.h>
#include "ControlsManager.h"
#include "ConfigManager.h"

#define LOG_TAG "CustomControls"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

static ControlsManager* g_controlsManager = nullptr;

extern "C" {
    void ControlsManager_Init();
    void ControlsManager_Render();
    void ControlsManager_OnTouch(int x, int y, int action);
}

__attribute__((constructor))
void mod_init() {
    LOGI("Initializing CustomControls mod...");
    ConfigManager::getInstance().loadConfig();
    g_controlsManager = new ControlsManager();
    LOGI("CustomControls initialized successfully");
}

__attribute__((destructor))
void mod_exit() {
    LOGI("Shutting down CustomControls");
    if (g_controlsManager) {
        delete g_controlsManager;
        g_controlsManager = nullptr;
    }
}

void ControlsManager_Init() {
    if (g_controlsManager) {
        g_controlsManager->initialize();
    }
}

void ControlsManager_Render() {
    if (g_controlsManager) {
        g_controlsManager->render();
    }
}

void ControlsManager_OnTouch(int x, int y, int action) {
    if (g_controlsManager) {
        g_controlsManager->onTouchEvent(x, y, action);
    }
}
