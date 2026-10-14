
cmake_minimum_required(VERSION 3.20)

project(ProjectStellar
    VERSION 1.0
    DESCRIPTION "Project Stellar - Solar System Computer Graphics"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(stellar
    src/main.cpp
)

target_include_directories(stellar PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)
