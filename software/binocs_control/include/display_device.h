#ifndef BINOCS_CONTROL_DISPLAY_DEVICE_
#define BINOCS_CONTROL_DISPLAY_DEVICE_

#include "image_source.h"

class iDisplayDevice {
  public:
    virtual void displayImages(image_collection_t collection) = 0;
};

class MonitorDisplay : public iDisplayDevice {
  public:
    MonitorDisplay();
    void displayImages(image_collection_t collection);
};

class SimpleStereoViewer : public iDisplayDevice {
  public:
    SimpleStereoViewer(int _interpupilary_distance, int _eye_width, int _eye_height);
    void displayImages(image_collection_t collection);
  
  private:
    int width;
    int height;
    int eye_width;
    int eye_height;
    int interpupilary_distance;
    cv::Mat view_buffer;
};

#endif