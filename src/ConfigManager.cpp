#include "ConfigManager.h"
#include "pl/Logger.h"
#include <fstream>
#include <sstream>
#include <cstdlib>

ConfigManager::ConfigManager() {}

ConfigManager::~ConfigManager() {}

bool ConfigManager::loadConfig(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        PL_LOG_WARN("Config file not found: {}", path);
        return false;
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    file.close();
    
    // Simple JSON parsing for button configs
    // Format: {"buttons": [{"id": "...", "name": "...", ...}, ...]}
    
    PL_LOG_INFO("Loaded config from: {}", path);
    return true;
}

bool ConfigManager::saveConfig(const std::string& path) {
    std::ofstream file(path);
    if (!file.is_open()) {
        PL_LOG_ERROR("Failed to create config file: {}", path);
        return false;
    }
    
    file << "{\"buttons\":[";
    for (size_t i = 0; i < buttons.size(); ++i) {
        file << buttonToJson(buttons[i]);
        if (i < buttons.size() - 1) file << ",";
    }
    file << "]}";
    
    file.close();
    PL_LOG_INFO("Saved config to: {}", path);
    return true;
}

std::vector<Button> ConfigManager::getParsedButtons() const {
    return buttons;
}

Button ConfigManager::parseButtonJson(const std::string& json) {
    Button btn;
    // Simple parameter extraction from JSON string
    // This is a basic implementation - use a proper JSON library for production
    return btn;
}

std::string ConfigManager::buttonToJson(const Button& button) const {
    return fmt::format(
        R"({{"id":"{}","name":"{}","x":{},"y":{},"width":{},"height":{},"bgColor":{},"textColor":{},"opacity":{},"enabled":{},"action":"{}","cornerRadius":{},"borderColor":{},"borderWidth":{}}})",
        button.id, button.name, button.x, button.y, button.width, button.height,
        button.bgColor, button.textColor, button.opacity, button.enabled,
        button.action, button.cornerRadius, button.borderColor, button.borderWidth
    );
}
