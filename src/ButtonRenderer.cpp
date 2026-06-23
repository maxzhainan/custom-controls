#include "ButtonRenderer.h"
#include "pl/Logger.h"

ButtonRenderer::ButtonRenderer() 
    : viewportWidth(1080), viewportHeight(1920) {}

ButtonRenderer::~ButtonRenderer() {}

void ButtonRenderer::renderButton(const Button& button) {
    if (!button.enabled) return;
    
    // Draw background with rounded corners
    uint32_t bgColorAlpha = applyOpacity(button.bgColor, button.opacity);
    drawRoundedRect(button.x, button.y, button.width, button.height, 
                    button.cornerRadius, bgColorAlpha, button.opacity);
    
    // Draw border if needed
    if (button.borderWidth > 0) {
        uint32_t borderColorAlpha = applyOpacity(button.borderColor, button.opacity);
        drawRoundedRect(button.x, button.y, button.width, button.height,
                        button.cornerRadius, borderColorAlpha, button.opacity);
    }
    
    // Draw text
    uint32_t textColorAlpha = applyOpacity(button.textColor, button.opacity);
    float textX = button.x + button.width / 2.0f;
    float textY = button.y + button.height / 2.0f;
    drawText(textX, textY, button.name, textColorAlpha, button.opacity);
}

void ButtonRenderer::renderButtons(const std::vector<Button>& buttons) {
    for (const auto& button : buttons) {
        renderButton(button);
    }
}

void ButtonRenderer::setViewport(int width, int height) {
    viewportWidth = width;
    viewportHeight = height;
}

void ButtonRenderer::drawRoundedRect(float x, float y, float w, float h,
                                      float radius, uint32_t color, float opacity) {
    // This would be implemented with actual rendering calls
    // Placeholder for OpenGL/Vulkan rendering
    // In real implementation, use device-specific rendering APIs
}

void ButtonRenderer::drawText(float x, float y, const std::string& text,
                               uint32_t color, float opacity) {
    // This would be implemented with actual text rendering
    // Placeholder for text rendering
    // In real implementation, use device-specific text rendering APIs
}

uint32_t ButtonRenderer::applyOpacity(uint32_t color, float opacity) {
    uint8_t a = static_cast<uint8_t>((color >> 24 & 0xFF) * opacity);
    return (color & 0x00FFFFFF) | (a << 24);
}
