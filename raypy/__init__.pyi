"""CPython native bindings for Raylib"""

RAYLIB_VERSION: str
RAYLIB_VERSION_MAJOR: int
RAYLIB_VERSION_MINOR: int
RAYLIB_VERSION_PATCH: int
PI: float
DEG2RAD: float
RAD2DEG: float

class Vector2:
    """Vector2, 2 components"""

    x: float
    """Vector x component"""

    y: float
    """Vector y component"""

    def __init__(self, x: float = ..., y: float = ...) -> None: ...

class Vector3:
    """Vector3, 3 components"""

    x: float
    """Vector x component"""

    y: float
    """Vector y component"""

    z: float
    """Vector z component"""

    def __init__(self, x: float = ..., y: float = ..., z: float = ...) -> None: ...

class Vector4:
    """Vector4, 4 components"""

    x: float
    """Vector x component"""

    y: float
    """Vector y component"""

    z: float
    """Vector z component"""

    w: float
    """Vector w component"""

    def __init__(self, x: float = ..., y: float = ..., z: float = ..., w: float = ...) -> None: ...

Quaternion = Vector4

class Matrix:
    """Matrix, 4x4 components, column major, OpenGL style, right-handed"""

    m0: float
    m4: float
    m8: float
    m12: float
    m1: float
    m5: float
    m9: float
    m13: float
    m2: float
    m6: float
    m10: float
    m14: float
    m3: float
    m7: float
    m11: float
    m15: float

    def __init__(self,
        m0: float = ..., m4: float = ..., m8: float = ..., m12: float = ...,
        m1: float = ..., m5: float = ..., m9: float = ..., m13: float = ...,
        m2: float = ..., m6: float = ..., m10: float = ..., m14: float = ...,
        m3: float = ..., m7: float = ..., m11: float = ..., m15: float = ...) -> None: ...

class Color:
    """Color, 4 components, R8G8B8A8 (32bit)"""

    r: int
    """Color red value"""

    g: int
    """Color green value"""

    b: int
    """Color blue value"""

    a: int
    """Color alpha value"""

    def __init__(self, r: int, g: int, b: int, a: int | None = ...) -> None: ...


class Rectangle:
    """Rectangle, 4 components"""

    x: float      
    """Rectangle top-left corner position x"""

    y: float      
    """Rectangle top-left corner position y"""

    width: float  
    """Rectangle width"""

    height: float 
    """Rectangle height"""

    def __init__(self, x: float = ..., y: float = ..., width: float = ..., height: float = ...) -> None: ...


class Image:
    """Image, pixel data stored in CPU memory (RAM)"""

    data: int
    """Image raw data"""

    width: int
    """Image base width"""

    height: int
    """Image base height"""

    mipmaps: int
    """Mipmap levels, 1 by default"""

    format: int
    """Data format (PixelFormat type)"""


class Texture:
    """Texture, tex data stored in GPU memory (VRAM)"""

    id: int
    """OpenGL texture id"""
    
    width: int
    """Texture base width"""
    
    height: int
    """Texture base height"""
    
    mipmaps: int
    """Mipmap levels, 1 by default"""
    
    format: int
    """Data format (PixelFormat type)"""


"""Texture2D, same as Texture"""
Texture2D = Texture

"""TextureCubemap, same as Texture"""
TextureCubemap = Texture


class RenderTexture:
    """RenderTexture, fbo for texture rendering"""

    id: int
    """"OpenGL framebuffer object id"""

    texture: Texture
    """Color buffer attachment texture"""

    depth: Texture
    """Depth buffer attachment texture"""


"""RenderTexture2D, same as RenderTexture"""
RenderTexture2D = RenderTexture


class NPatchInfo:
    """NPatchInfo, n-patch layout info"""

    source: Rectangle
    """Texture source rectangle"""

    left: int
    """Left border offset"""

    top: int
    """Top border offset"""

    right: int
    """Right border offset"""

    bottom: int
    """Bottom border offset"""

    layout: int
    """Layout of the n-patch: 3x3, 1x3 or 3x1"""


class GlyphInfo:
    """GlyphInfo, font characters glyphs info"""

    value: int
    """Character value (Unicode)"""

    offsetX: int
    """Character offset X when drawing"""

    offsetY: int
    """Character offset Y when drawing"""

    advanceX: int
    """Character advance position X"""

    image: Image
    """Character image data"""


