#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <filesystem>
#include <pthread.h>
#include <atomic>

#define PATH "\\"
#define IMAGE(i) "image_" + std::to_string(i)
#define JPG ".jpg"
#define IMAGE_NAME(i) IMAGE(i) + JPG
#define NUM_OF_THREADS 9

/**
 * represents the context each thread needs for running the program
 */
struct t_context
{
    std::atomic<int> *atomic_counter;
    const std::vector<std::string> &images_path;
};

/**
 * converts all images in args to gray scale for each thread
 * @param args the arguments for each thread
 */
void * convert_imgsMT(void *args);

/**
 * converts all images in args to gray scale
 * @param images_path reference to a vector with all images to be converted
 * @return 0 on success and 1 on failure
 */
int convert_imgs(std::vector<std::string> &images_path);

/**
 * convert an image to gray scale
 * @param path the path for the image
 * @return cv::Mat object represents the new image
 */
cv::Mat do_something(const std::string& path);

/**
 * get all files from a directory
 * @param images_path reference vector to contain all paths
 * @param path directory path
 * @return number of files in directory
 */
int get_filepath_in_dir(std::vector<std::string> &images_path, const std::string &path);

/**
 * change &path to be of the form: "/image_i.jpg" while i is the index of the file
 */
void set_file_name(std::string &path, const int index);

/**
 * convert an image to gray scale and save it to the disk
 * @param path image path
 * @param index index of the image to be saved
 * @return true iff succeed
 */
bool x_action(std::string &path, const int index);

/**
 * convert images in given directory to gray scale and save them to disk.
 * the function runs with multiple threads in parallel
 * @param path directory path
 * @param num_of_threads
 * @return number of images in the given directory. in case of an error the code will do 'exit(1)'
 */
int run_image_to_gray_MT(const std::string &path, int num_of_threads);

/**
 * convert images in given directory to gray scale and save them to disk
 * @param path directory path
 * @return number of images in the given directory. in case of error return -1.
 */
int run_image_to_gray(const std::string &path);

#endif //UTILS_H