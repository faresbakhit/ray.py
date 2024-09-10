#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <descrobject.h> // Py_T_FLOAT
#include <stddef.h> // offsetof
#include <raylib.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#define METH_O_TYPE_ERROR(obj, type)                                                          \
    if (PyErr_Occurred()) {                                                                   \
        if (PyErr_ExceptionMatches(PyExc_TypeError)) {                                        \
            PyErr_Clear();                                                                    \
            PyErr_Format(PyExc_TypeError, "argument must be %s, not %s", type,                \
                         Py_TYPE(obj)->tp_name);                                              \
        }                                                                                     \
        return NULL;                                                                          \
    }

#define WINDOW_IS_READY()                                                                     \
    if (!IsWindowReady()) {                                                                   \
        PyErr_SetString(PyExc_RuntimeError, "window not initialized");                        \
        return NULL;                                                                          \
    }

/* Vector2 */

typedef struct {
    PyObject_HEAD float x;
    float y;
} RayPy_Vector2Object;

static void
RayPy_Vector2_dealloc(RayPy_Vector2Object *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static RayPy_Vector2Object *
RayPy_Vector2_new(PyTypeObject *type, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds))
{
    RayPy_Vector2Object *self = (RayPy_Vector2Object *)type->tp_alloc(type, 0);
    if (self == NULL)
        return NULL;
    self->x = 0.0;
    self->y = 0.0;
    return self;
}

static int
RayPy_Vector2_init(RayPy_Vector2Object *self, PyObject *args, PyObject *Py_UNUSED(kwds))
{
    if (!PyArg_ParseTuple(args, "|ff", &self->x, &self->y)) {
        return -1;
    }
    return 0;
}

static PyMemberDef RayPy_Vector2_members[] = {
    {"x", Py_T_FLOAT, offsetof(RayPy_Vector2Object, x), 0, "Vector x component"},
    {"y", Py_T_FLOAT, offsetof(RayPy_Vector2Object, y), 0, "Vector y component"},
    {NULL}
};

static PyObject *
RayPy_Vector2_repr(RayPy_Vector2Object *self)
{
    PyObject *x = PyFloat_FromDouble(self->x);
    PyObject *y = PyFloat_FromDouble(self->y);
    return PyUnicode_FromFormat("Vector2(%R, %R)", x, y);
}

static PyObject *
RayPy_Vector2_richcompare(RayPy_Vector2Object *self, RayPy_Vector2Object *other, int op)
{
    switch (op) {
    case Py_EQ:
        return PyBool_FromLong(
            self->x == other->x
            && self->y == other->y);
    case Py_NE:
        return PyBool_FromLong(
            self->x != other->x
            || self->y != other->y);
    default:
        Py_RETURN_NOTIMPLEMENTED;
    }
}

static PyTypeObject RayPy_Vector2_Type = {
    .ob_base = PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "raypy.Vector2",
    .tp_doc = PyDoc_STR("Vector2, 2 components"),
    .tp_basicsize = sizeof(RayPy_Vector2Object),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = (newfunc)RayPy_Vector2_new,
    .tp_init = (initproc)RayPy_Vector2_init,
    .tp_repr = (reprfunc)RayPy_Vector2_repr,
    .tp_dealloc = (destructor)RayPy_Vector2_dealloc,
    .tp_members = RayPy_Vector2_members,
    .tp_richcompare = (richcmpfunc)RayPy_Vector2_richcompare,
};

/* Vector3 */

typedef struct {
    PyObject_HEAD float x;
    float y;
    float z;
} RayPy_Vector3Object;

static void
RayPy_Vector3_dealloc(RayPy_Vector3Object *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static RayPy_Vector3Object *
RayPy_Vector3_new(PyTypeObject *type, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds))
{
    RayPy_Vector3Object *self = (RayPy_Vector3Object *)type->tp_alloc(type, 0);
    if (self == NULL)
        return NULL;
    self->x = 0.0;
    self->y = 0.0;
    self->z = 0.0;
    return self;
}

static int
RayPy_Vector3_init(RayPy_Vector3Object *self, PyObject *args, PyObject *Py_UNUSED(kwds))
{
    if (!PyArg_ParseTuple(args, "|fff", &self->x, &self->y, &self->z)) {
        return -1;
    }
    return 0;
}

static PyMemberDef RayPy_Vector3_members[] = {
    {"x", Py_T_FLOAT, offsetof(RayPy_Vector3Object, x), 0, "Vector x component"},
    {"y", Py_T_FLOAT, offsetof(RayPy_Vector3Object, y), 0, "Vector y component"},
    {"z", Py_T_FLOAT, offsetof(RayPy_Vector3Object, z), 0, "Vector z component"},
    {NULL}
};

static PyObject *
RayPy_Vector3_repr(RayPy_Vector3Object *self)
{
    PyObject *x = PyFloat_FromDouble(self->x);
    PyObject *y = PyFloat_FromDouble(self->y);
    PyObject *z = PyFloat_FromDouble(self->z);
    return PyUnicode_FromFormat("Vector3(%R, %R, %R)", x, y, z);
}

static PyObject *
RayPy_Vector3_richcompare(RayPy_Vector3Object *self, RayPy_Vector3Object *other, int op)
{
    switch (op) {
    case Py_EQ:
        return PyBool_FromLong(
            self->x == other->x
            && self->y == other->y
            && self->z == other->z);
    case Py_NE:
        return PyBool_FromLong(
            self->x != other->x
            || self->y != other->y
            || self->z != other->z);
    default:
        Py_RETURN_NOTIMPLEMENTED;
    }
}

static PyTypeObject RayPy_Vector3_Type = {
    .ob_base = PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "raypy.Vector3",
    .tp_doc = PyDoc_STR("Vector3, 3 components"),
    .tp_basicsize = sizeof(RayPy_Vector3Object),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = (newfunc)RayPy_Vector3_new,
    .tp_init = (initproc)RayPy_Vector3_init,
    .tp_repr = (reprfunc)RayPy_Vector3_repr,
    .tp_dealloc = (destructor)RayPy_Vector3_dealloc,
    .tp_members = RayPy_Vector3_members,
    .tp_richcompare = (richcmpfunc)RayPy_Vector3_richcompare,
};

/* Vector4 */

typedef struct {
    PyObject_HEAD float x;
    float y;
    float z;
    float w;
} RayPy_Vector4Object;

static void
RayPy_Vector4_dealloc(RayPy_Vector4Object *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static RayPy_Vector4Object *
RayPy_Vector4_new(PyTypeObject *type, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds))
{
    RayPy_Vector4Object *self = (RayPy_Vector4Object *)type->tp_alloc(type, 0);
    if (self == NULL)
        return NULL;
    self->x = 0.0;
    self->y = 0.0;
    self->z = 0.0;
    self->w = 0.0;
    return self;
}

static int
RayPy_Vector4_init(RayPy_Vector4Object *self, PyObject *args, PyObject *Py_UNUSED(kwds))
{
    if (!PyArg_ParseTuple(args, "|ffff", &self->x, &self->y, &self->z, &self->w)) {
        return -1;
    }
    return 0;
}

static PyMemberDef RayPy_Vector4_members[] = {
    {"x", Py_T_FLOAT, offsetof(RayPy_Vector4Object, x), 0, "Vector x component"},
    {"y", Py_T_FLOAT, offsetof(RayPy_Vector4Object, y), 0, "Vector y component"},
    {"z", Py_T_FLOAT, offsetof(RayPy_Vector4Object, z), 0, "Vector z component"},
    {"w", Py_T_FLOAT, offsetof(RayPy_Vector4Object, w), 0, "Vector w component"},
    {NULL}
};

static PyObject *
RayPy_Vector4_repr(RayPy_Vector4Object *self)
{
    PyObject *x = PyFloat_FromDouble(self->x);
    PyObject *y = PyFloat_FromDouble(self->y);
    PyObject *z = PyFloat_FromDouble(self->z);
    PyObject *w = PyFloat_FromDouble(self->w);
    return PyUnicode_FromFormat("Vector4(%R, %R, %R, %R)", x, y, z, w);
}

static PyObject *
RayPy_Vector4_richcompare(RayPy_Vector4Object *self, RayPy_Vector4Object *other, int op)
{
    switch (op) {
    case Py_EQ:
        return PyBool_FromLong(
            self->x == other->x
            && self->y == other->y
            && self->z == other->z
            && self->w == other->w);
    case Py_NE:
        return PyBool_FromLong(
            self->x != other->x
            || self->y != other->y
            || self->z != other->z
            || self->w != other->w);
    default:
        Py_RETURN_NOTIMPLEMENTED;
    }
}

static PyTypeObject RayPy_Vector4_Type = {
    .ob_base = PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "raypy.Vector4",
    .tp_doc = PyDoc_STR("Vector4, 4 components"),
    .tp_basicsize = sizeof(RayPy_Vector4Object),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = (newfunc)RayPy_Vector4_new,
    .tp_init = (initproc)RayPy_Vector4_init,
    .tp_repr = (reprfunc)RayPy_Vector4_repr,
    .tp_dealloc = (destructor)RayPy_Vector4_dealloc,
    .tp_members = RayPy_Vector4_members,
    .tp_richcompare = (richcmpfunc)RayPy_Vector4_richcompare,
};

/* Color */

typedef struct {
    PyObject_HEAD unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} RayPy_ColorObject;

static void
RayPy_Color_dealloc(RayPy_ColorObject *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static RayPy_ColorObject *
RayPy_Color_new(PyTypeObject *type, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds))
{
    RayPy_ColorObject *self = (RayPy_ColorObject *)type->tp_alloc(type, 0);
    if (self == NULL)
        return NULL;
    self->r = 0;
    self->g = 0;
    self->b = 0;
    self->a = 255;
    return self;
}

static int
RayPy_Color_init(RayPy_ColorObject *self, PyObject *args, PyObject *Py_UNUSED(kwds))
{
    if (!PyArg_ParseTuple(args, "bbb|b", &self->r, &self->g, &self->b, &self->a)) {
        return -1;
    }
    return 0;
}

static PyMemberDef RayPy_Color_members[] = {
    {"r", Py_T_UBYTE, offsetof(RayPy_ColorObject, r), 0, "Color red value"},
    {"g", Py_T_UBYTE, offsetof(RayPy_ColorObject, g), 0, "Color green value"},
    {"b", Py_T_UBYTE, offsetof(RayPy_ColorObject, b), 0, "Color blue value"},
    {"a", Py_T_UBYTE, offsetof(RayPy_ColorObject, a), 0, "Color alpha value"},
    {NULL}
};

static PyObject *
RayPy_Color_repr(RayPy_ColorObject *self)
{
    PyObject *r = PyLong_FromUnsignedLong(self->r);
    PyObject *g = PyLong_FromUnsignedLong(self->g);
    PyObject *b = PyLong_FromUnsignedLong(self->b);
    PyObject *a = PyLong_FromUnsignedLong(self->a);
    return PyUnicode_FromFormat("Color(%R, %R, %R, %R)", r, g, b, a);
}

