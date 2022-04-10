#include "display_device.h"

MonitorDisplay::MonitorDisplay() {

}

void MonitorDisplay::displayImages(image_collection_t collection) {
    cv::imshow("leftimage", collection.left_im);
    cv::imshow("rightimage", collection.right_im);
    cv::waitKey(1);
}