def swap_screen_buffer() -> None: ...
def poll_input_events() -> None: ...
def wait_time(ms: float, /) -> None: ...
def show_cursor() -> None: ...
def hide_cursor() -> None: ...
def is_cursor_hidden() -> bool: ...
def enable_cursor() -> None: ...
def disable_cursor() -> None: ...
def is_cursor_on_screen() -> bool: ...
def clear_background(color: Color, /) -> None: ...
def begin_drawing() -> None: ...
def end_drawing() -> None: ...
def set_target_fps(fps: int, /) -> None: ...
def get_fps() -> int: ...
def get_frame_time() -> float: ...
def get_time() -> float: ...
def get_random_value(min: int, max: int, /) -> int: ...
def set_random_seed(seed: int, /) -> None: ...
def take_screenshot(file_name: str, /) -> None: ...
def set_config_flags(flags: int, /) -> None: ...
def trace_log(log_level: int, text: str, /) -> None: ...
def set_trace_log_level(log_level: int, /) -> None: ...
def open_url(url: str, /) -> None: ...
def is_key_pressed(key: int, /) -> bool: ...
def is_key_down(key: int, /) -> bool: ...
def is_key_released(key: int, /) -> bool: ...
def is_key_up(key: int, /) -> bool: ...
def set_exit_key(key: int, /) -> None: ...
def get_key_pressed() -> int: ...
def get_char_pressed() -> int: ...
def draw_fps(pos_x: int, pos_y: int, /) -> None: ...
def draw_text(text: str, pos_x: int, pos_y: int, font_size: int, color: Color) -> None: ...


def init_window(width: int, height: int, title: str, /) -> None:
    """Initialize window and OpenGL context"""
    ...


def close_window() -> None:
    """Close window and unload OpenGL context"""
    ...								


def window_should_close() -> bool:
    """Check if application should close (KEY_ESCAPE pressed or windows close icon clicked)"""
    ...						


def is_window_ready() -> bool:
    """Check if window has been initialized successfully"""
    ...							


def is_window_fullscreen() -> bool:
    """Check if window is currently fullscreen"""
    ...						


def is_window_hidden() -> bool:
    """Check if window is currently hidden (only PLATFORM_DESKTOP)"""
    ...							


def is_window_minimized() -> bool:
    """Check if window is currently minimized (only PLATFORM_DESKTOP)"""
    ...						


def is_window_maximized() -> bool:
    """Check if window is currently maximized (only PLATFORM_DESKTOP)"""
    ...						


def is_window_focused() -> bool:
    """Check if window is currently focused (only PLATFORM_DESKTOP)"""
    ...							


def is_window_resized() -> bool:
    """Check if window has been resized last frame"""
    ...							


def is_window_state(flag: int, /) -> bool:
    """Check if one specific window flag is enabled"""
    ...				


def set_window_state(flags: int, /) -> None:
    """Set window configuration state using flags (only PLATFORM_DESKTOP)"""
    ...				


def clear_window_state(flags: int, /) -> None:
    """Clear window configuration state flags"""
    ...			


def toggle_fullscreen() -> None:
    """Toggle window state: fullscreen/windowed (only PLATFORM_DESKTOP)"""
    ...							


def toggle_borderless_windowed() -> None:
    """Toggle window state: borderless windowed (only PLATFORM_DESKTOP)"""
    ...					


def maximize_window() -> None:
    """Set window state: maximized, if resizable (only PLATFORM_DESKTOP)"""
    ...							


def minimize_window() -> None:
    """Set window state: minimized, if resizable (only PLATFORM_DESKTOP)"""
    ...							


def restore_window() -> None:
    """Set window state: not minimized/maximized (only PLATFORM_DESKTOP)"""
    ...							


def set_window_icon(image: Image, /) -> None:
    """Set icon for window (single image, RGBA 32bit, only PLATFORM_DESKTOP)"""
    ...						


def set_window_icons(images: list[Image], count: int, /) -> None:
    """Set icon for window (multiple images, RGBA 32bit, only PLATFORM_DESKTOP)"""
    ...		


def set_window_title(title: str, /) -> None:
    """Set title for window (only PLATFORM_DESKTOP and PLATFORM_WEB)"""
    ...				


def set_window_position(x: int, y: int, /) -> None:
    """Set window position on screen (only PLATFORM_DESKTOP)"""
    ...				


def set_window_monitor(monitor: int, /) -> None:
    """Set monitor for the current window"""
    ...					


def set_window_min_size(width: int, height: int, /) -> None:
    """Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)"""
    ...		


def set_window_max_size(width: int, height: int, /) -> None:
    """Set window maximum dimensions (for FLAG_WINDOW_RESIZABLE)"""
    ...		


def set_window_size(width: int, height: int, /) -> None:
    """Set window dimensions"""
    ...			


def set_window_opacity(opacity: float, /) -> None:
    """Set window opacity [0.0f..1.0f] (only PLATFORM_DESKTOP)"""
    ...				


def set_window_focused() -> None:
    """Set window focused (only PLATFORM_DESKTOP)"""
    ...							


def get_window_handle() -> int:
    """Get native window handle"""
    ...							


def get_screen_width() -> int:
    """Get current screen width"""
    ...							


def get_screen_height() -> int:
    """Get current screen height"""
    ...							


