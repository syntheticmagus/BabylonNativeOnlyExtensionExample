set(EXTENSION_NAME "HelloExtensions")

set(SOURCES 
    "Include/Babylon/Extensions/HelloExtensions.h"
    "Source/HelloExtensions.cpp")

add_library(${EXTENSION_NAME} ${SOURCES})
warnings_as_errors(${EXTENSION_NAME})

target_include_directories(${EXTENSION_NAME} PRIVATE "Include/Babylon/Extensions")
target_include_directories(${EXTENSION_NAME} INTERFACE "Include")

target_link_to_dependencies(${EXTENSION_NAME}
    PUBLIC JsRuntime)

set(BABYLON_NATIVE_PLAYGROUND_EXTENSION_LIBRARIES
    ${BABYLON_NATIVE_PLAYGROUND_EXTENSION_LIBRARIES}
    PRIVATE ${EXTENSION_NAME}
    CACHE INTERNAL "")

set_property(TARGET ${EXTENSION_NAME} PROPERTY FOLDER Extensions)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})