static PyObject *
RayPy_Color_richcompare(RayPy_ColorObject *self, RayPy_ColorObject *other, int op)
{
    switch (op) {
    case Py_EQ:
        return PyBool_FromLong(
            self->r == other->r
            && self->g == other->g
            && self->b == other->b
            && self->a == other->a);
    case Py_NE:
        return PyBool_FromLong(
            self->r != other->r
            || self->g != other->g
            || self->b != other->b
            || self->a != other->a);
    default:
        Py_RETURN_NOTIMPLEMENTED;
    }
}

static PyTypeObject RayPy_Color_Type = {
    .ob_base = PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "raypy.Color",
    .tp_doc = PyDoc_STR("Color, 4 components, R8G8B8A8 (32bit)"),
    .tp_basicsize = sizeof(RayPy_ColorObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = (newfunc)RayPy_Color_new,
    .tp_init = (initproc)RayPy_Color_init,
    .tp_repr = (reprfunc)RayPy_Color_repr,
    .tp_dealloc = (destructor)RayPy_Color_dealloc,
    .tp_members = RayPy_Color_members,
    .tp_richcompare = (richcmpfunc)RayPy_Color_richcompare,
};

Color
RayPy_Color_AsColor(RayPy_ColorObject *obj)
{
    Color color = {0};
    if (obj == NULL) {
        PyErr_BadInternalCall();
    }
    if (!PyObject_TypeCheck(obj, &RayPy_Color_Type)) {
        PyErr_Format(PyExc_TypeError, "must be raypy.Color, not %s", Py_TYPE(obj)->tp_name);
        return color;
    }
    color.r = obj->r;
    color.g = obj->g;
    color.b = obj->b;
    color.a = obj->a;
    return color;
}

/* Rectangle */

typedef struct {
    PyObject_HEAD float x;
    float y;
    float width;
    float height;
} RayPy_RectangleObject;

static void
RayPy_Rectangle_dealloc(RayPy_RectangleObject *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static RayPy_RectangleObject *
RayPy_Rectangle_new(PyTypeObject *type, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds))
{
    RayPy_RectangleObject *self = (RayPy_RectangleObject *)type->tp_alloc(type, 0);
    if (self == NULL)
        return NULL;
    self->x = 0.0;
    self->y = 0.0;
    self->width = 0.0;
    self->height = 0.0;
    return self;
}

static int
RayPy_Rectangle_init(RayPy_RectangleObject *self, PyObject *args, PyObject *Py_UNUSED(kwds))
{
    if (!PyArg_ParseTuple(args, "|ffff", &self->x, &self->y, &self->width, &self->height)) {
        return -1;
    }
    return 0;
}

static PyMemberDef RayPy_Rectangle_members[] = {
    {"x", Py_T_FLOAT, offsetof(RayPy_RectangleObject, x), 0, "Rectangle top-left corner position x"},
    {"y", Py_T_FLOAT, offsetof(RayPy_RectangleObject, y), 0, "Rectangle top-left corner position y"},
    {"width", Py_T_FLOAT, offsetof(RayPy_RectangleObject, width), 0, "Rectangle width"},
    {"height", Py_T_FLOAT, offsetof(RayPy_RectangleObject, height), 0, "Rectangle height"},
    {NULL}
};

static PyObject *
RayPy_Rectangle_repr(RayPy_RectangleObject *self)
{
    PyObject *x = PyFloat_FromDouble(self->x);
    PyObject *y = PyFloat_FromDouble(self->y);
    PyObject *width = PyFloat_FromDouble(self->width);
    PyObject *height = PyFloat_FromDouble(self->height);
    return PyUnicode_FromFormat("Rectangle(%R, %R, %R, %R)", x, y, width, height);
}

static PyObject *
RayPy_Rectangle_richcompare(RayPy_RectangleObject *self, RayPy_RectangleObject *other, int op)
{
    switch (op) {
    case Py_EQ:
        return PyBool_FromLong(
            self->x == other->x
            && self->y == other->y
            && self->width == other->width
            && self->height == other->height);
    case Py_NE:
        return PyBool_FromLong(
            self->x != other->x
            || self->y != other->y
            || self->width != other->width
            || self->height != other->height);
    default:
        Py_RETURN_NOTIMPLEMENTED;
    }
}

static PyTypeObject RayPy_Rectangle_Type = {
    .ob_base = PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "raypy.Rectangle",
    .tp_doc = PyDoc_STR("Rectangle, 4 components"),
    .tp_basicsize = sizeof(RayPy_RectangleObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = (newfunc)RayPy_Rectangle_new,
    .tp_init = (initproc)RayPy_Rectangle_init,
    .tp_repr = (reprfunc)RayPy_Rectangle_repr,
    .tp_dealloc = (destructor)RayPy_Rectangle_dealloc,
    .tp_members = RayPy_Rectangle_members,
    .tp_richcompare = (richcmpfunc)RayPy_Rectangle_richcompare,
};

/* Image */

typedef struct {
    PyObject_HEAD Image i;
} RayPy_ImageObject;

static void
RayPy_Image_dealloc(RayPy_ImageObject *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static RayPy_ImageObject *
RayPy_Image_new(PyTypeObject *type, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
    RayPy_ImageObject *self = (RayPy_ImageObject *)type->tp_alloc(type, 0);
    if (self == NULL)
        return NULL;
    return self;
}

static int
RayPy_Image_init(RayPy_ImageObject *self, PyObject *args, PyObject *Py_UNUSED(kwds))
{
    PyErr_SetString(PyExc_TypeError,
                        "raypy.Image cannot be instantiated directly from"
                        " Python. Use the provided module-level functions"
                        " instead.");
    return -1;
}

static PyMemberDef RayPy_Image_members[] = {
    {"width", Py_T_INT, offsetof(RayPy_ImageObject, i.width), 0, "Image base width"},
    {"height", Py_T_INT, offsetof(RayPy_ImageObject, i.height), 0, "Image base height"},
    {"mipmaps", Py_T_INT, offsetof(RayPy_ImageObject, i.mipmaps), 0, "Mipmap levels, 1 by default"},
    {"format", Py_T_INT, offsetof(RayPy_ImageObject, i.format), 0, "Data format (PixelFormat type)"},
    {NULL}
};

static PyTypeObject RayPy_Image_Type = {
    .ob_base = PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "raypy.Image",
    .tp_doc = "Image, pixel data stored in CPU memory (RAM)",
    .tp_basicsize = sizeof(RayPy_ImageObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = (newfunc)RayPy_Image_new,
    .tp_init = (initproc)RayPy_Image_init,
    .tp_dealloc = (destructor)RayPy_Image_dealloc,
    .tp_members = RayPy_Image_members,
};

/* Texture */

typedef struct {
    PyObject_HEAD Texture t;
} RayPy_TextureObject;

static void
RayPy_Texture_dealloc(RayPy_TextureObject *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static RayPy_TextureObject *
RayPy_Texture_new(PyTypeObject *type, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds)) {
    RayPy_TextureObject *self = (RayPy_TextureObject *)type->tp_alloc(type, 0);
    if (self == NULL)
        return NULL;
    return self;
}

static int
RayPy_Texture_init(RayPy_TextureObject *self, PyObject *args, PyObject *Py_UNUSED(kwds))
{
    PyErr_SetString(PyExc_TypeError,
                        "raypy.Texture cannot be instantiated directly from"
                        " Python. Use the provided module-level functions"
                        " instead.");
    return -1;
}

static PyMemberDef RayPy_Texture_members[] = {
    {"id", Py_T_UINT, offsetof(RayPy_TextureObject, t.id), 0, "OpenGL texture id"},
    {"width", Py_T_INT, offsetof(RayPy_TextureObject, t.width), 0, "Texture base width"},
    {"height", Py_T_INT, offsetof(RayPy_TextureObject, t.height), 0, "Texture base height"},
    {"mipmaps", Py_T_INT, offsetof(RayPy_TextureObject, t.mipmaps), 0, "Mipmap levels, 1 by default"},
    {"format", Py_T_INT, offsetof(RayPy_TextureObject, t.format), 0, "Data format (PixelFormat type)"},
    {NULL}
};

static PyTypeObject RayPy_Texture_Type = {
    .ob_base = PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "raypy.Texture",
    .tp_doc = "Texture, tex data stored in GPU memory (VRAM)",
    .tp_basicsize = sizeof(RayPy_TextureObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = (newfunc)RayPy_Texture_new,
    .tp_init = (initproc)RayPy_Texture_init,
    .tp_dealloc = (destructor)RayPy_Texture_dealloc,
    .tp_members = RayPy_Texture_members,
};

static PyObject *
RayPy_InitWindow(PyObject *Py_UNUSED(self), PyObject *args, PyObject *keywds)
{
    int width, height;
    const char *title;
    static char *kwlist[] = {"width", "height", "title", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "iis", kwlist, &width, &height, &title))
        return NULL;
    InitWindow(width, height, title);
    Py_RETURN_NONE;
}

PyDoc_STRVAR(init_window_doc, "Initialize window and OpenGL context");

static PyObject *
RayPy_WindowShouldClose(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    return PyBool_FromLong(WindowShouldClose());
}

PyDoc_STRVAR(window_should_close_doc, "Check if KEY_ESCAPE pressed or Close icon pressed");

static PyObject *
RayPy_CloseWindow(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    if (!IsWindowReady())
        return (PyErr_SetString(PyExc_TypeError, ""), NULL);
    CloseWindow();
    Py_RETURN_NONE;
}

PyDoc_STRVAR(close_window_doc, "Close window and unload OpenGL context");

static PyObject *
RayPy_IsWindowReady(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    return PyBool_FromLong(IsWindowReady());
}

PyDoc_STRVAR(is_window_ready_doc, "Check if window has been initialized successfully");

static PyObject *
RayPy_IsWindowFullscreen(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    return PyBool_FromLong(IsWindowFullscreen());
}

PyDoc_STRVAR(is_window_fullscreen_doc, "Check if window is currently fullscreen");

static PyObject *
RayPy_IsWindowHidden(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    return PyBool_FromLong(IsWindowHidden());
}

PyDoc_STRVAR(is_window_hidden_doc,
             "Check if window is currently hidden (only PLATFORM_DESKTOP)");

static PyObject *
RayPy_IsWindowMinimized(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    return PyBool_FromLong(IsWindowMinimized());
}

PyDoc_STRVAR(is_window_minimized_doc,
             "Check if window is currently minimized (only PLATFORM_DESKTOP)");

static PyObject *
RayPy_IsWindowMaximized(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    return PyBool_FromLong(IsWindowMaximized());
}

PyDoc_STRVAR(is_window_maximized_doc,
             "Check if window is currently maximized (only PLATFORM_DESKTOP)");

static PyObject *
RayPy_IsWindowFocused(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    return PyBool_FromLong(IsWindowFocused());
}

PyDoc_STRVAR(is_window_focused_doc,
             "Check if window is currently focused (only PLATFORM_DESKTOP)");

static PyObject *
RayPy_IsWindowResized(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    return PyBool_FromLong(IsWindowResized());
}

PyDoc_STRVAR(is_window_resized_doc, "Check if window has been resized last frame");

static PyObject *
RayPy_IsWindowState(PyObject *Py_UNUSED(self), PyObject *obj)
{
    unsigned int flag = PyLong_AsUnsignedLong(obj);
    METH_O_TYPE_ERROR(obj, "int");
    return PyBool_FromLong(IsWindowState(flag));
}

PyDoc_STRVAR(is_window_state_doc, "Check if one specific window flag is enabled");

static PyObject *
RayPy_SetWindowState(PyObject *Py_UNUSED(self), PyObject *obj)
{
    WINDOW_IS_READY();
    unsigned int flag = PyLong_AsUnsignedLong(obj);
    METH_O_TYPE_ERROR(obj, "int");
    SetWindowState(flag);
    Py_RETURN_NONE;
}

PyDoc_STRVAR(set_window_state_doc, "Set window configuration state using flags");

static PyObject *
RayPy_ClearWindowState(PyObject *Py_UNUSED(self), PyObject *obj)
{
    unsigned int flag = PyLong_AsUnsignedLong(obj);
    METH_O_TYPE_ERROR(obj, "int");
    ClearWindowState(flag);
    Py_RETURN_NONE;
}

PyDoc_STRVAR(clear_window_state_doc, "Clear window configuration state flags");

static PyObject *
RayPy_ToggleFullscreen(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    WINDOW_IS_READY();
    ToggleFullscreen();
    Py_RETURN_NONE;
}

PyDoc_STRVAR(toggle_fullscreen_doc,
             "Toggle window state: fullscreen/windowed (only PLATFORM_DESKTOP)");

static PyObject *
RayPy_MaximizeWindow(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    WINDOW_IS_READY();
    MaximizeWindow();
    Py_RETURN_NONE;
}

PyDoc_STRVAR(maximize_window_doc,
             "Set window state: maximized, if resizable (only PLATFORM_DESKTOP)");

static PyObject *
RayPy_MinimizeWindow(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    WINDOW_IS_READY();
    MinimizeWindow();
    Py_RETURN_NONE;
}

PyDoc_STRVAR(minimize_window_doc,
             "Set window state: minimized, if resizable (only PLATFORM_DESKTOP)");

static PyObject *
RayPy_RestoreWindow(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    WINDOW_IS_READY();
    RestoreWindow();
    Py_RETURN_NONE;
}

PyDoc_STRVAR(restore_window_doc,
             "Set window state: not minimized/maximized (only PLATFORM_DESKTOP)");

static PyObject *
RayPy_SetWindowIcon(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(obj)) // TODO
{
    Py_RETURN_NONE;
}

PyDoc_STRVAR(set_window_icon_doc, "Set icon for window (only PLATFORM_DESKTOP)");

static PyObject *
RayPy_SetWindowTitle(PyObject *Py_UNUSED(self), PyObject *obj)
{
    WINDOW_IS_READY();
    Py_ssize_t len;
    const char *title = PyUnicode_AsUTF8AndSize(obj, &len);
    METH_O_TYPE_ERROR(obj, "str");
    SetWindowTitle(title);
    Py_RETURN_NONE;
}

PyDoc_STRVAR(set_window_title_doc, "Set title for window (only PLATFORM_DESKTOP)");

static PyObject *
RayPy_SetWindowPosition(PyObject *Py_UNUSED(self), PyObject *args)
{
    int x, y;
    WINDOW_IS_READY();
    if (!PyArg_ParseTuple(args, "ii", &x, &y))
        return NULL;
    SetWindowPosition(x, y);
    Py_RETURN_NONE;
}

PyDoc_STRVAR(set_window_position_doc, "Set window position on screen (only PLATFORM_DESKTOP)");

static PyObject *
RayPy_SetWindowMonitor(PyObject *Py_UNUSED(self), PyObject *obj)
{
    int monitor = PyLong_AsLong(obj);
    METH_O_TYPE_ERROR(obj, "int");
    SetWindowMonitor(monitor);
    Py_RETURN_NONE;
}

PyDoc_STRVAR(set_window_monitor_doc, "Set monitor for the current window (fullscreen mode)");

static PyObject *
RayPy_SetWindowMinSize(PyObject *Py_UNUSED(self), PyObject *args, PyObject *keywds)
{
    WINDOW_IS_READY();
    int width, height;
    static char *kwlist[] = {"width", "height", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "ii", kwlist, &width, &height))
        return NULL;
    SetWindowMinSize(width, height);
    Py_RETURN_NONE;
}

PyDoc_STRVAR(set_window_min_size_doc,
             "Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)");

static PyObject *
RayPy_SetWindowSize(PyObject *Py_UNUSED(self), PyObject *args, PyObject *keywds)
{
    WINDOW_IS_READY();
    int width, height;
    static char *kwlist[] = {"width", "height", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "ii", kwlist, &width, &height))
        return NULL;
    SetWindowSize(width, height);
    Py_RETURN_NONE;
}

PyDoc_STRVAR(set_window_size_doc, "Set window dimensions");

static PyObject *
RayPy_GetWindowHandle(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    PyObject *obj = PyLong_FromVoidPtr(GetWindowHandle());
    if (obj == NULL) {
        PyErr_SetString(PyExc_ValueError,
                        "couldn't convert internal 'GetWindowHandle' type to python object");
        return NULL;
    }
    return obj;
}

PyDoc_STRVAR(get_window_handle_doc, "Get native window handle");

static PyObject *
RayPy_GetScreenWidth(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    return PyLong_FromLong(GetScreenWidth());
}

PyDoc_STRVAR(get_screen_width_doc, "Get current screen width");

static PyObject *
RayPy_GetScreenHeight(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    return PyLong_FromLong(GetScreenHeight());
}

PyDoc_STRVAR(get_screen_height_doc, "Get current screen height");

static PyObject *
RayPy_GetMonitorCount(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    return PyLong_FromLong(GetMonitorCount());
}

PyDoc_STRVAR(get_monitor_count_doc, "Get number of connected monitors");

static PyObject *
RayPy_GetCurrentMonitor(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    WINDOW_IS_READY();
    return PyLong_FromLong(GetCurrentMonitor());
}

PyDoc_STRVAR(get_current_monitor_doc, "Get current connected monitor");

static PyObject *
RayPy_GetMonitorPosition(PyObject *Py_UNUSED(self), PyObject *obj)
{
    int monitor = PyLong_AsLong(obj);
    METH_O_TYPE_ERROR(obj, "int");
    Vector2 pos = GetMonitorPosition(monitor);
    return PyObject_CallFunction((PyObject *)&RayPy_Vector2_Type, "dd", pos.x, pos.y);
}

PyDoc_STRVAR(get_monitor_position_doc, "Get specified monitor position");

static PyObject *
RayPy_GetMonitorWidth(PyObject *Py_UNUSED(self), PyObject *obj)
{
    int monitor = PyLong_AsLong(obj);
    METH_O_TYPE_ERROR(obj, "int");
    return PyLong_FromLong(GetMonitorWidth(monitor));
}

PyDoc_STRVAR(get_monitor_width_doc, "Get specified monitor width (max available by monitor)");

static PyObject *
RayPy_GetMonitorHeight(PyObject *Py_UNUSED(self), PyObject *obj)
{
    int monitor = PyLong_AsLong(obj);
    METH_O_TYPE_ERROR(obj, "int");
    return PyLong_FromLong(GetMonitorHeight(monitor));
}

PyDoc_STRVAR(get_monitor_height_doc,
             "Get specified monitor height (max available by monitor)");

static PyObject *
RayPy_GetMonitorPhysicalWidth(PyObject *Py_UNUSED(self), PyObject *obj)
{
    int monitor = PyLong_AsLong(obj);
    METH_O_TYPE_ERROR(obj, "int");
    return PyLong_FromLong(GetMonitorPhysicalWidth(monitor));
}

PyDoc_STRVAR(get_monitor_physical_width_doc,
             "Get specified monitor physical width in millimetres");

static PyObject *
RayPy_GetMonitorPhysicalHeight(PyObject *Py_UNUSED(self), PyObject *obj)
{
    int monitor = PyLong_AsLong(obj);
    METH_O_TYPE_ERROR(obj, "int");
    return PyLong_FromLong(GetMonitorPhysicalHeight(monitor));
}

PyDoc_STRVAR(get_monitor_physical_height_doc,
             "Get specified monitor physical height in millimetres");

static PyObject *
RayPy_GetMonitorRefreshRate(PyObject *Py_UNUSED(self), PyObject *obj)
{
    int monitor = PyLong_AsLong(obj);
    METH_O_TYPE_ERROR(obj, "int");
    return PyLong_FromLong(GetMonitorRefreshRate(monitor));
}

PyDoc_STRVAR(get_monitor_refresh_rate_doc, "Get specified monitor refresh rate");

static PyObject *
RayPy_GetWindowPosition(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    WINDOW_IS_READY();
    Vector2 pos = GetWindowPosition();
    return PyObject_CallFunction((PyObject *)&RayPy_Vector2_Type, "dd", pos.x, pos.y);
}

PyDoc_STRVAR(get_window_position_doc, "Get window position XY on monitor");

static PyObject *
RayPy_GetWindowScaleDPI(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    WINDOW_IS_READY();
    Vector2 scale = GetWindowScaleDPI();
    return PyObject_CallFunction((PyObject *)&RayPy_Vector2_Type, "dd", scale.x, scale.y);
}

PyDoc_STRVAR(get_window_scale_dpi_doc, "Get window scale DPI factor");

static PyObject *
RayPy_GetMonitorName(PyObject *Py_UNUSED(self), PyObject *obj)
{
    int monitor = PyLong_AsLong(obj);
    METH_O_TYPE_ERROR(obj, "int");
    return PyUnicode_FromString(GetMonitorName(monitor));
}

PyDoc_STRVAR(get_monitor_name_doc,
             "Get the human-readable, UTF-8 encoded name of the primary monitor");

static PyObject *
RayPy_SetClipboardText(PyObject *Py_UNUSED(self), PyObject *obj)
{
    Py_ssize_t len;
    const char *text = PyUnicode_AsUTF8AndSize(obj, &len);
    METH_O_TYPE_ERROR(obj, "str");
    SetClipboardText(text);
    Py_RETURN_NONE;
}

PyDoc_STRVAR(set_clipboard_text_doc, "Set clipboard text content");

static PyObject *
RayPy_GetClipboardText(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    const char *text = GetClipboardText();
    if (text == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "window not initialized");
        return NULL;
    }
    return PyUnicode_FromString(text);
}

PyDoc_STRVAR(get_clipboard_text_doc, "Get clipboard text content");

static PyObject *
RayPy_SwapScreenBuffer(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    WINDOW_IS_READY();
    SwapScreenBuffer();
    Py_RETURN_NONE;
}

PyDoc_STRVAR(swap_screen_buffer_doc, "Swap back buffer with front buffer (screen drawing)");

static PyObject *
RayPy_PollInputEvents(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    PollInputEvents();
    Py_RETURN_NONE;
}

PyDoc_STRVAR(poll_input_events_doc, "Register all input events");

static PyObject *
RayPy_WaitTime(PyObject *Py_UNUSED(self), PyObject *args)
{
    WINDOW_IS_READY();
    double monitor = PyFloat_AsDouble(args);
    METH_O_TYPE_ERROR(args, "float");
    WaitTime((float)monitor);
    Py_RETURN_NONE;
}

PyDoc_STRVAR(wait_time_doc, "Wait for some milliseconds (halt program execution)");

PyObject *
RayPy_ShowCursor(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    WINDOW_IS_READY();
    ShowCursor();
    Py_RETURN_NONE;
}

PyDoc_STRVAR(show_cursor_doc, "Shows cursor");

PyObject *
RayPy_HideCursor(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    WINDOW_IS_READY();
    HideCursor();
    Py_RETURN_NONE;
}

PyDoc_STRVAR(hide_cursor_doc, "Hides cursor");

PyObject *
RayPy_IsCursorHidden(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    return PyBool_FromLong(IsCursorHidden());
}

PyDoc_STRVAR(is_cursor_hidden_doc, "Check if cursor is not visible");

PyObject *
RayPy_EnableCursor(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    WINDOW_IS_READY();
    EnableCursor();
    Py_RETURN_NONE;
}

PyDoc_STRVAR(enable_cursor_doc, "Enables cursor (unlock cursor)");

PyObject *
RayPy_DisableCursor(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    WINDOW_IS_READY();
    DisableCursor();
    Py_RETURN_NONE;
}

PyDoc_STRVAR(disable_cursor_doc, "Disables cursor (lock cursor)");

PyObject *
RayPy_IsCursorOnScreen(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    return PyBool_FromLong(IsCursorOnScreen());
}

PyDoc_STRVAR(is_cursor_on_screen_doc, "Check if cursor is on the screen");

static PyObject *
RayPy_ClearBackground(PyObject *Py_UNUSED(self), PyObject *obj)
{
    WINDOW_IS_READY();
    Color color = RayPy_Color_AsColor((RayPy_ColorObject *)obj);
    METH_O_TYPE_ERROR(obj, "raypy.Color");
    ClearBackground(color);
    Py_RETURN_NONE;
}

PyDoc_STRVAR(clear_background_doc, "Set background color (framebuffer clear color)");

static PyObject *
RayPy_BeginDrawing(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    BeginDrawing();
    Py_RETURN_NONE;
}

PyDoc_STRVAR(begin_drawing_doc, "Setup canvas (framebuffer) to start drawing");

static PyObject *
RayPy_EndDrawing(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    EndDrawing();
    Py_RETURN_NONE;
}

PyDoc_STRVAR(end_drawing_doc, "End canvas drawing and swap buffers (double buffering)");

static PyObject *
RayPy_SetTargetFPS(PyObject *Py_UNUSED(self), PyObject *obj)
{
    int fps = PyLong_AsLong(obj);
    METH_O_TYPE_ERROR(obj, "int");
    SetTargetFPS(fps);
    Py_RETURN_NONE;
}

PyDoc_STRVAR(set_target_fps_doc, "Set target FPS (maximum)");

static PyObject *
RayPy_GetFPS(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    return PyLong_FromLong(GetFPS());
}

PyDoc_STRVAR(get_fps_doc, "Get current FPS");

static PyObject *
RayPy_GetFrameTime(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    return PyFloat_FromDouble((double)GetFrameTime());
}

PyDoc_STRVAR(get_frame_time_doc, "Get time in seconds for last frame drawn (delta time)");

static PyObject *
RayPy_GetTime(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    return PyFloat_FromDouble(GetTime());
}

PyDoc_STRVAR(get_time_doc, "Get elapsed time in seconds since InitWindow()");

static PyObject *
RayPy_GetRandomValue(PyObject *Py_UNUSED(self), PyObject *args)
{
    int min, max;
    if (!PyArg_ParseTuple(args, "ii", &min, &max))
        return NULL;
    int val = GetRandomValue(min, max);
    return PyLong_FromLong(val);
}

PyDoc_STRVAR(get_random_value_doc, "Get a random value between min and max (both included)");

static PyObject *
RayPy_SetRandomSeed(PyObject *Py_UNUSED(self), PyObject *obj)
{
    unsigned int seed;
    if (!PyArg_Parse(obj, "I", &seed)) {
        return NULL;
    };
    SetRandomSeed(seed);
    Py_RETURN_NONE;
}

PyDoc_STRVAR(set_random_seed_doc, "Set the seed for the random number generator");

static PyObject *
RayPy_TakeScreenshot(PyObject *Py_UNUSED(self), PyObject *obj)
{
    Py_ssize_t len;
    const char *file_name = PyUnicode_AsUTF8AndSize(obj, &len);
    METH_O_TYPE_ERROR(obj, "str");
    TakeScreenshot(file_name);
    Py_RETURN_NONE;
}

PyDoc_STRVAR(take_screenshot_doc,
             "Takes a screenshot of current screen (filename extension defines format)");

static PyObject *
RayPy_SetConfigFlags(PyObject *Py_UNUSED(self), PyObject *obj)
{
    unsigned int flags;
    if (!PyArg_Parse(obj, "I", &flags)) {
        return NULL;
    };
    SetConfigFlags(flags);
    Py_RETURN_NONE;
}

PyDoc_STRVAR(set_config_flags_doc, "Setup init configuration flags (view FLAGS)");

static PyObject *
RayPy_TraceLog(PyObject *Py_UNUSED(self), PyObject *args)
{
    int log_level;
    const char *text;
    if (!PyArg_ParseTuple(args, "if", &log_level, &text))
        return NULL;
    TraceLog(log_level, text);
    Py_RETURN_NONE;
}

PyDoc_STRVAR(trace_log_doc,
             "Show trace log messages (LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERROR...)");

static PyObject *
RayPy_SetTraceLogLevel(PyObject *Py_UNUSED(self), PyObject *obj)
{
    long log_level = PyLong_AsLong(obj);
    METH_O_TYPE_ERROR(obj, "int");
    SetTraceLogLevel(log_level);
    Py_RETURN_NONE;
}

PyDoc_STRVAR(set_trace_log_level_doc, "Set the current threshold (minimum) log level");

static PyObject *
RayPy_OpenURL(PyObject *Py_UNUSED(self), PyObject *obj)
{
    Py_ssize_t len;
    const char *url = PyUnicode_AsUTF8AndSize(obj, &len);
    METH_O_TYPE_ERROR(obj, "str");
    OpenURL(url);
    Py_RETURN_NONE;
}

PyDoc_STRVAR(open_url_doc, "Open URL with default system browser (if available)");

static PyObject *
RayPy_IsKeyPressed(PyObject *Py_UNUSED(self), PyObject *obj)
{
    int key = PyLong_AsLong(obj);
    METH_O_TYPE_ERROR(obj, "int");
    return PyBool_FromLong(IsKeyPressed(key));
}

PyDoc_STRVAR(is_key_pressed_doc, "Check if a key has been pressed once");

static PyObject *
RayPy_IsKeyDown(PyObject *Py_UNUSED(self), PyObject *obj)
{
    int key = PyLong_AsLong(obj);
    METH_O_TYPE_ERROR(obj, "int");
    return PyBool_FromLong(IsKeyDown(key));
}

PyDoc_STRVAR(is_key_down_doc, "Check if a key is being pressed");

static PyObject *
RayPy_IsKeyReleased(PyObject *Py_UNUSED(self), PyObject *obj)
{
    int key = PyLong_AsLong(obj);
    METH_O_TYPE_ERROR(obj, "int");
    return PyBool_FromLong(IsKeyReleased(key));
}

PyDoc_STRVAR(is_key_released_doc, "Check if a key has been released once");

static PyObject *
RayPy_IsKeyUp(PyObject *Py_UNUSED(self), PyObject *obj)
{
    int key = PyLong_AsLong(obj);
    METH_O_TYPE_ERROR(obj, "int");
    return PyBool_FromLong(IsKeyUp(key));
}

PyDoc_STRVAR(is_key_up_doc, "Check if a key is NOT being pressed");

static PyObject *
RayPy_SetExitKey(PyObject *Py_UNUSED(self), PyObject *obj)
{
    int key = PyLong_AsLong(obj);
    METH_O_TYPE_ERROR(obj, "int");
    SetExitKey(key);
    Py_RETURN_NONE;
}

PyDoc_STRVAR(set_exit_key_doc, "Set a custom key to exit program (default is ESC)");

static PyObject *
RayPy_GetKeyPressed(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    return PyLong_FromLong(GetKeyPressed());
}

PyDoc_STRVAR(get_key_pressed_doc, "Get key pressed (keycode), call it multiple times for keys "
                                  "queued, returns 0 when the queue is empty");

static PyObject *
RayPy_GetCharPressed(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    return PyLong_FromLong(GetCharPressed());
}

PyDoc_STRVAR(get_char_pressed_doc, "Get char pressed (unicode), call it multiple times for "
                                   "chars queued, returns 0 when the queue is empty");

static PyObject *
RayPy_DrawFPS(PyObject *Py_UNUSED(self), PyObject *args)
{
    int pos_x, pos_y;
    if (!PyArg_ParseTuple(args, "ii", &pos_x, &pos_y))
        return NULL;
    DrawFPS(pos_x, pos_y);
    Py_RETURN_NONE;
}

PyDoc_STRVAR(draw_fps_doc, "Draw current FPS");

static PyObject *
RayPy_DrawText(PyObject *Py_UNUSED(self), PyObject *args, PyObject *keywds)
{
    const char *text;
    int pos_x, pos_y, font_size;
    PyObject *color_obj;
    static char *kwlist[] = {"text", "pos_x", "pos_y", "font_size", "color", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "siiiO", kwlist, &text, &pos_x, &pos_y,
                                     &font_size, &color_obj))
        return NULL;
    Color color = RayPy_Color_AsColor((RayPy_ColorObject *)color_obj);
    METH_O_TYPE_ERROR(color_obj, "raypy.Color");
    DrawText(text, pos_x, pos_y, font_size, color);
    Py_RETURN_NONE;
}

