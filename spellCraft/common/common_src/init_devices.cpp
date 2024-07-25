#include "init_devices.hpp"

void get_all_platforms(cl_uint& num_platforms, cl_platform_id*& platforms){
    clGetPlatformIDs (1,NULL,&num_platforms);
    platforms = (cl_platform_id*) malloc(sizeof(cl_platform_id) * num_platforms);
    clGetPlatformIDs (num_platforms, platforms, NULL);
}

void print_platforms(const cl_uint num_platforms, const cl_platform_id* platforms){
    std::cout<<"printing platforms"<<std::endl;
    for (cl_uint i = 0; i< num_platforms; ++i){
        cl_platform_id cur_platform = platforms[i];
        std::string cur_platform_name = commonUtil::get_platform_name(cur_platform);
        std::cout<< cur_platform_name <<std::endl;
    }
    std::cout<<std::endl;
}


void get_devices(const cl_uint num_platforms, const cl_platform_id* platforms,
std::vector<cl_device_id>& all_CPUs, std::vector<cl_device_id>&all_GPUs, std::vector<cl_d:wa
evice_id>&all_ACUs
std::vector<cl_platform_id>& CPU_used_platforms,std::vector<cl_platform_id>& GPU_used_platforms, std::vect ){

    cl_device_type all_device_types[] = {CL_DEVICE_TYPE_CPU,CL_DEVICE_TYPE_GPU,CL_DEVICE_TYPE_ACCELERATOR};
    std::vector<cl_device_id>* all_device_result [] = {&all_CPUs, &all_GPUs, &all_ACUs};
    std::vector<cl_platform_id>* all_platform_result [] = {&CPU_used_platforms,&GPU_used_platforms,&ACU_used_platforms};

    for (int device_type_id = 0; device_type_id < 3; ++device_type_id){

        cl_device_type cur_device_type = all_device_types[device_type_id];
        std::vector<cl_device_id>& cur_device_result = *all_device_result[device_type_id];
        std::vector<cl_platform_id>& cur_platform_result = *all_platform_result[device_type_id];

        std::vector<std::vector<cl_device_id>> platforms_device_vec_vec;
        std::vector<cl_uint> platforms_device_num_vec;

        for (int cur_platform_id = 0; cur_platform_id < num_platforms; ++cur_platform_id){
            std::vector<cl_device_id> platform_device_vec;
            cl_uint platform_device_num;
            clGetDeviceIDs(platforms[cur_platform_id],cur_device_type,1,NULL,&platform_device_num);
            cl_device_id platform_devices [platform_device_num];
            clGetDeviceIDs(platforms[cur_platform_id],cur_device_type,platform_device_num,platform_devices,NULL);
            for (int cur_device_id = 0; cur_device_id < platform_device_num;++cur_device_id){
                platform_device_vec.push_back(platform_devices[cur_device_id]);
            }
            platforms_device_vec_vec.push_back(platform_device_vec);
            platforms_device_num_vec.push_back(platform_device_num);

        }

        //if a previous platform already has the device of the same name, do not add that device
        for (int cur_platform_id = 0; cur_platform_id < num_platforms; ++cur_platform_id){
            for (int cur_device_id = 0; cur_device_id < platforms_device_num_vec[cur_platform_id]; ++cur_device_id){
                bool previously_found = false;
                for (int check_platform_id = cur_platform_id-1; check_platform_id < cur_platform_id; ++check_platform_id){
                    if (check_platform_id < 0) continue;
                    std::string cur_device_name = commonUtil::get_device_name(platforms_device_vec_vec[cur_platform_id][cur_device_id]);
                    for (int check_device_id = 0; check_device_id <platforms_device_num_vec[check_platform_id];++check_device_id){
                        std::string check_device_name = commonUtil::get_device_name(platforms_device_vec_vec[check_platform_id][check_device_id]);
                        if (cur_device_name == check_device_name) previously_found = true;
                    } 
                }
                if (previously_found == false){
                    cur_device_result.push_back(platforms_device_vec_vec[cur_platform_id][cur_device_id]);
                    cur_platform_result.push_back(platforms[cur_platform_id]);
                }
            }
        }

    }
}

void print_devices (const std::vector<cl_device_id>&all_CPUs, const std::vector<cl_device_id>&all_GPUs, const std::vector<cl_device_id>&all_ACUs){

    std::cout<<"printing devices by type"<<std::endl;
    std::cout<<"cpu list: "<<std::endl;
    for (cl_device_id cpu : all_CPUs){
        std::cout<<commonUtil::get_device_name(cpu)<<std::endl;
    }
    std::cout<<"gpu list: "<<std::endl;
    for (cl_device_id gpu : all_GPUs){
        std::cout<<commonUtil::get_device_name(gpu)<<std::endl;
    }
    std::cout<<"acu list: "<<std::endl;
    for (cl_device_id acu : all_ACUs){
        std::cout<<commonUtil::get_device_name(acu)<<std::endl;
    }
    std::cout<<std::endl;
}