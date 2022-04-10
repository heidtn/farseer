#include "image_source.h"
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include "image_stabalization.h"

using namespace cv;

int main(int argc, char **argv) {
    USBStereoSource source("/dev/video4");
    ImageStabalization stabalizer;

    while (true) {
        auto res = source.GetImages();
        auto stabalized = stabalizer.stabalizeImages(res);

        cv::imshow("frame", res.left_im);
        cv::imshow("filtered", stabalized.left_im);
        auto key = cv::waitKey(1);
        if(key == 'q') {
            return 0;
        }
    }
    return 0;
}
