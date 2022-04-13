#include "display_device.h"
#include <X11/Xlib.h>

MonitorDisplay::MonitorDisplay() {}

void MonitorDisplay::displayImages(image_collection_t collection) {
    cv::imshow("leftimage", collection.left_im);
    cv::imshow("rightimage", collection.right_im);
    cv::waitKey(1);
}

SimpleStereoViewer::SimpleStereoViewer(int _interpupilary_distance, int _eye_width, int _eye_height) {
    cv::namedWindow("View", cv::WND_PROP_FULLSCREEN);
    cv::setWindowProperty("View", cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
    eye_width = _eye_width;
    eye_height = _eye_height;
    interpupilary_distance = _interpupilary_distance;

    Display* disp = XOpenDisplay(0);
    Screen*  scrn = DefaultScreenOfDisplay(disp);
    width  = scrn->width;
    height = scrn->height;

    view_buffer.create(height, width, CV_8UC3);
}

void SimpleStereoViewer::displayImages(image_collection_t collection) {
    cv::Mat resized_left;
    cv::Mat resized_right;

    cv::resize(collection.left_im, resized_left, cv::Size(eye_width, eye_height));
    cv::resize(collection.right_im, resized_right, cv::Size(eye_width, eye_height));

    int row_start = (height / 2) - (resized_left.rows / 2);
    int left_col_start = (width / 2) - (resized_left.cols / 2) - (interpupilary_distance / 2);
    int right_col_start = left_col_start + interpupilary_distance;

    resized_left.copyTo(view_buffer(cv::Rect(left_col_start, row_start, resized_left.cols, resized_left.rows)));
    resized_right.copyTo(view_buffer(cv::Rect(right_col_start, row_start, resized_right.cols, resized_right.rows)));

    cv::imshow("View", view_buffer);
    cv::waitKey(1);
}