def get_render_width() -> int:
    """Get current render width (it considers HiDPI)"""
    ...							


def get_render_height() -> int:
    """Get current render height (it considers HiDPI)"""
    ...							


def get_monitor_count() -> int:
    """Get number of connected monitors"""
    ...							


def get_current_monitor() -> int:
    """Get current connected monitor"""
    ...							


def get_monitor_position(monitor: int, /) -> Vector2:
    """Get specified monitor position"""
    ...				


def get_monitor_width(monitor: int, /) -> int:
    """Get specified monitor width (current video mode used by monitor)"""
    ...					


def get_monitor_height(monitor: int, /) -> int:
    """Get specified monitor height (current video mode used by monitor)"""
    ...					


def get_monitor_physical_width(monitor: int, /) -> int:
    """Get specified monitor physical width in millimetres"""
    ...			


def get_monitor_physical_height(monitor: int, /) -> int:
    """Get specified monitor physical height in millimetres"""
    ...			


def get_monitor_refresh_rate(monitor: int, /) -> int:
    """Get specified monitor refresh rate"""
    ...				


def get_window_position() -> Vector2:
    """Get window position XY on monitor"""
    ...						


def get_window_scale_dpi() -> Vector2:
    """Get window scale DPI factor"""
    ...						


def get_monitor_name(monitor: int, /) -> str:
    """Get the human-readable, UTF-8 encoded name of the specified monitor"""
    ...				


def set_clipboard_text(text: str, /) -> None:
    """Set clipboard text content"""
    ...				


def get_clipboard_text() -> str:
    """Get clipboard text content"""
    ...					


def enable_event_waiting() -> None:
    """Enable waiting for events on end_drawing(), no automatic event polling"""
    ...						


def disable_event_waiting() -> None:
    """Disable waiting for events on end_drawing(), automatic events polling"""
    ...						


# System/Window config flags
# NOTE: Every bit registers one state (use it with bit masks)
# By default all flags are set to 0

"""Set to try enabling V-Sync on GPU"""
FLAG_VSYNC_HINT: int

"""Set to run program in fullscreen"""
FLAG_FULLSCREEN_MODE: int

"""Set to allow resizable window"""
FLAG_WINDOW_RESIZABLE: int

"""Set to disable window decoration (frame and buttons)"""
FLAG_WINDOW_UNDECORATED: int

"""Set to hide window"""
FLAG_WINDOW_HIDDEN: int

"""Set to minimize window (iconify)"""
FLAG_WINDOW_MINIMIZED: int

"""Set to maximize window (expanded to monitor)"""
FLAG_WINDOW_MAXIMIZED: int

"""Set to window non focused"""
FLAG_WINDOW_UNFOCUSED: int

"""Set to window always on top"""
FLAG_WINDOW_TOPMOST: int

"""Set to allow windows running while minimized"""
FLAG_WINDOW_ALWAYS_RUN: int

"""Set to allow transparent framebuffer"""
FLAG_WINDOW_TRANSPARENT: int

"""Set to support HighDPI"""
FLAG_WINDOW_HIGHDPI: int

"""Set to support mouse passthrough, only supported when FLAG_WINDOW_UNDECORATED"""
FLAG_WINDOW_MOUSE_PASSTHROUGH: int

"""Set to run program in borderless windowed mode"""
FLAG_BORDERLESS_WINDOWED_MODE: int

"""Set to try enabling MSAA 4X"""
FLAG_MSAA_4X_HINT: int

"""Set to try enabling interlaced video format (for V3D)"""
FLAG_INTERLACED_HINT: int

# Trace log level
# NOTE: Organized by priority level

"""Display all logs"""
LOG_ALL: int

"""Trace logging, intended for internal use only"""
LOG_TRACE: int

"""Debug logging, used for internal debugging, it should be disabled on release builds"""
LOG_DEBUG: int

"""Info logging, used for program execution info"""
LOG_INFO: int

"""Warning logging, used on recoverable failures"""
LOG_WARNING: int

"""Error logging, used on unrecoverable failures"""
LOG_ERROR: int

"""Fatal logging, used to abort program: exit(EXIT_FAILURE)"""
LOG_FATAL: int

"""Disable logging"""
LOG_NONE: int

# Keyboard keys (US keyboard layout)
# NOTE: Use GetKeyPressed() to allow redefining
# required keys for alternative layouts

"""Key: NULL, used for no key pressed"""
KEY_NULL: int

# Alphanumeric keys

"""Key: '"""
KEY_APOSTROPHE: int

"""Key: ,"""
KEY_COMMA: int

"""Key: -"""
KEY_MINUS: int

"""Key: ."""
KEY_PERIOD: int

"""Key: /"""
KEY_SLASH: int

"""Key: 0"""
KEY_ZERO: int

