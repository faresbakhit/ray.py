#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <raylib.h>
#include <stdint.h>
#include <stdio.h>
#include <structmember.h>

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

typedef struct {
    PyObject_HEAD double x;
    double y;
} RayPy_Vector2Object;

static void
RayPy_Vector2_dealloc(RayPy_Vector2Object *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *
RayPy_Vector2_repr(RayPy_Vector2Object *self)
{
    char buf[64];
    PyOS_snprintf(buf, sizeof(buf), "<Vector2(%g, %g)>", self->x, self->y);
    return PyUnicode_FromString(buf);
}

static PyObject *
RayPy_Vector2_richcompare(RayPy_Vector2Object *self, RayPy_Vector2Object *other, int op)
{
    switch (op) {
    case Py_EQ:
        return PyBool_FromLong(self->x == other->x && self->y == other->y);
    case Py_NE:
        return PyBool_FromLong(self->x != other->x && self->y != other->y);
    default:
        Py_RETURN_NOTIMPLEMENTED;
    }
}

static PyObject *
RayPy_Vector2_get_x(RayPy_Vector2Object *self, void *Py_UNUSED(closure))
{
    return PyLong_FromLong(self->x);
}

static int
RayPy_Vector2_set_x(RayPy_Vector2Object *self, PyObject *value, void *Py_UNUSED(closure))
{
    double x = PyFloat_AsDouble(value);
    if (PyErr_Occurred()) {
        if (PyErr_ExceptionMatches(PyExc_TypeError)) {
            PyErr_Clear();
            PyErr_Format(PyExc_TypeError, "Vector2.x must be float, got %s",
                         Py_TYPE(value)->tp_name);
        }
        return -1;
    }
    self->x = x;
    return 0;
}

static PyObject *
RayPy_Vector2_get_y(RayPy_Vector2Object *self, void *Py_UNUSED(closure))
{
    return PyLong_FromLong(self->y);
}

static int
RayPy_Vector2_set_y(RayPy_Vector2Object *self, PyObject *value, void *Py_UNUSED(closure))
{
    double y = PyFloat_AsDouble(value);
    if (PyErr_Occurred()) {
        if (PyErr_ExceptionMatches(PyExc_TypeError)) {
            PyErr_Clear();
            PyErr_Format(PyExc_TypeError, "Vector2.y must be float, got %s",
                         Py_TYPE(value)->tp_name);
        }
        return -1;
    }
    self->y = y;
    return 0;
}

static PyGetSetDef RayPy_Vector2_getset[] = {
    {"x", (getter)RayPy_Vector2_get_x, (setter)RayPy_Vector2_set_x, NULL, NULL},
    {"y", (getter)RayPy_Vector2_get_y, (setter)RayPy_Vector2_set_y, NULL, NULL},
    {NULL}};

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
    PyObject *xobj = NULL, *yobj = NULL;
    if (!PyArg_ParseTuple(args, "|OO", &xobj, &yobj)) {
        return -1;
    }
    if (xobj) {
        double x = PyFloat_AsDouble(xobj);
        if (PyErr_Occurred()) {
            return -1;
        }
        self->x = x;
        if (!yobj) {
            self->y = x;
        }
    }
    if (yobj) {
        double y = PyFloat_AsDouble(yobj);
        if (PyErr_Occurred()) {
            return -1;
        }
        self->y = y;
    }
    return 0;
}

static PyTypeObject RayPy_Vector2_Type = {
    PyVarObject_HEAD_INIT(NULL, 0).tp_name = "raypy.Vector2",
    .tp_basicsize = sizeof(RayPy_Vector2Object),
    .tp_itemsize = 0,
    .tp_dealloc = (destructor)RayPy_Vector2_dealloc,
    .tp_repr = (reprfunc)RayPy_Vector2_repr,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_doc = "Vector2 type",
    .tp_richcompare = (richcmpfunc)RayPy_Vector2_richcompare,
    .tp_getset = RayPy_Vector2_getset,
    .tp_init = (initproc)RayPy_Vector2_init,
    .tp_new = (newfunc)RayPy_Vector2_new,
};

typedef struct {
    PyObject_HEAD double x;
    double y;
    double z;
} RayPy_Vector3Object;

static void
RayPy_Vector3_dealloc(RayPy_Vector3Object *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *
RayPy_Vector3_repr(RayPy_Vector3Object *self)
{
    char buf[91];
    PyOS_snprintf(buf, sizeof(buf), "<Vector3(%g, %g, %g)>", self->x, self->y, self->z);
    return PyUnicode_FromString(buf);
}

static PyObject *
RayPy_Vector3_richcompare(RayPy_Vector3Object *self, RayPy_Vector3Object *other, int op)
{
    switch (op) {
    case Py_EQ:
        return PyBool_FromLong(self->x == other->x && self->y == other->y &&
                               self->z == other->z);
    case Py_NE:
        return PyBool_FromLong(self->x != other->x && self->y != other->y &&
                               self->z != other->z);
    default:
        Py_RETURN_NOTIMPLEMENTED;
    }
}

static PyObject *
RayPy_Vector3_get_x(RayPy_Vector3Object *self, void *Py_UNUSED(closure))
{
    return PyLong_FromLong(self->x);
}

static int
RayPy_Vector3_set_x(RayPy_Vector3Object *self, PyObject *value, void *Py_UNUSED(closure))
{
    double x = PyFloat_AsDouble(value);
    if (PyErr_Occurred()) {
        if (PyErr_ExceptionMatches(PyExc_TypeError)) {
            PyErr_Clear();
            PyErr_Format(PyExc_TypeError, "Vector3.x must be float, got %s",
                         Py_TYPE(value)->tp_name);
        }
        return -1;
    }
    self->x = x;
    return 0;
}

static PyObject *
RayPy_Vector3_get_y(RayPy_Vector3Object *self, void *Py_UNUSED(closure))
{
    return PyLong_FromLong(self->y);
}

static int
RayPy_Vector3_set_y(RayPy_Vector3Object *self, PyObject *value, void *Py_UNUSED(closure))
{
    double y = PyFloat_AsDouble(value);
    if (PyErr_Occurred()) {
        if (PyErr_ExceptionMatches(PyExc_TypeError)) {
            PyErr_Clear();
            PyErr_Format(PyExc_TypeError, "Vector3.y must be float, got %s",
                         Py_TYPE(value)->tp_name);
        }
        return -1;
    }
    self->y = y;
    return 0;
}

static PyObject *
RayPy_Vector3_get_z(RayPy_Vector3Object *self, void *Py_UNUSED(closure))
{
    return PyLong_FromLong(self->z);
}

static int
RayPy_Vector3_set_z(RayPy_Vector3Object *self, PyObject *value, void *Py_UNUSED(closure))
{
    double z = PyFloat_AsDouble(value);
    if (PyErr_Occurred()) {
        if (PyErr_ExceptionMatches(PyExc_TypeError)) {
            PyErr_Clear();
            PyErr_Format(PyExc_TypeError, "Vector3.z must be float, got %s",
                         Py_TYPE(value)->tp_name);
        }
        return -1;
    }
    self->z = z;
    return 0;
}

static PyGetSetDef RayPy_Vector3_getset[] = {
    {"x", (getter)RayPy_Vector3_get_x, (setter)RayPy_Vector3_set_x, NULL, NULL},
    {"y", (getter)RayPy_Vector3_get_y, (setter)RayPy_Vector3_set_y, NULL, NULL},
    {"z", (getter)RayPy_Vector3_get_z, (setter)RayPy_Vector3_set_z, NULL, NULL},
    {NULL}};

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
    PyObject *xobj = NULL, *yobj = NULL, *zobj = NULL;
    if (!PyArg_ParseTuple(args, "|OOO", &xobj, &yobj, &zobj)) {
        return -1;
    }
    if (xobj) {
        double x = PyFloat_AsDouble(xobj);
        if (PyErr_Occurred()) {
            return -1;
        }
        self->x = x;
        if (!yobj) {
            self->y = x;
            self->z = x;
        }
    }
    if (yobj) {
        double y = PyFloat_AsDouble(yobj);
        if (PyErr_Occurred()) {
            return -1;
        }
        self->y = y;
    }
    if (zobj) {
        double z = PyFloat_AsDouble(zobj);
        if (PyErr_Occurred()) {
            return -1;
        }
        self->z = z;
    }
    return 0;
}

static PyTypeObject RayPy_Vector3_Type = {
    PyVarObject_HEAD_INIT(NULL, 0).tp_name = "raypy.Vector3",
    .tp_basicsize = sizeof(RayPy_Vector3Object),
    .tp_itemsize = 0,
    .tp_dealloc = (destructor)RayPy_Vector3_dealloc,
    .tp_repr = (reprfunc)RayPy_Vector3_repr,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_doc = "Vector3 type",
    .tp_richcompare = (richcmpfunc)RayPy_Vector3_richcompare,
    .tp_getset = RayPy_Vector3_getset,
    .tp_init = (initproc)RayPy_Vector3_init,
    .tp_new = (newfunc)RayPy_Vector3_new,
};

typedef struct {
    PyObject_HEAD double x;
    double y;
    double z;
    double w;
} RayPy_Vector4Object;

