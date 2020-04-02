#include "test.h"

int check_and_delete_images_from_dir(int num_of_images, const std::string &dir_path)
{
    std::string path;
    for (int i = 1; i <= num_of_images; i++)
    {
        path = dir_path + PATH + IMAGE_NAME(i);
        if(remove(path.std::string::c_str()) != 0)
            return 1;
    }
    return 0;
}

std::chrono::duration<double> test_image_to_gray_MT(const std::string &dir_path, const int num_of_threads)
{
    auto start = std::chrono::high_resolution_clock::now();
    int num_of_images = run_image_to_gray_MT(dir_path, num_of_threads);
    auto end = std::chrono::high_resolution_clock::now();

    assert(!check_and_delete_images_from_dir(num_of_images, dir_path));
    return end - start;
}

std::chrono::duration<double> test_image_to_gray(const std::string &dir_path)
{
    auto start = std::chrono::high_resolution_clock::now();
    int num_of_images = run_image_to_gray(dir_path);
    auto end = std::chrono::high_resolution_clock::now();

    assert(!check_and_delete_images_from_dir(num_of_images, dir_path));
    return end - start;
}

void benchmark_native_vs_multythread(std::string &path)
{
    std::chrono::duration<double> native{};
    std::chrono::duration<double> multi_threads{};

    for (int i = 0; i < NUM_OF_ITER; ++i)
    {
        native += test_image_to_gray(path);
        multi_threads += test_image_to_gray_MT(path, NUM_OF_THREADS);
    }
    native /= NUM_OF_ITER;
    multi_threads /= NUM_OF_ITER;

    std::cout << "average run time of native implementation: " << native.count()  <<  " microseconds" << std::endl;
    std::cout << "average run time of " << NUM_OF_THREADS << " multi threads implementation: " << multi_threads.count()  << " microseconds" << std::endl;
}

int test_do_something(std::string &path)
{
    cv::Mat gray_img = do_something(path);
    assert(gray_img.channels() == 1);
    return 0;
}

void test_runtime_vs_num_of_threads(const std::string &path, int max_num_of_threads)
{
    std::cout << "number of threads : runtime in microseconds" << std::endl;
    for (int i = 1; i <= max_num_of_threads; ++i)
    {
        std::chrono::duration<double> sum_runtime{};
        for (int j = 0; j < NUM_OF_ITER; ++j)
            sum_runtime += test_image_to_gray_MT(path, i);
        std::cout << i << " : " << (sum_runtime / NUM_OF_ITER).count() << std::endl;
    }
}

/**
 * run a benchmark between the implementations of ImageToGray.
 * check the runtime of the multi threads implementation vs number of threads.
 * @param argc argc should be always 2!
 * @param argv argv[1] should be the directory path
 */
int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "expected directory path as argument" << std::endl;
        return 1;
    }

    std::string path = argv[1];

    benchmark_native_vs_multythread(path);
    std::cout << std::endl;
    test_runtime_vs_num_of_threads(path, 10);

    return 0;
}