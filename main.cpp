#include "oclutil.h"

#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>

#define CL_COUNT 3

int main(void)
{
    std::string fileName("square.cl");
    std::string routineName("square");
    int     routines        = 1;
    int     clCount         = CL_COUNT;
    float   clIn[CL_COUNT]  = { 2.f, 3.75f, 9.41f };
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

    return EXIT_SUCCESS;
}