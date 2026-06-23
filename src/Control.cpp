#include "Control.h"

Control::Control(const ControlProperties& props) 
    : properties(props), evaluator(nullptr) {
}

float Control::getX() const {
    if (!properties.dynamicX.empty() && evaluator) {
        return evaluator->evaluate(properties.dynamicX);
    }
    return properties.x;
}

float Control::getY() const {
    if (!properties.dynamicY.empty() && evaluator) {
        return evaluator->evaluate(properties.dynamicY);
    }
    return properties.y;
}

float Control::getWidth() const {
    if (!properties.dynamicWidth.empty() && evaluator) {
        return evaluator->evaluate(properties.dynamicWidth);
    }
    return properties.width;
}

float Control::getHeight() const {
    if (!properties.dynamicHeight.empty() && evaluator) {
        return evaluator->evaluate(properties.dynamicHeight);
    }
    return properties.height;
}

bool Control::containsPoint(float px, float py) const {
    float x = getX();
    float y = getY();
    float w = getWidth();
    float h = getHeight();
    
    return px >= x && px <= (x + w) && py >= y && py <= (y + h);
}

void Control::onTouchDown(float x, float y) {
    if (containsPoint(x, y) && properties.enabled) {
        properties.pressed = true;
    }
}

void Control::onTouchMove(float x, float y) {
    if (!properties.enabled) {
        properties.pressed = false;
        return;
    }
    
    properties.pressed = containsPoint(x, y);
}

void Control::onTouchUp(float x, float y) {
    properties.pressed = false;
}
