#ifndef JOYSTICK_CONTROL_H
#define JOYSTICK_CONTROL_H

#include "Control.h"
#include <cmath>

class JoystickControl : public Control {
public:
    JoystickControl(const ControlProperties& props);
    
    // Movement callback
    using MovementCallback = std::function<void(float, float)>;
    void setOnMovement(MovementCallback callback) { onMovementCallback = callback; }
    
    // Properties
    float getRadius() const { return radius; }
    float getDeadZone() const { return deadZone; }
    
    // Get current position
    float getAxisX() const { return axisX; }
    float getAxisY() const { return axisY; }
    
    // Override touch events
    void onTouchDown(float x, float y) override;
    void onTouchMove(float x, float y) override;
    void onTouchUp(float x, float y) override;
    
private:
    float radius = 50;
    float deadZone = 0.2f;
    float axisX = 0;
    float axisY = 0;
    
    MovementCallback onMovementCallback = nullptr;
    
    void calculateAxis(float px, float py);
    void applyDeadZone();
};

#endif // JOYSTICK_CONTROL_H