"""Key: 1"""
KEY_ONE: int

"""Key: 2"""
KEY_TWO: int

"""Key: 3"""
KEY_THREE: int

"""Key: 4"""
KEY_FOUR: int

"""Key: 5"""
KEY_FIVE: int

"""Key: 6"""
KEY_SIX: int

"""Key: 7"""
KEY_SEVEN: int

"""Key: 8"""
KEY_EIGHT: int

"""Key: 9"""
KEY_NINE: int

"""Key: ;"""
KEY_SEMICOLON: int

"""Key: ="""
KEY_EQUAL: int

"""Key: A | a"""
KEY_A: int

"""Key: B | b"""
KEY_B: int

"""Key: C | c"""
KEY_C: int

"""Key: D | d"""
KEY_D: int

"""Key: E | e"""
KEY_E: int

"""Key: F | f"""
KEY_F: int

"""Key: G | g"""
KEY_G: int

"""Key: H | h"""
KEY_H: int

"""Key: I | i"""
KEY_I: int

"""Key: J | j"""
KEY_J: int

"""Key: K | k"""
KEY_K: int

"""Key: L | l"""
KEY_L: int

"""Key: M | m"""
KEY_M: int

"""Key: N | n"""
KEY_N: int

"""Key: O | o"""
KEY_O: int

"""Key: P | p"""
KEY_P: int

"""Key: Q | q"""
KEY_Q: int

"""Key: R | r"""
KEY_R: int

"""Key: S | s"""
KEY_S: int

"""Key: T | t"""
KEY_T: int

"""Key: U | u"""
KEY_U: int

"""Key: V | v"""
KEY_V: int

"""Key: W | w"""
KEY_W: int

"""Key: X | x"""
KEY_X: int

"""Key: Y | y"""
KEY_Y: int

"""Key: Z | z"""
KEY_Z: int

"""Key: ["""
KEY_LEFT_BRACKET: int

"""Key: '\'"""
KEY_BACKSLASH: int

"""Key: ]"""
KEY_RIGHT_BRACKET: int

"""Key: `"""
KEY_GRAVE: int

# Function keys

"""Key: Space"""
KEY_SPACE: int

"""Key: Esc"""
KEY_ESCAPE: int

"""Key: Enter"""
KEY_ENTER: int

"""Key: Tab"""
KEY_TAB: int

"""Key: Backspace"""
KEY_BACKSPACE: int

"""Key: Ins"""
KEY_INSERT: int

"""Key: Del"""
KEY_DELETE: int

"""Key: Cursor right"""
KEY_RIGHT: int

"""Key: Cursor left"""
KEY_LEFT: int

"""Key: Cursor down"""
KEY_DOWN: int

"""Key: Cursor up"""
KEY_UP: int

"""Key: Page up"""
KEY_PAGE_UP: int

"""Key: Page down"""
KEY_PAGE_DOWN: int

"""Key: Home"""
KEY_HOME: int

"""Key: End"""
KEY_END: int

"""Key: Caps lock"""
KEY_CAPS_LOCK: int

"""Key: Scroll down"""
KEY_SCROLL_LOCK: int

"""Key: Num lock"""
KEY_NUM_LOCK: int

"""Key: Print screen"""
KEY_PRINT_SCREEN: int

"""Key: Pause"""
KEY_PAUSE: int

"""Key: F1"""
KEY_F1: int

"""Key: F2"""
KEY_F2: int

"""Key: F3"""
KEY_F3: int

"""Key: F4"""
KEY_F4: int

"""Key: F5"""
KEY_F5: int

"""Key: F6"""
KEY_F6: int

"""Key: F7"""
KEY_F7: int

"""Key: F8"""
KEY_F8: int

"""Key: F9"""
KEY_F9: int

"""Key: F10"""
KEY_F10: int

"""Key: F11"""
KEY_F11: int

"""Key: F12"""
KEY_F12: int

"""Key: Shift left"""
KEY_LEFT_SHIFT: int

"""Key: Control left"""
KEY_LEFT_CONTROL: int

"""Key: Alt left"""
KEY_LEFT_ALT: int

"""Key: Super left"""
KEY_LEFT_SUPER: int

"""Key: Shift right"""
KEY_RIGHT_SHIFT: int

"""Key: Control right"""
KEY_RIGHT_CONTROL: int

"""Key: Alt right"""
KEY_RIGHT_ALT: int

"""Key: Super right"""
KEY_RIGHT_SUPER: int

"""Key: KB menu"""
KEY_KB_MENU: int

# Keypad keys

"""Key: Keypad 0"""
KEY_KP_0: int

"""Key: Keypad 1"""
KEY_KP_1: int

"""Key: Keypad 2"""
KEY_KP_2: int

"""Key: Keypad 3"""
KEY_KP_3: int

"""Key: Keypad 4"""
KEY_KP_4: int

