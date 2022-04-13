#include "binoc_manager.h"
#include "display_device.h"
#include "image_source.h"
#include "image_stabalization.h"

BinocManager::BinocManager() {
    display = std::make_unique<SimpleStereoViewer>(); 
    source = std::make_unique<USBStereoSource>("/dev/video4"); 
    stabalizer = std::make_unique<ImageStabalization>(); 
}

void BinocManager::run() {
    while(true) {
        image_collection_t res = source->getImages();
        image_collection_t stabalized = stabalizer->stabalizeImages(res);
        display->displayImages(stabalized);
    }
}