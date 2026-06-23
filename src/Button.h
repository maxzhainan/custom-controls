#pragma once

#include <string>
#include <cstdint>
#include <functional>

struct Button {
    std::string id;
    std::string name;
    float x, y;
    float width, height;
    uint32_t bgColor;
    uint32_t textColor;
    float opacity;
    bool enabled;
    std::string action;
    float cornerRadius;
    uint32_t borderColor;
    float borderWidth;
    
    Button() 
        : x(0), y(0), width(80), height(60),
          bgColor(0xFF333333), textColor(0xFFFFFFFF),
          opacity(1.0f), enabled(true), cornerRadius(8.0f),
          borderColor(0xFF666666), borderWidth(1.0f) {}
    
    bool pointInBounds(float px, float py) const {
        return px >= x && px <= x + width && 
               py >= y && py <= y + height;
    }
};

enum class ButtonAction {
    BRIGHTNESS_UP,
    BRIGHTNESS_DOWN,
    VOLUME_UP,
    VOLUME_DOWN,
    TOGGLE_MENU,
    CUSTOM,
    NONE
};

ButtonAction parseAction(const std::string& action);
