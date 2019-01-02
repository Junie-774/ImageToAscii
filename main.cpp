#include <iostream>
#include <sstream>
#include <opencv4/opencv2/opencv.hpp>
#include "args.h"

using namespace cv;

char grayscaleToAscii(int grayScale, const std::string& charset) {
    double normalized = static_cast<double>(grayScale) / 255;
    return charset[static_cast<int>(std::ceil(normalized * charset.size() - 1))];
}

int main(int argc, char** argv )
{
    int argsProcessed = 1; // first argument is program name

    if ( argc < 2 )
    {
        printf("usage: DisplayImage.out <options> <Image_Path> <options>\n");
        return -1;
    }

    std::string fileName;
    std::pair<int, int> asciiDims; // {width, height}
    std::string charset = "$@%&W#*okbmZOLCJUYXzcvxr/|)1{[?-+~<>i!lI;:,\"^`'. ";

    bool customSize = false;
    bool customWidth = false;
    bool customHeight = false;
    bool invert = false;

    while (argsProcessed < argc) {

        static std::string noArgGivenError = "Error: option requires an argument: ";

        std::string currentArg = argv[argsProcessed++];
        int argsLeft = argc - argsProcessed;

        if (currentArg == "-d" || currentArg == "--dimensions") {

            if (argsLeft < 1) {
                std::cout << noArgGivenError << "--dimensions\n";
                return -1;
            }

            asciiDims = getDimsFromString(argv[argsProcessed++]);
            customSize = true;
        }
        else if (currentArg == "-w" || currentArg == "--width") {

            if (argsLeft < 1) {
                std::cout << noArgGivenError << "--width\n";
                return -1;
            }

            asciiDims.first = getNumFromString(argv[argsProcessed++]);
            customWidth = true;
        }
        else if (currentArg == "-h" || currentArg == "--height") {

            if (argsLeft < 1) {
                std::cout << noArgGivenError << "--height\n";
                return -1;
            }

            asciiDims.second = getNumFromString(argv[argsProcessed++]);
            customHeight = true;
        }
        else if (currentArg == "--charset") {

            if (argsLeft < 1) {
                std::cout << noArgGivenError << "--charset\n";
                return -1;
            }

            charset = argv[argsProcessed++];
            if (*charset.begin() == '\"' && *(charset.end() - 1) == '\"') {
                charset = charset.substr(1, charset.size() - 2);
            }
        }
        else if (currentArg == "-i" || currentArg == "--invert") {

            invert = true;
        }
        else {

            if (!fileName.empty()) {
                std::cout << "Error: Unknown argument: " << currentArg << "\n";
                return -1;
            }

            fileName = currentArg;
        }

    }
    if (fileName.empty()) {
        std::cout << "Error: no image file given\n";
    }

    if (asciiDims.first == -1 || asciiDims.second == -1) {
        // An error should already have been printed during parsing
        return -1;
    }

    Mat image = imread(fileName, 1);

    if ( !image.data )
    {
        std::cout << "No image data \n";
        return -1;
    }

    double fontRatio = 0.5; // Because most fonts don't have square characters
    constexpr int defaultWidth = 50;

    double imageRatio = static_cast<double>(image.cols) / image.rows;

    // No custom dimensions given
    if (!customSize && !(customWidth || customHeight)) {

        asciiDims = {defaultWidth / fontRatio,
                     static_cast<int>(std::round(defaultWidth / imageRatio))};
    }
    // if the height or width is specified, we may have to determine the other
    // using the aspect ratio of the image
    else {
        // Width given, automatic height
        if (customWidth && !customHeight) {
            asciiDims.second = static_cast<int>(asciiDims.first / imageRatio * fontRatio);
        }
        // Height given, custom width
        else if (!customWidth && customHeight) {
            asciiDims.first = static_cast<int>(asciiDims.second * imageRatio / fontRatio);
        }
    }
    std::cout << "w: " << asciiDims.first << ", h: " << asciiDims.second << std::endl;

    if (invert) {
        std::reverse(charset.begin(), charset.end());
    }

    cvtColor(image, image, COLOR_BGR2GRAY);

    // Resize the image to match the ascii dimensions
    double xImgScale = static_cast<double>(asciiDims.first) / image.cols;
    double yImgScale = static_cast<double>(asciiDims.second) / image.rows;

    cv::resize(image, image, Size(), xImgScale, yImgScale);

    // Traverse in reverse order because the image is indexed [row, column],
    // but the dimensions are given in [width, height]
    for (int i = 0; i < asciiDims.second; i++) {
        for (int j = 0; j < asciiDims.first; j++) {

            auto grayscale = static_cast<int>(image.at<uchar>(i, j));
            char c = grayscaleToAscii(grayscale, charset);

            std::cout << c ;
        }

        std::cout << "\n";
    }

    return 0;
}
