#ifndef BINOCS_CONTROL_BINOC_MANAGER_
#define BINOCS_CONTROL_BINOC_MANAGER_

#include "display_device.h"
#include "image_source.h"
#include "image_stabalization.h"

class BinocManager {
public:
    BinocManager();
    void run();
    void setupDesktopDisplay();
    void setupGenericStereo(int interpupil, int width, int height);
    void setupSimpleUSB(std::string &dev_name);
    void setupMonocularUSB(std::string &dev_name);
    void setupDualCameras(std::string &left_cam_name, std::string right_cam_name);

  private:
    std::unique_ptr<iDisplayDevice> display;
    std::unique_ptr<iImageSource> source;
    std::unique_ptr<ImageStabalization> stabalizer;
};

#endif