cmake_minimum_required(VERSION 3.28)
project(IPAndRIP)

find_package(PkgConfig REQUIRED)
find_library(PCAP_LIB pcap PATHS /usr/local/opt/libpcap)

pkg_check_modules(GTK4 REQUIRED gtk4)

include_directories(${GTK4_INCLUDE_DIRS})
link_directories(${GTK4_LIBRARY_DIRS})


add_executable(IPAndRIP view/main.cpp
        view/gtk_page_route_config.h
)
target_link_libraries(IPAndRIP ${GTK4_LIBRARIES})
target_link_libraries(IPAndRIP ${PCAP_LIB})