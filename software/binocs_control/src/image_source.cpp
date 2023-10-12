#include "image_source.h"

#ifdef BUILD_PI
#include <raspicam/
#endif

USBStereoSource::USBStereoSource(const std::string &dev_name) {
    cap.open(dev_name, cv::CAP_ANY);
    if (!cap.isOpened()) {
        throw std::runtime_error("Error!  Unable to open camera with name " + dev_name);
    }
}

image_collection_t USBStereoSource::getImages() {
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

USBMonocularSource::USBMonocularSource(const std::string &dev_name) {
    cap.open(dev_name, cv::CAP_ANY);
    if (!cap.isOpened()) {
        throw std::runtime_error("Error!  Unable to open camera with name " + dev_name);
    }
}

image_collection_t USBMonocularSource::getImages() {
    cap.read(raw_image);
    left_im = raw_image.clone();
    right_im = raw_image.clone();
    image_collection_t collection;
    collection.left_im = left_im;
    collection.right_im = right_im;
    return collection;
}

DualCameraSource::DualCameraSource(const std::string &left_cam_name,
                                   const std::string &right_cam_name) {

    #ifdef BUILD_PI
    #error "BUILDING PI"
    #else
        cap_left.open(left_cam_name);
        cap_right.open(right_cam_name);
    #endif


    if (!cap_left.isOpened()) {
        throw std::runtime_error("Error!  Unable to open camera with name " + left_cam_name);
    }

    if (!cap_right.isOpened()) {
        throw std::runtime_error("Error!  Unable to open camera with name " + right_cam_name);
    }
}

image_collection_t DualCameraSource::getImages() {
    cap_left.read(left_im);
    cap_right.read(right_im);
    image_collection_t collection;
    collection.left_im = left_im;
    collection.right_im = right_im;
    return collection;
}