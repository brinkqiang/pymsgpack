# -*- coding: utf-8 -*-
import pytest

m = pytest.importorskip("pybind11_tests.test_math")

print(m.add(123, 456))