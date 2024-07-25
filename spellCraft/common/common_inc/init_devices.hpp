#ifndef INIT_DEVICES_HPP
#define INIT_DEVICES_HPP

#include <CL/cl.h>
#include <SDL2/SDL.h>

#include <iostream>
#include <vector>

#include "common_util.hpp"

//returns platforms as cl_platform_id in an array
void get_all_platforms(cl_uint& num_platforms, cl_platform_id*& platforms);

void print_platforms(const cl_uint num_platforms, const cl_platform_id* platforms);

//returns devices as cl_device_id vectors seperated by cpu, gpu, acu
//returns all the used platforms (some unused ones passed in will not be returned)
void get_devices(const cl_uint num_platforms, const cl_platform_id* platforms, std::vector<cl_device_id>& all_CPUs, std::vector<cl_device_id>&all_GPUs, std::vector<cl_device_id>&all_ACUs
std::vector<cl_platform_id>& CPU_used_platforms,std::vector<cl_platform_id>& GPU_used_platforms, std::vector<cl_platform_id>& ACU_used_platforms );

void print_devices (const std::vector<cl_device_id>&all_CPUs, const std::vector<cl_device_id>&all_GPUs, const std::vector<cl_device_id>&all_ACUs);


#endif