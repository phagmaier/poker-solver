cmake_minimum_required(VERSION 3.20)

# Set the project name and version
project(MyProject VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find the Raylib package using pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(RAYLIB REQUIRED raylib)

# Find all .cpp files in the src directory
#file(GLOB SOURCES "src/*.cpp")

# Specify your executable
#add_executable(runme ${SOURCES})
add_executable(runme "main.cpp")

# Include directories
target_include_directories(runme PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${RAYLIB_INCLUDE_DIRS}
)

# Link the libraries
target_link_libraries(runme PRIVATE ${RAYLIB_LIBRARIES})
