#include "InputDispatcher.h"
#include <iostream>

InputDispatcher::InputDispatcher() {
}

void InputDispatcher::onKeyDown(int keyCode) {
    if (keyState[keyCode] == false) {
        keyState[keyCode] = true;
        if (debugMode) {
            std::cout << "Key DOWN: " << keyCode << std::endl;
        }
        if (keyCallback) {
            keyCallback(keyCode, true);
        }
    }
}

void InputDispatcher::onKeyUp(int keyCode) {
    if (keyState[keyCode] == true) {
        keyState[keyCode] = false;
        if (debugMode) {
            std::cout << "Key UP: " << keyCode << std::endl;
        }
        if (keyCallback) {
            keyCallback(keyCode, false);
        }
    }
}

void InputDispatcher::dispatchKeyCodes(const std::vector<int>& codes, bool press) {
    for (int code : codes) {
        if (press) {
            onKeyDown(code);
        } else {
            onKeyUp(code);
        }
    }
}
