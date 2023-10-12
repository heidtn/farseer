#ifndef BINOCS_CONTROL_IMAGE_STABALIZATION_
#define BINOCS_CONTROL_IMAGE_STABALIZATION_

#include "image_source.h"
#include <opencv2/opencv.hpp>

/**
 * @brief stabalizes the incoming images
 * 
 * @details much of this code was pulled from here: https://learnopencv.com/video-stabilization-using-point-feature-matching-in-opencv/
 * 
 */

struct TransformParam {
    TransformParam() {
        dx = 0.0;
        dy = 0.0;
        da = 0.0;
    }
    TransformParam(double _dx, double _dy, double _da) {
        dx = _dx;
        dy = _dy;
        da = _da;
    }

    double dx;
    double dy;
    double da; // angle

    void getTransform(cv::Mat &T) {
        // Reconstruct transformation matrix accordingly to new values
        T.at<double>(0, 0) = cos(da);
        T.at<double>(0, 1) = -sin(da);
        T.at<double>(1, 0) = sin(da);
        T.at<double>(1, 1) = cos(da);

        T.at<double>(0, 2) = dx;
        T.at<double>(1, 2) = dy;
    }

    void setTransform(const cv::Mat &T) {
        dx = T.at<double>(0, 2);
        dy = T.at<double>(1, 2);

        // Extract rotation angle
        da = atan2(T.at<double>(1, 0), T.at<double>(0, 0));
    }

    TransformParam operator+(const TransformParam b) const {
        double new_dx = dx + b.dx;
        double new_dy = dy + b.dy;
        double new_da = da + b.da;
        return TransformParam(new_dx, new_dy, new_da);
    }

    TransformParam operator*(const double b) const {
        return TransformParam(dx * b, dy * b, da * b);
    }

    float length_2d() {
        return sqrt(dx*dx + dy*dy);
    }

    void normalize() {
        float length = length_2d();
        dx /= length;
        dy /= length;
    }

    void operator+=(const TransformParam b) {
        dx += b.dx;
        dy += b.dy;
        da += b.da;
    }
};

class ImageStabalization {
  public:
    image_collection_t stabalizeImages(image_collection_t collection);

  private:
    image_collection_t last_images;
    TransformParam last_transform;
    TransformParam summed_transform;
    // the smoothing parameter for subsequent positions
    double alpha = 0.5;
};

#endif