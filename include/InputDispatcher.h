#ifndef INPUT_DISPATCHER_H
#define INPUT_DISPATCHER_H

#include <vector>
#include <functional>
#include <unordered_map>

class InputDispatcher {
public:
    InputDispatcher();
    
    // Callback types
    using KeyCodeCallback = std::function<void(int)>;
    using KeyStateCallback = std::function<void(int, bool)>;
    
    // Register callbacks
    void onKeyDown(int keyCode);
    void onKeyUp(int keyCode);
    void dispatchKeyCodes(const std::vector<int>& codes, bool press);
    
    // Listen for key events
    void setKeyCallback(KeyStateCallback callback) { keyCallback = callback; }
    void setDebugMode(bool debug) { debugMode = debug; }
    
private:
    KeyStateCallback keyCallback = nullptr;
    std::unordered_map<int, bool> keyState;
    bool debugMode = false;
};

#endif // INPUT_DISPATCHER_H
