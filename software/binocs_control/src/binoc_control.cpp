#include "binoc_manager.h"
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <toml.hpp>

using namespace cv;

void configureSource(BinocManager &manager, toml::table &tbl) {
    std::optional<std::string> source_type = tbl["ImageSource"]["type"].value<std::string>();

    if(*source_type == "SingleUSB") {
        std::optional<std::string> dev_name = tbl["ImageSource"]["source"].value<std::string>();
        manager.setupSimpleUSB(*dev_name);
    } else {
        throw std::runtime_error("Invalid source type!");
    }
}

void configureDisplay(BinocManager &manager, toml::table &tbl) {
    std::optional<std::string> source_type = tbl["DisplayDevice"]["type"].value<std::string>();
    if(*source_type == "SimpleStereoViewer") {
        std::optional<int> interpupil = tbl["DisplayDevice"]["interpupil"].value<int>();
        std::optional<int> width = tbl["DisplayDevice"]["image_width"].value<int>();
        std::optional<int> height = tbl["DisplayDevice"]["image_height"].value<int>();
        manager.setupGenericStereo(*interpupil, *width, *height);
    } else {
        throw std::runtime_error("Invalid display type!");
    }
}

int main(int argc, char **argv) {
    toml::table tbl;
    if(argc == 1) {
        std::cerr << "Enter a filename for parsing" << std::endl;
        return 1;
    }
    try {
        tbl = toml::parse_file(argv[1]);
        std::cout << tbl << "\n";
    } catch (const toml::parse_error &err) {
        std::cerr << "Parsing failed:\n" << err << "\n";
        return 1;
    }

    BinocManager manager;
    configureSource(manager, tbl);
    configureDisplay(manager, tbl);


    manager.run();

    return 0;
}
