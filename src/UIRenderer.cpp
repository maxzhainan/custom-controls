#include "UIRenderer.h"
#include <android/log.h>

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "CustomControls", __VA_ARGS__)

UIRenderer& UIRenderer::getInstance() {
    static UIRenderer instance;
    return instance;
}

UIRenderer::UIRenderer() {
    setupGLContext();
}

UIRenderer::~UIRenderer() {
    teardownGLContext();
}

void UIRenderer::setupGLContext() {
    // Initialize OpenGL context
    LOGI("OpenGL context initialized");
}

void UIRenderer::teardownGLContext() {
    // Cleanup OpenGL
    LOGI("OpenGL context destroyed");
}

void UIRenderer::drawButton(const ControlButton& button) {
    // Draw rounded rectangle with label
    drawRect(button.x, button.y, button.width, button.height, 
             0.2f, 0.6f, 1.0f, button.opacity);
    drawText(button.label, button.x + 10, button.y + 35);
}

void UIRenderer::drawConfigMenu(const std::vector<ControlButton>& buttons) {
    // Semi-transparent overlay
    drawRect(0, 0, 1280, 720, 0.0f, 0.0f, 0.0f, 0.5f);
    
    // Config menu title
    drawText("CONTROL CONFIG", 100, 50);
    
    // Button list
    int yOffset = 100;
    for (const auto& btn : buttons) {
        drawText(btn.label + ": " + std::to_string(btn.keyCode), 100, yOffset);
        yOffset += 50;
    }
}

void UIRenderer::drawRect(int x, int y, int width, int height, 
                          float r, float g, float b, float a) {
    // OpenGL rendering code placeholder
    LOGI("Drawing rect at (%d, %d) size (%d, %d)", x, y, width, height);
}

void UIRenderer::drawText(const std::string& text, int x, int y) {
    // Text rendering placeholder
    LOGI("Drawing text '%s' at (%d, %d)", text.c_str(), x, y);
}