static void
RayPy_Vector4_dealloc(RayPy_Vector4Object *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *
RayPy_Vector4_repr(RayPy_Vector4Object *self)
{
    char buf[118];
    PyOS_snprintf(buf, sizeof(buf), "<Vector4(%g, %g, %g, %g)>", self->x, self->y, self->z,
                  self->w);
    return PyUnicode_FromString(buf);
}

static PyObject *
RayPy_Vector4_richcompare(RayPy_Vector4Object *self, RayPy_Vector4Object *other, int op)
{
    switch (op) {
    case Py_EQ:
        return PyBool_FromLong(self->x == other->x && self->y == other->y &&
                               self->z == other->z && self->w == other->w);
    case Py_NE:
        return PyBool_FromLong(self->x != other->x && self->y != other->y &&
                               self->z != other->z && self->w != other->w);
    default:
        Py_RETURN_NOTIMPLEMENTED;
    }
}

static PyObject *
RayPy_Vector4_get_x(RayPy_Vector4Object *self, void *Py_UNUSED(closure))
{
    return PyLong_FromLong(self->x);
}

static int
RayPy_Vector4_set_x(RayPy_Vector4Object *self, PyObject *value, void *Py_UNUSED(closure))
{
    double x = PyFloat_AsDouble(value);
    if (PyErr_Occurred()) {
        if (PyErr_ExceptionMatches(PyExc_TypeError)) {
            PyErr_Clear();
            PyErr_Format(PyExc_TypeError, "Vector4.x must be float, got %s",
                         Py_TYPE(value)->tp_name);
        }
        return -1;
    }
    self->x = x;
    return 0;
}

static PyObject *
RayPy_Vector4_get_y(RayPy_Vector4Object *self, void *Py_UNUSED(closure))
{
    return PyLong_FromLong(self->y);
}

static int
RayPy_Vector4_set_y(RayPy_Vector4Object *self, PyObject *value, void *Py_UNUSED(closure))
{
    double y = PyFloat_AsDouble(value);
    if (PyErr_Occurred()) {
        if (PyErr_ExceptionMatches(PyExc_TypeError)) {
            PyErr_Clear();
            PyErr_Format(PyExc_TypeError, "Vector4.y must be float, got %s",
                         Py_TYPE(value)->tp_name);
        }
        return -1;
    }
    self->y = y;
    return 0;
}

static PyObject *
RayPy_Vector4_get_z(RayPy_Vector4Object *self, void *Py_UNUSED(closure))
{
    return PyLong_FromLong(self->z);
}

static int
RayPy_Vector4_set_z(RayPy_Vector4Object *self, PyObject *value, void *Py_UNUSED(closure))
{
    double z = PyFloat_AsDouble(value);
    if (PyErr_Occurred()) {
        if (PyErr_ExceptionMatches(PyExc_TypeError)) {
            PyErr_Clear();
            PyErr_Format(PyExc_TypeError, "Vector4.z must be float, got %s",
                         Py_TYPE(value)->tp_name);
        }
        return -1;
    }
    self->z = z;
    return 0;
}

static PyObject *
RayPy_Vector4_get_w(RayPy_Vector4Object *self, void *Py_UNUSED(closure))
{
    return PyLong_FromLong(self->w);
}

static int
RayPy_Vector4_set_w(RayPy_Vector4Object *self, PyObject *value, void *Py_UNUSED(closure))
{
    double w = PyFloat_AsDouble(value);
    if (PyErr_Occurred()) {
        if (PyErr_ExceptionMatches(PyExc_TypeError)) {
            PyErr_Clear();
            PyErr_Format(PyExc_TypeError, "Vector4.w must be float, got %s",
                         Py_TYPE(value)->tp_name);
        }
        return -1;
    }
    self->w = w;
    return 0;
}

static PyGetSetDef RayPy_Vector4_getset[] = {
    {"x", (getter)RayPy_Vector4_get_x, (setter)RayPy_Vector4_set_x, NULL, NULL},
    {"y", (getter)RayPy_Vector4_get_y, (setter)RayPy_Vector4_set_y, NULL, NULL},
    {"z", (getter)RayPy_Vector4_get_z, (setter)RayPy_Vector4_set_z, NULL, NULL},
    {"w", (getter)RayPy_Vector4_get_w, (setter)RayPy_Vector4_set_w, NULL, NULL},
    {NULL}};

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
    PyObject *xobj = NULL, *yobj = NULL, *zobj = NULL, *wobj = NULL;
    if (!PyArg_ParseTuple(args, "|OOOO", &xobj, &yobj, &zobj, &wobj)) {
        return -1;
    }
    if (xobj) {
        double x = PyFloat_AsDouble(xobj);
        if (PyErr_Occurred()) {
            return -1;
        }
        self->x = x;
        if (!yobj) {
            self->y = x;
            self->z = x;
            self->w = x;
        }
    }
    if (yobj) {
        double y = PyFloat_AsDouble(yobj);
        if (PyErr_Occurred()) {
            return -1;
        }
        self->y = y;
    }
    if (zobj) {
        double z = PyFloat_AsDouble(zobj);
        if (PyErr_Occurred()) {
            return -1;
        }
        self->z = z;
    }
    if (wobj) {
        double w = PyFloat_AsDouble(wobj);
        if (PyErr_Occurred()) {
            return -1;
        }
        self->w = w;
    }
    return 0;
}

static PyTypeObject RayPy_Vector4_Type = {
    PyVarObject_HEAD_INIT(NULL, 0).tp_name = "raypy.Vector4",
    .tp_basicsize = sizeof(RayPy_Vector4Object),
    .tp_itemsize = 0,
    .tp_dealloc = (destructor)RayPy_Vector4_dealloc,
    .tp_repr = (reprfunc)RayPy_Vector4_repr,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_doc = "Vector4 type",
    .tp_richcompare = (richcmpfunc)RayPy_Vector4_richcompare,
    .tp_getset = RayPy_Vector4_getset,
    .tp_init = (initproc)RayPy_Vector4_init,
    .tp_new = (newfunc)RayPy_Vector4_new,
};

typedef struct {
    PyObject_HEAD uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} RayPy_ColorObject;

