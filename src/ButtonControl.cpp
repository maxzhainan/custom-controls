#include "ButtonControl.h"

ButtonControl::ButtonControl(const ControlProperties& props) 
    : Control(props) {
}

void ButtonControl::onTouchDown(float x, float y) {
    Control::onTouchDown(x, y);
    
    if (properties.pressed && onPressCallback) {
        onPressCallback(properties.keyCodes);
    }
}

void ButtonControl::onTouchUp(float x, float y) {
    if (properties.pressed && onReleaseCallback) {
        onReleaseCallback(properties.keyCodes);
    }
    
    Control::onTouchUp(x, y);
}
