/********************************************************************
**       This cc file is generated by program,                     **
**            Please do not change it directly.                    **
**                   Auther: brinkqiang                            **
********************************************************************/
// source: pymsgpackex.pkg

#include "pymsgpackex.pybind11.h"


#include "msgpack_fix32.hpp"

#include "msgpack_variant.hpp"

#include "msgpack_loader.hpp"

#include "creature_attr_def.msgpack.hpp"


#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <algorithm>

PYBIND11_MODULE(pymsgpackex, m) {

    pybind11::class_<Fix32>(m, "Fix32")
    .def(pybind11::init<>())
    .def("to_string", &Fix32::to_string, pybind11::return_value_policy::automatic_reference)
    .def("__str__", &Fix32::__str__, pybind11::return_value_policy::automatic_reference)
    .def_readwrite("value", &Fix32::value);

    pybind11::class_<Fix32Vec2>(m, "Fix32Vec2");

    pybind11::class_<Fix32Vec3>(m, "Fix32Vec3");

    pybind11::class_<CMsgPackLoader>(m, "CMsgPackLoader")
    .def(pybind11::init<>())
    .def("Init", &CMsgPackLoader::Init, pybind11::return_value_policy::automatic_reference)
    .def("UnInit", &CMsgPackLoader::UnInit, pybind11::return_value_policy::automatic_reference)
    .def("Load", &CMsgPackLoader::Load, pybind11::return_value_policy::automatic_reference)
    .def("Reload", &CMsgPackLoader::Reload, pybind11::return_value_policy::automatic_reference)
    .def("Save", &CMsgPackLoader::Save, pybind11::return_value_policy::automatic_reference)
    .def_readwrite("creature_attr_def_info", &CMsgPackLoader::creature_attr_def_info);

    pybind11::class_<creature_attr_def>(m, "creature_attr_def")
    .def(pybind11::init<>())
    .def_readwrite("maximun", &creature_attr_def::maximun)
    .def_readwrite("minimun", &creature_attr_def::minimun)
    .def_readwrite("use_centimeter", &creature_attr_def::use_centimeter)
    .def_readwrite("key", &creature_attr_def::key)
    .def_readwrite("defs", &creature_attr_def::defs)
    .def_readwrite("type", &creature_attr_def::type)
    .def_readwrite("desc", &creature_attr_def::desc)
    .def_readwrite("desc_bit", &creature_attr_def::desc_bit);

    pybind11::class_<creature_attr_def_data>(m, "creature_attr_def_data")
    .def(pybind11::init<>())
    .def("add", &creature_attr_def_data::add, pybind11::return_value_policy::automatic_reference)
    .def("get", &creature_attr_def_data::get, pybind11::return_value_policy::automatic_reference)
    .def("to_msgpack", &creature_attr_def_data::to_msgpack, pybind11::return_value_policy::automatic_reference)
    .def("from_msgpack", &creature_attr_def_data::from_msgpack, pybind11::return_value_policy::automatic_reference)
    .def("load", &creature_attr_def_data::load, pybind11::return_value_policy::automatic_reference)
    .def("save", &creature_attr_def_data::save, pybind11::return_value_policy::automatic_reference)
    .def_readwrite("data", &creature_attr_def_data::data);

}
