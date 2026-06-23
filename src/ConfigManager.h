#pragma once
#include <string>
#include <map>
#include <vector>
#include "ControlsManager.h"

struct Config {
    std::string presetName;
    std::map<std::string, std::vector<ControlButton>> presets;
    float buttonOpacity = 0.7f;
    int buttonSize = 80;
    bool editMode = false;
};

class ConfigManager {
public:
    static ConfigManager& getInstance();
    
    void loadConfig();
    void saveConfig();
    void createDefaultConfig();
    void importConfig(const std::string& jsonPath);
    void exportConfig(const std::string& jsonPath);
    
    const Config& getConfig() const;
    void setConfig(const Config& cfg);
    void addPreset(const std::string& name, const std::vector<ControlButton>& buttons);
    
private:
    ConfigManager();
    ~ConfigManager() = default;
    
    Config config;
    std::string configPath;
    
    std::string getConfigPath();
    bool fileExists(const std::string& path);
};
