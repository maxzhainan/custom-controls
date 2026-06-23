cmake_minimum_required(VERSION 3.10)
project(CoreArchitecture)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

# Add source files
set(SOURCES
    src/ExpressionEvaluator.cpp
    src/Control.cpp
    src/ButtonControl.cpp
    src/JoystickControl.cpp
    src/LayoutManager.cpp
    src/InputDispatcher.cpp
)

# Create library
add_library(core_architecture STATIC ${SOURCES})

# Optional: Example executable
add_executable(core_example examples/example.cpp)
target_link_libraries(core_example core_architecture)

# Include nlohmann/json (header-only)
# Download from: https://github.com/nlohmann/json/releases
# Or install via: apt-get install nlohmann-json3-dev
