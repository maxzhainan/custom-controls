#pragma once

#include "Button.h"
#include <vector>
#include <unordered_map>
#include <memory>

class ButtonManager {
public:
    ButtonManager();
    ~ButtonManager();
    
    void addButton(const Button& button);
    void removeButton(const std::string& id);
    Button* getButton(const std::string& id);
    std::vector<Button>& getButtons();
    
    void handleTouchDown(float x, float y);
    void handleTouchUp(float x, float y);
    void handleTouchMove(float x, float y);
    
    Button* getTouchedButton(float x, float y);
    void clearTouchedButton();
    
    void update();
    void reset();
    
private:
    std::vector<Button> buttons;
    Button* currentTouched;
};
