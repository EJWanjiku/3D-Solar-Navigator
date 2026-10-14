
cmake_minimum_required(VERSION 3.20)

project(ProjectStellar
    VERSION 1.0
    DESCRIPTION "Project Stellar - Solar System Computer Graphics"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Main project
add_executable(stellar
    src/main.cpp
)

# Digital Differential Analyzer line drawing algorithm
add_executable(digital_differential_analyzer
    src/digital_differential_analyzer.cpp
)

target_include_directories(stellar PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_include_directories(digital_differential_analyzer PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

add_executable(bresenham_line_drawing
    src/bresenham_line_drawing.cpp
)

target_include_directories(bresenham_line_drawing PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)