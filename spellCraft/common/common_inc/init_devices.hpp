#ifndef INIT_DEVICES_HPP
#define INIT_DEVICES_HPP

#include <CL/cl.h>
#include <SDL2/SDL.h>

#include <iostream>
#include <vector>
using std::vector;


void get_platforms(cl_uint& num_platforms, cl_platform_id*& platforms);
void get_devices(const cl_uint num_platforms, const cl_platform_id* platforms, vector<cl_device_id>& all_CPUs, vector<cl_device_id>&all_GPUs, vector<cl_device_id>&all_ACUs);
void print_devices (const vector<cl_device_id>&all_CPUs, const vector<cl_device_id>&all_GPUs, const vector<cl_device_id>&all_ACUs);



#endif