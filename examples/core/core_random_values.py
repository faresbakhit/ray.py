import sys

import raypy


def main() -> int:
    screen_width = 800
    screen_height = 450

    raypy.init_window(screen_width, screen_height, "raylib [core] example - generate random values")
    # raypy.set_random_seed(0xAABBCCFF)  # Set a custom random seed if desired, by default: "time(NULL)"
    rand_value = raypy.get_random_value(-8, 5)
    frames_counter = 0

    raypy.set_target_fps(60)

    while not raypy.window_should_close():
        frames_counter += 1

        if ((frames_counter / 120) % 2) == 1:
            rand_value = raypy.get_random_value(-8, 5)
            frames_counter = 0

        raypy.begin_drawing()

        raypy.clear_background(raypy.RAYWHITE)
        raypy.draw_text("Every 2 seconds a new random value is generated:", 130, 100, 20, raypy.MAROON)
        raypy.draw_text(str(rand_value), 360, 180, 80, raypy.LIGHTGRAY)

        raypy.end_drawing()

    raypy.close_window()

    return 0


if __name__ == "__main__":
    sys.exit(main())
