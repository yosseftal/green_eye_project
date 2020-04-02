#include "../utils/utils.h"


/**
 * a program that get a directory with images, convert them to gray scale and save to the disk
 * the program runs multi threads
 * @param argc should be always 2!
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
    run_image_to_gray_MT(path, NUM_OF_THREADS);
//	std::vector<std::string> images_path(0);
//	std::vector<pthread_t> threads((NUM_OF_THREADS - 1));
//    std::atomic<int> atomic_counter(0);
//    get_filepath_in_dir(images_path, path);
//
//	struct t_context c = {&atomic_counter,
//						  images_path};
//
//	//init threads
//    for (int i = 0; i < NUM_OF_THREADS - 1; ++i)
//        pthread_create(&(threads[i]), NULL, convert_imgsMT, &c);
//
//    // n'th thread will be the main thread
//    convert_imgsMT(&c);
//
//    for (int i = 0; i < NUM_OF_THREADS - 1; ++i)
//        pthread_join(threads[i], NULL);

    return 0;
}