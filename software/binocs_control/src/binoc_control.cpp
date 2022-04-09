#include "image_source.h"
#include <opencv2/opencv.hpp>
#include <stdio.h>

using namespace cv;

int main(int argc, char **argv) {
    USBStereoSource source("/dev/video4");

    while (true) {
        auto res = source.GetImages();
        cv::imshow("frame", res.left_im);
        auto key = cv::waitKey(1);
        if(key == 'q') {
            return 0;
        }
    }
    return 0;
}
