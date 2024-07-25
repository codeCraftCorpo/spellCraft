#include "common_util.hpp"

namespace commonUtil{

std::string get_platform_name (const cl_platform_id platform){
    char platform_name [100];
    clGetPlatformInfo(platform, CL_PLATFORM_NAME, sizeof(platform_name),&platform_name, NULL);
    std::string str_name (platform_name);
    return str_name;
}

std::string get_device_name (const cl_device_id device){
    char device_name [100];
    clGetDeviceInfo(device, CL_DEVICE_NAME, sizeof(device_name),device_name, NULL);
    std::string str_name (device_name);
    return str_name;
}

}