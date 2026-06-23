#include <iostream>
#include "LayoutManager.h"
#include "InputDispatcher.h"

int main() {
    // Initialize managers
    LayoutManager layoutManager;
    InputDispatcher inputDispatcher;
    
    // Set screen dimensions
    layoutManager.setScreenDimensions(1920, 1080);
    
    // Load default layout
    if (!layoutManager.loadLayout("assets/layouts/default.json")) {
        std::cerr << "Failed to load layout" << std::endl;
        return 1;
    }
    
    std::cout << "Loaded layout: " << layoutManager.getLayoutName() << std::endl;
    std::cout << "Screen: " << layoutManager.getScreenWidth() 
              << "x" << layoutManager.getScreenHeight() << std::endl;
    
    // Get and inspect controls
    const auto& controls = layoutManager.getControls();
    std::cout << "Total controls: " << controls.size() << std::endl;
    
    for (const auto& control : controls) {
        std::cout << "\nControl: " << control->getId() << std::endl;
        std::cout << "  Position: (" << control->getX() << ", " << control->getY() << ")" << std::endl;
        std::cout << "  Size: " << control->getWidth() << "x" << control->getHeight() << std::endl;
        std::cout << "  Enabled: " << (control->isEnabled() ? "yes" : "no") << std::endl;
    }
    
    // Simulate touch input
    std::cout << "\n--- Simulating touch input ---" << std::endl;
    
    // Find jump button and simulate touch
    auto jumpButton = layoutManager.getControlById("button_jump");
    if (jumpButton) {
        std::cout << "Touch down on jump button" << std::endl;
        layoutManager.onTouchDown(100, 300);
        
        // Connect input dispatcher
        inputDispatcher.setDebugMode(true);
        inputDispatcher.setKeyCallback([](int keyCode, bool pressed) {
            std::cout << "Key " << keyCode << " - " << (pressed ? "pressed" : "released") << std::endl;
        });
        
        std::cout << "Touch up" << std::endl;
        layoutManager.onTouchUp(100, 300);
    }
    
    return 0;
}
