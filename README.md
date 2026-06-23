# Custom Buttons Mod for LeviLaunchroid

On-screen customizable buttons for Minecraft on Android, similar to Amethyst/PojavLauncher.

## Features

- Customizable buttons with adjustable size, position, opacity
- Button appearance customization (colors, borders, corner radius)
- Multiple built-in actions (brightness, volume, menu toggle)
- JSON-based configuration
- Touch input handling
- Persistent configuration storage

## Building

```bash
mkdir build && cd build
cmake ..
make
```

Output: `libCustomButtons.so`

## Configuration

Place `config.json` at `/sdcard/CustomButtons/config.json`

### Button Properties

- `id`: Unique identifier
- `name`: Display text
- `x`, `y`: Position on screen
- `width`, `height`: Button dimensions
- `bgColor`: Background color (hex ARGB)
- `textColor`: Text color (hex ARGB)
- `opacity`: 0.0-1.0
- `enabled`: true/false
- `action`: brightness_up, brightness_down, volume_up, volume_down, toggle_menu
- `cornerRadius`: Border radius in pixels
- `borderColor`: Border color (hex ARGB)
- `borderWidth`: Border thickness

## Actions

- `brightness_up` - Increase screen brightness
- `brightness_down` - Decrease screen brightness
- `volume_up` - Increase volume
- `volume_down` - Decrease volume
- `toggle_menu` - Toggle menu visibility

## Integration

1. Build the mod
2. Place `libCustomButtons.so` in LeviLaunchroid's mod directory
3. Create `/sdcard/CustomButtons/config.json` with button definitions
4. Restart the launcher

## Example Config

See `config_example.json` for a complete example with brightness and volume buttons.
