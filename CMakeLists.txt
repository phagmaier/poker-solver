cmake_minimum_required(VERSION 3.31)
project(Project)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add optimization flags (this will enable maximum optimizations)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # Disable optimizations in Debug mode to make debugging easier
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
else()
    # Enable aggressive optimizations in non-debug builds
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -funroll-loops -fomit-frame-pointer -flto")
endif()

# Specify the source files
set(SOURCES
    src/Card.cpp
    src/main.cpp
    src/make_dics.cpp
    src/Deck.cpp
    src/hand_evaluator.cpp
)

# Create the executable
add_executable(runme ${SOURCES})

