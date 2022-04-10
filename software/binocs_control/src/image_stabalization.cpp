#include "image_stabalization.h"

static void fixBorder(cv::Mat &frame_stabilized)
{
  cv::Mat T = cv::getRotationMatrix2D(cv::Point2f(frame_stabilized.cols/2, frame_stabilized.rows/2), 0, 1.04); 
  cv::warpAffine(frame_stabilized, frame_stabilized, T, frame_stabilized.size()); 
}

image_collection_t ImageStabalization::stabalizeImages(image_collection_t collection) {
    image_collection_t processed_images;
    processed_images.left_im = collection.left_im.clone();
    processed_images.right_im = collection.right_im.clone();

    cv::Mat left_gray, right_gray;
    cv::cvtColor(collection.left_im, left_gray, cv::COLOR_BGR2GRAY);
    cv::cvtColor(collection.right_im, right_gray, cv::COLOR_BGR2GRAY);
    //ImageStabalization();

    if (last_images.left_im.empty()) {
        last_images.left_im = left_gray.clone();
        last_images.right_im = right_gray.clone();
        return processed_images;
    }

    // calculate good features to track
    std::vector<cv::Point2f> cur_pts, prev_pts;
    cv::goodFeaturesToTrack(last_images.left_im, prev_pts, 200, 0.01, 30);

    std::vector<uchar> status;
    std::vector<float> err;
    cv::calcOpticalFlowPyrLK(last_images.left_im, left_gray, prev_pts, cur_pts, status, err);

    // Filter only valid points
    auto prev_it = prev_pts.begin();
    auto curr_it = cur_pts.begin();
    for (size_t k = 0; k < status.size(); k++) {
        if (status[k]) {
            prev_it++;
            curr_it++;
        } else {
            prev_it = prev_pts.erase(prev_it);
            curr_it = cur_pts.erase(curr_it);
        }
    }

    // Find transformation matrix
    cv::Mat T;
    if(cur_pts.size() != 0) {
        T = cv::estimateRigidTransform(prev_pts, cur_pts, false);
    }

    // In rare cases no transform is found.
    // We'll just use the last known good transform.
    TransformParam cur_transform;
    if (T.data == NULL) {
        cv::Mat empty(cv::Size(3, 2), CV_64F);
        cur_transform.setTransform(empty);
    } else {
        cur_transform.setTransform(T);
    }

    TransformParam zero_transform;
    summed_transform += cur_transform;

    TransformParam smoothed_transform;
    summed_transform = summed_transform*alpha + zero_transform*(1.0-alpha);
    smoothed_transform = summed_transform*-1.0;

    cv::Mat smoothed_matrix(cv::Size(3, 2), CV_64F);
    smoothed_transform.getTransform(smoothed_matrix);

    // Apply affine wrapping to the given frame
    cv::warpAffine(collection.left_im, processed_images.left_im, smoothed_matrix,
                   collection.left_im.size());
    cv::warpAffine(collection.right_im, processed_images.right_im, smoothed_matrix,
                   collection.right_im.size());

    // Scale image to remove black border artifact
    fixBorder(processed_images.left_im);
    fixBorder(processed_images.right_im);

    last_images.left_im = left_gray.clone();
    last_images.right_im = right_gray.clone();

    return processed_images;
}