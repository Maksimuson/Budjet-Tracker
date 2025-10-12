cmake_minimum_required(VERSION 3.10)

project(BudgetTracker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ”казываем путь к pkg-config дл€ MinGW
set(PKG_CONFIG_EXECUTABLE C:/msys64/mingw64/bin/pkg-config.exe)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_executable(BudgetTracker
    src/main.cpp
    src/app_window.h   
    src/app_window.cpp
    src/model.h
    src/model.cpp 
    src/storage.h
    src/storage.cpp )

target_link_libraries(BudgetTracker ${GTK3_LIBRARIES})
