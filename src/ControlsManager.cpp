#include "ControlsManager.h"
#include "ConfigManager.h"
#include <android/log.h>

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "CustomControls", __VA_ARGS__)

ControlsManager::ControlsManager() {
    loadDefaultLayout();
}

ControlsManager::~ControlsManager() = default;

void ControlsManager::initialize() {
    const auto& config = ConfigManager::getInstance().getConfig();
    if (!config.presetName.empty()) {
        loadPreset(config.presetName);
    } else {
        loadDefaultLayout();
    }
}

void ControlsManager::loadDefaultLayout() {
    buttons.clear();
    defaultButtons = {
        {"jump", "JUMP", 50, 500, 80, 80, 32},        // SPACE
        {"crouch", "SNEAK", 150, 500, 80, 80, 29},    // ALT
        {"attack", "ATTACK", 1000, 500, 80, 80, 1},   // PRIMARY
        {"place", "PLACE", 1100, 500, 80, 80, 3},     // SECONDARY
        {"drop", "DROP", 900, 500, 80, 80, 16},       // Q
        {"inventory", "INV", 50, 50, 80, 80, 18},     // E
    };
    buttons = defaultButtons;
    LOGI("Loaded default control layout");
}

void ControlsManager::addButton(const ControlButton& button) {
    buttons.push_back(button);
}

void ControlsManager::removeButton(const std::string& id) {
    buttons.erase(
        std::remove_if(buttons.begin(), buttons.end(),
                      [&id](const ControlButton& b) { return b.id == id; }),
        buttons.end()
    );
}

void ControlsManager::render() {
    if (configMenuVisible) {
        renderConfigMenu();
    } else {
        for (auto& button : buttons) {
            renderButton(button);
        }
    }
}

void ControlsManager::renderButton(const ControlButton& button) {
    // Placeholder for actual OpenGL rendering
    // In real implementation, draw rounded rect with label
    LOGI("Rendering button: %s at (%d, %d)", button.label.c_str(), button.x, button.y);
}

void ControlsManager::renderConfigMenu() {
    // Config menu UI rendering
    LOGI("Rendering config menu");
}

void ControlsManager::onTouchEvent(int x, int y, int action) {
    if (configMenuVisible) {
        // Handle config menu interactions
        return;
    }
    
    ControlButton* button = getButtonAtPosition(x, y);
    if (!button) return;
    
    switch (action) {
        case 0: // DOWN
            button->isDragging = true;
            injectKeyCode(button->keyCode);
            break;
        case 1: // UP
            button->isDragging = false;
            break;
        case 2: // MOVE
            if (button->isDragging) {
                button->x = x - button->width / 2;
                button->y = y - button->height / 2;
            }
            break;
    }
}

ControlButton* ControlsManager::getButtonAtPosition(int x, int y) {
    for (auto& button : buttons) {
        if (x >= button.x && x <= button.x + button.width &&
            y >= button.y && y <= button.y + button.height) {
            return &button;
        }
    }
    return nullptr;
}

void ControlsManager::injectKeyCode(int keyCode) {
    // Hook to inject key event into game
    LOGI("Injecting key code: %d", keyCode);
}

void ControlsManager::loadPreset(const std::string& presetName) {
    const auto& config = ConfigManager::getInstance().getConfig();
    auto it = config.presets.find(presetName);
    if (it != config.presets.end()) {
        buttons = it->second;
        LOGI("Loaded preset: %s", presetName.c_str());
    } else {
        LOGI("Preset not found: %s, using default", presetName.c_str());
        loadDefaultLayout();
    }
}

void ControlsManager::showConfigMenu() {
    configMenuVisible = true;
    LOGI("Config menu shown");
}

void ControlsManager::hideConfigMenu() {
    configMenuVisible = false;
    ConfigManager::getInstance().saveConfig();
    LOGI("Config menu hidden, config saved");
}
