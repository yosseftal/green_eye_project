#ifndef GREEN_EYE_TEST_H
#define GREEN_EYE_TEST_H
#include <chrono>
#include "../utils/utils.h"
#include <cstdio>

// number of iteration to be performed for estimating the run time of each implementation
#define NUM_OF_ITER 10

/**
 * check that the desired images where writen to disk and delete them
 * @param num_of_images number of expected images
 * @param dir_path directory path
 * @return 0 iff all desired images where found and deleted
 */
int check_and_delete_images_from_dir(int num_of_images, const std::string &dir_path);

/**
 * check how much time it take to simulate ImageToGrayMT.cpp
 * @param dir_path directory path
 * @param num_of_threads number of threads to run in parallel
 * @return time in microseconds
 */
std::chrono::duration<double> test_image_to_gray_MT(const std::string &dir_path, const int num_of_threads);

/**
 * check how much time it take to simulate ImageToGray.cpp
 * @param dir_path directory path
 * @return time in microseconds
 */
std::chrono::duration<double> test_image_to_gray(const std::string &dir_path);

/**
 * run the 2 implementation of ImageToGray and print the average run time of each.
 * number of iteration is specified in #define NUM_OF_ITER
 * @param path directory path
 */
void benchmark_native_vs_multythread(std::string &path);

/**
 * check that a given image is converted to gray scale
 * @param path path to image
 */
int test_do_something(std::string &path);

/**
 * check the runtime of the multi threads implementation vs number of threads
 * @param path directory path
 * @param max_num_of_threads
 */
void test_runtime_vs_num_of_threads(const std::string &path, int max_num_of_threads);

#endif //GREEN_EYE_TEST_H
