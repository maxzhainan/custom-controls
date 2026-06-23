#include "ConfigMenu.h"
#include <android/log.h>

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "CustomControls", __VA_ARGS__)

ConfigMenu::ConfigMenu() : visible(true), selectedIndex(0) {
    LOGI("ConfigMenu created");
}

ConfigMenu::~ConfigMenu() = default;

void ConfigMenu::show() {
    visible = true;
    LOGI("ConfigMenu shown");
}

void ConfigMenu::hide() {
    visible = false;
    LOGI("ConfigMenu hidden");
}

bool ConfigMenu::isVisible() const {
    return visible;
}

void ConfigMenu::handleInput(int x, int y, int action) {
    if (!visible) return;
    
    // Simple menu navigation
    // Calculate which menu item was tapped
    for (size_t i = 0; i < mainMenu.size(); ++i) {
        int itemY = 100 + (i * 80);
        if (y >= itemY && y <= itemY + 70 && x >= 50 && x <= 1230) {
            selectedIndex = i;
            if (action == 0) { // DOWN
                LOGI("Menu item selected: %s", mainMenu[i].label.c_str());
            }
        }
    }
}

void ConfigMenu::render() {
    if (!visible) return;
    drawMenu();
}

void ConfigMenu::setAction(MenuAction action, std::function<void()> callback) {
    // Hook callback for menu actions
    LOGI("Menu action registered: %d", (int)action);
}

void ConfigMenu::drawMenu() {
    // Draw semi-transparent background
    // Draw title: "CUSTOMCONTROLS - SELECT LAYOUT"
    // Draw menu items
    
    int yOffset = 100;
    for (size_t i = 0; i < mainMenu.size(); ++i) {
        bool selected = (selectedIndex == (int)i);
        drawButton(mainMenu[i], selected);
        yOffset += 80;
    }
}

void ConfigMenu::drawButton(const MenuItem& item, bool selected) {
    // Draw menu button with selection highlight
    LOGI("Drawing menu item: %s (selected: %s)", item.label.c_str(), 
         selected ? "yes" : "no");
}
