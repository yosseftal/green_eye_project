cmake_minimum_required(VERSION 3.14)
project(green_eye_image_to_gray)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenCV REQUIRED)

include_directories(.)

add_executable(green_eye_image_to_gray
        imageToGray.cpp
        ../utils/utils.cpp
        ../utils/utils.h)
target_link_libraries( green_eye_image_to_gray ${OpenCV_LIBS} )