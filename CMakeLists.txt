cmake_minimum_required(VERSION 3.5)
project(Project)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOURCES
src/Card.cpp
src/main.cpp
src/Head.cpp
src/helperfunctions.cpp
src/Deck.cpp
src/Node.cpp
src/Tree.cpp
)
add_executable(runme ${SOURCES})
