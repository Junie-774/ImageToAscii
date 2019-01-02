cmake_minimum_required(VERSION 3.13)
project(ImageToAscii)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(ImageToAscii main.cpp args.cpp args.h)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
