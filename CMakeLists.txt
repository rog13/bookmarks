cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project("Bookmarks")
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Qml Quick Concurrent)
add_subdirectory(src)
