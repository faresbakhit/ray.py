"""CPython native bindings for Raylib"""

RAYLIB_VERSION: str
PI: float
DEG2RAD: float
RAD2DEG: float

class Vector2:
    x: float
    y: float
    def __init__(self, x: float | None = ..., y: float | None = ...) -> None: ...

class Vector3:
    x: float
    y: float
    z: float
    def __init__(self, x: float | None = ..., y: float | None = ..., z: float | None = ...) -> None: ...

class Vector4:
    x: float
    y: float
    z: float
    w: float
    def __init__(self, x: float | None = ..., y: float | None = ..., z: float | None = ..., w: float | None = ...) -> None: ...

Quaternion = Vector4

class Color:
    r: int
    g: int
    b: int
    a: int
    def __init__(self, r: int, g: int, b: int, a: int | None = ...) -> None: ...

LIGHTGRAY: Color
GRAY: Color
DARKGRAY: Color
YELLOW: Color
GOLD: Color
ORANGE: Color
PINK: Color
RED: Color
MAROON: Color
GREEN: Color
LIME: Color
DARKGREEN: Color
SKYBLUE: Color
BLUE: Color
DARKBLUE: Color
PURPLE: Color
VIOLET: Color
DARKPURPLE: Color
BEIGE: Color
BROWN: Color
DARKBROWN: Color

WHITE: Color
BLACK: Color
BLANK: Color
MAGENTA: Color
RAYWHITE: Color