static void
RayPy_Color_dealloc(RayPy_ColorObject *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *
RayPy_Color_repr(RayPy_ColorObject *self)
{
    char buf[28]; // CONST[15] + (4 * 3) + NULL_CHAR[1]
    snprintf(buf, sizeof(buf), "<Color(%d, %d, %d, %d)>", self->r, self->g, self->b, self->a);
    return PyUnicode_FromString(buf);
}

static PyObject *
RayPy_Color_richcompare(RayPy_ColorObject *self, RayPy_ColorObject *other, int op)
{
    switch (op) {
    case Py_EQ:
        return PyBool_FromLong(self->r == other->r && self->g == other->g &&
                               self->b == other->b && self->a == other->a);
    case Py_NE:
        return PyBool_FromLong(self->r != other->r && self->g != other->g &&
                               self->b != other->b && self->a != other->a);
    default:
        Py_RETURN_NOTIMPLEMENTED;
    }
}

static PyObject *
RayPy_Color_get_r(RayPy_ColorObject *self, void *Py_UNUSED(closure))
{
    return PyLong_FromLong(self->r);
}

static int
RayPy_Color_set_r(RayPy_ColorObject *self, PyObject *value, void *Py_UNUSED(closure))
{
    long r = PyLong_AsLong(value);
    if (PyErr_Occurred()) {
        if (PyErr_ExceptionMatches(PyExc_TypeError)) {
            PyErr_Clear();
            PyErr_Format(PyExc_TypeError, "Color.r must be int, got %s",
                         Py_TYPE(value)->tp_name);
        }
        return -1;
    }
    if (r < 0 || r > 255) {
        PyErr_SetString(PyExc_ValueError,
                        "color values must be greater than 0 and lower than 255");
        return -1;
    }
    self->r = (uint8_t)r;
    return 0;
}

static PyObject *
RayPy_Color_get_g(RayPy_ColorObject *self, void *Py_UNUSED(closure))
{
    return PyLong_FromLong(self->g);
}

static int
RayPy_Color_set_g(RayPy_ColorObject *self, PyObject *value, void *Py_UNUSED(closure))
{
    long g = PyLong_AsLong(value);
    if (PyErr_Occurred()) {
        if (PyErr_ExceptionMatches(PyExc_TypeError)) {
            PyErr_Clear();
            PyErr_Format(PyExc_TypeError, "Color.g must be int, got %s",
                         Py_TYPE(value)->tp_name);
        }
        return -1;
    }
    if (g < 0 || g > 255) {
        PyErr_SetString(PyExc_ValueError,
                        "color values must be greater than 0 and lower than 255");
        return -1;
    }
    self->g = (uint8_t)g;
    return 0;
}

static PyObject *
RayPy_Color_get_b(RayPy_ColorObject *self, void *Py_UNUSED(closure))
{
    return PyLong_FromLong(self->b);
}

static int
RayPy_Color_set_b(RayPy_ColorObject *self, PyObject *value, void *Py_UNUSED(closure))
{
    long b = PyLong_AsLong(value);
    if (PyErr_Occurred()) {
        if (PyErr_ExceptionMatches(PyExc_TypeError)) {
            PyErr_Clear();
            PyErr_Format(PyExc_TypeError, "Color.b must be int, got %s",
                         Py_TYPE(value)->tp_name);
        }
        return -1;
    }
    if (b < 0 || b > 255) {
        PyErr_SetString(PyExc_ValueError,
                        "color values must be greater than 0 and lower than 255");
        return -1;
    }
    self->b = (uint8_t)b;
    return 0;
}

static PyObject *
RayPy_Color_get_a(RayPy_ColorObject *self, void *Py_UNUSED(closure))
{
    return PyLong_FromLong(self->a);
}

static int
RayPy_Color_set_a(RayPy_ColorObject *self, PyObject *value, void *Py_UNUSED(closure))
{
    long a = PyLong_AsLong(value);
    if (PyErr_Occurred()) {
        if (PyErr_ExceptionMatches(PyExc_TypeError)) {
            PyErr_Clear();
            PyErr_Format(PyExc_TypeError, "Color.a must be int, got %s",
                         Py_TYPE(value)->tp_name);
        }
        return -1;
    }
    if (a < 0 || a > 255) {
        PyErr_SetString(PyExc_ValueError,
                        "color values must be greater than 0 and lower than 255");
        return -1;
    }
    self->a = (uint8_t)a;
    return 0;
}

static PyGetSetDef RayPy_Color_getset[] = {
    {"r", (getter)RayPy_Color_get_r, (setter)RayPy_Color_set_r, NULL, NULL},
    {"g", (getter)RayPy_Color_get_g, (setter)RayPy_Color_set_g, NULL, NULL},
    {"b", (getter)RayPy_Color_get_b, (setter)RayPy_Color_set_b, NULL, NULL},
    {"a", (getter)RayPy_Color_get_a, (setter)RayPy_Color_set_a, NULL, NULL},
    {NULL}};

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
RayPy_Color_init(RayPy_ColorObject *obj, PyObject *args, PyObject *Py_UNUSED(kwds))
{
    unsigned char r, g, b, a = 255;
    if (!PyArg_ParseTuple(args, "bbb|b", &r, &g, &b, &a)) {
        if (PyErr_ExceptionMatches(PyExc_OverflowError)) {
            PyErr_Clear();
            PyErr_SetString(PyExc_ValueError,
                            "color values must be greater than 0 and lower than 255");
        }
        return -1;
    }
    obj->r = r;
    obj->g = g;
    obj->b = b;
    obj->a = a;
    return 0;
}

static PyTypeObject RayPy_Color_Type = {
    PyVarObject_HEAD_INIT(NULL, 0).tp_name = "raypy.Color",
    .tp_basicsize = sizeof(RayPy_ColorObject),
    .tp_itemsize = 0,
    .tp_dealloc = (destructor)RayPy_Color_dealloc,
    .tp_repr = (reprfunc)RayPy_Color_repr,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_doc = "Color type",
    .tp_richcompare = (richcmpfunc)RayPy_Color_richcompare,
    .tp_getset = RayPy_Color_getset,
    .tp_init = (initproc)RayPy_Color_init,
    .tp_new = (newfunc)RayPy_Color_new,
};

Color
RayPy_Color_AsColor(RayPy_ColorObject *obj)
{
    Color color;
    if (obj == NULL)
        PyErr_BadInternalCall();
    if (!PyObject_TypeCheck(obj, &RayPy_Color_Type)) {
        PyErr_SetString(PyExc_TypeError, "a raypy.Color type is required");
        return color;
    }
    color.r = obj->r;
    color.g = obj->g;
    color.b = obj->b;
    color.a = obj->a;
    return color;
}

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
    {"init_window", (PyCFunction)(void (*)(void))RayPy_InitWindow,
     METH_VARARGS | METH_KEYWORDS, init_window_doc},
    {"window_should_close", (PyCFunction)RayPy_WindowShouldClose, METH_NOARGS,
     window_should_close_doc},
    {"close_window", (PyCFunction)RayPy_CloseWindow, METH_NOARGS, close_window_doc},
    {"is_window_ready", (PyCFunction)RayPy_IsWindowReady, METH_NOARGS, is_window_ready_doc},
    {"is_window_fullscreen", (PyCFunction)RayPy_IsWindowFullscreen, METH_NOARGS,
     is_window_fullscreen_doc},
    {"is_window_hidden", (PyCFunction)RayPy_IsWindowHidden, METH_NOARGS, is_window_hidden_doc},
    {"is_window_minimized", (PyCFunction)RayPy_IsWindowMinimized, METH_NOARGS,
     is_window_minimized_doc},
    {"is_window_maximized", (PyCFunction)RayPy_IsWindowMaximized, METH_NOARGS,
     is_window_maximized_doc},
    {"is_window_focused", (PyCFunction)RayPy_IsWindowFocused, METH_NOARGS,
     is_window_focused_doc},
    {"is_window_resized", (PyCFunction)RayPy_IsWindowResized, METH_NOARGS,
     is_window_resized_doc},
    {"is_window_state", (PyCFunction)RayPy_IsWindowState, METH_O, is_window_state_doc},
    {"set_window_state", (PyCFunction)RayPy_SetWindowState, METH_O, set_window_state_doc},
    {"clear_window_state", (PyCFunction)RayPy_ClearWindowState, METH_O,
     clear_window_state_doc},
    {"toggle_fullscreen", (PyCFunction)RayPy_ToggleFullscreen, METH_NOARGS,
     toggle_fullscreen_doc},
    {"maximize_window", (PyCFunction)RayPy_MaximizeWindow, METH_NOARGS, maximize_window_doc},
    {"minimize_window", (PyCFunction)RayPy_MinimizeWindow, METH_NOARGS, minimize_window_doc},
    {"restore_window", (PyCFunction)RayPy_RestoreWindow, METH_NOARGS, restore_window_doc},
    {"set_window_icon", (PyCFunction)RayPy_SetWindowIcon, METH_O, set_window_icon_doc},
    {"set_window_title", (PyCFunction)RayPy_SetWindowTitle, METH_O, set_window_title_doc},
    {"set_window_position", (PyCFunction)RayPy_SetWindowPosition, METH_VARARGS,
     set_window_position_doc},
    {"set_window_monitor", (PyCFunction)RayPy_SetWindowMonitor, METH_O,
     set_window_monitor_doc},
    {"set_window_min_size", (PyCFunction)(void (*)(void))RayPy_SetWindowMinSize,
     METH_VARARGS | METH_KEYWORDS, set_window_min_size_doc},
    {"set_window_size", (PyCFunction)(void (*)(void))RayPy_SetWindowSize,
     METH_VARARGS | METH_KEYWORDS, set_window_size_doc},
    {"get_window_handle", (PyCFunction)RayPy_GetWindowHandle, METH_NOARGS,
     get_window_handle_doc},
    {"get_screen_width", (PyCFunction)RayPy_GetScreenWidth, METH_NOARGS, get_screen_width_doc},
    {"get_screen_height", (PyCFunction)RayPy_GetScreenHeight, METH_NOARGS,
     get_screen_height_doc},
    {"get_monitor_count", (PyCFunction)RayPy_GetMonitorCount, METH_NOARGS,
     get_monitor_count_doc},
    {"get_current_monitor", (PyCFunction)RayPy_GetCurrentMonitor, METH_NOARGS,
     get_current_monitor_doc},
    {"get_monitor_position", (PyCFunction)RayPy_GetMonitorPosition, METH_O,
     get_monitor_position_doc},
    {"get_monitor_width", (PyCFunction)RayPy_GetMonitorWidth, METH_O, get_monitor_width_doc},
    {"get_monitor_height", (PyCFunction)RayPy_GetMonitorHeight, METH_O,
     get_monitor_height_doc},
    {"get_monitor_physical_width", (PyCFunction)RayPy_GetMonitorPhysicalWidth, METH_O,
     get_monitor_physical_width_doc},
    {"get_monitor_physical_height", (PyCFunction)RayPy_GetMonitorPhysicalHeight, METH_O,
     get_monitor_physical_height_doc},
    {"get_monitor_refresh_tate", (PyCFunction)RayPy_GetMonitorRefreshRate, METH_O,
     get_monitor_refresh_rate_doc},
    {"get_window_position", (PyCFunction)RayPy_GetWindowPosition, METH_NOARGS,
     get_window_position_doc},
    {"get_window_scale_dpi", (PyCFunction)RayPy_GetWindowScaleDPI, METH_NOARGS,
     get_window_scale_dpi_doc},
    {"get_monitor_name", (PyCFunction)RayPy_GetMonitorName, METH_O, get_monitor_name_doc},
    {"set_clipboard_text", (PyCFunction)RayPy_SetClipboardText, METH_O,
     set_clipboard_text_doc},
    {"get_clipboard_text", (PyCFunction)RayPy_GetClipboardText, METH_NOARGS,
     get_clipboard_text_doc},
    {"swap_screen_buffer", (PyCFunction)RayPy_SwapScreenBuffer, METH_NOARGS,
     swap_screen_buffer_doc},
    {"poll_input_events", (PyCFunction)RayPy_PollInputEvents, METH_NOARGS,
     poll_input_events_doc},
    {"wait_time", (PyCFunction)RayPy_WaitTime, METH_O, wait_time_doc},
    {"show_cursor", (PyCFunction)RayPy_ShowCursor, METH_NOARGS, show_cursor_doc},
    {"hide_cursor", (PyCFunction)RayPy_HideCursor, METH_NOARGS, hide_cursor_doc},
    {"is_cursor_hidden", (PyCFunction)RayPy_IsCursorHidden, METH_NOARGS, is_cursor_hidden_doc},
    {"enable_cursor", (PyCFunction)RayPy_EnableCursor, METH_NOARGS, enable_cursor_doc},
    {"disable_cursor", (PyCFunction)RayPy_DisableCursor, METH_NOARGS, disable_cursor_doc},
    {"is_cursor_on_screen", (PyCFunction)RayPy_IsCursorOnScreen, METH_NOARGS,
     is_cursor_on_screen_doc},
    {"clear_background", (PyCFunction)RayPy_ClearBackground, METH_O, clear_background_doc},
    {"begin_drawing", (PyCFunction)RayPy_BeginDrawing, METH_NOARGS, begin_drawing_doc},
    {"end_drawing", (PyCFunction)RayPy_EndDrawing, METH_NOARGS, end_drawing_doc},
    {"set_target_fps", (PyCFunction)RayPy_SetTargetFPS, METH_O, set_target_fps_doc},
    {"get_fps", (PyCFunction)RayPy_GetFPS, METH_NOARGS, get_fps_doc},
    {"get_frame_time", (PyCFunction)RayPy_GetFrameTime, METH_NOARGS, get_frame_time_doc},
    {"get_time", (PyCFunction)RayPy_GetTime, METH_NOARGS, get_time_doc},
    {"get_random_value", (PyCFunction)RayPy_GetRandomValue, METH_VARARGS,
     get_random_value_doc},
    {"set_random_seed", (PyCFunction)RayPy_SetRandomSeed, METH_O, set_random_seed_doc},
    {"take_screenshot", (PyCFunction)RayPy_TakeScreenshot, METH_O, take_screenshot_doc},
    {"set_config_flags", (PyCFunction)RayPy_SetConfigFlags, METH_O, set_config_flags_doc},
    {"trace_log", (PyCFunction)RayPy_TraceLog, METH_VARARGS, trace_log_doc},
    {"set_trace_log_level_doc", (PyCFunction)RayPy_SetTraceLogLevel, METH_O,
     set_trace_log_level_doc},
    {"open_url", (PyCFunction)RayPy_OpenURL, METH_O, open_url_doc},
    {"is_key_pressed", (PyCFunction)RayPy_IsKeyPressed, METH_O, is_key_pressed_doc},
    {"is_key_down", (PyCFunction)RayPy_IsKeyDown, METH_O, is_key_down_doc},
    {"is_key_released", (PyCFunction)RayPy_IsKeyReleased, METH_O, is_key_released_doc},
    {"is_key_up", (PyCFunction)RayPy_IsKeyUp, METH_O, is_key_up_doc},
    {"set_exit_key", (PyCFunction)RayPy_SetExitKey, METH_O, set_exit_key_doc},
    {"get_key_pressed", (PyCFunction)RayPy_GetKeyPressed, METH_NOARGS, get_key_pressed_doc},
    {"get_char_pressed", (PyCFunction)RayPy_GetCharPressed, METH_NOARGS, get_char_pressed_doc},
    {"draw_fps", (PyCFunction)RayPy_DrawFPS, METH_VARARGS, draw_fps_doc},
    {"draw_text", (PyCFunction)(void (*)(void))RayPy_DrawText, METH_VARARGS | METH_KEYWORDS,
     draw_text_doc},
    {NULL, NULL, 0, NULL}};

