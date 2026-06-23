#ifndef BUTTON_CONTROL_H
#define BUTTON_CONTROL_H

#include "Control.h"
#include <functional>

class ButtonControl : public Control {
public:
    ButtonControl(const ControlProperties& props);
    
    // Callbacks
    using KeyCodeCallback = std::function<void(const std::vector<int>&)>;
    
    void setOnPress(KeyCodeCallback callback) { onPressCallback = callback; }
    void setOnRelease(KeyCodeCallback callback) { onReleaseCallback = callback; }
    
    // Override touch events
    void onTouchDown(float x, float y) override;
    void onTouchUp(float x, float y) override;
    
    // Get keycodes to send
    const std::vector<int>& getKeyCodes() const { return properties.keyCodes; }
    
private:
    KeyCodeCallback onPressCallback = nullptr;
    KeyCodeCallback onReleaseCallback = nullptr;
};

#endif // BUTTON_CONTROL_H
