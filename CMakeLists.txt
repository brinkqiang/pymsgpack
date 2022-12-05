cmake_minimum_required(VERSION 3.2)

PROJECT(pymsgpack)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
INCLUDE(cmake/PythonModuleImport.cmake)

ModuleSetCompileOptions()
ModuleSetUseFolders()

SET(DMCONFIG_VERSION_MAJOR "1")
SET(DMCONFIG_VERSION_MINOR "0")
SET(DMCONFIG_VERSION_PATCH "1")
SET(DMCONFIG_VERSION "${DMCONFIG_VERSION_MAJOR}.${DMCONFIG_VERSION_MINOR}.${DMCONFIG_VERSION_PATCH}")

MESSAGE(STATUS "VERSION: ${DMCONFIG_VERSION}")

find_package(PythonInterp 2.7 REQUIRED)
find_package(PythonLibs 2.7 REQUIRED)
find_package(Python 2.7 REQUIRED OPTIONAL_COMPONENTS NumPy)

if (PYTHONLIBS_FOUND)
    include_directories(${PYTHON_INCLUDE_DIRS})
    LINK_DIRECTORIES(${PYTHON_INCLUDE_DIRS}/../libs)
endif ()

ModuleInclude("dmformat" "thirdparty/dmformat")

ModuleImport("dmpybind11" "thirdparty/dmpybind11")
ModuleImport("dmtest" "thirdparty/dmtest")
ModuleImport("dmmsgpack" "thirdparty/dmmsgpack")

PyModuleImport("module" "dmtest;pybind11::module;${PYTHON_LIBRARIES}")

ExeImport("test" "dmtest;pymsgpack;pybind11::module;${PYTHON_LIBRARIES}")
ExeImport("tools" "dmtest;pymsgpack;pybind11::module;${PYTHON_LIBRARIES}")

ADD_CUSTOM_COMMAND(
    TARGET pymsgpack
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/module/pymsgpack/pymsgpack.py
    ${CMAKE_CURRENT_SOURCE_DIR}/file/creature_attr_def.py.bin  
    ${CMAKE_CURRENT_SOURCE_DIR}/file/model.py.bin  
    $<TARGET_FILE_DIR:pymsgpack>
)
