#include "Button.h"

ButtonAction parseAction(const std::string& action) {
    if (action == "brightness_up") return ButtonAction::BRIGHTNESS_UP;
    if (action == "brightness_down") return ButtonAction::BRIGHTNESS_DOWN;
    if (action == "volume_up") return ButtonAction::VOLUME_UP;
    if (action == "volume_down") return ButtonAction::VOLUME_DOWN;
    if (action == "toggle_menu") return ButtonAction::TOGGLE_MENU;
    if (action == "custom") return ButtonAction::CUSTOM;
    return ButtonAction::NONE;
}
