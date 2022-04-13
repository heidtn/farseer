#include "display_device.h"
#include <X11/Xlib.h>

MonitorDisplay::MonitorDisplay() {}

void MonitorDisplay::displayImages(image_collection_t collection) {
    cv::imshow("leftimage", collection.left_im);
    cv::imshow("rightimage", collection.right_im);
    cv::waitKey(1);
}

SimpleStereoViewer::SimpleStereoViewer() {
    cv::namedWindow("View", cv::WND_PROP_FULLSCREEN);
    cv::setWindowProperty("View", cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);

    //width = cv::getWindowImageRect("View").width;
    //height = cv::getWindowImageRect("View").height;

    Display* disp = XOpenDisplay(0);
    Screen*  scrn = DefaultScreenOfDisplay(disp);
    width  = scrn->width;
    height = scrn->height;

    view_buffer.create(height, width, CV_8UC3);
    //view_buffer = cv::Mat::zeros(width, height, CV_8UC3);

    interpupilary_distance = width / 8;
}

void SimpleStereoViewer::displayImages(image_collection_t collection) {
    int row_start = (height / 2) - (collection.left_im.rows / 2);
    int left_col_start = (width / 2) - (collection.left_im.cols / 2) - (interpupilary_distance / 2);
    int right_col_start = left_col_start + interpupilary_distance;

    collection.left_im.copyTo(view_buffer(cv::Rect(left_col_start, row_start, collection.left_im.cols, collection.left_im.rows)));
    collection.right_im.copyTo(view_buffer(cv::Rect(right_col_start, row_start, collection.right_im.cols, collection.right_im.rows)));

    
    std::cout << cv::getWindowImageRect("View") << std::endl;

    cv::imshow("View", view_buffer);
    cv::waitKey(1);
}