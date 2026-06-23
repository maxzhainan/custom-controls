// ConfigMenu.h - Fallback menu when config.json missing
#pragma once
#include <vector>
#include <string>
#include <functional>

enum class MenuAction {
    SELECT_PRESET,
    IMPORT_CONFIG,
    EXPORT_CONFIG,
    RESET_DEFAULTS,
    CONFIRM,
    CANCEL
};

struct MenuItem {
    std::string label;
    MenuAction action;
    int index;
};

class ConfigMenu {
public:
    ConfigMenu();
    ~ConfigMenu();
    
    void show();
    void hide();
    bool isVisible() const;
    
    void handleInput(int x, int y, int action);
    void render();
    
    void setAction(MenuAction action, std::function<void()> callback);
    
private:
    bool visible = true;
    int selectedIndex = 0;
    
    std::vector<MenuItem> mainMenu = {
        {"Default Layout", MenuAction::SELECT_PRESET, 0},
        {"Compact Layout", MenuAction::SELECT_PRESET, 1},
        {"PvP Layout", MenuAction::SELECT_PRESET, 2},
        {"Import Config", MenuAction::IMPORT_CONFIG, 3},
        {"Export Config", MenuAction::EXPORT_CONFIG, 4},
        {"Reset Defaults", MenuAction::RESET_DEFAULTS, 5},
    };
    
    void drawMenu();
    void drawButton(const MenuItem& item, bool selected);
};
