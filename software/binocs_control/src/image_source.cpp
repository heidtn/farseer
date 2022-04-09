#include "image_source.h"

USBStereoSource::USBStereoSource(const std::string &dev_name) {
    cap.open(dev_name, cv::CAP_ANY);
    if (!cap.isOpened()) {
        throw std::runtime_error("Error!  Unable to open camera with name " + dev_name);
    }
}

image_collection_t USBStereoSource::GetImages() {
    cap.read(raw_image);
    int width = raw_image.cols; 
    int height = raw_image.rows;
    int halfpoint = width / 2;
    
    left_im = raw_image(cv::Range(0, height), cv::Range(0, halfpoint));
    right_im = raw_image(cv::Range(0, height), cv::Range(halfpoint, width));
    image_collection_t collection;
    collection.left_im = left_im;
    collection.right_im = right_im;
    return collection;
}