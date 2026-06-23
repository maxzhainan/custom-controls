#include "ButtonManager.h"
#include <algorithm>
#include <fmt/format.h>

ButtonManager::ButtonManager() : currentTouched(nullptr) {}

ButtonManager::~ButtonManager() {}

void ButtonManager::addButton(const Button& button) {
    buttons.push_back(button);
}

void ButtonManager::removeButton(const std::string& id) {
    auto it = std::find_if(buttons.begin(), buttons.end(),
        [&id](const Button& b) { return b.id == id; });
    if (it != buttons.end()) {
        buttons.erase(it);
    }
}

Button* ButtonManager::getButton(const std::string& id) {
    for (auto& btn : buttons) {
        if (btn.id == id) return &btn;
    }
    return nullptr;
}

std::vector<Button>& ButtonManager::getButtons() {
    return buttons;
}

void ButtonManager::handleTouchDown(float x, float y) {
    currentTouched = getTouchedButton(x, y);
}

void ButtonManager::handleTouchUp(float x, float y) {
    if (currentTouched && currentTouched->pointInBounds(x, y)) {
        // Button pressed
    }
    currentTouched = nullptr;
}

void ButtonManager::handleTouchMove(float x, float y) {
    if (currentTouched && !currentTouched->pointInBounds(x, y)) {
        currentTouched = nullptr;
    }
}

Button* ButtonManager::getTouchedButton(float x, float y) {
    for (auto& btn : buttons) {
        if (btn.enabled && btn.pointInBounds(x, y)) {
            return &btn;
        }
    }
    return nullptr;
}

void ButtonManager::clearTouchedButton() {
    currentTouched = nullptr;
}

void ButtonManager::update() {
    // Update button states if needed
}

void ButtonManager::reset() {
    buttons.clear();
    currentTouched = nullptr;
}
