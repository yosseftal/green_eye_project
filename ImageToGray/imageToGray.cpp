#include "../utils/utils.h"

/**
 * a program that get a directory with images, convert them to gray scale and saves them to the disk
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
    run_image_to_gray(path);

    return 0;

}