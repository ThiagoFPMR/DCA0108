# Define the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name and specify the programming language
project(CPUSchedulingTask LANGUAGES CXX)

# Include the directory for header files
include_directories(include)

# Collect all .cpp files from the src directory
file(GLOB SOURCES "src/*.cpp")

# Add an executable target with the collected source files
add_executable(CPUSchedulingTask ${SOURCES})