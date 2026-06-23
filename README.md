# CustomControls

Customizable on-screen controls mod for Minecraft: Bedrock Edition. Inspired by Amethyst and PojavLauncher.

## Features

- 🎮 Customizable button layouts (drag & drop positioning)
- 📋 Multiple presets (default, compact, pvp)
- 💾 JSON config import/export
- 🔧 Edit mode for button repositioning
- ⚡ Fast key injection with proper KeyCodes
- 🎨 Adjustable opacity and button sizes
- 📱 Touch-optimized interface

## Installation

### Requirements
- LeviLauncher (Android)
- Android NDK r26+
- CMake 3.21+

### Build
```bash
mkdir build && cd build
cmake -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK/build/cmake/android.toolchain.cmake \
      -DANDROID_PLATFORM=android-26 \
      -DANDROID_ABI=arm64-v8a ..
cmake --build . --config Release
```

### Install
1. Copy `libCustomControls.so` to LeviLauncher mods folder
2. Place `config.json` in `/sdcard/Android/data/com.mojang.minecraftpe/files/`
3. Launch Minecraft

## Configuration

### Default Presets
- **default**: Standard WASD-style layout
- **compact**: Minimal button layout
- **pvp**: Large attack/place buttons for PvP

### Custom Presets
Edit `config.json` and add new preset:

```json
{
  "presetName": "custom",
  "presets": {
    "custom": [
      {
        "id": "jump",
        "label": "JUMP",
        "x": 50,
        "y": 500,
        "width": 80,
        "height": 80,
        "keyCode": 32
      }
    ]
  }
}
```

### KeyCodes Reference
- `32`: SPACE (Jump)
- `29`: ALT (Sneak)
- `1`: LMB (Attack)
- `3`: RMB (Place)
- `16`: Q (Drop)
- `18`: E (Inventory)
- `19-24`: Arrow Keys
- `45`: M (Map)
- `46`: L (Crafting)

## Edit Mode

Press config button (default: INV) to enter edit mode:
- Drag buttons to reposition
- Long press to remove
- Confirm to save

## KeyCode Injection

The mod hooks directly into input system:
```cpp
void ControlsManager::injectKeyCode(int keyCode) {
    // Sends KeyCode to game input thread
}
```

## Config Menu (Fallback)

If `config.json` not found, default menu appears:
- Select preset
- Import config
- Export config
- Reset to defaults

## API Hooks

```cpp
void ControlsManager_Init();
void ControlsManager_Render();
void ControlsManager_OnTouch(int x, int y, int action);
```

## License

MIT License - see LICENSE file

## Credits

- Inspired by [Amethyst](https://github.com/angelauramc)
- Design pattern from [PojavLauncher](https://github.com/PojavLauncherTeam)
- Built for OpenMCBE community
