# Core Architecture - Control Layout System

A JSON-based, expression-evaluated control layout system for game input handling with dynamic positioning.

## Features

- **JSON-based Control Layouts** - Define controls in declarative JSON format
- **Dynamic Positioning** - Use mathematical expressions (exp4j-like) for responsive layouts
- **Expression Evaluation Engine** - Runtime evaluation of position/size expressions
- **Touch Event Handling** - Full multi-touch support with collision detection
- **Button Controls** - Simple press/release buttons with keycode dispatch
- **Joystick Controls** - Analog stick input with deadzone and axis mapping
- **Button Drawers** - Container controls for grouping related buttons
- **Safe Area Boundaries** - Screen boundary constraints for UI layout
- **Input Dispatcher** - Centralized keyboard/mouse input dispatching

## Architecture

```
LayoutManager (coordinator)
├── ExpressionEvaluator (expression parsing & evaluation)
├── Control (base class)
│   ├── ButtonControl
│   ├── JoystickControl
│   └── SafeArea
└── InputDispatcher (key event handling)
```

## File Structure

```
core-architecture/
├── include/
│   ├── Control.h
│   ├── ButtonControl.h
│   ├── JoystickControl.h
│   ├── LayoutManager.h
│   ├── ExpressionEvaluator.h
│   └── InputDispatcher.h
├── src/
│   ├── Control.cpp
│   ├── ButtonControl.cpp
│   ├── JoystickControl.cpp
│   ├── LayoutManager.cpp
│   ├── ExpressionEvaluator.cpp
│   └── InputDispatcher.cpp
├── assets/layouts/
│   └── default.json (sample layout)
├── examples/
│   └── example.cpp
├── lib/
│   └── nlohmann/
│       └── json.hpp (JSON library stub)
├── CMakeLists.txt
└── README.md
```

## JSON Layout Format

### Basic Structure
```json
{
  "version": "1.0",
  "name": "Default Control Layout",
  "controls": [
    { /* control definitions */ }
  ]
}
```

### Control Properties

#### Static Position
```json
{
  "id": "button_jump",
  "type": "button",
  "name": "Jump",
  "x": 100,
  "y": 300,
  "width": 60,
  "height": 60,
  "keyCodes": [32],
  "color": "#FF5722"
}
```

#### Dynamic Position
```json
{
  "id": "button_menu",
  "type": "button",
  "name": "Menu",
  "dynamicX": "screenWidth - 70",
  "dynamicY": "screenHeight - 70",
  "width": 60,
  "height": 60,
  "keyCodes": [27]
}
```

### Control Types

#### Button
Simple press/release with keycode dispatch.
```json
{
  "id": "button_jump",
  "type": "button",
  "keyCodes": [32]
}
```

#### Joystick
Analog stick with axis movement.
```json
{
  "id": "joystick_left",
  "type": "joystick",
  "x": 50,
  "y": 400,
  "width": 100,
  "height": 100,
  "radius": 50,
  "deadZone": 0.2
}
```

#### Button Drawer
Container for grouped buttons.
```json
{
  "id": "action_drawer",
  "type": "button_drawer",
  "children": [
    { "id": "attack", "keyCodes": [17] },
    { "id": "interact", "keyCodes": [69] }
  ]
}
```

#### Safe Area
Defines viewport boundaries.
```json
{
  "id": "safe_area",
  "type": "safe_area",
  "dynamicWidth": "screenWidth - safeAreaPadding * 2",
  "dynamicHeight": "screenHeight - safeAreaPadding * 2"
}
```

## Expression Evaluation

Variables available in expressions:
- `screenWidth` - Display width in pixels
- `screenHeight` - Display height in pixels
- `safeAreaPadding` - Safe area margin (default: 10px)

### Supported Operations
- Arithmetic: `+`, `-`, `*`, `/`, `%`
- Functions: `sin()`, `cos()`, `tan()`, `sqrt()`, `abs()`, `floor()`, `ceil()`
- Parentheses: `(expression)`

### Example Expressions
```
screenWidth - 70                    // Right-aligned at 70px from edge
screenHeight / 2                    // Vertically centered
screenWidth * 0.5 - width / 2       // Horizontally centered
(screenWidth - 200) / 2             // Complex calculation
```

## Usage Example

```cpp
#include "LayoutManager.h"
#include "InputDispatcher.h"

int main() {
    LayoutManager layoutMgr;
    InputDispatcher inputMgr;
    
    // Set screen size
    layoutMgr.setScreenDimensions(1920, 1080);
    
    // Load layout
    layoutMgr.loadLayout("assets/layouts/default.json");
    
    // Setup input callbacks
    inputMgr.setKeyCallback([](int keyCode, bool pressed) {
        std::cout << "Key: " << keyCode << " - " 
                  << (pressed ? "down" : "up") << std::endl;
    });
    
    // Simulate touch
    layoutMgr.onTouchDown(100, 300);  // Touch down
    layoutMgr.onTouchMove(105, 305);  // Touch move
    layoutMgr.onTouchUp(100, 300);    // Touch up
    
    return 0;
}
```

## Building

### Requirements
- C++17 or later
- CMake 3.10+
- nlohmann/json library

### Compile
```bash
mkdir build
cd build
cmake ..
make
./core_example
```

### With nlohmann/json
```bash
# Ubuntu/Debian
apt-get install nlohmann-json3-dev

# Or download from GitHub
# https://github.com/nlohmann/json/releases
```

## Input Mapping

### Touch Coordinates
Touch input is in screen-space (0,0 at top-left).

### Button Press to KeyCode
Buttons dispatch keyboard keycodes when touched.

### Joystick to Movement
Joystick position converted to normalized axis values (-1.0 to 1.0).

### Multi-touch Support
All controls can be touched simultaneously.

## Configuration Options

### Layout Metadata
```json
{
  "metadata": {
    "scale": 1.0,
    "safeAreaPadding": 10
  }
}
```

### Control Rendering
```json
{
  "renderConfig": {
    "enableTouchFeedback": true,
    "buttonPressOpacity": 0.7,
    "defaultBorderWidth": 2,
    "defaultCornerRadius": 8,
    "textSize": 14
  }
}
```

## License

Open source - Use freely in your projects.

## Contributing

Add new control types or features as needed:

1. Create new Control subclass (e.g., `SliderControl`)
2. Add parsing in `LayoutManager::createControlFromJson()`
3. Define JSON schema in documentation
4. Update example layouts

---

**Version**: 1.0  
**Last Updated**: June 2024
