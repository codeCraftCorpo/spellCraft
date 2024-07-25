#ifndef COMMON_UTIL_HPP
#define COMMON_UTIL_HPP

#include <CL/cl.h>
#include <SDL2/SDL.h>
#include <string>

namespace commonUtil{

std::string get_platform_name (const cl_platform_id platform);
std::string get_device_name (const cl_device_id device);

}

#endif