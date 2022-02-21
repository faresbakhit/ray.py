<img align="left" src="https://github.com/faresahmedb/ray.py/blob/main/.github/ray.py.png" width="288px">

**ray.py - CPython native bindings for Raylib**

ray.py is a cross-platform bindings for the great graphics library [raylib](https://www.raylib.com/) 4.0+ with performance in-mind as it's build using the native Python/C API and statically links `libraylib` so you don't miss any frame!

Check out [examples](https://github.com/faresahmedb/ray.py/blob/main/examples) converted from [raylib/examples](https://github.com/raysan5/raylib/blob/master/examples)

<br>
<br>
<br>
<br>
<br>

---

## Getting Started

ray.py uses Python3 C API so you would need Python 3.0+ installed on your system, If you don't have it install it using your system's package manager or follow the [instructions](https://www.python.org/download) provided in the python website.

### Installing

This requires having [pip](https://pip.pypa.io/en/stable/) and an internet connection, If your current envirnment doesn't have pip installed follow [this](https://pip.pypa.io/en/stable/installation/) instructions

```
python3 -m pip install ray.py
python3 -c "import raypy"
```

The first command installs `ray.py` and second ensures that it's working.

### Quick Start

```python
import raypy

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
```

## Building

This requires having `git`, `python3-dev` installed on your system

```
git clone https://github.com/faresahmedb/ray.py.git
cd ray.py
python3 -m venv .venv
source .venv/bin/activate OR .venv\Scripts\activate
python -m pip install build
python -m build
```

This will download the latest version of [raysan5/raylib](https://github.com/raysan5/raylib) releases and link our source files against it if you wish to change the release version or use your own repo, check `python setup.py download_deps --help`

If all goes okay you should have two new files in `dist` one of them is `ray.py-X.Y.X.tar.gz` (sdist) and the other is `ray.py-X.Y.Z-PLATFORM` (wheel)

## How does this differs from other bindings?

This bindings is 100% native written in C and statically linked with `libraylib` so the performance is very close to other popular python graphics libraries like pygame.

The motivation behinde this library was that other raylib bindings were very slow as they were all written in python using `ctypes` or tools like `cffi` which tends to slow down C calls so much so I decided to just write it all in C and see how it goes.

## License

ray.py is licensed under an unmodified zlib/libpng license, see the [LICENSE](LICENSE) file for details.