"""Key: Keypad 5"""
KEY_KP_5: int

"""Key: Keypad 6"""
KEY_KP_6: int

"""Key: Keypad 7"""
KEY_KP_7: int

"""Key: Keypad 8"""
KEY_KP_8: int

"""Key: Keypad 9"""
KEY_KP_9: int

"""Key: Keypad ."""
KEY_KP_DECIMAL: int

"""Key: Keypad /"""
KEY_KP_DIVIDE: int

"""Key: Keypad *"""
KEY_KP_MULTIPLY: int

"""Key: Keypad -"""
KEY_KP_SUBTRACT: int

"""Key: Keypad +"""
KEY_KP_ADD: int

"""Key: Keypad Enter"""
KEY_KP_ENTER: int

"""Key: Keypad ="""
KEY_KP_EQUAL: int

# Android key buttons

"""Key: Android back button"""
KEY_BACK: int

"""Key: Android menu button"""
KEY_MENU: int

"""Key: Android volume up button"""
KEY_VOLUME_UP: int

"""Key: Android volume down button"""
KEY_VOLUME_DOWN: int

# Add backwards compatibility support for deprecated names
MOUSE_LEFT_BUTTON: int
MOUSE_RIGHT_BUTTON: int
MOUSE_MIDDLE_BUTTON: int

# Mouse buttons

"""Mouse button left"""
MOUSE_BUTTON_LEFT: int

"""Mouse button right"""
MOUSE_BUTTON_RIGHT: int

"""Mouse button middle (pressed wheel)"""
MOUSE_BUTTON_MIDDLE: int

"""Mouse button side (advanced mouse device)"""
MOUSE_BUTTON_SIDE: int

"""Mouse button extra (advanced mouse device)"""
MOUSE_BUTTON_EXTRA: int

"""Mouse button forward (advanced mouse device)"""
MOUSE_BUTTON_FORWARD: int

"""Mouse button back (advanced mouse device)"""
MOUSE_BUTTON_BACK: int

# Mouse cursor

"""Default pointer shape"""
MOUSE_CURSOR_DEFAULT: int

"""Arrow shape"""
MOUSE_CURSOR_ARROW: int

"""Text writing cursor shape"""
MOUSE_CURSOR_IBEAM: int

"""Cross shape"""
MOUSE_CURSOR_CROSSHAIR: int

"""Pointing hand cursor"""
MOUSE_CURSOR_POINTING_HAND: int

"""Horizontal resize/move arrow shape"""
MOUSE_CURSOR_RESIZE_EW: int

"""Vertical resize/move arrow shape"""
MOUSE_CURSOR_RESIZE_NS: int

"""Top-left to bottom-right diagonal resize/move arrow shape"""
MOUSE_CURSOR_RESIZE_NWSE: int

"""The top-right to bottom-left diagonal resize/move arrow shape"""
MOUSE_CURSOR_RESIZE_NESW: int

"""The omnidirectional resize/move cursor shape"""
MOUSE_CURSOR_RESIZE_ALL: int

"""The operation-not-allowed shape"""
MOUSE_CURSOR_NOT_ALLOWED: int

# Gamepad buttons

"""Unknown button, just for error checking"""
GAMEPAD_BUTTON_UNKNOWN: int

"""Gamepad left DPAD up button"""
GAMEPAD_BUTTON_LEFT_FACE_UP: int

"""Gamepad left DPAD right button"""
GAMEPAD_BUTTON_LEFT_FACE_RIGHT: int

"""Gamepad left DPAD down button"""
GAMEPAD_BUTTON_LEFT_FACE_DOWN: int

"""Gamepad left DPAD left button"""
GAMEPAD_BUTTON_LEFT_FACE_LEFT: int

"""Gamepad right button up (i.e. PS3: Triangle, Xbox: Y)"""
GAMEPAD_BUTTON_RIGHT_FACE_UP: int

"""Gamepad right button right (i.e. PS3: Square, Xbox: X)"""
GAMEPAD_BUTTON_RIGHT_FACE_RIGHT: int

"""Gamepad right button down (i.e. PS3: Cross, Xbox: A)"""
GAMEPAD_BUTTON_RIGHT_FACE_DOWN: int

"""Gamepad right button left (i.e. PS3: Circle, Xbox: B)"""
GAMEPAD_BUTTON_RIGHT_FACE_LEFT: int

"""Gamepad top/back trigger left (first), it could be a trailing button"""
GAMEPAD_BUTTON_LEFT_TRIGGER_1: int

"""Gamepad top/back trigger left (second), it could be a trailing button"""
GAMEPAD_BUTTON_LEFT_TRIGGER_2: int

"""Gamepad top/back trigger right (one), it could be a trailing button"""
GAMEPAD_BUTTON_RIGHT_TRIGGER_1: int