static int
RayPy_exec(PyObject *m)
{
    if (PyModule_AddStringConstant(m, "RAYLIB_VERSION", RAYLIB_VERSION))
        goto error;

    /* Basic Defines */
    if (PyModule_AddObject(m, "PI", PyFloat_FromDouble(PI)))
        goto error;
    if (PyModule_AddObject(m, "DEG2RAD", PyFloat_FromDouble(DEG2RAD)))
        goto error;
    if (PyModule_AddObject(m, "RAD2DEG", PyFloat_FromDouble(RAD2DEG)))
        goto error;

    /* Structures Definition */
    if (PyType_Ready(&RayPy_Vector2_Type))
        goto error;
    Py_INCREF(&RayPy_Vector2_Type);
    if (PyModule_AddObject(m, "Vector2", (PyObject *)&RayPy_Vector2_Type)) {
        Py_DECREF(&RayPy_Vector2_Type);
        goto error;
    }
    if (PyType_Ready(&RayPy_Vector3_Type))
        goto error;
    Py_INCREF(&RayPy_Vector3_Type);
    if (PyModule_AddObject(m, "Vector3", (PyObject *)&RayPy_Vector3_Type)) {
        Py_DECREF(&RayPy_Vector3_Type);
        goto error;
    }
    if (PyType_Ready(&RayPy_Vector4_Type))
        goto error;
    Py_INCREF(&RayPy_Vector4_Type);
    if (PyModule_AddObject(m, "Vector4", (PyObject *)&RayPy_Vector4_Type)) {
        Py_DECREF(&RayPy_Vector4_Type);
        goto error;
    }
    if (PyModule_AddObject(m, "Quaternion", (PyObject *)&RayPy_Vector4_Type)) {
        Py_DECREF(&RayPy_Vector4_Type);
        goto error;
    }
    if (PyType_Ready(&RayPy_Color_Type))
        goto error;
    Py_INCREF(&RayPy_Color_Type);
    if (PyModule_AddObject(m, "Color", (PyObject *)&RayPy_Color_Type)) {
        Py_DECREF(&RayPy_Color_Type);
        goto error;
    }

    // clang-format off

    /* Basic Colors */
    if (PyModule_AddObject(m, "LIGHTGRAY", PyObject_CallFunction((PyObject *)&RayPy_Color_Type, "bbbb", 200, 200, 200, 255)))
        goto error;
    if (PyModule_AddObject(m, "GRAY", PyObject_CallFunction((PyObject *)&RayPy_Color_Type, "bbbb", 130, 130, 130, 255)))
        goto error;
    if (PyModule_AddObject(m, "DARKGRAY", PyObject_CallFunction((PyObject *)&RayPy_Color_Type, "bbbb", 80, 80, 80, 255)))
        goto error;
    if (PyModule_AddObject(m, "YELLOW", PyObject_CallFunction((PyObject *)&RayPy_Color_Type, "bbbb", 253, 249, 0, 255)))
        goto error;
    if (PyModule_AddObject(m, "GOLD", PyObject_CallFunction((PyObject *)&RayPy_Color_Type, "bbbb", 255, 203, 0, 255)))
        goto error;
    if (PyModule_AddObject(m, "ORANGE", PyObject_CallFunction((PyObject *)&RayPy_Color_Type, "bbbb", 255, 161, 0, 255)))
        goto error;
    if (PyModule_AddObject(m, "PINK", PyObject_CallFunction((PyObject *)&RayPy_Color_Type, "bbbb", 255, 109, 194, 255)))
        goto error;
    if (PyModule_AddObject(m, "RED", PyObject_CallFunction((PyObject *)&RayPy_Color_Type, "bbbb", 230, 41, 55, 255)))
        goto error;
    if (PyModule_AddObject(m, "MAROON", PyObject_CallFunction((PyObject *)&RayPy_Color_Type, "bbbb", 190, 33, 55, 255)))
        goto error;
    if (PyModule_AddObject(m, "GREEN", PyObject_CallFunction((PyObject *)&RayPy_Color_Type, "bbbb", 0, 228, 48, 255)))
        goto error;
    if (PyModule_AddObject(m, "LIME", PyObject_CallFunction((PyObject *)&RayPy_Color_Type, "bbbb", 0, 158, 47, 255)))
        goto error;
    if (PyModule_AddObject(m, "DARKGREEN", PyObject_CallFunction((PyObject *)&RayPy_Color_Type, "bbbb", 0, 117, 44, 255)))
        goto error;
    if (PyModule_AddObject(m, "SKYBLUE", PyObject_CallFunction((PyObject *)&RayPy_Color_Type, "bbbb", 102, 191, 255, 255)))
        goto error;
    if (PyModule_AddObject(m, "BLUE", PyObject_CallFunction((PyObject *)&RayPy_Color_Type, "bbbb", 0, 121, 241, 255)))
        goto error;
    if (PyModule_AddObject(m, "DARKBLUE", PyObject_CallFunction((PyObject *)&RayPy_Color_Type, "bbbb", 0, 82, 172, 255)))
        goto error;
    if (PyModule_AddObject(m, "PURPLE", PyObject_CallFunction((PyObject *)&RayPy_Color_Type, "bbbb", 200, 122, 255, 255)))
        goto error;
    if (PyModule_AddObject(m, "VIOLET", PyObject_CallFunction((PyObject *)&RayPy_Color_Type, "bbbb", 135, 60, 190, 255)))
        goto error;
    if (PyModule_AddObject(m, "DARKPURPLE", PyObject_CallFunction((PyObject *)&RayPy_Color_Type, "bbbb", 112, 31, 126, 255)))
        goto error;
    if (PyModule_AddObject(m, "BEIGE", PyObject_CallFunction((PyObject *)&RayPy_Color_Type, "bbbb", 211, 176, 131, 255)))
        goto error;
    if (PyModule_AddObject(m, "BROWN", PyObject_CallFunction((PyObject *)&RayPy_Color_Type, "bbbb", 127, 106, 79, 255)))
        goto error;
    if (PyModule_AddObject(m, "DARKBROWN", PyObject_CallFunction((PyObject *)&RayPy_Color_Type, "bbbb", 76, 63, 47, 255)))
        goto error;
    if (PyModule_AddObject(m, "WHITE", PyObject_CallFunction((PyObject *)&RayPy_Color_Type, "bbbb", 255, 255, 255, 255)))
        goto error;
    if (PyModule_AddObject(m, "BLACK", PyObject_CallFunction((PyObject *)&RayPy_Color_Type, "bbbb", 0, 0, 0, 255)))
        goto error;
    if (PyModule_AddObject(m, "BLANK", PyObject_CallFunction((PyObject *)&RayPy_Color_Type, "bbbb", 0, 0, 0, 0)))
        goto error;
    if (PyModule_AddObject(m, "MAGENTA", PyObject_CallFunction((PyObject *)&RayPy_Color_Type, "bbbb", 255, 0, 255, 255)))
        goto error;
    if (PyModule_AddObject(m, "RAYWHITE", PyObject_CallFunction((PyObject *)&RayPy_Color_Type, "bbbb", 245, 245, 245, 255)))
        goto error;

    /* Enumerators Definition */
    if (PyModule_AddObject(m, "FLAG_VSYNC_HINT", PyLong_FromLong(FLAG_VSYNC_HINT)))
        goto error;
    if (PyModule_AddObject(m, "FLAG_FULLSCREEN_MODE", PyLong_FromLong(FLAG_FULLSCREEN_MODE)))
        goto error;
    if (PyModule_AddObject(m, "FLAG_WINDOW_RESIZABLE", PyLong_FromLong(FLAG_WINDOW_RESIZABLE)))
        goto error;
    if (PyModule_AddObject(m, "FLAG_WINDOW_UNDECORATED", PyLong_FromLong(FLAG_WINDOW_UNDECORATED)))
        goto error;
    if (PyModule_AddObject(m, "FLAG_WINDOW_HIDDEN", PyLong_FromLong(FLAG_WINDOW_HIDDEN)))
        goto error;
    if (PyModule_AddObject(m, "FLAG_WINDOW_MINIMIZED", PyLong_FromLong(FLAG_WINDOW_MINIMIZED)))
        goto error;
    if (PyModule_AddObject(m, "FLAG_WINDOW_MAXIMIZED", PyLong_FromLong(FLAG_WINDOW_MAXIMIZED)))
        goto error;
    if (PyModule_AddObject(m, "FLAG_WINDOW_UNFOCUSED", PyLong_FromLong(FLAG_WINDOW_UNFOCUSED)))
        goto error;
    if (PyModule_AddObject(m, "FLAG_WINDOW_TOPMOST", PyLong_FromLong(FLAG_WINDOW_TOPMOST)))
        goto error;
    if (PyModule_AddObject(m, "FLAG_WINDOW_ALWAYS_RUN", PyLong_FromLong(FLAG_WINDOW_ALWAYS_RUN)))
        goto error;
    if (PyModule_AddObject(m, "FLAG_WINDOW_TRANSPARENT", PyLong_FromLong(FLAG_WINDOW_TRANSPARENT)))
        goto error;
    if (PyModule_AddObject(m, "FLAG_WINDOW_HIGHDPI", PyLong_FromLong(FLAG_WINDOW_HIGHDPI)))
        goto error;
    if (PyModule_AddObject(m, "FLAG_MSAA_4X_HINT", PyLong_FromLong(FLAG_MSAA_4X_HINT)))
        goto error;
    if (PyModule_AddObject(m, "FLAG_INTERLACED_HINT", PyLong_FromLong(FLAG_INTERLACED_HINT)))
        goto error;
    if (PyModule_AddObject(m, "LOG_ALL", PyLong_FromLong(LOG_ALL)))
        goto error;
    if (PyModule_AddObject(m, "LOG_TRACE", PyLong_FromLong(LOG_TRACE)))
        goto error;
    if (PyModule_AddObject(m, "LOG_DEBUG", PyLong_FromLong(LOG_DEBUG)))
        goto error;
    if (PyModule_AddObject(m, "LOG_INFO", PyLong_FromLong(LOG_INFO)))
        goto error;
    if (PyModule_AddObject(m, "LOG_WARNING", PyLong_FromLong(LOG_WARNING)))
        goto error;
    if (PyModule_AddObject(m, "LOG_ERROR", PyLong_FromLong(LOG_ERROR)))
        goto error;
    if (PyModule_AddObject(m, "LOG_FATAL", PyLong_FromLong(LOG_FATAL)))
        goto error;
    if (PyModule_AddObject(m, "LOG_NONE", PyLong_FromLong(LOG_NONE)))
        goto error;
    if (PyModule_AddObject(m, "KEY_NULL", PyLong_FromLong(KEY_NULL)))
        goto error;
    if (PyModule_AddObject(m, "KEY_APOSTROPHE", PyLong_FromLong(KEY_APOSTROPHE)))
        goto error;
    if (PyModule_AddObject(m, "KEY_COMMA", PyLong_FromLong(KEY_COMMA)))
        goto error;
    if (PyModule_AddObject(m, "KEY_MINUS", PyLong_FromLong(KEY_MINUS)))
        goto error;
    if (PyModule_AddObject(m, "KEY_PERIOD", PyLong_FromLong(KEY_PERIOD)))
        goto error;
    if (PyModule_AddObject(m, "KEY_SLASH", PyLong_FromLong(KEY_SLASH)))
        goto error;
    if (PyModule_AddObject(m, "KEY_ZERO", PyLong_FromLong(KEY_ZERO)))
        goto error;
    if (PyModule_AddObject(m, "KEY_ONE", PyLong_FromLong(KEY_ONE)))
        goto error;
    if (PyModule_AddObject(m, "KEY_TWO", PyLong_FromLong(KEY_TWO)))
        goto error;
    if (PyModule_AddObject(m, "KEY_THREE", PyLong_FromLong(KEY_THREE)))
        goto error;
    if (PyModule_AddObject(m, "KEY_FOUR", PyLong_FromLong(KEY_FOUR)))
        goto error;
    if (PyModule_AddObject(m, "KEY_FIVE", PyLong_FromLong(KEY_FIVE)))
        goto error;
    if (PyModule_AddObject(m, "KEY_SIX", PyLong_FromLong(KEY_SIX)))
        goto error;
    if (PyModule_AddObject(m, "KEY_SEVEN", PyLong_FromLong(KEY_SEVEN)))
        goto error;
    if (PyModule_AddObject(m, "KEY_EIGHT", PyLong_FromLong(KEY_EIGHT)))
        goto error;
    if (PyModule_AddObject(m, "KEY_NINE", PyLong_FromLong(KEY_NINE)))
        goto error;
    if (PyModule_AddObject(m, "KEY_SEMICOLON", PyLong_FromLong(KEY_SEMICOLON)))
        goto error;
    if (PyModule_AddObject(m, "KEY_EQUAL", PyLong_FromLong(KEY_EQUAL)))
        goto error;
    if (PyModule_AddObject(m, "KEY_A", PyLong_FromLong(KEY_A)))
        goto error;
    if (PyModule_AddObject(m, "KEY_B", PyLong_FromLong(KEY_B)))
        goto error;
    if (PyModule_AddObject(m, "KEY_C", PyLong_FromLong(KEY_C)))
        goto error;
    if (PyModule_AddObject(m, "KEY_D", PyLong_FromLong(KEY_D)))
        goto error;
    if (PyModule_AddObject(m, "KEY_E", PyLong_FromLong(KEY_E)))
        goto error;
    if (PyModule_AddObject(m, "KEY_F", PyLong_FromLong(KEY_F)))
        goto error;
    if (PyModule_AddObject(m, "KEY_G", PyLong_FromLong(KEY_G)))
        goto error;
    if (PyModule_AddObject(m, "KEY_H", PyLong_FromLong(KEY_H)))
        goto error;
    if (PyModule_AddObject(m, "KEY_I", PyLong_FromLong(KEY_I)))
        goto error;
    if (PyModule_AddObject(m, "KEY_J", PyLong_FromLong(KEY_J)))
        goto error;
    if (PyModule_AddObject(m, "KEY_K", PyLong_FromLong(KEY_K)))
        goto error;
    if (PyModule_AddObject(m, "KEY_L", PyLong_FromLong(KEY_L)))
        goto error;
    if (PyModule_AddObject(m, "KEY_M", PyLong_FromLong(KEY_M)))
        goto error;
    if (PyModule_AddObject(m, "KEY_N", PyLong_FromLong(KEY_N)))
        goto error;
    if (PyModule_AddObject(m, "KEY_O", PyLong_FromLong(KEY_O)))
        goto error;
    if (PyModule_AddObject(m, "KEY_P", PyLong_FromLong(KEY_P)))
        goto error;
    if (PyModule_AddObject(m, "KEY_Q", PyLong_FromLong(KEY_Q)))
        goto error;
    if (PyModule_AddObject(m, "KEY_R", PyLong_FromLong(KEY_R)))
        goto error;
    if (PyModule_AddObject(m, "KEY_S", PyLong_FromLong(KEY_S)))
        goto error;
    if (PyModule_AddObject(m, "KEY_T", PyLong_FromLong(KEY_T)))
        goto error;
    if (PyModule_AddObject(m, "KEY_U", PyLong_FromLong(KEY_U)))
        goto error;
    if (PyModule_AddObject(m, "KEY_V", PyLong_FromLong(KEY_V)))
        goto error;
    if (PyModule_AddObject(m, "KEY_W", PyLong_FromLong(KEY_W)))
        goto error;
    if (PyModule_AddObject(m, "KEY_X", PyLong_FromLong(KEY_X)))
        goto error;
    if (PyModule_AddObject(m, "KEY_Y", PyLong_FromLong(KEY_Y)))
        goto error;
    if (PyModule_AddObject(m, "KEY_Z", PyLong_FromLong(KEY_Z)))
        goto error;
    if (PyModule_AddObject(m, "KEY_LEFT_BRACKET", PyLong_FromLong(KEY_LEFT_BRACKET)))
        goto error;
    if (PyModule_AddObject(m, "KEY_BACKSLASH", PyLong_FromLong(KEY_BACKSLASH)))
        goto error;
    if (PyModule_AddObject(m, "KEY_RIGHT_BRACKET", PyLong_FromLong(KEY_RIGHT_BRACKET)))
        goto error;
    if (PyModule_AddObject(m, "KEY_GRAVE", PyLong_FromLong(KEY_GRAVE)))
        goto error;
    if (PyModule_AddObject(m, "KEY_SPACE", PyLong_FromLong(KEY_SPACE)))
        goto error;
    if (PyModule_AddObject(m, "KEY_ESCAPE", PyLong_FromLong(KEY_ESCAPE)))
        goto error;
    if (PyModule_AddObject(m, "KEY_ENTER", PyLong_FromLong(KEY_ENTER)))
        goto error;
    if (PyModule_AddObject(m, "KEY_TAB", PyLong_FromLong(KEY_TAB)))
        goto error;
    if (PyModule_AddObject(m, "KEY_BACKSPACE", PyLong_FromLong(KEY_BACKSPACE)))
        goto error;
    if (PyModule_AddObject(m, "KEY_INSERT", PyLong_FromLong(KEY_INSERT)))
        goto error;
    if (PyModule_AddObject(m, "KEY_DELETE", PyLong_FromLong(KEY_DELETE)))
        goto error;
    if (PyModule_AddObject(m, "KEY_RIGHT", PyLong_FromLong(KEY_RIGHT)))
        goto error;
    if (PyModule_AddObject(m, "KEY_LEFT", PyLong_FromLong(KEY_LEFT)))
        goto error;
    if (PyModule_AddObject(m, "KEY_DOWN", PyLong_FromLong(KEY_DOWN)))
        goto error;
    if (PyModule_AddObject(m, "KEY_UP", PyLong_FromLong(KEY_UP)))
        goto error;
    if (PyModule_AddObject(m, "KEY_PAGE_UP", PyLong_FromLong(KEY_PAGE_UP)))
        goto error;
    if (PyModule_AddObject(m, "KEY_PAGE_DOWN", PyLong_FromLong(KEY_PAGE_DOWN)))
        goto error;
    if (PyModule_AddObject(m, "KEY_HOME", PyLong_FromLong(KEY_HOME)))
        goto error;
    if (PyModule_AddObject(m, "KEY_END", PyLong_FromLong(KEY_END)))
        goto error;
    if (PyModule_AddObject(m, "KEY_CAPS_LOCK", PyLong_FromLong(KEY_CAPS_LOCK)))
        goto error;
    if (PyModule_AddObject(m, "KEY_SCROLL_LOCK", PyLong_FromLong(KEY_SCROLL_LOCK)))
        goto error;
    if (PyModule_AddObject(m, "KEY_NUM_LOCK", PyLong_FromLong(KEY_NUM_LOCK)))
        goto error;
    if (PyModule_AddObject(m, "KEY_PRINT_SCREEN", PyLong_FromLong(KEY_PRINT_SCREEN)))
        goto error;
    if (PyModule_AddObject(m, "KEY_PAUSE", PyLong_FromLong(KEY_PAUSE)))
        goto error;
    if (PyModule_AddObject(m, "KEY_F1", PyLong_FromLong(KEY_F1)))
        goto error;
    if (PyModule_AddObject(m, "KEY_F2", PyLong_FromLong(KEY_F2)))
        goto error;
    if (PyModule_AddObject(m, "KEY_F3", PyLong_FromLong(KEY_F3)))
        goto error;
    if (PyModule_AddObject(m, "KEY_F4", PyLong_FromLong(KEY_F4)))
        goto error;
    if (PyModule_AddObject(m, "KEY_F5", PyLong_FromLong(KEY_F5)))
        goto error;
    if (PyModule_AddObject(m, "KEY_F6", PyLong_FromLong(KEY_F6)))
        goto error;
    if (PyModule_AddObject(m, "KEY_F7", PyLong_FromLong(KEY_F7)))
        goto error;
    if (PyModule_AddObject(m, "KEY_F8", PyLong_FromLong(KEY_F8)))
        goto error;
    if (PyModule_AddObject(m, "KEY_F9", PyLong_FromLong(KEY_F9)))
        goto error;
    if (PyModule_AddObject(m, "KEY_F10", PyLong_FromLong(KEY_F10)))
        goto error;
    if (PyModule_AddObject(m, "KEY_F11", PyLong_FromLong(KEY_F11)))
        goto error;
    if (PyModule_AddObject(m, "KEY_F12", PyLong_FromLong(KEY_F12)))
        goto error;
    if (PyModule_AddObject(m, "KEY_LEFT_SHIFT", PyLong_FromLong(KEY_LEFT_SHIFT)))
        goto error;
    if (PyModule_AddObject(m, "KEY_LEFT_CONTROL", PyLong_FromLong(KEY_LEFT_CONTROL)))
        goto error;
    if (PyModule_AddObject(m, "KEY_LEFT_ALT", PyLong_FromLong(KEY_LEFT_ALT)))
        goto error;
    if (PyModule_AddObject(m, "KEY_LEFT_SUPER", PyLong_FromLong(KEY_LEFT_SUPER)))
        goto error;
    if (PyModule_AddObject(m, "KEY_RIGHT_SHIFT", PyLong_FromLong(KEY_RIGHT_SHIFT)))
        goto error;
    if (PyModule_AddObject(m, "KEY_RIGHT_CONTROL", PyLong_FromLong(KEY_RIGHT_CONTROL)))
        goto error;
    if (PyModule_AddObject(m, "KEY_RIGHT_ALT", PyLong_FromLong(KEY_RIGHT_ALT)))
        goto error;
    if (PyModule_AddObject(m, "KEY_RIGHT_SUPER", PyLong_FromLong(KEY_RIGHT_SUPER)))
        goto error;
    if (PyModule_AddObject(m, "KEY_KB_MENU", PyLong_FromLong(KEY_KB_MENU)))
        goto error;
    if (PyModule_AddObject(m, "KEY_KP_0", PyLong_FromLong(KEY_KP_0)))
        goto error;
    if (PyModule_AddObject(m, "KEY_KP_1", PyLong_FromLong(KEY_KP_1)))
        goto error;
    if (PyModule_AddObject(m, "KEY_KP_2", PyLong_FromLong(KEY_KP_2)))
        goto error;
    if (PyModule_AddObject(m, "KEY_KP_3", PyLong_FromLong(KEY_KP_3)))
        goto error;
    if (PyModule_AddObject(m, "KEY_KP_4", PyLong_FromLong(KEY_KP_4)))
        goto error;
    if (PyModule_AddObject(m, "KEY_KP_5", PyLong_FromLong(KEY_KP_5)))
        goto error;
    if (PyModule_AddObject(m, "KEY_KP_6", PyLong_FromLong(KEY_KP_6)))
        goto error;
    if (PyModule_AddObject(m, "KEY_KP_7", PyLong_FromLong(KEY_KP_7)))
        goto error;
    if (PyModule_AddObject(m, "KEY_KP_8", PyLong_FromLong(KEY_KP_8)))
        goto error;
    if (PyModule_AddObject(m, "KEY_KP_9", PyLong_FromLong(KEY_KP_9)))
        goto error;
    if (PyModule_AddObject(m, "KEY_KP_DECIMAL", PyLong_FromLong(KEY_KP_DECIMAL)))
        goto error;
    if (PyModule_AddObject(m, "KEY_KP_DIVIDE", PyLong_FromLong(KEY_KP_DIVIDE)))
        goto error;
    if (PyModule_AddObject(m, "KEY_KP_MULTIPLY", PyLong_FromLong(KEY_KP_MULTIPLY)))
        goto error;
    if (PyModule_AddObject(m, "KEY_KP_SUBTRACT", PyLong_FromLong(KEY_KP_SUBTRACT)))
        goto error;
    if (PyModule_AddObject(m, "KEY_KP_ADD", PyLong_FromLong(KEY_KP_ADD)))
        goto error;
    if (PyModule_AddObject(m, "KEY_KP_ENTER", PyLong_FromLong(KEY_KP_ENTER)))
        goto error;
    if (PyModule_AddObject(m, "KEY_KP_EQUAL", PyLong_FromLong(KEY_KP_EQUAL)))
        goto error;
    if (PyModule_AddObject(m, "KEY_BACK", PyLong_FromLong(KEY_BACK)))
        goto error;
    if (PyModule_AddObject(m, "KEY_MENU", PyLong_FromLong(KEY_MENU)))
        goto error;
    if (PyModule_AddObject(m, "KEY_VOLUME_UP", PyLong_FromLong(KEY_VOLUME_UP)))
        goto error;
    if (PyModule_AddObject(m, "KEY_VOLUME_DOWN", PyLong_FromLong(KEY_VOLUME_DOWN)))
        goto error;
    if (PyModule_AddObject(m, "MOUSE_BUTTON_LEFT", PyLong_FromLong(MOUSE_BUTTON_LEFT)))
        goto error;
    if (PyModule_AddObject(m, "MOUSE_BUTTON_RIGHT", PyLong_FromLong(MOUSE_BUTTON_RIGHT)))
        goto error;
    if (PyModule_AddObject(m, "MOUSE_BUTTON_MIDDLE", PyLong_FromLong(MOUSE_BUTTON_MIDDLE)))
        goto error;
    if (PyModule_AddObject(m, "MOUSE_BUTTON_SIDE", PyLong_FromLong(MOUSE_BUTTON_SIDE)))
        goto error;
    if (PyModule_AddObject(m, "MOUSE_BUTTON_EXTRA", PyLong_FromLong(MOUSE_BUTTON_EXTRA)))
        goto error;
    if (PyModule_AddObject(m, "MOUSE_BUTTON_FORWARD", PyLong_FromLong(MOUSE_BUTTON_FORWARD)))
        goto error;
    if (PyModule_AddObject(m, "MOUSE_BUTTON_BACK", PyLong_FromLong(MOUSE_BUTTON_BACK)))
        goto error;
    if (PyModule_AddObject(m, "MOUSE_CURSOR_DEFAULT", PyLong_FromLong(MOUSE_CURSOR_DEFAULT)))
        goto error;
    if (PyModule_AddObject(m, "MOUSE_CURSOR_ARROW", PyLong_FromLong(MOUSE_CURSOR_ARROW)))
        goto error;
    if (PyModule_AddObject(m, "MOUSE_CURSOR_IBEAM", PyLong_FromLong(MOUSE_CURSOR_IBEAM)))
        goto error;
    if (PyModule_AddObject(m, "MOUSE_CURSOR_CROSSHAIR", PyLong_FromLong(MOUSE_CURSOR_CROSSHAIR)))
        goto error;
    if (PyModule_AddObject(m, "MOUSE_CURSOR_POINTING_HAND", PyLong_FromLong(MOUSE_CURSOR_POINTING_HAND)))
        goto error;
    if (PyModule_AddObject(m, "MOUSE_CURSOR_RESIZE_EW", PyLong_FromLong(MOUSE_CURSOR_RESIZE_EW)))
        goto error;
    if (PyModule_AddObject(m, "MOUSE_CURSOR_RESIZE_NS", PyLong_FromLong(MOUSE_CURSOR_RESIZE_NS)))
        goto error;
    if (PyModule_AddObject(m, "MOUSE_CURSOR_RESIZE_NWSE", PyLong_FromLong(MOUSE_CURSOR_RESIZE_NWSE)))
        goto error;
    if (PyModule_AddObject(m, "MOUSE_CURSOR_RESIZE_NESW", PyLong_FromLong(MOUSE_CURSOR_RESIZE_NESW)))
        goto error;
    if (PyModule_AddObject(m, "MOUSE_CURSOR_RESIZE_ALL", PyLong_FromLong(MOUSE_CURSOR_RESIZE_ALL)))
        goto error;
    if (PyModule_AddObject(m, "MOUSE_CURSOR_NOT_ALLOWED", PyLong_FromLong(MOUSE_CURSOR_NOT_ALLOWED)))
        goto error;
    if (PyModule_AddObject(m, "GAMEPAD_BUTTON_UNKNOWN", PyLong_FromLong(GAMEPAD_BUTTON_UNKNOWN)))
        goto error;
    if (PyModule_AddObject(m, "GAMEPAD_BUTTON_LEFT_FACE_UP", PyLong_FromLong(GAMEPAD_BUTTON_LEFT_FACE_UP)))
        goto error;
    if (PyModule_AddObject(m, "GAMEPAD_BUTTON_LEFT_FACE_RIGHT", PyLong_FromLong(GAMEPAD_BUTTON_LEFT_FACE_RIGHT)))
        goto error;
    if (PyModule_AddObject(m, "GAMEPAD_BUTTON_LEFT_FACE_DOWN", PyLong_FromLong(GAMEPAD_BUTTON_LEFT_FACE_DOWN)))
        goto error;
    if (PyModule_AddObject(m, "GAMEPAD_BUTTON_LEFT_FACE_LEFT", PyLong_FromLong(GAMEPAD_BUTTON_LEFT_FACE_LEFT)))
        goto error;
    if (PyModule_AddObject(m, "GAMEPAD_BUTTON_RIGHT_FACE_UP", PyLong_FromLong(GAMEPAD_BUTTON_RIGHT_FACE_UP)))
        goto error;
    if (PyModule_AddObject(m, "GAMEPAD_BUTTON_RIGHT_FACE_RIGHT", PyLong_FromLong(GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)))
        goto error;
    if (PyModule_AddObject(m, "GAMEPAD_BUTTON_RIGHT_FACE_DOWN", PyLong_FromLong(GAMEPAD_BUTTON_RIGHT_FACE_DOWN)))
        goto error;
    if (PyModule_AddObject(m, "GAMEPAD_BUTTON_RIGHT_FACE_LEFT", PyLong_FromLong(GAMEPAD_BUTTON_RIGHT_FACE_LEFT)))
        goto error;
    if (PyModule_AddObject(m, "GAMEPAD_BUTTON_LEFT_TRIGGER_1", PyLong_FromLong(GAMEPAD_BUTTON_LEFT_TRIGGER_1)))
        goto error;
    if (PyModule_AddObject(m, "GAMEPAD_BUTTON_LEFT_TRIGGER_2", PyLong_FromLong(GAMEPAD_BUTTON_LEFT_TRIGGER_2)))
        goto error;
    if (PyModule_AddObject(m, "GAMEPAD_BUTTON_RIGHT_TRIGGER_1", PyLong_FromLong(GAMEPAD_BUTTON_RIGHT_TRIGGER_1)))
        goto error;
    if (PyModule_AddObject(m, "GAMEPAD_BUTTON_RIGHT_TRIGGER_2", PyLong_FromLong(GAMEPAD_BUTTON_RIGHT_TRIGGER_2)))
        goto error;
    if (PyModule_AddObject(m, "GAMEPAD_BUTTON_MIDDLE_LEFT", PyLong_FromLong(GAMEPAD_BUTTON_MIDDLE_LEFT)))
        goto error;
    if (PyModule_AddObject(m, "GAMEPAD_BUTTON_MIDDLE", PyLong_FromLong(GAMEPAD_BUTTON_MIDDLE)))
        goto error;
    if (PyModule_AddObject(m, "GAMEPAD_BUTTON_MIDDLE_RIGHT", PyLong_FromLong(GAMEPAD_BUTTON_MIDDLE_RIGHT)))
        goto error;
    if (PyModule_AddObject(m, "GAMEPAD_BUTTON_LEFT_THUMB", PyLong_FromLong(GAMEPAD_BUTTON_LEFT_THUMB)))
        goto error;
    if (PyModule_AddObject(m, "GAMEPAD_BUTTON_RIGHT_THUMB", PyLong_FromLong(GAMEPAD_BUTTON_RIGHT_THUMB)))
        goto error;
    if (PyModule_AddObject(m, "GAMEPAD_AXIS_LEFT_X", PyLong_FromLong(GAMEPAD_AXIS_LEFT_X)))
        goto error;
    if (PyModule_AddObject(m, "GAMEPAD_AXIS_LEFT_Y", PyLong_FromLong(GAMEPAD_AXIS_LEFT_Y)))
        goto error;
    if (PyModule_AddObject(m, "GAMEPAD_AXIS_RIGHT_X", PyLong_FromLong(GAMEPAD_AXIS_RIGHT_X)))
        goto error;
    if (PyModule_AddObject(m, "GAMEPAD_AXIS_RIGHT_Y", PyLong_FromLong(GAMEPAD_AXIS_RIGHT_Y)))
        goto error;
    if (PyModule_AddObject(m, "GAMEPAD_AXIS_LEFT_TRIGGER", PyLong_FromLong(GAMEPAD_AXIS_LEFT_TRIGGER)))
        goto error;
    if (PyModule_AddObject(m, "GAMEPAD_AXIS_RIGHT_TRIGGER", PyLong_FromLong(GAMEPAD_AXIS_RIGHT_TRIGGER)))
        goto error;
    if (PyModule_AddObject(m, "MATERIAL_MAP_ALBEDO", PyLong_FromLong(MATERIAL_MAP_ALBEDO)))
        goto error;
    if (PyModule_AddObject(m, "MATERIAL_MAP_METALNESS", PyLong_FromLong(MATERIAL_MAP_METALNESS)))
        goto error;
    if (PyModule_AddObject(m, "MATERIAL_MAP_NORMAL", PyLong_FromLong(MATERIAL_MAP_NORMAL)))
        goto error;
    if (PyModule_AddObject(m, "MATERIAL_MAP_ROUGHNESS", PyLong_FromLong(MATERIAL_MAP_ROUGHNESS)))
        goto error;
    if (PyModule_AddObject(m, "MATERIAL_MAP_OCCLUSION", PyLong_FromLong(MATERIAL_MAP_OCCLUSION)))
        goto error;
    if (PyModule_AddObject(m, "MATERIAL_MAP_EMISSION", PyLong_FromLong(MATERIAL_MAP_EMISSION)))
        goto error;
    if (PyModule_AddObject(m, "MATERIAL_MAP_HEIGHT", PyLong_FromLong(MATERIAL_MAP_HEIGHT)))
        goto error;
    if (PyModule_AddObject(m, "MATERIAL_MAP_CUBEMAP", PyLong_FromLong(MATERIAL_MAP_CUBEMAP)))
        goto error;
    if (PyModule_AddObject(m, "MATERIAL_MAP_IRRADIANCE", PyLong_FromLong(MATERIAL_MAP_IRRADIANCE)))
        goto error;
    if (PyModule_AddObject(m, "MATERIAL_MAP_PREFILTER", PyLong_FromLong(MATERIAL_MAP_PREFILTER)))
        goto error;
    if (PyModule_AddObject(m, "MATERIAL_MAP_BRDF", PyLong_FromLong(MATERIAL_MAP_BRDF)))
        goto error;
    if (PyModule_AddObject(m, "MATERIAL_MAP_DIFFUSE", PyLong_FromLong(MATERIAL_MAP_DIFFUSE)))
        goto error;
    if (PyModule_AddObject(m, "MATERIAL_MAP_SPECULAR", PyLong_FromLong(MATERIAL_MAP_SPECULAR)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_LOC_VERTEX_POSITION", PyLong_FromLong(SHADER_LOC_VERTEX_POSITION)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_LOC_VERTEX_TEXCOORD01", PyLong_FromLong(SHADER_LOC_VERTEX_TEXCOORD01)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_LOC_VERTEX_TEXCOORD02", PyLong_FromLong(SHADER_LOC_VERTEX_TEXCOORD02)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_LOC_VERTEX_NORMAL", PyLong_FromLong(SHADER_LOC_VERTEX_NORMAL)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_LOC_VERTEX_TANGENT", PyLong_FromLong(SHADER_LOC_VERTEX_TANGENT)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_LOC_VERTEX_COLOR", PyLong_FromLong(SHADER_LOC_VERTEX_COLOR)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_LOC_MATRIX_MVP", PyLong_FromLong(SHADER_LOC_MATRIX_MVP)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_LOC_MATRIX_VIEW", PyLong_FromLong(SHADER_LOC_MATRIX_VIEW)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_LOC_MATRIX_PROJECTION", PyLong_FromLong(SHADER_LOC_MATRIX_PROJECTION)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_LOC_MATRIX_MODEL", PyLong_FromLong(SHADER_LOC_MATRIX_MODEL)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_LOC_MATRIX_NORMAL", PyLong_FromLong(SHADER_LOC_MATRIX_NORMAL)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_LOC_VECTOR_VIEW", PyLong_FromLong(SHADER_LOC_VECTOR_VIEW)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_LOC_COLOR_DIFFUSE", PyLong_FromLong(SHADER_LOC_COLOR_DIFFUSE)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_LOC_COLOR_SPECULAR", PyLong_FromLong(SHADER_LOC_COLOR_SPECULAR)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_LOC_COLOR_AMBIENT", PyLong_FromLong(SHADER_LOC_COLOR_AMBIENT)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_LOC_MAP_ALBEDO", PyLong_FromLong(SHADER_LOC_MAP_ALBEDO)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_LOC_MAP_METALNESS", PyLong_FromLong(SHADER_LOC_MAP_METALNESS)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_LOC_MAP_NORMAL", PyLong_FromLong(SHADER_LOC_MAP_NORMAL)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_LOC_MAP_ROUGHNESS", PyLong_FromLong(SHADER_LOC_MAP_ROUGHNESS)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_LOC_MAP_OCCLUSION", PyLong_FromLong(SHADER_LOC_MAP_OCCLUSION)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_LOC_MAP_EMISSION", PyLong_FromLong(SHADER_LOC_MAP_EMISSION)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_LOC_MAP_HEIGHT", PyLong_FromLong(SHADER_LOC_MAP_HEIGHT)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_LOC_MAP_CUBEMAP", PyLong_FromLong(SHADER_LOC_MAP_CUBEMAP)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_LOC_MAP_IRRADIANCE", PyLong_FromLong(SHADER_LOC_MAP_IRRADIANCE)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_LOC_MAP_PREFILTER", PyLong_FromLong(SHADER_LOC_MAP_PREFILTER)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_LOC_MAP_BRDF", PyLong_FromLong(SHADER_LOC_MAP_BRDF)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_LOC_MAP_DIFFUSE", PyLong_FromLong(SHADER_LOC_MAP_DIFFUSE)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_LOC_MAP_SPECULAR", PyLong_FromLong(SHADER_LOC_MAP_SPECULAR)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_UNIFORM_FLOAT", PyLong_FromLong(SHADER_UNIFORM_FLOAT)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_UNIFORM_VEC2", PyLong_FromLong(SHADER_UNIFORM_VEC2)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_UNIFORM_VEC3", PyLong_FromLong(SHADER_UNIFORM_VEC3)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_UNIFORM_VEC4", PyLong_FromLong(SHADER_UNIFORM_VEC4)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_UNIFORM_INT", PyLong_FromLong(SHADER_UNIFORM_INT)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_UNIFORM_IVEC2", PyLong_FromLong(SHADER_UNIFORM_IVEC2)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_UNIFORM_IVEC3", PyLong_FromLong(SHADER_UNIFORM_IVEC3)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_UNIFORM_IVEC4", PyLong_FromLong(SHADER_UNIFORM_IVEC4)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_UNIFORM_SAMPLER2D", PyLong_FromLong(SHADER_UNIFORM_SAMPLER2D)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_ATTRIB_FLOAT", PyLong_FromLong(SHADER_ATTRIB_FLOAT)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_ATTRIB_VEC2", PyLong_FromLong(SHADER_ATTRIB_VEC2)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_ATTRIB_VEC3", PyLong_FromLong(SHADER_ATTRIB_VEC3)))
        goto error;
    if (PyModule_AddObject(m, "SHADER_ATTRIB_VEC4", PyLong_FromLong(SHADER_ATTRIB_VEC4)))
        goto error;
    if (PyModule_AddObject(m, "PIXELFORMAT_UNCOMPRESSED_GRAYSCALE", PyLong_FromLong(PIXELFORMAT_UNCOMPRESSED_GRAYSCALE)))
        goto error;
    if (PyModule_AddObject(m, "PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA", PyLong_FromLong(PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA)))
        goto error;
    if (PyModule_AddObject(m, "PIXELFORMAT_UNCOMPRESSED_R5G6B5", PyLong_FromLong(PIXELFORMAT_UNCOMPRESSED_R5G6B5)))
        goto error;
    if (PyModule_AddObject(m, "PIXELFORMAT_UNCOMPRESSED_R8G8B8", PyLong_FromLong(PIXELFORMAT_UNCOMPRESSED_R8G8B8)))
        goto error;
    if (PyModule_AddObject(m, "PIXELFORMAT_UNCOMPRESSED_R5G5B5A1", PyLong_FromLong(PIXELFORMAT_UNCOMPRESSED_R5G5B5A1)))
        goto error;
    if (PyModule_AddObject(m, "PIXELFORMAT_UNCOMPRESSED_R4G4B4A4", PyLong_FromLong(PIXELFORMAT_UNCOMPRESSED_R4G4B4A4)))
        goto error;
    if (PyModule_AddObject(m, "PIXELFORMAT_UNCOMPRESSED_R8G8B8A8", PyLong_FromLong(PIXELFORMAT_UNCOMPRESSED_R8G8B8A8)))
        goto error;
    if (PyModule_AddObject(m, "PIXELFORMAT_UNCOMPRESSED_R32", PyLong_FromLong(PIXELFORMAT_UNCOMPRESSED_R32)))
        goto error;
    if (PyModule_AddObject(m, "PIXELFORMAT_UNCOMPRESSED_R32G32B32", PyLong_FromLong(PIXELFORMAT_UNCOMPRESSED_R32G32B32)))
        goto error;
    if (PyModule_AddObject(m, "PIXELFORMAT_UNCOMPRESSED_R32G32B32A32", PyLong_FromLong(PIXELFORMAT_UNCOMPRESSED_R32G32B32A32)))
        goto error;
    if (PyModule_AddObject(m, "PIXELFORMAT_COMPRESSED_DXT1_RGB", PyLong_FromLong(PIXELFORMAT_COMPRESSED_DXT1_RGB)))
        goto error;
    if (PyModule_AddObject(m, "PIXELFORMAT_COMPRESSED_DXT1_RGBA", PyLong_FromLong(PIXELFORMAT_COMPRESSED_DXT1_RGBA)))
        goto error;
    if (PyModule_AddObject(m, "PIXELFORMAT_COMPRESSED_DXT3_RGBA", PyLong_FromLong(PIXELFORMAT_COMPRESSED_DXT3_RGBA)))
        goto error;
    if (PyModule_AddObject(m, "PIXELFORMAT_COMPRESSED_DXT5_RGBA", PyLong_FromLong(PIXELFORMAT_COMPRESSED_DXT5_RGBA)))
        goto error;
    if (PyModule_AddObject(m, "PIXELFORMAT_COMPRESSED_ETC1_RGB", PyLong_FromLong(PIXELFORMAT_COMPRESSED_ETC1_RGB)))
        goto error;
    if (PyModule_AddObject(m, "PIXELFORMAT_COMPRESSED_ETC2_RGB", PyLong_FromLong(PIXELFORMAT_COMPRESSED_ETC2_RGB)))
        goto error;
    if (PyModule_AddObject(m, "PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA", PyLong_FromLong(PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA)))
        goto error;
    if (PyModule_AddObject(m, "PIXELFORMAT_COMPRESSED_PVRT_RGB", PyLong_FromLong(PIXELFORMAT_COMPRESSED_PVRT_RGB)))
        goto error;
    if (PyModule_AddObject(m, "PIXELFORMAT_COMPRESSED_PVRT_RGBA", PyLong_FromLong(PIXELFORMAT_COMPRESSED_PVRT_RGBA)))
        goto error;
    if (PyModule_AddObject(m, "PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA", PyLong_FromLong(PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA)))
        goto error;
    if (PyModule_AddObject(m, "PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA", PyLong_FromLong(PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA)))
        goto error;
    if (PyModule_AddObject(m, "TEXTURE_FILTER_POINT", PyLong_FromLong(TEXTURE_FILTER_POINT)))
        goto error;
    if (PyModule_AddObject(m, "TEXTURE_FILTER_BILINEAR", PyLong_FromLong(TEXTURE_FILTER_BILINEAR)))
        goto error;
    if (PyModule_AddObject(m, "TEXTURE_FILTER_TRILINEAR", PyLong_FromLong(TEXTURE_FILTER_TRILINEAR)))
        goto error;
    if (PyModule_AddObject(m, "TEXTURE_FILTER_ANISOTROPIC_4X", PyLong_FromLong(TEXTURE_FILTER_ANISOTROPIC_4X)))
        goto error;
    if (PyModule_AddObject(m, "TEXTURE_FILTER_ANISOTROPIC_8X", PyLong_FromLong(TEXTURE_FILTER_ANISOTROPIC_8X)))
        goto error;
    if (PyModule_AddObject(m, "TEXTURE_FILTER_ANISOTROPIC_16X", PyLong_FromLong(TEXTURE_FILTER_ANISOTROPIC_16X)))
        goto error;
    if (PyModule_AddObject(m, "TEXTURE_WRAP_REPEAT", PyLong_FromLong(TEXTURE_WRAP_REPEAT)))
        goto error;
    if (PyModule_AddObject(m, "TEXTURE_WRAP_CLAMP", PyLong_FromLong(TEXTURE_WRAP_CLAMP)))
        goto error;
    if (PyModule_AddObject(m, "TEXTURE_WRAP_MIRROR_REPEAT", PyLong_FromLong(TEXTURE_WRAP_MIRROR_REPEAT)))
        goto error;
    if (PyModule_AddObject(m, "TEXTURE_WRAP_MIRROR_CLAMP", PyLong_FromLong(TEXTURE_WRAP_MIRROR_CLAMP)))
        goto error;
    if (PyModule_AddObject(m, "CUBEMAP_LAYOUT_AUTO_DETECT", PyLong_FromLong(CUBEMAP_LAYOUT_AUTO_DETECT)))
        goto error;
    if (PyModule_AddObject(m, "CUBEMAP_LAYOUT_LINE_VERTICAL", PyLong_FromLong(CUBEMAP_LAYOUT_LINE_VERTICAL)))
        goto error;
    if (PyModule_AddObject(m, "CUBEMAP_LAYOUT_LINE_HORIZONTAL", PyLong_FromLong(CUBEMAP_LAYOUT_LINE_HORIZONTAL)))
        goto error;
    if (PyModule_AddObject(m, "CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR", PyLong_FromLong(CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR)))
        goto error;
    if (PyModule_AddObject(m, "CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE", PyLong_FromLong(CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE)))
        goto error;
    if (PyModule_AddObject(m, "CUBEMAP_LAYOUT_PANORAMA", PyLong_FromLong(CUBEMAP_LAYOUT_PANORAMA)))
        goto error;
    if (PyModule_AddObject(m, "FONT_DEFAULT", PyLong_FromLong(FONT_DEFAULT)))
        goto error;
    if (PyModule_AddObject(m, "FONT_BITMAP", PyLong_FromLong(FONT_BITMAP)))
        goto error;
    if (PyModule_AddObject(m, "FONT_SDF", PyLong_FromLong(FONT_SDF)))
        goto error;
    if (PyModule_AddObject(m, "BLEND_ALPHA", PyLong_FromLong(BLEND_ALPHA)))
        goto error;
    if (PyModule_AddObject(m, "BLEND_ADDITIVE", PyLong_FromLong(BLEND_ADDITIVE)))
        goto error;
    if (PyModule_AddObject(m, "BLEND_MULTIPLIED", PyLong_FromLong(BLEND_MULTIPLIED)))
        goto error;
    if (PyModule_AddObject(m, "BLEND_ADD_COLORS", PyLong_FromLong(BLEND_ADD_COLORS)))
        goto error;
    if (PyModule_AddObject(m, "BLEND_SUBTRACT_COLORS", PyLong_FromLong(BLEND_SUBTRACT_COLORS)))
        goto error;
    if (PyModule_AddObject(m, "BLEND_CUSTOM", PyLong_FromLong(BLEND_CUSTOM)))
        goto error;
    if (PyModule_AddObject(m, "GESTURE_NONE", PyLong_FromLong(GESTURE_NONE)))
        goto error;
    if (PyModule_AddObject(m, "GESTURE_TAP", PyLong_FromLong(GESTURE_TAP)))
        goto error;
    if (PyModule_AddObject(m, "GESTURE_DOUBLETAP", PyLong_FromLong(GESTURE_DOUBLETAP)))
        goto error;
    if (PyModule_AddObject(m, "GESTURE_HOLD", PyLong_FromLong(GESTURE_HOLD)))
        goto error;
    if (PyModule_AddObject(m, "GESTURE_DRAG", PyLong_FromLong(GESTURE_DRAG)))
        goto error;
    if (PyModule_AddObject(m, "GESTURE_SWIPE_RIGHT", PyLong_FromLong(GESTURE_SWIPE_RIGHT)))
        goto error;
    if (PyModule_AddObject(m, "GESTURE_SWIPE_LEFT", PyLong_FromLong(GESTURE_SWIPE_LEFT)))
        goto error;
    if (PyModule_AddObject(m, "GESTURE_SWIPE_UP", PyLong_FromLong(GESTURE_SWIPE_UP)))
        goto error;
    if (PyModule_AddObject(m, "GESTURE_SWIPE_DOWN", PyLong_FromLong(GESTURE_SWIPE_DOWN)))
        goto error;
    if (PyModule_AddObject(m, "GESTURE_PINCH_IN", PyLong_FromLong(GESTURE_PINCH_IN)))
        goto error;
    if (PyModule_AddObject(m, "GESTURE_PINCH_OUT", PyLong_FromLong(GESTURE_PINCH_OUT)))
        goto error;
    if (PyModule_AddObject(m, "CAMERA_CUSTOM", PyLong_FromLong(CAMERA_CUSTOM)))
        goto error;
    if (PyModule_AddObject(m, "CAMERA_FREE", PyLong_FromLong(CAMERA_FREE)))
        goto error;
    if (PyModule_AddObject(m, "CAMERA_ORBITAL", PyLong_FromLong(CAMERA_ORBITAL)))
        goto error;
    if (PyModule_AddObject(m, "CAMERA_FIRST_PERSON", PyLong_FromLong(CAMERA_FIRST_PERSON)))
        goto error;
    if (PyModule_AddObject(m, "CAMERA_THIRD_PERSON", PyLong_FromLong(CAMERA_THIRD_PERSON)))
        goto error;
    if (PyModule_AddObject(m, "CAMERA_PERSPECTIVE", PyLong_FromLong(CAMERA_PERSPECTIVE)))
        goto error;
    if (PyModule_AddObject(m, "CAMERA_ORTHOGRAPHIC", PyLong_FromLong(CAMERA_ORTHOGRAPHIC)))
        goto error;
    if (PyModule_AddObject(m, "NPATCH_NINE_PATCH", PyLong_FromLong(NPATCH_NINE_PATCH)))
        goto error;
    if (PyModule_AddObject(m, "NPATCH_THREE_PATCH_VERTICAL", PyLong_FromLong(NPATCH_THREE_PATCH_VERTICAL)))
        goto error;
    if (PyModule_AddObject(m, "NPATCH_THREE_PATCH_HORIZONTAL", PyLong_FromLong(NPATCH_THREE_PATCH_HORIZONTAL)))
        goto error;

    // clang-format on

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
