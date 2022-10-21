
macro(SUBDIRLIST result curdir)
FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
SET(dirlist "")
FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
        LIST(APPEND dirlist ${child})
    ENDIF()
ENDFOREACH()
SET(${result} ${dirlist})
endmacro()

macro(PyModuleImport ModulePath DependsLib)
MESSAGE(STATUS "PyModuleImport ${ModulePath} ${DependsLib}")

IF (IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${ModulePath})
    SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR}/${ModulePath})
    FOREACH(subdir ${SUBDIRS})
        MESSAGE(STATUS "INCLUDE -> ${CMAKE_CURRENT_SOURCE_DIR}/${ModulePath}/${subdir}")
        INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/${ModulePath}/${subdir})
        FILE(GLOB_RECURSE BIN_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/${ModulePath}/${subdir}/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/${ModulePath}/${subdir}/*.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/${ModulePath}/${subdir}/*.c
        ${CMAKE_CURRENT_SOURCE_DIR}/${ModulePath}/${subdir}/*.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/${ModulePath}/${subdir}/*.h)

        LIST(FILTER BIN_SOURCES EXCLUDE REGEX "${CMAKE_CURRENT_SOURCE_DIR}/${ModulePath}/${subdir}/tpl/*")

        MESSAGE(STATUS "BIN_SOURCES ${LIB_SOURCES}")

        ADD_LIBRARY(${subdir} SHARED ${BIN_SOURCES})
        TARGET_LINK_LIBRARIES(${subdir} ${DependsLib})

        IF (UNIX OR APPLE)
          set_property (TARGET ${subdir} PROPERTY PREFIX "")
        ELSEIF(WIN32)
          set_property (TARGET ${subdir} PROPERTY SUFFIX ".pyd")
        ENDIF()

        MESSAGE(STATUS $<TARGET_FILE:${subdir}>)
        ADD_CUSTOM_COMMAND(
        TARGET ${subdir} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/${ModulePath}/${subdir}/${subdir}.py
        $<TARGET_FILE_DIR:${subdir}>
        )

    ENDFOREACH()
ENDIF()

endmacro(PyModuleImport)
