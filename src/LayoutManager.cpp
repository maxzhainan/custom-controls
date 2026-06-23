#include "LayoutManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

LayoutManager::LayoutManager() 
    : evaluator(std::make_unique<ExpressionEvaluator>()) {
}

bool LayoutManager::loadLayout(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open layout file: " << filePath << std::endl;
        return false;
    }
    
    try {
        json layoutJson;
        file >> layoutJson;
        return loadFromJson(layoutJson);
    } catch (const std::exception& e) {
        std::cerr << "Failed to parse JSON: " << e.what() << std::endl;
        return false;
    }
}

bool LayoutManager::loadFromJson(const json& layoutJson) {
    try {
        controls.clear();
        
        // Load metadata
        if (layoutJson.contains("name")) {
            layoutName = layoutJson["name"];
        }
        
        if (layoutJson.contains("version")) {
            layoutVersion = layoutJson["version"];
        }
        
        // Load controls
        if (layoutJson.contains("controls") && layoutJson["controls"].is_array()) {
            for (const auto& controlJson : layoutJson["controls"]) {
                auto control = createControlFromJson(controlJson);
                if (control) {
                    control->setExpressionEvaluator(evaluator.get());
                    controls.push_back(control);
                }
            }
        }
        
        updateEvaluatorVariables();
        return true;
        
    } catch (const std::exception& e) {
        std::cerr << "Error loading layout from JSON: " << e.what() << std::endl;
        return false;
    }
}

bool LayoutManager::saveLayout(const std::string& filePath) {
    try {
        json layoutJson;
        layoutJson["version"] = layoutVersion;
        layoutJson["name"] = layoutName;
        
        json controlsArray = json::array();
        
        for (const auto& control : controls) {
            const auto& props = control->getProperties();
            json controlJson;
            controlJson["id"] = props.id;
            controlJson["name"] = props.name;
            controlJson["type"] = static_cast<int>(props.type);
            controlJson["x"] = props.x;
            controlJson["y"] = props.y;
            controlJson["width"] = props.width;
            controlJson["height"] = props.height;
            controlJson["color"] = props.color;
            controlJson["enabled"] = props.enabled;
            
            if (!props.dynamicX.empty()) {
                controlJson["dynamicX"] = props.dynamicX;
            }
            if (!props.dynamicY.empty()) {
                controlJson["dynamicY"] = props.dynamicY;
            }
            
            controlsArray.push_back(controlJson);
        }
        
        layoutJson["controls"] = controlsArray;
        
        std::ofstream file(filePath);
        file << layoutJson.dump(2);
        return true;
        
    } catch (const std::exception& e) {
        std::cerr << "Failed to save layout: " << e.what() << std::endl;
        return false;
    }
}

std::shared_ptr<Control> LayoutManager::getControlById(const std::string& id) const {
    for (const auto& control : controls) {
        if (control->getId() == id) {
            return control;
        }
    }
    return nullptr;
}

void LayoutManager::setScreenDimensions(float width, float height) {
    screenWidth = width;
    screenHeight = height;
    updateEvaluatorVariables();
}

void LayoutManager::onTouchDown(float x, float y) {
    for (auto& control : controls) {
        control->onTouchDown(x, y);
    }
}

void LayoutManager::onTouchMove(float x, float y) {
    for (auto& control : controls) {
        control->onTouchMove(x, y);
    }
}

void LayoutManager::onTouchUp(float x, float y) {
    for (auto& control : controls) {
        control->onTouchUp(x, y);
    }
}

std::shared_ptr<Control> LayoutManager::createControlFromJson(const json& controlJson) {
    if (!controlJson.contains("id") || !controlJson.contains("type")) {
        return nullptr;
    }
    
    ControlProperties props = parseControlProperties(controlJson);
    
    switch (props.type) {
        case ControlType::Button:
            return std::make_shared<ButtonControl>(props);
        case ControlType::Joystick:
            return std::make_shared<JoystickControl>(props);
        default:
            return std::make_shared<Control>(props);
    }
}

ControlProperties LayoutManager::parseControlProperties(const json& json) {
    ControlProperties props;
    
    props.id = json["id"];
    props.name = json.value("name", "");
    
    std::string typeStr = json.value("type", "button");
    if (typeStr == "button") props.type = ControlType::Button;
    else if (typeStr == "joystick") props.type = ControlType::Joystick;
    else if (typeStr == "button_drawer") props.type = ControlType::ButtonDrawer;
    else if (typeStr == "safe_area") props.type = ControlType::SafeArea;
    else props.type = ControlType::Button;
    
    props.x = json.value("x", 0.0f);
    props.y = json.value("y", 0.0f);
    props.width = json.value("width", 60.0f);
    props.height = json.value("height", 60.0f);
    
    props.dynamicX = json.value("dynamicX", "");
    props.dynamicY = json.value("dynamicY", "");
    props.dynamicWidth = json.value("dynamicWidth", "");
    props.dynamicHeight = json.value("dynamicHeight", "");
    
    props.color = json.value("color", "#FFFFFF");
    props.opacity = json.value("opacity", 1.0f);
    props.cornerRadius = json.value("cornerRadius", 8);
    
    props.enabled = json.value("enabled", true);
    
    // Parse keyCodes array
    if (json.contains("keyCodes") && json["keyCodes"].is_array()) {
        for (const auto& code : json["keyCodes"]) {
            props.keyCodes.push_back(code);
        }
    }
    
    return props;
}

void LayoutManager::updateEvaluatorVariables() {
    evaluator->setVariable("screenWidth", screenWidth);
    evaluator->setVariable("screenHeight", screenHeight);
    evaluator->setVariable("safeAreaPadding", 10);
}
