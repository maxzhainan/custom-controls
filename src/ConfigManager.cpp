#include "ConfigManager.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <android/log.h>
#include <cJSON.h>

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "CustomControls", __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, "CustomControls", __VA_ARGS__)

ConfigManager& ConfigManager::getInstance() {
    static ConfigManager instance;
    return instance;
}

ConfigManager::ConfigManager() {
    configPath = getConfigPath();
}

std::string ConfigManager::getConfigPath() {
    // Typically /sdcard/Android/data/com.mojang.minecraftpe/files/controls_config.json
    return "/sdcard/Android/data/com.mojang.minecraftpe/files/controls_config.json";
}

bool ConfigManager::fileExists(const std::string& path) {
    std::ifstream file(path);
    return file.good();
}

void ConfigManager::loadConfig() {
    if (fileExists(configPath)) {
        importConfig(configPath);
        LOGI("Loaded config from: %s", configPath.c_str());
    } else {
        LOGI("Config not found, creating default");
        createDefaultConfig();
    }
}

void ConfigManager::createDefaultConfig() {
    config.presetName = "default";
    config.buttonOpacity = 0.7f;
    config.buttonSize = 80;
    config.editMode = false;
    
    std::vector<ControlButton> defaultLayout = {
        {"jump", "JUMP", 50, 500, 80, 80, 32},
        {"crouch", "SNEAK", 150, 500, 80, 80, 29},
        {"attack", "ATTACK", 1000, 500, 80, 80, 1},
        {"place", "PLACE", 1100, 500, 80, 80, 3},
        {"drop", "DROP", 900, 500, 80, 80, 16},
        {"inventory", "INV", 50, 50, 80, 80, 18},
    };
    
    config.presets["default"] = defaultLayout;
    saveConfig();
}

void ConfigManager::importConfig(const std::string& jsonPath) {
    std::ifstream file(jsonPath);
    if (!file.is_open()) {
        LOGE("Failed to open config file: %s", jsonPath.c_str());
        createDefaultConfig();
        return;
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    
    cJSON* root = cJSON_Parse(buffer.str().c_str());
    if (!root) {
        LOGE("Failed to parse JSON config");
        createDefaultConfig();
        return;
    }
    
    // Parse preset name
    cJSON* presetNameObj = cJSON_GetObjectItem(root, "presetName");
    if (presetNameObj && presetNameObj->valuestring) {
        config.presetName = presetNameObj->valuestring;
    }
    
    // Parse presets
    cJSON* presetsObj = cJSON_GetObjectItem(root, "presets");
    if (presetsObj) {
        cJSON* preset = presetsObj->child;
        while (preset) {
            std::vector<ControlButton> buttons;
            cJSON* button = preset->child;
            while (button) {
                ControlButton btn;
                btn.id = cJSON_GetStringValue(cJSON_GetObjectItem(button, "id"));
                btn.label = cJSON_GetStringValue(cJSON_GetObjectItem(button, "label"));
                btn.x = cJSON_GetNumberValue(cJSON_GetObjectItem(button, "x"));
                btn.y = cJSON_GetNumberValue(cJSON_GetObjectItem(button, "y"));
                btn.width = cJSON_GetNumberValue(cJSON_GetObjectItem(button, "width"));
                btn.height = cJSON_GetNumberValue(cJSON_GetObjectItem(button, "height"));
                btn.keyCode = cJSON_GetNumberValue(cJSON_GetObjectItem(button, "keyCode"));
                buttons.push_back(btn);
                button = button->next;
            }
            config.presets[preset->string] = buttons;
            preset = preset->next;
        }
    }
    
    cJSON_Delete(root);
}

void ConfigManager::saveConfig() {
    cJSON* root = cJSON_CreateObject();
    
    cJSON_AddStringToObject(root, "presetName", config.presetName.c_str());
    cJSON* presetsObj = cJSON_AddObjectToObject(root, "presets");
    
    for (const auto& [presetName, buttons] : config.presets) {
        cJSON* presetArray = cJSON_AddArrayToObject(presetsObj, presetName.c_str());
        for (const auto& btn : buttons) {
            cJSON* buttonObj = cJSON_CreateObject();
            cJSON_AddStringToObject(buttonObj, "id", btn.id.c_str());
            cJSON_AddStringToObject(buttonObj, "label", btn.label.c_str());
            cJSON_AddNumberToObject(buttonObj, "x", btn.x);
            cJSON_AddNumberToObject(buttonObj, "y", btn.y);
            cJSON_AddNumberToObject(buttonObj, "width", btn.width);
            cJSON_AddNumberToObject(buttonObj, "height", btn.height);
            cJSON_AddNumberToObject(buttonObj, "keyCode", btn.keyCode);
            cJSON_AddItemToArray(presetArray, buttonObj);
        }
    }
    
    char* jsonStr = cJSON_Print(root);
    
    std::ofstream file(configPath);
    if (file.is_open()) {
        file << jsonStr;
        file.close();
        LOGI("Config saved to: %s", configPath.c_str());
    } else {
        LOGE("Failed to save config to: %s", configPath.c_str());
    }
    
    free(jsonStr);
    cJSON_Delete(root);
}

void ConfigManager::exportConfig(const std::string& jsonPath) {
    std::string backup = configPath;
    configPath = jsonPath;
    saveConfig();
    configPath = backup;
    LOGI("Config exported to: %s", jsonPath.c_str());
}

const Config& ConfigManager::getConfig() const {
    return config;
}

void ConfigManager::setConfig(const Config& cfg) {
    config = cfg;
    saveConfig();
}

void ConfigManager::addPreset(const std::string& name, const std::vector<ControlButton>& buttons) {
    config.presets[name] = buttons;
    saveConfig();
    LOGI("Preset added: %s", name.c_str());
}