"""Gamepad top/back trigger right (second), it could be a trailing button"""
GAMEPAD_BUTTON_RIGHT_TRIGGER_2: int

"""Gamepad center buttons, left one (i.e. PS3: Select)"""
GAMEPAD_BUTTON_MIDDLE_LEFT: int

"""Gamepad center buttons, middle one (i.e. PS3: PS, Xbox: XBOX)"""
GAMEPAD_BUTTON_MIDDLE: int

"""Gamepad center buttons, right one (i.e. PS3: Start)"""
GAMEPAD_BUTTON_MIDDLE_RIGHT: int

"""Gamepad joystick pressed button left"""
GAMEPAD_BUTTON_LEFT_THUMB: int

"""Gamepad joystick pressed button right"""
GAMEPAD_BUTTON_RIGHT_THUMB: int

# Gamepad axis

"""Gamepad left stick X axis"""
GAMEPAD_AXIS_LEFT_X: int

"""Gamepad left stick Y axis"""
GAMEPAD_AXIS_LEFT_Y: int

"""Gamepad right stick X axis"""
GAMEPAD_AXIS_RIGHT_X: int

"""Gamepad right stick Y axis"""
GAMEPAD_AXIS_RIGHT_Y: int

"""Gamepad back trigger left, pressure level: [1..-1]"""
GAMEPAD_AXIS_LEFT_TRIGGER: int

"""Gamepad back trigger right, pressure level: [1..-1]"""
GAMEPAD_AXIS_RIGHT_TRIGGER: int

# Material map index

"""Albedo material (same as: MATERIAL_MAP_DIFFUSE)"""
MATERIAL_MAP_ALBEDO: int

"""Metalness material (same as: MATERIAL_MAP_SPECULAR)"""
MATERIAL_MAP_METALNESS: int

"""Normal material"""
MATERIAL_MAP_NORMAL: int

"""Roughness material"""
MATERIAL_MAP_ROUGHNESS: int

"""Ambient occlusion material"""
MATERIAL_MAP_OCCLUSION: int

"""Emission material"""
MATERIAL_MAP_EMISSION: int

"""Heightmap material"""
MATERIAL_MAP_HEIGHT: int

"""Cubemap material (NOTE: Uses GL_TEXTURE_CUBE_MAP)"""
MATERIAL_MAP_CUBEMAP: int

"""Irradiance material (NOTE: Uses GL_TEXTURE_CUBE_MAP)"""
MATERIAL_MAP_IRRADIANCE: int

"""Prefilter material (NOTE: Uses GL_TEXTURE_CUBE_MAP)"""
MATERIAL_MAP_PREFILTER: int

"""Brdf material"""
MATERIAL_MAP_BRDF: int
MATERIAL_MAP_DIFFUSE: int
MATERIAL_MAP_SPECULAR: int

# Shader location index

"""Shader location: vertex attribute: position"""
SHADER_LOC_VERTEX_POSITION: int

"""Shader location: vertex attribute: texcoord01"""
SHADER_LOC_VERTEX_TEXCOORD01: int

"""Shader location: vertex attribute: texcoord02"""
SHADER_LOC_VERTEX_TEXCOORD02: int

"""Shader location: vertex attribute: normal"""
SHADER_LOC_VERTEX_NORMAL: int

"""Shader location: vertex attribute: tangent"""
SHADER_LOC_VERTEX_TANGENT: int

"""Shader location: vertex attribute: color"""
SHADER_LOC_VERTEX_COLOR: int

"""Shader location: matrix uniform: model-view-projection"""
SHADER_LOC_MATRIX_MVP: int

"""Shader location: matrix uniform: view (camera transform)"""
SHADER_LOC_MATRIX_VIEW: int

"""Shader location: matrix uniform: projection"""
SHADER_LOC_MATRIX_PROJECTION: int

"""Shader location: matrix uniform: model (transform)"""
SHADER_LOC_MATRIX_MODEL: int

"""Shader location: matrix uniform: normal"""
SHADER_LOC_MATRIX_NORMAL: int

"""Shader location: vector uniform: view"""
SHADER_LOC_VECTOR_VIEW: int

"""Shader location: vector uniform: diffuse color"""
SHADER_LOC_COLOR_DIFFUSE: int

"""Shader location: vector uniform: specular color"""
SHADER_LOC_COLOR_SPECULAR: int

"""Shader location: vector uniform: ambient color"""
SHADER_LOC_COLOR_AMBIENT: int

"""Shader location: sampler2d texture: albedo (same as: SHADER_LOC_MAP_DIFFUSE)"""
SHADER_LOC_MAP_ALBEDO: int

"""Shader location: sampler2d texture: metalness (same as: SHADER_LOC_MAP_SPECULAR)"""
SHADER_LOC_MAP_METALNESS: int

"""Shader location: sampler2d texture: normal"""
SHADER_LOC_MAP_NORMAL: int

