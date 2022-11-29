cmake_minimum_required(VERSION 3.10)

set (APP_SOURCES
Color.cpp
Image.cpp
Main.cpp
Primitives.cpp
Tools.cpp
Utilities.cpp
Window.cpp
)

set (APP_HEADERS
Button.hpp
CordsPair.hpp
Widget.hpp
Window.hpp
Color.hpp
Event.hpp
Image.hpp
Main.hpp
Primitives.hpp
Tools.hpp
Utilities.hpp
)

set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(Graph ${APP_SOURCES} ${APP_HEADERS})

add_compile_options(-rdynamic -fpic)
target_link_libraries(Graph PRIVATE sfml-graphics sfml-window sfml-system)
set_property(TARGET Graph PROPERTY ENABLE_EXPORTS ON)