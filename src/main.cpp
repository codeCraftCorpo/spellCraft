#include <CL/cl.h>
#include <SDL2/SDL.h>

#include <init_devices.hpp>

#include <iostream>
#include <vector>

int main(int argc, char* argv[]) 
{
    cl_uint num_platforms;
    cl_platform_id* platforms;
    get_platforms(num_platforms,platforms);
    print_platforms(num_platforms,platforms);
    std::vector<cl_device_id> all_CPUs, all_GPUs, all_ACUs;
    get_devices(num_platforms,platforms,all_CPUs,all_GPUs,all_ACUs);
    print_devices(all_CPUs,all_GPUs,all_ACUs);

    return 0;

}