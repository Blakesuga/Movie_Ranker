cmake_minimum_required(VERSION 3.15)
project(MovieRanker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()
if(NOT MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
endif()

file(GLOB SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_executable(MovieRanker ${SOURCES}
        src/main.cpp
        src/quicksort.cpp
        src/weighted_score.cpp
        src/benchmark.h
        src/benchmark.cpp
        src/sorting.cpp)
        src/benchmark.cpp
        src/loader.cpp)

target_compile_definitions(MovieRanker PRIVATE DATA_DIR="${CMAKE_SOURCE_DIR}/data")

if(MSVC)
    target_compile_options(MovieRanker PRIVATE /W4)
else()
    target_compile_options(MovieRanker PRIVATE -Wall -Wextra)
endif()