"""Shader location: sampler2d texture: roughness"""
SHADER_LOC_MAP_ROUGHNESS: int

"""Shader location: sampler2d texture: occlusion"""
SHADER_LOC_MAP_OCCLUSION: int

"""Shader location: sampler2d texture: emission"""
SHADER_LOC_MAP_EMISSION: int

"""Shader location: sampler2d texture: height"""
SHADER_LOC_MAP_HEIGHT: int

"""Shader location: samplerCube texture: cubemap"""
SHADER_LOC_MAP_CUBEMAP: int

"""Shader location: samplerCube texture: irradiance"""
SHADER_LOC_MAP_IRRADIANCE: int

"""Shader location: samplerCube texture: prefilter"""
SHADER_LOC_MAP_PREFILTER: int

"""Shader location: sampler2d texture: brdf"""
SHADER_LOC_MAP_BRDF: int
SHADER_LOC_MAP_DIFFUSE: int
SHADER_LOC_MAP_SPECULAR: int

# Shader uniform data type

"""Shader uniform type: float"""
SHADER_UNIFORM_FLOAT: int

"""Shader uniform type: vec2 (2 float)"""
SHADER_UNIFORM_VEC2: int

"""Shader uniform type: vec3 (3 float)"""
SHADER_UNIFORM_VEC3: int

"""Shader uniform type: vec4 (4 float)"""
SHADER_UNIFORM_VEC4: int

"""Shader uniform type: int"""
SHADER_UNIFORM_INT: int

"""Shader uniform type: ivec2 (2 int)"""
SHADER_UNIFORM_IVEC2: int

"""Shader uniform type: ivec3 (3 int)"""
SHADER_UNIFORM_IVEC3: int

"""Shader uniform type: ivec4 (4 int)"""
SHADER_UNIFORM_IVEC4: int

"""Shader uniform type: sampler2d"""
SHADER_UNIFORM_SAMPLER2D: int

# Shader attribute data types

"""Shader attribute type: float"""
SHADER_ATTRIB_FLOAT: int

"""Shader attribute type: vec2 (2 float)"""
SHADER_ATTRIB_VEC2: int

"""Shader attribute type: vec3 (3 float)"""
SHADER_ATTRIB_VEC3: int

"""Shader attribute type: vec4 (4 float)"""
SHADER_ATTRIB_VEC4: int

# Pixel formats
# NOTE: Support depends on OpenGL version and platform

"""8 bit per pixel (no alpha)"""
PIXELFORMAT_UNCOMPRESSED_GRAYSCALE: int

"""8*2 bpp (2 channels)"""
PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA: int

"""16 bpp"""
PIXELFORMAT_UNCOMPRESSED_R5G6B5: int

"""24 bpp"""
PIXELFORMAT_UNCOMPRESSED_R8G8B8: int

"""16 bpp (1 bit alpha)"""
PIXELFORMAT_UNCOMPRESSED_R5G5B5A1: int

"""16 bpp (4 bit alpha)"""
PIXELFORMAT_UNCOMPRESSED_R4G4B4A4: int

"""32 bpp"""
PIXELFORMAT_UNCOMPRESSED_R8G8B8A8: int

"""32 bpp (1 channel - float)"""
PIXELFORMAT_UNCOMPRESSED_R32: int

"""32*3 bpp (3 channels - float)"""
PIXELFORMAT_UNCOMPRESSED_R32G32B32: int

"""32*4 bpp (4 channels - float)"""
PIXELFORMAT_UNCOMPRESSED_R32G32B32A32: int

"""16 bpp (1 channel - half float)"""
PIXELFORMAT_UNCOMPRESSED_R16: int

"""16*3 bpp (3 channels - half float)"""
PIXELFORMAT_UNCOMPRESSED_R16G16B16: int

"""16*4 bpp (4 channels - half float)"""
PIXELFORMAT_UNCOMPRESSED_R16G16B16A16: int

"""4 bpp (no alpha)"""
PIXELFORMAT_COMPRESSED_DXT1_RGB: int

"""4 bpp (1 bit alpha)"""
PIXELFORMAT_COMPRESSED_DXT1_RGBA: int

"""8 bpp"""
PIXELFORMAT_COMPRESSED_DXT3_RGBA: int

"""8 bpp"""
PIXELFORMAT_COMPRESSED_DXT5_RGBA: int

"""4 bpp"""
PIXELFORMAT_COMPRESSED_ETC1_RGB: int

"""4 bpp"""
PIXELFORMAT_COMPRESSED_ETC2_RGB: int

"""8 bpp"""
PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA: int

"""4 bpp"""
PIXELFORMAT_COMPRESSED_PVRT_RGB: int

"""4 bpp"""
PIXELFORMAT_COMPRESSED_PVRT_RGBA: int

