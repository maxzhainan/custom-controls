#ifndef LAYOUT_MANAGER_H
#define LAYOUT_MANAGER_H

#include <string>
#include <vector>
#include <memory>
#include <nlohmann/json.hpp>
#include "Control.h"
#include "ButtonControl.h"
#include "JoystickControl.h"
#include "ExpressionEvaluator.h"

using json = nlohmann::json;

class LayoutManager {
public:
    LayoutManager();
    
    // Load layout from JSON file
    bool loadLayout(const std::string& filePath);
    
    // Load layout from JSON object
    bool loadFromJson(const json& layoutJson);
    
    // Save layout to file
    bool saveLayout(const std::string& filePath);
    
    // Get controls
    const std::vector<std::shared_ptr<Control>>& getControls() const { 
        return controls; 
    }
    
    std::shared_ptr<Control> getControlById(const std::string& id) const;
    
    // Screen dimensions
    void setScreenDimensions(float width, float height);
    float getScreenWidth() const { return screenWidth; }
    float getScreenHeight() const { return screenHeight; }
    
    // Touch input
    void onTouchDown(float x, float y);
    void onTouchMove(float x, float y);
    void onTouchUp(float x, float y);
    
    // Layout info
    std::string getLayoutName() const { return layoutName; }
    std::string getLayoutVersion() const { return layoutVersion; }
    
private:
    std::vector<std::shared_ptr<Control>> controls;
    std::unique_ptr<ExpressionEvaluator> evaluator;
    
    float screenWidth = 1920;
    float screenHeight = 1080;
    std::string layoutName = "Unknown";
    std::string layoutVersion = "1.0";
    
    // Helpers
    std::shared_ptr<Control> createControlFromJson(const json& controlJson);
    ControlProperties parseControlProperties(const json& json);
    void updateEvaluatorVariables();
};

#endif // LAYOUT_MANAGER_H
