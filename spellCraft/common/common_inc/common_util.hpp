#ifndef COMMON_UTIL_HPP
#define COMMON_UTIL_HPP

#include <CL/cl.hpp>
#include <SDL2/SDL.h>
#include <string>
#include <iostream>

namespace commonUtil{

std::string get_device_name (const cl_device_id device);
cl_ulong get_device_memory (const cl_device_id device);
std::string get_platform_name (const cl_platform_id platform);
cl_ulong get_context_memory (const cl_context context);
cl_uint get_context_compute_units (const cl_context context);

}

#endif
