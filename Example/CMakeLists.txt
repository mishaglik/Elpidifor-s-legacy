cmake_minimum_required(VERSION 3.10)

project(Elpidifor VERSION 3.0)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR}/..)
file(MAKE_DIRECTORY "./bin/")
file(MAKE_DIRECTORY "./Plugins/")
add_subdirectory(${PROJECT_SOURCE_DIR}/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/pluginsrc)
