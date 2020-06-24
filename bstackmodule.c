#include <Python.h>

typedef struct BNode {
  PyObject *data;
  struct BNode *next;
} BNode;

typedef struct BStack {
    PyObject_HEAD
    unsigned int count;
    struct BNode *head;
} BStack;

static int BStack_init(BStack *self, PyObject *args, PyObject *kwds) {
  self->count = 0;
  self->head = NULL;
  return 0;
}

static void BStack_dealloc(BStack *self) {
  if(self->count == 0 && self->head == NULL) return;
  do {
    BNode *n = self->head;
    self->head = n->next;
    Py_TYPE(self)->tp_free((PyObject *) self);
  } while(self->head != NULL);
  self->count = 0;
}

static PyObject* BStack_push(BStack *self, PyObject *args) {
  PyObject *obj;
  if(!PyArg_ParseTuple(args, "O", &obj)) {
    return NULL;
  }
  BNode *bn = malloc(sizeof(BNode));
  bn->data = obj;
  bn->next = self->head;
  self->head = bn;
  self->count++;
  Py_INCREF(obj);
  Py_RETURN_NONE;
}

static PyObject* BStack_pop(BStack *self, PyObject *args) {
  BNode *bn = self->head;
  self->head = bn->next;
  PyObject *nData = bn->data;
  Py_DECREF(nData);
  free(bn);
  self->count--;
  return nData;
}

static PyMethodDef BStack_methods[] = {
    {"push", (PyCFunction) BStack_push, METH_VARARGS, "Push a value to the stack object"},
    {"pop", (PyCFunction) BStack_pop, METH_NOARGS, "Pop a value from the stack object"},
    {NULL}  /* Sentinel */
};

static PyTypeObject BStackType = {
  PyVarObject_HEAD_INIT(NULL, 0)
  .tp_name = "bcollections.bstack",
  .tp_doc = "Custom Stack",
  .tp_basicsize = sizeof(BStack),
  .tp_itemsize = 0,
  .tp_flags = Py_TPFLAGS_DEFAULT,
  .tp_new = PyType_GenericNew,
  .tp_init = (initproc) BStack_init,
  .tp_dealloc = (destructor) BStack_dealloc,
  .tp_methods = BStack_methods
};

static PyModuleDef bcollectionsmodule = {
  PyModuleDef_HEAD_INIT,
  .m_name = "bcollections",
  .m_doc = "A module implementing my own data structure module.",
  .m_size = -1,
};

PyMODINIT_FUNC PyInit_bcollections() {
  if(PyType_Ready(&BStackType) < 0) {
    return NULL;
  }
  PyObject *m = PyModule_Create(&bcollectionsmodule);
  if(m == NULL) {
    return NULL;
  }
  Py_INCREF(&BStackType);
  PyModule_AddObject(m, "BStack", (PyObject *) &BStackType);
  return m;
}
