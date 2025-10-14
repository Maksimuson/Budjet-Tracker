cmake_minimum_required(VERSION 3.15)

project(BudgetTracker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Знайти pkg-config
find_package(PkgConfig REQUIRED)

# Підключити GTK3 через pkg-config
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# Виконувані файли
add_executable(BudgetTracker
    src/app_window.h
    src/model.h
    src/storage.h
    src/main.cpp
    src/app_window.cpp
    src/model.cpp
    src/storage.cpp
)

# Підключення директорій і бібліотек GTK
target_include_directories(BudgetTracker PRIVATE ${GTK3_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_directories(BudgetTracker PRIVATE ${GTK3_LIBRARY_DIRS})
target_compile_options(BudgetTracker PRIVATE ${GTK3_CFLAGS_OTHER})
target_link_libraries(BudgetTracker PRIVATE ${GTK3_LIBRARIES})