PyDoc_STRVAR(draw_text_doc, "Draw text (using default font)");

static PyMethodDef raypymethods[] = {
    {"init_window", (PyCFunction)(void (*)(void))RayPy_InitWindow, METH_VARARGS | METH_KEYWORDS, init_window_doc},
    {"window_should_close", (PyCFunction)RayPy_WindowShouldClose, METH_NOARGS, window_should_close_doc},
    {"close_window", (PyCFunction)RayPy_CloseWindow, METH_NOARGS, close_window_doc},
    {"is_window_ready", (PyCFunction)RayPy_IsWindowReady, METH_NOARGS, is_window_ready_doc},
    {"is_window_fullscreen", (PyCFunction)RayPy_IsWindowFullscreen, METH_NOARGS, is_window_fullscreen_doc},
    {"is_window_hidden", (PyCFunction)RayPy_IsWindowHidden, METH_NOARGS, is_window_hidden_doc},
    {"is_window_minimized", (PyCFunction)RayPy_IsWindowMinimized, METH_NOARGS, is_window_minimized_doc},
    {"is_window_maximized", (PyCFunction)RayPy_IsWindowMaximized, METH_NOARGS, is_window_maximized_doc},
    {"is_window_focused", (PyCFunction)RayPy_IsWindowFocused, METH_NOARGS, is_window_focused_doc},
    {"is_window_resized", (PyCFunction)RayPy_IsWindowResized, METH_NOARGS, is_window_resized_doc},
    {"is_window_state", (PyCFunction)RayPy_IsWindowState, METH_O, is_window_state_doc},
    {"set_window_state", (PyCFunction)RayPy_SetWindowState, METH_O, set_window_state_doc},
    {"clear_window_state", (PyCFunction)RayPy_ClearWindowState, METH_O, clear_window_state_doc},
    {"toggle_fullscreen", (PyCFunction)RayPy_ToggleFullscreen, METH_NOARGS, toggle_fullscreen_doc},
    {"maximize_window", (PyCFunction)RayPy_MaximizeWindow, METH_NOARGS, maximize_window_doc},
    {"minimize_window", (PyCFunction)RayPy_MinimizeWindow, METH_NOARGS, minimize_window_doc},
    {"restore_window", (PyCFunction)RayPy_RestoreWindow, METH_NOARGS, restore_window_doc},
    {"set_window_icon", (PyCFunction)RayPy_SetWindowIcon, METH_O, set_window_icon_doc},
    {"set_window_title", (PyCFunction)RayPy_SetWindowTitle, METH_O, set_window_title_doc},
    {"set_window_position", (PyCFunction)RayPy_SetWindowPosition, METH_VARARGS, set_window_position_doc},
    {"set_window_monitor", (PyCFunction)RayPy_SetWindowMonitor, METH_O, set_window_monitor_doc},
    {"set_window_min_size", (PyCFunction)(void (*)(void))RayPy_SetWindowMinSize, METH_VARARGS | METH_KEYWORDS, set_window_min_size_doc},
    {"set_window_size", (PyCFunction)(void (*)(void))RayPy_SetWindowSize, METH_VARARGS | METH_KEYWORDS, set_window_size_doc},
    {"get_window_handle", (PyCFunction)RayPy_GetWindowHandle, METH_NOARGS, get_window_handle_doc},
    {"get_screen_width", (PyCFunction)RayPy_GetScreenWidth, METH_NOARGS, get_screen_width_doc},
    {"get_screen_height", (PyCFunction)RayPy_GetScreenHeight, METH_NOARGS, get_screen_height_doc},
    {"get_monitor_count", (PyCFunction)RayPy_GetMonitorCount, METH_NOARGS, get_monitor_count_doc},
    {"get_current_monitor", (PyCFunction)RayPy_GetCurrentMonitor, METH_NOARGS, get_current_monitor_doc},
    {"get_monitor_position", (PyCFunction)RayPy_GetMonitorPosition, METH_O, get_monitor_position_doc},
    {"get_monitor_width", (PyCFunction)RayPy_GetMonitorWidth, METH_O, get_monitor_width_doc},
    {"get_monitor_height", (PyCFunction)RayPy_GetMonitorHeight, METH_O, get_monitor_height_doc},
    {"get_monitor_physical_width", (PyCFunction)RayPy_GetMonitorPhysicalWidth, METH_O, get_monitor_physical_width_doc},
    {"get_monitor_physical_height", (PyCFunction)RayPy_GetMonitorPhysicalHeight, METH_O, get_monitor_physical_height_doc},
    {"get_monitor_refresh_tate", (PyCFunction)RayPy_GetMonitorRefreshRate, METH_O, get_monitor_refresh_rate_doc},
    {"get_window_position", (PyCFunction)RayPy_GetWindowPosition, METH_NOARGS, get_window_position_doc},
    {"get_window_scale_dpi", (PyCFunction)RayPy_GetWindowScaleDPI, METH_NOARGS, get_window_scale_dpi_doc},
    {"get_monitor_name", (PyCFunction)RayPy_GetMonitorName, METH_O, get_monitor_name_doc},
    {"set_clipboard_text", (PyCFunction)RayPy_SetClipboardText, METH_O, set_clipboard_text_doc},
    {"get_clipboard_text", (PyCFunction)RayPy_GetClipboardText, METH_NOARGS, get_clipboard_text_doc},
    {"swap_screen_buffer", (PyCFunction)RayPy_SwapScreenBuffer, METH_NOARGS, swap_screen_buffer_doc},
    {"poll_input_events", (PyCFunction)RayPy_PollInputEvents, METH_NOARGS, poll_input_events_doc},
    {"wait_time", (PyCFunction)RayPy_WaitTime, METH_O, wait_time_doc},
    {"show_cursor", (PyCFunction)RayPy_ShowCursor, METH_NOARGS, show_cursor_doc},
    {"hide_cursor", (PyCFunction)RayPy_HideCursor, METH_NOARGS, hide_cursor_doc},
    {"is_cursor_hidden", (PyCFunction)RayPy_IsCursorHidden, METH_NOARGS, is_cursor_hidden_doc},
    {"enable_cursor", (PyCFunction)RayPy_EnableCursor, METH_NOARGS, enable_cursor_doc},
    {"disable_cursor", (PyCFunction)RayPy_DisableCursor, METH_NOARGS, disable_cursor_doc},
    {"is_cursor_on_screen", (PyCFunction)RayPy_IsCursorOnScreen, METH_NOARGS, is_cursor_on_screen_doc},
    {"clear_background", (PyCFunction)RayPy_ClearBackground, METH_O, clear_background_doc},
    {"begin_drawing", (PyCFunction)RayPy_BeginDrawing, METH_NOARGS, begin_drawing_doc},
    {"end_drawing", (PyCFunction)RayPy_EndDrawing, METH_NOARGS, end_drawing_doc},
    {"set_target_fps", (PyCFunction)RayPy_SetTargetFPS, METH_O, set_target_fps_doc},
    {"get_fps", (PyCFunction)RayPy_GetFPS, METH_NOARGS, get_fps_doc},
    {"get_frame_time", (PyCFunction)RayPy_GetFrameTime, METH_NOARGS, get_frame_time_doc},
    {"get_time", (PyCFunction)RayPy_GetTime, METH_NOARGS, get_time_doc},
    {"get_random_value", (PyCFunction)RayPy_GetRandomValue, METH_VARARGS, get_random_value_doc},
    {"set_random_seed", (PyCFunction)RayPy_SetRandomSeed, METH_O, set_random_seed_doc},
    {"take_screenshot", (PyCFunction)RayPy_TakeScreenshot, METH_O, take_screenshot_doc},
    {"set_config_flags", (PyCFunction)RayPy_SetConfigFlags, METH_O, set_config_flags_doc},
    {"trace_log", (PyCFunction)RayPy_TraceLog, METH_VARARGS, trace_log_doc},
    {"set_trace_log_level_doc", (PyCFunction)RayPy_SetTraceLogLevel, METH_O, set_trace_log_level_doc},
    {"open_url", (PyCFunction)RayPy_OpenURL, METH_O, open_url_doc},
    {"is_key_pressed", (PyCFunction)RayPy_IsKeyPressed, METH_O, is_key_pressed_doc},
    {"is_key_down", (PyCFunction)RayPy_IsKeyDown, METH_O, is_key_down_doc},
    {"is_key_released", (PyCFunction)RayPy_IsKeyReleased, METH_O, is_key_released_doc},
    {"is_key_up", (PyCFunction)RayPy_IsKeyUp, METH_O, is_key_up_doc},
    {"set_exit_key", (PyCFunction)RayPy_SetExitKey, METH_O, set_exit_key_doc},
    {"get_key_pressed", (PyCFunction)RayPy_GetKeyPressed, METH_NOARGS, get_key_pressed_doc},
    {"get_char_pressed", (PyCFunction)RayPy_GetCharPressed, METH_NOARGS, get_char_pressed_doc},
    {"draw_fps", (PyCFunction)RayPy_DrawFPS, METH_VARARGS, draw_fps_doc},
    {"draw_text", (PyCFunction)(void (*)(void))RayPy_DrawText, METH_VARARGS | METH_KEYWORDS, draw_text_doc},
    {NULL, NULL, 0, NULL}};

