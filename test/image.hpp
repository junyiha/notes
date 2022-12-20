#include "base.hpp"


class Image : public Base
{
public:
    std::string m_file;
    std::string m_dir_path;

public:
    Image();

    virtual ~Image();

public:
    int PngToJpeg();
};

Image::Image() {

}

Image::~Image() {

}

int Image::PngToJpeg() {
    std::string pre_str;
    std::string post_str;
    std::vector <std::string> files;

    cv::namedWindow("tmp", cv::WINDOW_NORMAL);
    OpenDir(m_dir_path.c_str(), files);
    
    for (int i = 0; i < files.size(); i++) {
        printf("%s \n", files[i].c_str());
        SeparationName(files[i].c_str(), pre_str, post_str);
        
        if (strcmp(post_str.c_str(), "jpg") == 0) {
            cv::Mat frame = cv::imread(files[i].c_str());
            cv::imshow("tmp",frame);
            cv::waitKey(200);
        }
    }

    return 0;
}