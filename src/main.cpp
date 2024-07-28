#include <CL/cl.hpp>
#include <SDL2/SDL.h>

#include <init_devices.hpp>

#include <iostream>
#include <vector>

int main(int argc, char* argv[]) 
{
    initCommon init_common = initCommon();
    init_common.print_all_contexts();
    return 0;

}