FLAG_VSYNC_HINT: int
FLAG_FULLSCREEN_MODE: int
FLAG_WINDOW_RESIZABLE: int
FLAG_WINDOW_UNDECORATED: int
FLAG_WINDOW_HIDDEN: int
FLAG_WINDOW_MINIMIZED: int
FLAG_WINDOW_MAXIMIZED: int
FLAG_WINDOW_UNFOCUSED: int
FLAG_WINDOW_TOPMOST: int
FLAG_WINDOW_ALWAYS_RUN: int
FLAG_WINDOW_TRANSPARENT: int
FLAG_WINDOW_HIGHDPI: int
FLAG_MSAA_4X_HINT: int
FLAG_INTERLACED_HINT: int
LOG_ALL: int
LOG_TRACE: int
LOG_DEBUG: int
LOG_INFO: int
LOG_WARNING: int
LOG_ERROR: int
LOG_FATAL: int
LOG_NONE: int
KEY_NULL: int
KEY_APOSTROPHE: int
KEY_COMMA: int
KEY_MINUS: int
KEY_PERIOD: int
KEY_SLASH: int
KEY_ZERO: int
KEY_ONE: int
KEY_TWO: int
KEY_THREE: int
KEY_FOUR: int
KEY_FIVE: int
KEY_SIX: int
KEY_SEVEN: int
KEY_EIGHT: int
KEY_NINE: int
KEY_SEMICOLON: int
KEY_EQUAL: int
KEY_A: int
KEY_B: int
KEY_C: int
KEY_D: int
KEY_E: int
KEY_F: int
KEY_G: int
KEY_H: int
KEY_I: int
KEY_J: int
KEY_K: int
KEY_L: int
KEY_M: int
KEY_N: int
KEY_O: int
KEY_P: int
KEY_Q: int
KEY_R: int
KEY_S: int
KEY_T: int
KEY_U: int
KEY_V: int
KEY_W: int
KEY_X: int
KEY_Y: int
KEY_Z: int
KEY_LEFT_BRACKET: int
KEY_BACKSLASH: int
KEY_RIGHT_BRACKET: int
KEY_GRAVE: int
KEY_SPACE: int
KEY_ESCAPE: int
KEY_ENTER: int
KEY_TAB: int
KEY_BACKSPACE: int
KEY_INSERT: int
KEY_DELETE: int
KEY_RIGHT: int
KEY_LEFT: int
KEY_DOWN: int
KEY_UP: int
KEY_PAGE_UP: int
KEY_PAGE_DOWN: int
KEY_HOME: int
KEY_END: int
KEY_CAPS_LOCK: int
KEY_SCROLL_LOCK: int
KEY_NUM_LOCK: int
KEY_PRINT_SCREEN: int
KEY_PAUSE: int
KEY_F1: int
KEY_F2: int
KEY_F3: int
KEY_F4: int
KEY_F5: int
KEY_F6: int
KEY_F7: int
KEY_F8: int
KEY_F9: int
KEY_F10: int
KEY_F11: int
KEY_F12: int
KEY_LEFT_SHIFT: int
KEY_LEFT_CONTROL: int
KEY_LEFT_ALT: int
KEY_LEFT_SUPER: int
KEY_RIGHT_SHIFT: int
KEY_RIGHT_CONTROL: int
KEY_RIGHT_ALT: int
KEY_RIGHT_SUPER: int
KEY_KB_MENU: int
KEY_KP_0: int
KEY_KP_1: int
KEY_KP_2: int
KEY_KP_3: int
KEY_KP_4: int
KEY_KP_5: int
KEY_KP_6: int
KEY_KP_7: int
KEY_KP_8: int
KEY_KP_9: int
KEY_KP_DECIMAL: int
KEY_KP_DIVIDE: int
KEY_KP_MULTIPLY: int
KEY_KP_SUBTRACT: int
KEY_KP_ADD: int
KEY_KP_ENTER: int
KEY_KP_EQUAL: int
KEY_BACK: int
KEY_MENU: int
KEY_VOLUME_UP: int
KEY_VOLUME_DOWN: int
MOUSE_BUTTON_LEFT: int
MOUSE_BUTTON_RIGHT: int
MOUSE_BUTTON_MIDDLE: int
MOUSE_BUTTON_SIDE: int
MOUSE_BUTTON_EXTRA: int
MOUSE_BUTTON_FORWARD: int
MOUSE_BUTTON_BACK: int
MOUSE_CURSOR_DEFAULT: int
MOUSE_CURSOR_ARROW: int
MOUSE_CURSOR_IBEAM: int
MOUSE_CURSOR_CROSSHAIR: int
MOUSE_CURSOR_POINTING_HAND: int
MOUSE_CURSOR_RESIZE_EW: int
MOUSE_CURSOR_RESIZE_NS: int
MOUSE_CURSOR_RESIZE_NWSE: int
MOUSE_CURSOR_RESIZE_NESW: int
MOUSE_CURSOR_RESIZE_ALL: int
MOUSE_CURSOR_NOT_ALLOWED: int
GAMEPAD_BUTTON_UNKNOWN: int
GAMEPAD_BUTTON_LEFT_FACE_UP: int
GAMEPAD_BUTTON_LEFT_FACE_RIGHT: int
GAMEPAD_BUTTON_LEFT_FACE_DOWN: int
GAMEPAD_BUTTON_LEFT_FACE_LEFT: int
GAMEPAD_BUTTON_RIGHT_FACE_UP: int
GAMEPAD_BUTTON_RIGHT_FACE_RIGHT: int
GAMEPAD_BUTTON_RIGHT_FACE_DOWN: int
GAMEPAD_BUTTON_RIGHT_FACE_LEFT: int
GAMEPAD_BUTTON_LEFT_TRIGGER_1: int
GAMEPAD_BUTTON_LEFT_TRIGGER_2: int
GAMEPAD_BUTTON_RIGHT_TRIGGER_1: int
GAMEPAD_BUTTON_RIGHT_TRIGGER_2: int
GAMEPAD_BUTTON_MIDDLE_LEFT: int
GAMEPAD_BUTTON_MIDDLE: int
GAMEPAD_BUTTON_MIDDLE_RIGHT: int
GAMEPAD_BUTTON_LEFT_THUMB: int
GAMEPAD_BUTTON_RIGHT_THUMB: int
GAMEPAD_AXIS_LEFT_X: int
GAMEPAD_AXIS_LEFT_Y: int
GAMEPAD_AXIS_RIGHT_X: int
GAMEPAD_AXIS_RIGHT_Y: int
GAMEPAD_AXIS_LEFT_TRIGGER: int
GAMEPAD_AXIS_RIGHT_TRIGGER: int
MATERIAL_MAP_ALBEDO: int
MATERIAL_MAP_METALNESS: int
MATERIAL_MAP_NORMAL: int
MATERIAL_MAP_ROUGHNESS: int
MATERIAL_MAP_OCCLUSION: int
MATERIAL_MAP_EMISSION: int
MATERIAL_MAP_HEIGHT: int
MATERIAL_MAP_CUBEMAP: int
MATERIAL_MAP_IRRADIANCE: int
MATERIAL_MAP_PREFILTER: int
MATERIAL_MAP_BRDF: int
MATERIAL_MAP_ALBEDO: int
MATERIAL_MAP_METALNESS: int
SHADER_LOC_VERTEX_POSITION: int
SHADER_LOC_VERTEX_TEXCOORD01: int
SHADER_LOC_VERTEX_TEXCOORD02: int
SHADER_LOC_VERTEX_NORMAL: int
SHADER_LOC_VERTEX_TANGENT: int
SHADER_LOC_VERTEX_COLOR: int
SHADER_LOC_MATRIX_MVP: int
SHADER_LOC_MATRIX_VIEW: int
SHADER_LOC_MATRIX_PROJECTION: int
SHADER_LOC_MATRIX_MODEL: int
SHADER_LOC_MATRIX_NORMAL: int
SHADER_LOC_VECTOR_VIEW: int
SHADER_LOC_COLOR_DIFFUSE: int
SHADER_LOC_COLOR_SPECULAR: int
SHADER_LOC_COLOR_AMBIENT: int
SHADER_LOC_MAP_ALBEDO: int
SHADER_LOC_MAP_METALNESS: int
SHADER_LOC_MAP_NORMAL: int
SHADER_LOC_MAP_ROUGHNESS: int
SHADER_LOC_MAP_OCCLUSION: int
SHADER_LOC_MAP_EMISSION: int
SHADER_LOC_MAP_HEIGHT: int
SHADER_LOC_MAP_CUBEMAP: int
SHADER_LOC_MAP_IRRADIANCE: int
SHADER_LOC_MAP_PREFILTER: int
SHADER_LOC_MAP_BRDF: int
SHADER_LOC_MAP_DIFFUSE: int
SHADER_LOC_MAP_SPECULAR: int
SHADER_UNIFORM_FLOAT: int
SHADER_UNIFORM_VEC2: int
SHADER_UNIFORM_VEC3: int
SHADER_UNIFORM_VEC4: int
SHADER_UNIFORM_INT: int
SHADER_UNIFORM_IVEC2: int
SHADER_UNIFORM_IVEC3: int
SHADER_UNIFORM_IVEC4: int
SHADER_UNIFORM_SAMPLER2D: int
SHADER_ATTRIB_FLOAT: int
SHADER_ATTRIB_VEC2: int
SHADER_ATTRIB_VEC3: int
SHADER_ATTRIB_VEC4: int
PIXELFORMAT_UNCOMPRESSED_GRAYSCALE: int
PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA: int
PIXELFORMAT_UNCOMPRESSED_R5G6B5: int
PIXELFORMAT_UNCOMPRESSED_R8G8B8: int
PIXELFORMAT_UNCOMPRESSED_R5G5B5A1: int
PIXELFORMAT_UNCOMPRESSED_R4G4B4A4: int
PIXELFORMAT_UNCOMPRESSED_R8G8B8A8: int
PIXELFORMAT_UNCOMPRESSED_R32: int
PIXELFORMAT_UNCOMPRESSED_R32G32B32: int
PIXELFORMAT_UNCOMPRESSED_R32G32B32A32: int
PIXELFORMAT_COMPRESSED_DXT1_RGB: int
PIXELFORMAT_COMPRESSED_DXT1_RGBA: int
PIXELFORMAT_COMPRESSED_DXT3_RGBA: int
PIXELFORMAT_COMPRESSED_DXT5_RGBA: int
PIXELFORMAT_COMPRESSED_ETC1_RGB: int
PIXELFORMAT_COMPRESSED_ETC2_RGB: int
PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA: int
PIXELFORMAT_COMPRESSED_PVRT_RGB: int
PIXELFORMAT_COMPRESSED_PVRT_RGBA: int
PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA: int
PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA: int
TEXTURE_FILTER_POINT: int
TEXTURE_FILTER_BILINEAR: int
TEXTURE_FILTER_TRILINEAR: int
TEXTURE_FILTER_ANISOTROPIC_4X: int
TEXTURE_FILTER_ANISOTROPIC_8X: int
TEXTURE_FILTER_ANISOTROPIC_16X: int
TEXTURE_WRAP_REPEAT: int
TEXTURE_WRAP_CLAMP: int
TEXTURE_WRAP_MIRROR_REPEAT: int
TEXTURE_WRAP_MIRROR_CLAMP: int
CUBEMAP_LAYOUT_AUTO_DETECT: int
CUBEMAP_LAYOUT_LINE_VERTICAL: int
CUBEMAP_LAYOUT_LINE_HORIZONTAL: int
CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR: int
CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE: int
CUBEMAP_LAYOUT_PANORAMA: int
FONT_DEFAULT: int
FONT_BITMAP: int
FONT_SDF: int
BLEND_ALPHA: int
BLEND_ADDITIVE: int
BLEND_MULTIPLIED: int
BLEND_ADD_COLORS: int
BLEND_SUBTRACT_COLORS: int
BLEND_CUSTOM: int
GESTURE_NONE: int
GESTURE_TAP: int
GESTURE_DOUBLETAP: int
GESTURE_HOLD: int
GESTURE_DRAG: int
GESTURE_SWIPE_RIGHT: int
GESTURE_SWIPE_LEFT: int
GESTURE_SWIPE_UP: int
GESTURE_SWIPE_DOWN: int
GESTURE_PINCH_IN: int
GESTURE_PINCH_OUT: int
CAMERA_CUSTOM: int
CAMERA_FREE: int
CAMERA_ORBITAL: int
CAMERA_FIRST_PERSON: int
CAMERA_THIRD_PERSON: int
CAMERA_PERSPECTIVE: int
CAMERA_ORTHOGRAPHIC: int
NPATCH_NINE_PATCH: int
NPATCH_THREE_PATCH_VERTICAL: int
NPATCH_THREE_PATCH_HORIZONTAL: int

