cmake_minimum_required(VERSION 3.10)
project(PthreadsTask)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(PthreadsTask main.cpp)
target_link_libraries(PthreadsTask ${OpenCV_LIBS})