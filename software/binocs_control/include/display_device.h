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

#endif