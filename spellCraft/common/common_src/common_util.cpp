#include "common_util.hpp"

namespace commonUtil{

std::string get_device_name (const cl_device_id device){
    char device_name [100];
    clGetDeviceInfo(device, CL_DEVICE_NAME, sizeof(device_name),device_name, NULL);
    std::string str_name (device_name);
    return str_name;
}

cl_ulong get_device_memory (const cl_device_id device){
    cl_ulong memory_result;
    clGetDeviceInfo (device, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(memory_result),&memory_result,NULL);
    return memory_result;
}

cl_uint get_device_compute_units (const cl_device_id device){
    cl_uint units_result;
    clGetDeviceInfo (device, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(units_result), &units_result, NULL);
    return units_result;
}

std::string get_platform_name (const cl_platform_id platform){
    char platform_name [100];
    clGetPlatformInfo(platform, CL_PLATFORM_NAME, sizeof(platform_name),&platform_name, NULL);
    std::string str_name (platform_name);
    return str_name;
}

cl_ulong get_context_memory (const cl_context context){
    cl_ulong context_memory_result = 0;
    cl_device_id cur_devices[100];
    size_t num_devices_bytes;
    clGetContextInfo(context,CL_CONTEXT_DEVICES,sizeof(cur_devices), cur_devices, &num_devices_bytes);
    for (size_t i = 0; i < num_devices_bytes/sizeof(cl_device_id); ++i){
        context_memory_result += commonUtil::get_device_memory(cur_devices[i]);
    }
    return context_memory_result;
}

cl_uint get_context_compute_units (const cl_context context){
    cl_uint context_units_result = 0;
    cl_device_id cur_devices[100];
    size_t num_devices_bytes;
    clGetContextInfo(context,CL_CONTEXT_DEVICES,sizeof(cur_devices), cur_devices, &num_devices_bytes);
    for (size_t i = 0; i < num_devices_bytes/sizeof(cl_device_id); ++i){
        context_units_result += commonUtil::get_device_compute_units(cur_devices[i]);
    }
    return context_units_result;
}

}