#include <opencv2/opencv.hpp>
#include <stdio.h>
#include "binoc_manager.h"

using namespace cv;

int main(int argc, char **argv) {
    BinocManager manager;
    manager.run();  

    return 0;
}
