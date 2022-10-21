#include <pybind11/pybind11.h>
#include "pybind11_tests.h"

int add(int a, int b) {
    return a + b;
}

TEST_SUBMODULE(test_math, m) {
    m.def("add", &add, "add");
    m.def("ADD", [](int a, int b) -> int { return a + b; });
}