#include "oclutil.h"

#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>

#include <opencv2/opencv.hpp>


#define CL_COUNT 1

int main(void)
{
    /* Data */

    std::string fileName("square.cl");
    std::string routineName("square");
    int     routines        = 1;
    int     clCount         = CL_COUNT;
    float   clIn[CL_COUNT]  = { 2.f };
    float   clOut[CL_COUNT];

    std::ifstream sourceFile(fileName.c_str());
    if (sourceFile.fail())
        std::cout << "Failed to open OpenCL source file" << std::endl;
    std::string sourceCode(std::istreambuf_iterator<char>(sourceFile), (std::istreambuf_iterator<char>()));

    OCLutil ocl(CL_DEVICE_TYPE_GPU, fileName, "", routineName, routines);
    ocl.CarregarBuffer(clIn, clCount, 0, 0, false);
    ocl.CarregarBuffer(clOut, clCount, 0, 1, true);
    ocl.CarregarInt(clCount, 0, 2);
    ocl.Exec(0, cl::NDRange(1), cl::NullRange);
    ocl.LerBuffer(clOut, 1, 1);

    for (int i = 0; i < clCount; ++i)
        std::cout << clOut[i] << std::endl;

    /* Image */

    fileName        = "imgcpy.cl";
    routineName     = "imgcpy";
    cv::Mat clImgIn = cv::imread("./alaor.jpg");
    cv::Mat clImgOut(clImgIn.size(),CV_8UC3);

    std::ifstream sourceFileImg(fileName.c_str());
    if (sourceFileImg.fail())
        std::cout << "Failed to open OpenCL source file" << std::endl;
    std::string sourceCodeImg(std::istreambuf_iterator<char>(sourceFile), (std::istreambuf_iterator<char>()));

    OCLutil oclImg(CL_DEVICE_TYPE_GPU, fileName, "", routineName, routines);
    oclImg.CarregarCVMatf(clImgIn, 0, 0, false);
    oclImg.CarregarCVMatf(clImgOut, 0, 1, true);
    oclImg.Exec(0, cl::NDRange(clImgIn.cols, clImgIn.rows), cl::NullRange);
    oclImg.LerBufferImgf(clImgOut, 1);

    cv::imshow("Output", clImgOut);
    cv::waitKey();

    return EXIT_SUCCESS;
}