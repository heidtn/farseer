#include "binoc_manager.h"
#include "display_device.h"
#include "image_source.h"
#include "image_stabalization.h"

BinocManager::BinocManager() {
    stabalizer = std::make_unique<ImageStabalization>(); 
}

void BinocManager::setupGenericStereo(int interpupil, int width, int height) {
    display = std::make_unique<SimpleStereoViewer>(interpupil, width, height); 
}

void BinocManager::setupDesktopDisplay() {
    display = std::make_unique<MonitorDisplay>(); 
}

void BinocManager::setupSimpleUSB(std::string &dev_name) {
    source = std::make_unique<USBStereoSource>(dev_name); 
}

void BinocManager::setupMonocularUSB(std::string &dev_name) {
    source = std::make_unique<USBMonocularSource>(dev_name);
}

void BinocManager::setupDualCameras(std::string &left_cam_name, std::string right_cam_name) {
    source = std::make_unique<DualCameraSource>(left_cam_name, right_cam_name);
}

void BinocManager::run() {
    while(true) {
        image_collection_t res = source->getImages();
        if(res.left_im.data == NULL) continue;
        image_collection_t stabalized = stabalizer->stabalizeImages(res);
        display->displayImages(stabalized);
    }
}