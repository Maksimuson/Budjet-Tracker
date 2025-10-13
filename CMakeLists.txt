cmake_minimum_required(VERSION 3.10)

project(BudgetTracker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(BudgetTracker
    src/main.cpp
    src/app_window.h   
    src/app_window.cpp
    src/model.h
    src/model.cpp 
    src/storage.h
    src/storage.cpp )

target_link_libraries(BudgetTracker ${GTK3_LIBRARIES})
