#pragma once

#include "Button.h"
#include <vector>
#include <string>

class ConfigManager {
public:
    ConfigManager();
    ~ConfigManager();
    
    bool loadConfig(const std::string& path);
    bool saveConfig(const std::string& path);
    
    std::vector<Button> getParsedButtons() const;
    
private:
    std::vector<Button> buttons;
    
    Button parseButtonJson(const std::string& json);
    std::string buttonToJson(const Button& button) const;
};
