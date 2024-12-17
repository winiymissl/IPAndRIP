cmake_minimum_required(VERSION 3.28)
project(IPAndRIP)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

include_directories(${GTK4_INCLUDE_DIRS})
link_directories(${GTK4_LIBRARY_DIRS})

add_executable(IPAndRIP view/main.cpp
        settings.cpp
)
target_link_libraries(IPAndRIP ${GTK4_LIBRARIES})