# Callback to perform custom behavior -- in this case, copying runtime output artifacts like DLLs -- when 
# linked from an executable target as a library.
function(on_linked_as_dependency target)
    # Propagate this file to the target so that it will be transitively available to targets that
    # link to that one, too.
    propagate_on_linked_as_dependency_cmake_file(NativeOnlyExtension ${target})

    # We only need to actually copy files if we're being linked from an executable.
    get_target_property(type ${target} TYPE)
    if(${type} STREQUAL "EXECUTABLE")
        target_sources(${target} PUBLIC ${NATIVE_ONLY_EXTENSION_JS_SCRIPT_FILES})
        source_group(Scripts ${NATIVE_ONLY_EXTENSION_JS_SCRIPT_FILES})
        foreach(script ${NATIVE_ONLY_EXTENSION_JS_SCRIPT_FILES})
            get_filename_component(scriptName ${script} NAME)
            # add_custom_command(
            #     TARGET ${target}
            #     POST_BUILD 
            #     COMMAND ${CMAKE_COMMAND} -E copy_if_different ${script} $<TARGET_FILE_DIR:${target}>/Scripts/${scriptName})
            add_custom_command(
                OUTPUT "Scripts/${scriptName}"
                COMMAND "${CMAKE_COMMAND}" -E copy "${script}" "${CMAKE_CURRENT_BINARY_DIR}/Scripts/${scriptName}"
                COMMENT "Copying ${scriptName}"
                MAIN_DEPENDENCY "${script}")
        endforeach(script)
    endif()
endfunction()
