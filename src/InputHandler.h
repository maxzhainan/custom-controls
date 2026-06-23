// InputHandler.h - Direct KeyCode injection
#pragma once

namespace InputHandler {
    // Android KeyEvent constants
    enum class KeyAction {
        DOWN = 0,
        UP = 1,
        MULTIPLE = 2
    };
    
    // Standard Android KeyCodes
    enum class KeyCode {
        SPACE = 32,
        ALT_LEFT = 29,
        ALT_RIGHT = 60,
        SHIFT_LEFT = 59,
        SHIFT_RIGHT = 60,
        CTRL_LEFT = 113,
        CTRL_RIGHT = 114,
        
        // Game controls
        KEY_W = 26,
        KEY_A = 4,
        KEY_S = 22,
        KEY_D = 8,
        KEY_Q = 16,
        KEY_E = 18,
        
        // Mouse
        BUTTON_PRIMARY = 1,
        BUTTON_SECONDARY = 3,
        BUTTON_TERTIARY = 2,
    };
    
    void injectKey(int keyCode, KeyAction action);
    void injectMouseButton(int button, KeyAction action);
    void setModifierKey(int modifierCode, bool active);
}
