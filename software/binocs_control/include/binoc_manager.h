#ifndef BINOCS_CONTROL_BINOC_MANAGER_
#define BINOCS_CONTROL_BINOC_MANAGER_

#include "display_device.h"
#include "image_source.h"
#include "image_stabalization.h"

class BinocManager {
public:
    BinocManager();
    void run();

  private:
    std::unique_ptr<iDisplayDevice> display;
    std::unique_ptr<iImageSource> source;
    std::unique_ptr<ImageStabalization> stabalizer;
};

#endif