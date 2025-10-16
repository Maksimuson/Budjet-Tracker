cmake_minimum_required(VERSION 3.10)
project(BudgetTracker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------------------
# 1. Way to pkg-config
# ------------------------------------
set(PKG_CONFIG_EXECUTABLE "C:/msys64/mingw64/bin/pkg-config.exe")

# ------------------------------------
# 2. Connect GTK
# ------------------------------------
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# Конвертація шляхів із UNIX у Windows формат
foreach(_var IN ITEMS GTK3_INCLUDE_DIRS GTK3_LIBRARY_DIRS)
    if(${_var})
        file(TO_CMAKE_PATH "${${_var}}" ${_var})
    endif()
endforeach()

# ------------------------------------
# 3. Folders, libraries
# ------------------------------------
include_directories(${GTK3_INCLUDE_DIRS} src)
link_directories(${GTK3_LIBRARY_DIRS})

# ------------------------------------
# 4. Build file 
# ------------------------------------
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/app_window.cpp
    src/storage.cpp
    src/model.cpp
    src/app_window.h
    src/storage.h
    src/model.h

)

target_link_libraries(${PROJECT_NAME} ${GTK3_LIBRARIES})

# ------------------------------------
# 5. Copying GTK DLLs during build
# ------------------------------------
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "C:/msys64/mingw64/bin"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
)
