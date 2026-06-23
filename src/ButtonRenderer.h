#pragma once

#include "Button.h"
#include <vector>

class ButtonRenderer {
public:
    ButtonRenderer();
    ~ButtonRenderer();
    
    void renderButton(const Button& button);
    void renderButtons(const std::vector<Button>& buttons);
    
    void setViewport(int width, int height);
    
private:
    int viewportWidth;
    int viewportHeight;
    
    void drawRoundedRect(float x, float y, float w, float h, 
                         float radius, uint32_t color, float opacity);
    void drawText(float x, float y, const std::string& text, 
                  uint32_t color, float opacity);
    uint32_t applyOpacity(uint32_t color, float opacity);
};
