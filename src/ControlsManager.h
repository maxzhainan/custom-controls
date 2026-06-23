#pragma once
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

struct ControlButton {
    std::string id;
    std::string label;
    int x, y, width, height;
    int keyCode;
    bool isDragging = false;
    float opacity = 1.0f;
};

class ControlsManager {
public:
    ControlsManager();
    ~ControlsManager();
    
    void initialize();
    void render();
    void onTouchEvent(int x, int y, int action);
    void addButton(const ControlButton& button);
    void removeButton(const std::string& id);
    void loadPreset(const std::string& presetName);
    void showConfigMenu();
    void hideConfigMenu();
    
private:
    std::vector<ControlButton> buttons;
    std::vector<ControlButton> defaultButtons;
    bool configMenuVisible = false;
    int selectedButtonIndex = -1;
    
    void injectKeyCode(int keyCode);
    void renderButton(const ControlButton& button);
    void renderConfigMenu();
    ControlButton* getButtonAtPosition(int x, int y);
    void loadDefaultLayout();
};
