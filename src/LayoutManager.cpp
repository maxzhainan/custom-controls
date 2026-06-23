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



void LayoutManager::updateEvaluatorVariables() {
    evaluator->setVariable("screenWidth", screenWidth);
    evaluator->setVariable("screenHeight", screenHeight);
    evaluator->setVariable("safeAreaPadding", 10);
}
