#ifndef CONTROL_H
#define CONTROL_H

#include <string>
#include <vector>
#include "ExpressionEvaluator.h"

enum class ControlType {
    Button,
    Joystick,
    ButtonDrawer,
    SafeArea
};

struct ControlProperties {
    std::string id;
    std::string name;
    ControlType type;
    
    // Position (static or dynamic)
    float x = 0;
    float y = 0;
    std::string dynamicX = "";
    std::string dynamicY = "";
    
    // Size
    float width = 0;
    float height = 0;
    std::string dynamicWidth = "";
    std::string dynamicHeight = "";
    
    // Appearance
    std::string color = "#FFFFFF";
    float opacity = 1.0f;
    int cornerRadius = 8;
    
    // Input
    std::vector<int> keyCodes;
    
    // State
    bool enabled = true;
    bool pressed = false;
};

class Control {
public:
    Control(const ControlProperties& props);
    virtual ~Control() = default;
    
    // Getters
    const ControlProperties& getProperties() const { return properties; }
    std::string getId() const { return properties.id; }
    ControlType getType() const { return properties.type; }
    bool isEnabled() const { return properties.enabled; }
    bool isPressed() const { return properties.pressed; }
    
    // Position calculation
    float getX() const;
    float getY() const;
    float getWidth() const;
    float getHeight() const;
    
    // Bounds checking
    bool containsPoint(float px, float py) const;
    
    // Event handling
    virtual void onTouchDown(float x, float y);
    virtual void onTouchMove(float x, float y);
    virtual void onTouchUp(float x, float y);
    
    // Expression evaluation
    void setExpressionEvaluator(ExpressionEvaluator* eval) { evaluator = eval; }
    
    // Enable/Disable
    void setEnabled(bool enabled) { properties.enabled = enabled; }
    
protected:
    ControlProperties properties;
    ExpressionEvaluator* evaluator = nullptr;
};

#endif // CONTROL_H
