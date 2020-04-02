#include "utils.h"

void * convert_imgsMT(void *args)
{
    auto c = (t_context *) args;
    auto len = (int) c->images_path.size();
    int old_value = 0;
    std::string path;

    while ((old_value = (*(c->atomic_counter))++) < len)
    {
        path = c->images_path[old_value];
        if(!x_action(path, (old_value+1)))
            exit(1);
    }
    return NULL;
}

int convert_imgs(std::vector<std::string> &images_path)
{
    int len = images_path.size();
    std::string path;

    for (int i = 0; i < len; ++i)
    {
        path = images_path[i];
        if (!x_action(path, (i+1)))
            return 1;
    }

    return 0;
}

cv::Mat do_something(const std::string& path)
{
	return cv::imread(path, CV_LOAD_IMAGE_GRAYSCALE);
}

int get_filepath_in_dir(std::vector<std::string> &images_path, const std::string &path)
{
    std::string file_path;
    for (const auto & entry : std::filesystem::directory_iterator(path))
    {
        file_path = (path + PATH + entry.path().filename().string());
        images_path.push_back(file_path);
    }
    return images_path.size();
}

void set_file_name(std::string &path, const int index)
{
    path = path.substr(0, path.find_last_of("\\/")) + PATH + IMAGE_NAME(index);
}

bool x_action(std::string &path, const int index)
{
    cv::Mat gray_img;
    gray_img = do_something(path);
    if (!gray_img.data)
    {
        std::cerr << "image cannot be read!" << std::endl;
        return false;
    }
    set_file_name(path, index);
    if (!cv::imwrite(path, gray_img))
    {
        std::cerr << "image cannot be writen to disk!" << std::endl;
        return false;
    }
    return true;
}

int run_image_to_gray_MT(const std::string &path, const int num_of_threads)
{
    std::vector<std::string> images_path(0);
    std::vector<pthread_t> threads((num_of_threads - 1));
    std::atomic<int> atomic_counter(0);
    int num_of_images = get_filepath_in_dir(images_path, path);

    struct t_context c = {&atomic_counter,
                          images_path};

    //init threads
    for (int i = 0; i < num_of_threads - 1; ++i)
        pthread_create(&(threads[i]), NULL, convert_imgsMT, &c);

    // n'th thread will be the main thread
    convert_imgsMT(&c);

    for (int i = 0; i < num_of_threads - 1; ++i)
        pthread_join(threads[i], NULL);

    return num_of_images;
}

int run_image_to_gray(const std::string &path)
{
    std::vector<std::string> images_path(0);
    int num_of_images = get_filepath_in_dir(images_path, path);
    if (convert_imgs(images_path) != 0)
        return -1;
    return num_of_images;
}