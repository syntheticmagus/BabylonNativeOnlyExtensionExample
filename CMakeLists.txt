set(SOURCES 
    "Include/Babylon/Extensions/NativeOnlyExtension.h"
    "Source/NativeOnlyExtension.cpp")

    
add_library(NativeOnlyExtension ${SOURCES})
warnings_as_errors(NativeOnlyExtension)

add_on_linked_as_dependency_cmake_file(NativeOnlyExtension "${CMAKE_CURRENT_SOURCE_DIR}/OnLinkedAsDependency.cmake")
set(NATIVE_ONLY_EXTENSION_JS_SCRIPT_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/Scripts/NativeOnlyExtension.js"
    CACHE STRING "NativeOnlyExtension JS script files")

target_include_directories(NativeOnlyExtension PRIVATE "Include/Babylon/Extensions")
target_include_directories(NativeOnlyExtension INTERFACE "Include")

target_link_to_dependencies(NativeOnlyExtension
    PUBLIC napi
    PUBLIC ScriptLoader)

set(BABYLON_NATIVE_PLAYGROUND_EXTENSION_LIBRARIES
    ${BABYLON_NATIVE_PLAYGROUND_EXTENSION_LIBRARIES}
    PRIVATE NativeOnlyExtension
    CACHE INTERNAL "")

set_property(TARGET NativeOnlyExtension PROPERTY FOLDER Extensions)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})
