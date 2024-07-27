#ifndef INIT_DEVICES_HPP
#define INIT_DEVICES_HPP

#include <CL/cl.h>
#include <SDL2/SDL.h>

#include <iostream>
#include <vector>

#include "common_util.hpp"

struct platform_devices_struct{
    cl_platform_id platform;
    std::vector<cl_device_id> devices;
    platform_devices_struct(cl_platform_id platform, std::vector<cl_device_id> devices);
    
    //if two platforms access the same devices identified by name, delete those devices from the struct passed by parameter
    void delete_same_devices(platform_devices_struct &toDelete);
    
    void print_struct ()const;
};


//device data hierachy
//device type > platform = context (= in this implementation) > devices
class initCommon{
public:
    //call all init functions to initialize member variables
    initCommon();

    //gets all platforms as cl_platform_id in an array
    void init_all_platforms();

    //gets used platforms and associated devices in vectors
    //if multiple platforms access the same device, only one platform is added
    void init_used_platform_and_devices();

    //initalizes contexts based on platforms
    void init_contexts();

    void print_all_platform_and_devices () const;

    void print_all_contexts() const;

private:
    cl_uint num_all_platforms;
    cl_platform_id* all_platforms;

    std::vector<cl_device_type> all_device_types = {CL_DEVICE_TYPE_CPU,CL_DEVICE_TYPE_GPU,CL_DEVICE_TYPE_ACCELERATOR};

    //these structs' device vectors memory are used by the contexts created by init contexts function, so do not modify them after init contexts.
    std::vector<platform_devices_struct> CPU_platform_devices_struct_vec; 
    std::vector<platform_devices_struct> GPU_platform_devices_struct_vec; 
    std::vector<platform_devices_struct> ACU_platform_devices_struct_vec; 

    std::vector<cl_context> CPU_contexts;
    std::vector<cl_context> GPU_contexts;
    std::vector<cl_context> ACU_contexts;
};

#endif