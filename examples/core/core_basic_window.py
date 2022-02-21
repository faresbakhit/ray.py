import sys

import raypy


def main() -> int:
    screen_width = 800
    screen_height = 450

    raypy.init_window(screen_width, screen_height, "raylib [core] example - basic window")
    raypy.set_target_fps(60)

    while not raypy.window_should_close():
        raypy.begin_drawing()
        raypy.clear_background(raypy.RAYWHITE)
        raypy.draw_text("Congrats! You created your first window!", 190, 200, 20, raypy.LIGHTGRAY)
        raypy.end_drawing()

    raypy.close_window()

    return 0


if __name__ == "__main__":
    sys.exit(main())
