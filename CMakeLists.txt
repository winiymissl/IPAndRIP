cmake_minimum_required(VERSION 3.28)
project(IPAndRIP)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_executable(IPAndRIP main.c)
target_link_libraries(IPAndRIP ${GTK3_LIBRARIES})