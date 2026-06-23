#pragma once
#include "ControlsManager.h"
#include <memory>

class UIRenderer {
public:
    static UIRenderer& getInstance();
    
    void drawButton(const ControlButton& button);
    void drawConfigMenu(const std::vector<ControlButton>& buttons);
    void drawText(const std::string& text, int x, int y);
    void drawRect(int x, int y, int width, int height, float r, float g, float b, float a);
    
private:
    UIRenderer();
    ~UIRenderer();
    
    void setupGLContext();
    void teardownGLContext();
};
