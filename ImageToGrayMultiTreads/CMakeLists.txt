cmake_minimum_required(VERSION 3.14)
project(green_eye_image_to_gray_MT)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenCV REQUIRED)

include_directories(.)

add_executable(green_eye_image_to_gray_MT
        imageToGrayMT.cpp
        ../utils/utils.cpp
        ../utils/utils.h)
target_link_libraries( green_eye_image_to_gray_MT ${OpenCV_LIBS} )