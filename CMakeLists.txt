cmake_minimum_required(VERSION 3.21)
project(CustomControls)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/toolchain.cmake")
endif()

add_library(${PROJECT_NAME} SHARED
    src/main.cpp
    src/ControlsManager.cpp
    src/ConfigManager.cpp
    src/UIRenderer.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall -Wextra -O3
)

if(ANDROID)
    find_package(game-activity REQUIRED CONFIG)
    target_link_libraries(${PROJECT_NAME} PRIVATE game-activity::game-activity)
endif()
