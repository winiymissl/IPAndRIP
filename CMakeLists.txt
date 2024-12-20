cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(IPAndRIP)

find_package(PkgConfig REQUIRED)
find_library(PCAP_LIB pcap PATHS /usr/local/opt/libpcap)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)
pkg_check_modules(JSON_GLIB REQUIRED json-glib-1.0)
pkg_check_modules(GTK4 REQUIRED gtk4)

include_directories(${GTK4_INCLUDE_DIRS})
link_directories(${GTK4_LIBRARY_DIRS})
include_directories(${JSON_GLIB_INCLUDE_DIRS})
link_directories(${JSON_GLIB_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})


add_executable(IPAndRIP view/main.cpp
        view/main.cpp
        view/MainWindow.cpp
        view/MainWindow.h
        view/PageRouteConfig.cpp
        view/PageRouteConfig.h
        view/PageRouteConfigAssistant.cpp
        view/PageRouteConfigAssistant.h
)

target_link_libraries(IPAndRIP ${GTK4_LIBRARIES})
target_link_libraries(IPAndRIP ${PCAP_LIB})
target_link_libraries(IPAndRIP ${JSON_GLIB_LIBRARIES})
target_link_libraries(IPAndRIP ${GTKMM_LIBRARIES})
