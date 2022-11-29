
cmake_minimum_required(VERSION 3.10)

add_library(min MODULE MinTools/MinTools.hpp MinTools/MinTools.cpp)

set (Plugins
    min
)
file(MAKE_DIRECTORY "${PROJECT_SOURCE_DIR}/Plugins/")
set(CMAKE_VERBOSE_MAKEFILE ON)

foreach(Plugin ${Plugins})
# add_custom_command(TARGET ${Plugin} POST_BUILD        # Adds a post-build event to MyTest
    # COMMAND  ${CMAKE_COMMAND} -E copy_if_different      # which executes "cmake - E copy_if_different..."
        # "${PROJECT_SOURCE_DIR}/bin/pluginsrc/lib${Plugin}.so"    # <--this is in-file
        # "${PROJECT_SOURCE_DIR}/Plugins/${Plugin}.aboba.so") 
target_compile_definitions(${Plugin} PUBLIC PLUGIN)
endforeach()