#define RayPyModule_AddColorMacro(m, c) (PyModule_AddObject((m), #c, PyObject_CallFunction((PyObject *)&RayPy_Color_Type, "bbbb", (c).r, (c).g, (c).b, (c).a)))
#define RayPyModule_AddDoubleMacro(m, d) (PyModule_AddObject((m), #d, PyFloat_FromDouble((d))))

static int
RayPy_exec(PyObject *m)
{
#define PASTER(x,y) x ## _ ## y
#define EVALUATOR(x,y)  PASTER(x,y)
#define TYPENAME(name) EVALUATOR(RayPy, EVALUATOR(name, Type))

#define ADD_TYPE_ALIAS(type, name) \
    if (PyModule_AddObject(m, name, (PyObject *)&TYPENAME(type))) { \
        Py_DECREF(&TYPENAME(type)); \
        goto error; \
    } 

#define ADD_TYPE(type) \
    if (PyType_Ready(&TYPENAME(type))) goto error; \
    Py_INCREF(&TYPENAME(type)); \
    ADD_TYPE_ALIAS(type, #type)
    
    if (PyModule_AddStringMacro(m, RAYLIB_VERSION)) goto error;
    if (PyModule_AddIntMacro(m, RAYLIB_VERSION_MAJOR)) goto error;
    if (PyModule_AddIntMacro(m, RAYLIB_VERSION_MINOR)) goto error;
    if (PyModule_AddIntMacro(m, RAYLIB_VERSION_PATCH)) goto error;

    /* Basic Defines */
    if (RayPyModule_AddDoubleMacro(m, PI)) goto error;
    if (RayPyModule_AddDoubleMacro(m, DEG2RAD)) goto error;
    if (RayPyModule_AddDoubleMacro(m, RAD2DEG)) goto error;

    /* Structures Definition */
    ADD_TYPE(Vector2);
    ADD_TYPE(Vector3);
    ADD_TYPE(Vector4);
    ADD_TYPE_ALIAS(Vector4, "Quaternion")
    ADD_TYPE(Color);
    ADD_TYPE(Rectangle);
    ADD_TYPE(Image);
    ADD_TYPE(Texture);
    ADD_TYPE_ALIAS(Texture, "Texture2D")
    ADD_TYPE_ALIAS(Texture, "TextureCubemap")

    /* Basic Colors */
    if (RayPyModule_AddColorMacro(m, LIGHTGRAY)) goto error;
    if (RayPyModule_AddColorMacro(m, GRAY)) goto error;
    if (RayPyModule_AddColorMacro(m, DARKGRAY)) goto error;
    if (RayPyModule_AddColorMacro(m, YELLOW)) goto error;
    if (RayPyModule_AddColorMacro(m, GOLD)) goto error;
    if (RayPyModule_AddColorMacro(m, ORANGE)) goto error;
    if (RayPyModule_AddColorMacro(m, PINK)) goto error;
    if (RayPyModule_AddColorMacro(m, RED)) goto error;
    if (RayPyModule_AddColorMacro(m, MAROON)) goto error;
    if (RayPyModule_AddColorMacro(m, GREEN)) goto error;
    if (RayPyModule_AddColorMacro(m, LIME)) goto error;
    if (RayPyModule_AddColorMacro(m, DARKGREEN)) goto error;
    if (RayPyModule_AddColorMacro(m, SKYBLUE)) goto error;
    if (RayPyModule_AddColorMacro(m, BLUE)) goto error;
    if (RayPyModule_AddColorMacro(m, DARKBLUE)) goto error;
    if (RayPyModule_AddColorMacro(m, PURPLE)) goto error;
    if (RayPyModule_AddColorMacro(m, VIOLET)) goto error;
    if (RayPyModule_AddColorMacro(m, DARKPURPLE)) goto error;
    if (RayPyModule_AddColorMacro(m, BEIGE)) goto error;
    if (RayPyModule_AddColorMacro(m, BROWN)) goto error;
    if (RayPyModule_AddColorMacro(m, DARKBROWN)) goto error;
    if (RayPyModule_AddColorMacro(m, WHITE)) goto error;
    if (RayPyModule_AddColorMacro(m, BLACK)) goto error;
    if (RayPyModule_AddColorMacro(m, BLANK)) goto error;
    if (RayPyModule_AddColorMacro(m, MAGENTA)) goto error;
    if (RayPyModule_AddColorMacro(m, RAYWHITE)) goto error;

    /* Enumerators Definition */
    // System/Window config flags
    if (PyModule_AddIntMacro(m, FLAG_VSYNC_HINT)) goto error;
    if (PyModule_AddIntMacro(m, FLAG_FULLSCREEN_MODE)) goto error;
    if (PyModule_AddIntMacro(m, FLAG_WINDOW_RESIZABLE)) goto error;
    if (PyModule_AddIntMacro(m, FLAG_WINDOW_UNDECORATED)) goto error;
    if (PyModule_AddIntMacro(m, FLAG_WINDOW_HIDDEN)) goto error;
    if (PyModule_AddIntMacro(m, FLAG_WINDOW_MINIMIZED)) goto error;
    if (PyModule_AddIntMacro(m, FLAG_WINDOW_MAXIMIZED)) goto error;
    if (PyModule_AddIntMacro(m, FLAG_WINDOW_UNFOCUSED)) goto error;
    if (PyModule_AddIntMacro(m, FLAG_WINDOW_TOPMOST)) goto error;
    if (PyModule_AddIntMacro(m, FLAG_WINDOW_ALWAYS_RUN)) goto error;
    if (PyModule_AddIntMacro(m, FLAG_WINDOW_TRANSPARENT)) goto error;
    if (PyModule_AddIntMacro(m, FLAG_WINDOW_HIGHDPI)) goto error;
    if (PyModule_AddIntMacro(m, FLAG_WINDOW_MOUSE_PASSTHROUGH)) goto error;
    if (PyModule_AddIntMacro(m, FLAG_BORDERLESS_WINDOWED_MODE)) goto error;
    if (PyModule_AddIntMacro(m, FLAG_MSAA_4X_HINT)) goto error;
    if (PyModule_AddIntMacro(m, FLAG_INTERLACED_HINT)) goto error;
    // Trace log level
    if (PyModule_AddIntMacro(m, LOG_ALL)) goto error;
    if (PyModule_AddIntMacro(m, LOG_TRACE)) goto error;
    if (PyModule_AddIntMacro(m, LOG_DEBUG)) goto error;
    if (PyModule_AddIntMacro(m, LOG_INFO)) goto error;
    if (PyModule_AddIntMacro(m, LOG_WARNING)) goto error;
    if (PyModule_AddIntMacro(m, LOG_ERROR)) goto error;
    if (PyModule_AddIntMacro(m, LOG_FATAL)) goto error;
    if (PyModule_AddIntMacro(m, LOG_NONE)) goto error;
    // Keyboard keys (US keyboard layout)
    if (PyModule_AddIntMacro(m, KEY_NULL)) goto error;
    if (PyModule_AddIntMacro(m, KEY_APOSTROPHE)) goto error;
    if (PyModule_AddIntMacro(m, KEY_COMMA)) goto error;
    if (PyModule_AddIntMacro(m, KEY_MINUS)) goto error;
    if (PyModule_AddIntMacro(m, KEY_PERIOD)) goto error;
    if (PyModule_AddIntMacro(m, KEY_SLASH)) goto error;
    if (PyModule_AddIntMacro(m, KEY_ZERO)) goto error;
    if (PyModule_AddIntMacro(m, KEY_ONE)) goto error;
    if (PyModule_AddIntMacro(m, KEY_TWO)) goto error;
    if (PyModule_AddIntMacro(m, KEY_THREE)) goto error;
    if (PyModule_AddIntMacro(m, KEY_FOUR)) goto error;
    if (PyModule_AddIntMacro(m, KEY_FIVE)) goto error;
    if (PyModule_AddIntMacro(m, KEY_SIX)) goto error;
    if (PyModule_AddIntMacro(m, KEY_SEVEN)) goto error;
    if (PyModule_AddIntMacro(m, KEY_EIGHT)) goto error;
    if (PyModule_AddIntMacro(m, KEY_NINE)) goto error;
    if (PyModule_AddIntMacro(m, KEY_SEMICOLON)) goto error;
    if (PyModule_AddIntMacro(m, KEY_EQUAL)) goto error;
    if (PyModule_AddIntMacro(m, KEY_A)) goto error;
    if (PyModule_AddIntMacro(m, KEY_B)) goto error;
    if (PyModule_AddIntMacro(m, KEY_C)) goto error;
    if (PyModule_AddIntMacro(m, KEY_D)) goto error;
    if (PyModule_AddIntMacro(m, KEY_E)) goto error;
    if (PyModule_AddIntMacro(m, KEY_F)) goto error;
    if (PyModule_AddIntMacro(m, KEY_G)) goto error;
    if (PyModule_AddIntMacro(m, KEY_H)) goto error;
    if (PyModule_AddIntMacro(m, KEY_I)) goto error;
    if (PyModule_AddIntMacro(m, KEY_J)) goto error;
    if (PyModule_AddIntMacro(m, KEY_K)) goto error;
    if (PyModule_AddIntMacro(m, KEY_L)) goto error;
    if (PyModule_AddIntMacro(m, KEY_M)) goto error;
    if (PyModule_AddIntMacro(m, KEY_N)) goto error;
    if (PyModule_AddIntMacro(m, KEY_O)) goto error;
    if (PyModule_AddIntMacro(m, KEY_P)) goto error;
    if (PyModule_AddIntMacro(m, KEY_Q)) goto error;
    if (PyModule_AddIntMacro(m, KEY_R)) goto error;
    if (PyModule_AddIntMacro(m, KEY_S)) goto error;
    if (PyModule_AddIntMacro(m, KEY_T)) goto error;
    if (PyModule_AddIntMacro(m, KEY_U)) goto error;
    if (PyModule_AddIntMacro(m, KEY_V)) goto error;
    if (PyModule_AddIntMacro(m, KEY_W)) goto error;
    if (PyModule_AddIntMacro(m, KEY_X)) goto error;
    if (PyModule_AddIntMacro(m, KEY_Y)) goto error;
    if (PyModule_AddIntMacro(m, KEY_Z)) goto error;
    if (PyModule_AddIntMacro(m, KEY_LEFT_BRACKET)) goto error;
    if (PyModule_AddIntMacro(m, KEY_BACKSLASH)) goto error;
    if (PyModule_AddIntMacro(m, KEY_RIGHT_BRACKET)) goto error;
    if (PyModule_AddIntMacro(m, KEY_GRAVE)) goto error;
    if (PyModule_AddIntMacro(m, KEY_SPACE)) goto error;
    if (PyModule_AddIntMacro(m, KEY_ESCAPE)) goto error;
    if (PyModule_AddIntMacro(m, KEY_ENTER)) goto error;
    if (PyModule_AddIntMacro(m, KEY_TAB)) goto error;
    if (PyModule_AddIntMacro(m, KEY_BACKSPACE)) goto error;
    if (PyModule_AddIntMacro(m, KEY_INSERT)) goto error;
    if (PyModule_AddIntMacro(m, KEY_DELETE)) goto error;
    if (PyModule_AddIntMacro(m, KEY_RIGHT)) goto error;
    if (PyModule_AddIntMacro(m, KEY_LEFT)) goto error;
    if (PyModule_AddIntMacro(m, KEY_DOWN)) goto error;
    if (PyModule_AddIntMacro(m, KEY_UP)) goto error;
    if (PyModule_AddIntMacro(m, KEY_PAGE_UP)) goto error;
    if (PyModule_AddIntMacro(m, KEY_PAGE_DOWN)) goto error;
    if (PyModule_AddIntMacro(m, KEY_HOME)) goto error;
    if (PyModule_AddIntMacro(m, KEY_END)) goto error;
    if (PyModule_AddIntMacro(m, KEY_CAPS_LOCK)) goto error;
    if (PyModule_AddIntMacro(m, KEY_SCROLL_LOCK)) goto error;
    if (PyModule_AddIntMacro(m, KEY_NUM_LOCK)) goto error;
    if (PyModule_AddIntMacro(m, KEY_PRINT_SCREEN)) goto error;
    if (PyModule_AddIntMacro(m, KEY_PAUSE)) goto error;
    if (PyModule_AddIntMacro(m, KEY_F1)) goto error;
    if (PyModule_AddIntMacro(m, KEY_F2)) goto error;
    if (PyModule_AddIntMacro(m, KEY_F3)) goto error;
    if (PyModule_AddIntMacro(m, KEY_F4)) goto error;
    if (PyModule_AddIntMacro(m, KEY_F5)) goto error;
    if (PyModule_AddIntMacro(m, KEY_F6)) goto error;
    if (PyModule_AddIntMacro(m, KEY_F7)) goto error;
    if (PyModule_AddIntMacro(m, KEY_F8)) goto error;
    if (PyModule_AddIntMacro(m, KEY_F9)) goto error;
    if (PyModule_AddIntMacro(m, KEY_F10)) goto error;
    if (PyModule_AddIntMacro(m, KEY_F11)) goto error;
    if (PyModule_AddIntMacro(m, KEY_F12)) goto error;
    if (PyModule_AddIntMacro(m, KEY_LEFT_SHIFT)) goto error;
    if (PyModule_AddIntMacro(m, KEY_LEFT_CONTROL)) goto error;
    if (PyModule_AddIntMacro(m, KEY_LEFT_ALT)) goto error;
    if (PyModule_AddIntMacro(m, KEY_LEFT_SUPER)) goto error;
    if (PyModule_AddIntMacro(m, KEY_RIGHT_SHIFT)) goto error;
    if (PyModule_AddIntMacro(m, KEY_RIGHT_CONTROL)) goto error;
    if (PyModule_AddIntMacro(m, KEY_RIGHT_ALT)) goto error;
    if (PyModule_AddIntMacro(m, KEY_RIGHT_SUPER)) goto error;
    if (PyModule_AddIntMacro(m, KEY_KB_MENU)) goto error;
    if (PyModule_AddIntMacro(m, KEY_KP_0)) goto error;
    if (PyModule_AddIntMacro(m, KEY_KP_1)) goto error;
    if (PyModule_AddIntMacro(m, KEY_KP_2)) goto error;
    if (PyModule_AddIntMacro(m, KEY_KP_3)) goto error;
    if (PyModule_AddIntMacro(m, KEY_KP_4)) goto error;
    if (PyModule_AddIntMacro(m, KEY_KP_5)) goto error;
    if (PyModule_AddIntMacro(m, KEY_KP_6)) goto error;
    if (PyModule_AddIntMacro(m, KEY_KP_7)) goto error;
    if (PyModule_AddIntMacro(m, KEY_KP_8)) goto error;
    if (PyModule_AddIntMacro(m, KEY_KP_9)) goto error;
    if (PyModule_AddIntMacro(m, KEY_KP_DECIMAL)) goto error;
    if (PyModule_AddIntMacro(m, KEY_KP_DIVIDE)) goto error;
    if (PyModule_AddIntMacro(m, KEY_KP_MULTIPLY)) goto error;
    if (PyModule_AddIntMacro(m, KEY_KP_SUBTRACT)) goto error;
    if (PyModule_AddIntMacro(m, KEY_KP_ADD)) goto error;
    if (PyModule_AddIntMacro(m, KEY_KP_ENTER)) goto error;
    if (PyModule_AddIntMacro(m, KEY_KP_EQUAL)) goto error;
    if (PyModule_AddIntMacro(m, KEY_BACK)) goto error;
    if (PyModule_AddIntMacro(m, KEY_MENU)) goto error;
    if (PyModule_AddIntMacro(m, KEY_VOLUME_UP)) goto error;
    if (PyModule_AddIntMacro(m, KEY_VOLUME_DOWN)) goto error;
    // Add backwards compatibility support for deprecated names
    if (PyModule_AddIntMacro(m, MOUSE_LEFT_BUTTON)) goto error;
    if (PyModule_AddIntMacro(m, MOUSE_RIGHT_BUTTON)) goto error;
    if (PyModule_AddIntMacro(m, MOUSE_MIDDLE_BUTTON)) goto error;
    // Mouse buttons
    if (PyModule_AddIntMacro(m, MOUSE_BUTTON_LEFT)) goto error;
    if (PyModule_AddIntMacro(m, MOUSE_BUTTON_RIGHT)) goto error;
    if (PyModule_AddIntMacro(m, MOUSE_BUTTON_MIDDLE)) goto error;
    if (PyModule_AddIntMacro(m, MOUSE_BUTTON_SIDE)) goto error;
    if (PyModule_AddIntMacro(m, MOUSE_BUTTON_EXTRA)) goto error;
    if (PyModule_AddIntMacro(m, MOUSE_BUTTON_FORWARD)) goto error;
    if (PyModule_AddIntMacro(m, MOUSE_BUTTON_BACK)) goto error;
    // Mouse cursor
    if (PyModule_AddIntMacro(m, MOUSE_CURSOR_DEFAULT)) goto error;
    if (PyModule_AddIntMacro(m, MOUSE_CURSOR_ARROW)) goto error;
    if (PyModule_AddIntMacro(m, MOUSE_CURSOR_IBEAM)) goto error;
    if (PyModule_AddIntMacro(m, MOUSE_CURSOR_CROSSHAIR)) goto error;
    if (PyModule_AddIntMacro(m, MOUSE_CURSOR_POINTING_HAND)) goto error;
    if (PyModule_AddIntMacro(m, MOUSE_CURSOR_RESIZE_EW)) goto error;
    if (PyModule_AddIntMacro(m, MOUSE_CURSOR_RESIZE_NS)) goto error;
    if (PyModule_AddIntMacro(m, MOUSE_CURSOR_RESIZE_NWSE)) goto error;
    if (PyModule_AddIntMacro(m, MOUSE_CURSOR_RESIZE_NESW)) goto error;
    if (PyModule_AddIntMacro(m, MOUSE_CURSOR_RESIZE_ALL)) goto error;
    if (PyModule_AddIntMacro(m, MOUSE_CURSOR_NOT_ALLOWED)) goto error;
    // Gamepad buttons
    if (PyModule_AddIntMacro(m, GAMEPAD_BUTTON_UNKNOWN)) goto error;
    if (PyModule_AddIntMacro(m, GAMEPAD_BUTTON_LEFT_FACE_UP)) goto error;
    if (PyModule_AddIntMacro(m, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) goto error;
    if (PyModule_AddIntMacro(m, GAMEPAD_BUTTON_LEFT_FACE_DOWN)) goto error;
    if (PyModule_AddIntMacro(m, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) goto error;
    if (PyModule_AddIntMacro(m, GAMEPAD_BUTTON_RIGHT_FACE_UP)) goto error;
    if (PyModule_AddIntMacro(m, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)) goto error;
    if (PyModule_AddIntMacro(m, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) goto error;
    if (PyModule_AddIntMacro(m, GAMEPAD_BUTTON_RIGHT_FACE_LEFT)) goto error;
    if (PyModule_AddIntMacro(m, GAMEPAD_BUTTON_LEFT_TRIGGER_1)) goto error;
    if (PyModule_AddIntMacro(m, GAMEPAD_BUTTON_LEFT_TRIGGER_2)) goto error;
    if (PyModule_AddIntMacro(m, GAMEPAD_BUTTON_RIGHT_TRIGGER_1)) goto error;
    if (PyModule_AddIntMacro(m, GAMEPAD_BUTTON_RIGHT_TRIGGER_2)) goto error;
    if (PyModule_AddIntMacro(m, GAMEPAD_BUTTON_MIDDLE_LEFT)) goto error;
    if (PyModule_AddIntMacro(m, GAMEPAD_BUTTON_MIDDLE)) goto error;
    if (PyModule_AddIntMacro(m, GAMEPAD_BUTTON_MIDDLE_RIGHT)) goto error;
    if (PyModule_AddIntMacro(m, GAMEPAD_BUTTON_LEFT_THUMB)) goto error;
    if (PyModule_AddIntMacro(m, GAMEPAD_BUTTON_RIGHT_THUMB)) goto error;
    // Gamepad axis
    if (PyModule_AddIntMacro(m, GAMEPAD_AXIS_LEFT_X)) goto error;
    if (PyModule_AddIntMacro(m, GAMEPAD_AXIS_LEFT_Y)) goto error;
    if (PyModule_AddIntMacro(m, GAMEPAD_AXIS_RIGHT_X)) goto error;
    if (PyModule_AddIntMacro(m, GAMEPAD_AXIS_RIGHT_Y)) goto error;
    if (PyModule_AddIntMacro(m, GAMEPAD_AXIS_LEFT_TRIGGER)) goto error;
    if (PyModule_AddIntMacro(m, GAMEPAD_AXIS_RIGHT_TRIGGER)) goto error;
    // Material map index
    if (PyModule_AddIntMacro(m, MATERIAL_MAP_ALBEDO)) goto error;
    if (PyModule_AddIntMacro(m, MATERIAL_MAP_METALNESS)) goto error;
    if (PyModule_AddIntMacro(m, MATERIAL_MAP_NORMAL)) goto error;
    if (PyModule_AddIntMacro(m, MATERIAL_MAP_ROUGHNESS)) goto error;
    if (PyModule_AddIntMacro(m, MATERIAL_MAP_OCCLUSION)) goto error;
    if (PyModule_AddIntMacro(m, MATERIAL_MAP_EMISSION)) goto error;
    if (PyModule_AddIntMacro(m, MATERIAL_MAP_HEIGHT)) goto error;
    if (PyModule_AddIntMacro(m, MATERIAL_MAP_CUBEMAP)) goto error;
    if (PyModule_AddIntMacro(m, MATERIAL_MAP_IRRADIANCE)) goto error;
    if (PyModule_AddIntMacro(m, MATERIAL_MAP_PREFILTER)) goto error;
    if (PyModule_AddIntMacro(m, MATERIAL_MAP_BRDF)) goto error;
    if (PyModule_AddIntMacro(m, MATERIAL_MAP_DIFFUSE)) goto error;
    if (PyModule_AddIntMacro(m, MATERIAL_MAP_SPECULAR)) goto error;
    // Shader location index
    if (PyModule_AddIntMacro(m, SHADER_LOC_VERTEX_POSITION)) goto error;
    if (PyModule_AddIntMacro(m, SHADER_LOC_VERTEX_TEXCOORD01)) goto error;
    if (PyModule_AddIntMacro(m, SHADER_LOC_VERTEX_TEXCOORD02)) goto error;
    if (PyModule_AddIntMacro(m, SHADER_LOC_VERTEX_NORMAL)) goto error;
    if (PyModule_AddIntMacro(m, SHADER_LOC_VERTEX_TANGENT)) goto error;
    if (PyModule_AddIntMacro(m, SHADER_LOC_VERTEX_COLOR)) goto error;
    if (PyModule_AddIntMacro(m, SHADER_LOC_MATRIX_MVP)) goto error;
    if (PyModule_AddIntMacro(m, SHADER_LOC_MATRIX_VIEW)) goto error;
    if (PyModule_AddIntMacro(m, SHADER_LOC_MATRIX_PROJECTION)) goto error;
    if (PyModule_AddIntMacro(m, SHADER_LOC_MATRIX_MODEL)) goto error;
    if (PyModule_AddIntMacro(m, SHADER_LOC_MATRIX_NORMAL)) goto error;
    if (PyModule_AddIntMacro(m, SHADER_LOC_VECTOR_VIEW)) goto error;
    if (PyModule_AddIntMacro(m, SHADER_LOC_COLOR_DIFFUSE)) goto error;
    if (PyModule_AddIntMacro(m, SHADER_LOC_COLOR_SPECULAR)) goto error;
    if (PyModule_AddIntMacro(m, SHADER_LOC_COLOR_AMBIENT)) goto error;
    if (PyModule_AddIntMacro(m, SHADER_LOC_MAP_ALBEDO)) goto error;
    if (PyModule_AddIntMacro(m, SHADER_LOC_MAP_METALNESS)) goto error;
    if (PyModule_AddIntMacro(m, SHADER_LOC_MAP_NORMAL)) goto error;
    if (PyModule_AddIntMacro(m, SHADER_LOC_MAP_ROUGHNESS)) goto error;
    if (PyModule_AddIntMacro(m, SHADER_LOC_MAP_OCCLUSION)) goto error;
    if (PyModule_AddIntMacro(m, SHADER_LOC_MAP_EMISSION)) goto error;
    if (PyModule_AddIntMacro(m, SHADER_LOC_MAP_HEIGHT)) goto error;
    if (PyModule_AddIntMacro(m, SHADER_LOC_MAP_CUBEMAP)) goto error;
    if (PyModule_AddIntMacro(m, SHADER_LOC_MAP_IRRADIANCE)) goto error;
    if (PyModule_AddIntMacro(m, SHADER_LOC_MAP_PREFILTER)) goto error;
    if (PyModule_AddIntMacro(m, SHADER_LOC_MAP_BRDF)) goto error;
    if (PyModule_AddIntMacro(m, SHADER_LOC_MAP_DIFFUSE)) goto error;
    if (PyModule_AddIntMacro(m, SHADER_LOC_MAP_SPECULAR)) goto error;
    // Shader uniform data type
    if (PyModule_AddIntMacro(m, SHADER_UNIFORM_FLOAT)) goto error;
    if (PyModule_AddIntMacro(m, SHADER_UNIFORM_VEC2)) goto error;
    if (PyModule_AddIntMacro(m, SHADER_UNIFORM_VEC3)) goto error;
    if (PyModule_AddIntMacro(m, SHADER_UNIFORM_VEC4)) goto error;
    if (PyModule_AddIntMacro(m, SHADER_UNIFORM_INT)) goto error;
    if (PyModule_AddIntMacro(m, SHADER_UNIFORM_IVEC2)) goto error;
    if (PyModule_AddIntMacro(m, SHADER_UNIFORM_IVEC3)) goto error;
    if (PyModule_AddIntMacro(m, SHADER_UNIFORM_IVEC4)) goto error;
    if (PyModule_AddIntMacro(m, SHADER_UNIFORM_SAMPLER2D)) goto error;
    // Shader attribute data types
    if (PyModule_AddIntMacro(m, SHADER_ATTRIB_FLOAT)) goto error;
    if (PyModule_AddIntMacro(m, SHADER_ATTRIB_VEC2)) goto error;
    if (PyModule_AddIntMacro(m, SHADER_ATTRIB_VEC3)) goto error;
    if (PyModule_AddIntMacro(m, SHADER_ATTRIB_VEC4)) goto error;
    // Pixel formats
    if (PyModule_AddIntMacro(m, PIXELFORMAT_UNCOMPRESSED_GRAYSCALE)) goto error;
    if (PyModule_AddIntMacro(m, PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA)) goto error;
    if (PyModule_AddIntMacro(m, PIXELFORMAT_UNCOMPRESSED_R5G6B5)) goto error;
    if (PyModule_AddIntMacro(m, PIXELFORMAT_UNCOMPRESSED_R8G8B8)) goto error;
    if (PyModule_AddIntMacro(m, PIXELFORMAT_UNCOMPRESSED_R5G5B5A1)) goto error;
    if (PyModule_AddIntMacro(m, PIXELFORMAT_UNCOMPRESSED_R4G4B4A4)) goto error;
    if (PyModule_AddIntMacro(m, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8)) goto error;
    if (PyModule_AddIntMacro(m, PIXELFORMAT_UNCOMPRESSED_R32)) goto error;
    if (PyModule_AddIntMacro(m, PIXELFORMAT_UNCOMPRESSED_R32G32B32)) goto error;
    if (PyModule_AddIntMacro(m, PIXELFORMAT_UNCOMPRESSED_R32G32B32A32)) goto error;
    if (PyModule_AddIntMacro(m, PIXELFORMAT_UNCOMPRESSED_R16)) goto error;
    if (PyModule_AddIntMacro(m, PIXELFORMAT_UNCOMPRESSED_R16G16B16)) goto error;
    if (PyModule_AddIntMacro(m, PIXELFORMAT_UNCOMPRESSED_R16G16B16A16)) goto error;
    if (PyModule_AddIntMacro(m, PIXELFORMAT_COMPRESSED_DXT1_RGB)) goto error;
    if (PyModule_AddIntMacro(m, PIXELFORMAT_COMPRESSED_DXT1_RGBA)) goto error;
    if (PyModule_AddIntMacro(m, PIXELFORMAT_COMPRESSED_DXT3_RGBA)) goto error;
    if (PyModule_AddIntMacro(m, PIXELFORMAT_COMPRESSED_DXT5_RGBA)) goto error;
    if (PyModule_AddIntMacro(m, PIXELFORMAT_COMPRESSED_ETC1_RGB)) goto error;
    if (PyModule_AddIntMacro(m, PIXELFORMAT_COMPRESSED_ETC2_RGB)) goto error;
    if (PyModule_AddIntMacro(m, PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA)) goto error;
    if (PyModule_AddIntMacro(m, PIXELFORMAT_COMPRESSED_PVRT_RGB)) goto error;
    if (PyModule_AddIntMacro(m, PIXELFORMAT_COMPRESSED_PVRT_RGBA)) goto error;
    if (PyModule_AddIntMacro(m, PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA)) goto error;
    if (PyModule_AddIntMacro(m, PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA)) goto error;
    // Texture parameters: filter mode
    if (PyModule_AddIntMacro(m, TEXTURE_FILTER_POINT)) goto error;
    if (PyModule_AddIntMacro(m, TEXTURE_FILTER_BILINEAR)) goto error;
    if (PyModule_AddIntMacro(m, TEXTURE_FILTER_TRILINEAR)) goto error;
    if (PyModule_AddIntMacro(m, TEXTURE_FILTER_ANISOTROPIC_4X)) goto error;
    if (PyModule_AddIntMacro(m, TEXTURE_FILTER_ANISOTROPIC_8X)) goto error;
    if (PyModule_AddIntMacro(m, TEXTURE_FILTER_ANISOTROPIC_16X)) goto error;
    // Texture parameters: wrap mode
    if (PyModule_AddIntMacro(m, TEXTURE_WRAP_REPEAT)) goto error;
    if (PyModule_AddIntMacro(m, TEXTURE_WRAP_CLAMP)) goto error;
    if (PyModule_AddIntMacro(m, TEXTURE_WRAP_MIRROR_REPEAT)) goto error;
    if (PyModule_AddIntMacro(m, TEXTURE_WRAP_MIRROR_CLAMP)) goto error;
    // Cubemap layouts
    if (PyModule_AddIntMacro(m, CUBEMAP_LAYOUT_AUTO_DETECT)) goto error;
    if (PyModule_AddIntMacro(m, CUBEMAP_LAYOUT_LINE_VERTICAL)) goto error;
    if (PyModule_AddIntMacro(m, CUBEMAP_LAYOUT_LINE_HORIZONTAL)) goto error;
    if (PyModule_AddIntMacro(m, CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR)) goto error;
    if (PyModule_AddIntMacro(m, CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE)) goto error;
    if (PyModule_AddIntMacro(m, CUBEMAP_LAYOUT_PANORAMA)) goto error;
    // Font type, defines generation method
    if (PyModule_AddIntMacro(m, FONT_DEFAULT)) goto error;
    if (PyModule_AddIntMacro(m, FONT_BITMAP)) goto error;
    if (PyModule_AddIntMacro(m, FONT_SDF)) goto error;
    // Color blending modes (pre-defined)
    if (PyModule_AddIntMacro(m, BLEND_ALPHA)) goto error;
    if (PyModule_AddIntMacro(m, BLEND_ADDITIVE)) goto error;
    if (PyModule_AddIntMacro(m, BLEND_MULTIPLIED)) goto error;
    if (PyModule_AddIntMacro(m, BLEND_ADD_COLORS)) goto error;
    if (PyModule_AddIntMacro(m, BLEND_SUBTRACT_COLORS)) goto error;
    if (PyModule_AddIntMacro(m, BLEND_ALPHA_PREMULTIPLY)) goto error;
    if (PyModule_AddIntMacro(m, BLEND_CUSTOM)) goto error;
    if (PyModule_AddIntMacro(m, BLEND_CUSTOM_SEPARATE)) goto error;
    // Gesture
    if (PyModule_AddIntMacro(m, GESTURE_NONE)) goto error;
    if (PyModule_AddIntMacro(m, GESTURE_TAP)) goto error;
    if (PyModule_AddIntMacro(m, GESTURE_DOUBLETAP)) goto error;
    if (PyModule_AddIntMacro(m, GESTURE_HOLD)) goto error;
    if (PyModule_AddIntMacro(m, GESTURE_DRAG)) goto error;
    if (PyModule_AddIntMacro(m, GESTURE_SWIPE_RIGHT)) goto error;
    if (PyModule_AddIntMacro(m, GESTURE_SWIPE_LEFT)) goto error;
    if (PyModule_AddIntMacro(m, GESTURE_SWIPE_UP)) goto error;
    if (PyModule_AddIntMacro(m, GESTURE_SWIPE_DOWN)) goto error;
    if (PyModule_AddIntMacro(m, GESTURE_PINCH_IN)) goto error;
    if (PyModule_AddIntMacro(m, GESTURE_PINCH_OUT)) goto error;
    // Camera system modes
    if (PyModule_AddIntMacro(m, CAMERA_CUSTOM)) goto error;
    if (PyModule_AddIntMacro(m, CAMERA_FREE)) goto error;
    if (PyModule_AddIntMacro(m, CAMERA_ORBITAL)) goto error;
    if (PyModule_AddIntMacro(m, CAMERA_FIRST_PERSON)) goto error;
    if (PyModule_AddIntMacro(m, CAMERA_THIRD_PERSON)) goto error;
    // Camera projection
    if (PyModule_AddIntMacro(m, CAMERA_PERSPECTIVE)) goto error;
    if (PyModule_AddIntMacro(m, CAMERA_ORTHOGRAPHIC)) goto error;
    // N-patch layout
    if (PyModule_AddIntMacro(m, NPATCH_NINE_PATCH)) goto error;
    if (PyModule_AddIntMacro(m, NPATCH_THREE_PATCH_VERTICAL)) goto error;
    if (PyModule_AddIntMacro(m, NPATCH_THREE_PATCH_HORIZONTAL)) goto error;

    return 0;

error:
    Py_XDECREF(m);
    return -1;
}

int
RayPy_clear(PyObject *Py_UNUSED(self))
{
    if (IsWindowReady())
        CloseWindow();
    return 0;
}

static struct PyModuleDef_Slot RayPy_slots[] = {
    {Py_mod_exec, RayPy_exec},
    {0, NULL},
};

static struct PyModuleDef RayPy_module = {
    PyModuleDef_HEAD_INIT,
    .m_name = "raypy",
    .m_doc = "CPython native bindings for Raylib",
    .m_size = 0,
    .m_methods = raypymethods,
    .m_slots = RayPy_slots,
    .m_clear = RayPy_clear,
};

PyMODINIT_FUNC
PyInit_raypy(void)
{
    return PyModuleDef_Init(&RayPy_module);
}

/* for some reason old versions of setuptools/distutils require
  'PyInit___init__' to be present when building on win32 if
  the extension name is 'xx.__init__'. */
PyMODINIT_FUNC
PyInit___init__(void)
{
    return PyInit_raypy();
}

#ifdef __cplusplus
};
#endif