def init_window(width: int, height: int, title: str) -> None: ...
def window_should_close() -> bool: ...
def close_window() -> None: ...
def is_window_ready() -> bool: ...
def is_window_fullscreen() -> bool: ...
def is_window_hidden() -> bool: ...
def is_window_minimized() -> bool: ...
def is_window_maximized() -> bool: ...
def is_window_focused() -> bool: ...
def is_window_resized() -> bool: ...
def is_window_state(flag: int, /) -> bool: ...
def set_window_state(flags: int, /) -> None: ...
def clear_window_state(flags: int, /) -> None: ...
def toggle_fullscreen() -> None: ...
def maximize_window() -> None: ...
def minimize_window() -> None: ...
def restore_window() -> None: ...
def set_window_icon() -> None: ...  # TODO
def set_window_title(title: str, /) -> None: ...
def set_window_position(x: int, y: int, /) -> None: ...
def set_window_monitor(monitor: int, /) -> None: ...
def set_window_min_size(width: int, height: int) -> None: ...
def set_window_size(width: int, height: int) -> None: ...
def get_window_handle() -> int: ...
def get_screen_width() -> int: ...
def get_screen_height() -> int: ...
def get_monitor_count() -> int: ...
def get_current_monitor() -> int: ...
def get_monitor_position(monitor: int, /) -> Vector2: ...
def get_monitor_width(monitor: int, /) -> int: ...
def get_monitor_height(monitor: int, /) -> int: ...
def get_monitor_physical_width(monitor: int, /) -> int: ...
def get_monitor_physical_height(monitor: int, /) -> int: ...
def get_monitor_refresh_rate(monitor: int) -> int: ...
def get_window_position() -> Vector2: ...
def get_window_scale_dpi() -> Vector2: ...
def get_monitor_name(monitor: int, /) -> str: ...
def set_clipboard_text(text: str, /) -> None: ...
def get_clipboard_text() -> str: ...
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
