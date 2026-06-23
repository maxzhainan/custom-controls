#include "JoystickControl.h"

JoystickControl::JoystickControl(const ControlProperties& props) 
    : Control(props), radius(50), deadZone(0.2f), axisX(0), axisY(0) {
}

void JoystickControl::onTouchDown(float x, float y) {
    if (containsPoint(x, y) && properties.enabled) {
        properties.pressed = true;
        calculateAxis(x, y);
    }
}

void JoystickControl::onTouchMove(float x, float y) {
    if (!properties.enabled) {
        properties.pressed = false;
        axisX = 0;
        axisY = 0;
        return;
    }
    
    if (containsPoint(x, y) || properties.pressed) {
        properties.pressed = true;
        calculateAxis(x, y);
    } else {
        properties.pressed = false;
        axisX = 0;
        axisY = 0;
    }
}

void JoystickControl::onTouchUp(float x, float y) {
    properties.pressed = false;
    axisX = 0;
    axisY = 0;
    
    if (onMovementCallback) {
        onMovementCallback(0, 0);
    }
}

void JoystickControl::calculateAxis(float px, float py) {
    float cx = getX() + getWidth() / 2;
    float cy = getY() + getHeight() / 2;
    
    float dx = px - cx;
    float dy = py - cy;
    
    float distance = std::sqrt(dx * dx + dy * dy);
    
    if (distance > 0) {
        axisX = dx / radius;
        axisY = dy / radius;
        
        // Clamp to [-1, 1]
        float magnitude = std::sqrt(axisX * axisX + axisY * axisY);
        if (magnitude > 1.0f) {
            axisX /= magnitude;
            axisY /= magnitude;
        }
    } else {
        axisX = 0;
        axisY = 0;
    }
    
    applyDeadZone();
    
    if (onMovementCallback) {
        onMovementCallback(axisX, axisY);
    }
}

void JoystickControl::applyDeadZone() {
    float magnitude = std::sqrt(axisX * axisX + axisY * axisY);
    
    if (magnitude < deadZone) {
        axisX = 0;
        axisY = 0;
    } else if (magnitude > 1.0f) {
        axisX = 0;
        axisY = 0;
    }
}