"""8 bpp"""
PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA: int

"""2 bpp"""
PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA: int

# Texture parameters: filter mode
# NOTE 1: Filtering considers mipmaps if available in the texture
# NOTE 2: Filter is accordingly set for minification and magnification

"""No filter, just pixel approximation"""
TEXTURE_FILTER_POINT: int

"""Linear filtering"""
TEXTURE_FILTER_BILINEAR: int

"""Trilinear filtering (linear with mipmaps)"""
TEXTURE_FILTER_TRILINEAR: int

"""Anisotropic filtering 4x"""
TEXTURE_FILTER_ANISOTROPIC_4X: int

"""Anisotropic filtering 8x"""
TEXTURE_FILTER_ANISOTROPIC_8X: int

"""Anisotropic filtering 16x"""
TEXTURE_FILTER_ANISOTROPIC_16X: int

# Texture parameters: wrap mode

"""Repeats texture in tiled mode"""
TEXTURE_WRAP_REPEAT: int

"""Clamps texture to edge pixel in tiled mode"""
TEXTURE_WRAP_CLAMP: int

"""Mirrors and repeats the texture in tiled mode"""
TEXTURE_WRAP_MIRROR_REPEAT: int

"""Mirrors and clamps to border the texture in tiled mode"""
TEXTURE_WRAP_MIRROR_CLAMP: int

# Cubemap layouts

"""Automatically detect layout type"""
CUBEMAP_LAYOUT_AUTO_DETECT: int

"""Layout is defined by a vertical line with faces"""
CUBEMAP_LAYOUT_LINE_VERTICAL: int

"""Layout is defined by a horizontal line with faces"""
CUBEMAP_LAYOUT_LINE_HORIZONTAL: int

"""Layout is defined by a 3x4 cross with cubemap faces"""
CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR: int

"""Layout is defined by a 4x3 cross with cubemap faces"""
CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE: int

"""Layout is defined by a panorama image (equirrectangular map)"""
CUBEMAP_LAYOUT_PANORAMA: int

# Font type, defines generation method

"""Default font generation, anti-aliased"""
FONT_DEFAULT: int

"""Bitmap font generation, no anti-aliasing"""
FONT_BITMAP: int

"""SDF font generation, requires external shader"""
FONT_SDF: int

# Color blending modes (pre-defined)

"""Blend textures considering alpha (default)"""
BLEND_ALPHA: int

"""Blend textures adding colors"""
BLEND_ADDITIVE: int

"""Blend textures multiplying colors"""
BLEND_MULTIPLIED: int

"""Blend textures adding colors (alternative)"""
BLEND_ADD_COLORS: int

"""Blend textures subtracting colors (alternative)"""
BLEND_SUBTRACT_COLORS: int

"""Blend premultiplied textures considering alpha"""
BLEND_ALPHA_PREMULTIPLY: int

"""Blend textures using custom src/dst factors (use rlSetBlendFactors())"""
BLEND_CUSTOM: int

"""Blend textures using custom rgb/alpha separate src/dst factors (use rlSetBlendFactorsSeparate())"""
BLEND_CUSTOM_SEPARATE: int

# Gesture
# NOTE: Provided as bit-wise flags to enable only desired gestures

"""No gesture"""
GESTURE_NONE: int

"""Tap gesture"""
GESTURE_TAP: int

"""Double tap gesture"""
GESTURE_DOUBLETAP: int

"""Hold gesture"""
GESTURE_HOLD: int

"""Drag gesture"""
GESTURE_DRAG: int

"""Swipe right gesture"""
GESTURE_SWIPE_RIGHT: int

"""Swipe left gesture"""
GESTURE_SWIPE_LEFT: int

"""Swipe up gesture"""
GESTURE_SWIPE_UP: int

"""Swipe down gesture"""
GESTURE_SWIPE_DOWN: int

"""Pinch in gesture"""
GESTURE_PINCH_IN: int

"""Pinch out gesture"""
GESTURE_PINCH_OUT: int

# Camera system modes

"""Custom camera"""
CAMERA_CUSTOM: int

"""Free camera"""
CAMERA_FREE: int

"""Orbital camera"""
CAMERA_ORBITAL: int

"""First person camera"""
CAMERA_FIRST_PERSON: int

"""Third person camera"""
CAMERA_THIRD_PERSON: int

# Camera projection

"""Perspective projection"""
CAMERA_PERSPECTIVE: int

"""Orthographic projection"""
CAMERA_ORTHOGRAPHIC: int

# N-patch layout

"""Npatch layout: 3x3 tiles"""
NPATCH_NINE_PATCH: int

"""Npatch layout: 1x3 tiles"""
NPATCH_THREE_PATCH_VERTICAL: int

"""Npatch layout: 3x1 tiles"""
NPATCH_THREE_PATCH_HORIZONTAL: int
