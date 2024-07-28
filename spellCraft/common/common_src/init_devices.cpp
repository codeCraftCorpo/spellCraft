#include "init_devices.hpp"

platform_devices_struct::platform_devices_struct(cl_platform_id platform, std::vector<cl_device_id> devices){
    this->platform = platform;
    this->devices = devices;
}

void platform_devices_struct::delete_same_devices(platform_devices_struct &toDelete){
    for (int cur_device_id = 0; cur_device_id<this->devices.size(); ++cur_device_id){
        std::string cur_device_name = commonUtil::get_device_name(this->devices[cur_device_id]);
        for (int check_device_id = 0; check_device_id<toDelete.devices.size(); ++check_device_id){
            std::string check_device_name = commonUtil::get_device_name(toDelete.devices[check_device_id]);
            if (cur_device_name == check_device_name){
                toDelete.devices.erase(toDelete.devices.begin()+check_device_id);
                --check_device_id;
            }
        }
    }
}

void platform_devices_struct::print_struct() const {
    std::cout<<"platform: "<<commonUtil::get_platform_name(this->platform)<<std::endl;
    std::cout<<"related devices:"<<std::endl;
    for (int i = 0; i < this->devices.size(); ++i){
        std::cout<<commonUtil::get_device_name(this->devices[i])<<std::endl;
    }
}

initCommon::initCommon(){
    init_all_platforms();
    init_used_platform_and_devices();
    init_contexts();
    sort_contexts_by_memory();
}


void initCommon::init_all_platforms(){
    clGetPlatformIDs (1,NULL,&this->num_all_platforms);
    this->all_platforms = (cl_platform_id*) malloc(sizeof(cl_platform_id) * this->num_all_platforms);
    clGetPlatformIDs (this->num_all_platforms, this->all_platforms, NULL);
}

void initCommon::init_used_platform_and_devices(){

    std::vector<platform_devices_struct>* all_platform_devices_struct_vecs [] = {
    &this->CPU_platform_devices_struct_vec, &this->GPU_platform_devices_struct_vec, &this->ACU_platform_devices_struct_vec};

    for (int device_type_id = 0; device_type_id < 3; ++device_type_id){

        cl_device_type cur_device_type = this->all_device_types[device_type_id];
        std::vector<platform_devices_struct>& cur_platform_devices_struct_vec = *all_platform_devices_struct_vecs[device_type_id];        

        //for each platform, create a struct that adds all related devices
        for (int cur_platform_id = 0; cur_platform_id < this->num_all_platforms; ++cur_platform_id){
            cl_platform_id cur_platform = this->all_platforms[cur_platform_id];
            std::vector<cl_device_id> cur_device_vec;
            cl_uint platform_device_num;
            clGetDeviceIDs(cur_platform,cur_device_type,1,NULL,&platform_device_num);
            cl_device_id platform_devices [platform_device_num];
            clGetDeviceIDs(cur_platform,cur_device_type,platform_device_num,platform_devices,NULL);
            for (int cur_device_id = 0; cur_device_id < platform_device_num; ++cur_device_id){
                cur_device_vec.push_back(platform_devices[cur_device_id]);
            }
            platform_devices_struct cur_platform_devices_struct = platform_devices_struct(cur_platform, cur_device_vec);
            cur_platform_devices_struct_vec.push_back(cur_platform_devices_struct);
        }

        //different platforms may access the same device, so repeated devices are deleted from latter platforms 
        for (int cur_id = 0; cur_id < cur_platform_devices_struct_vec.size(); ++cur_id){
            for (int check_id = cur_id +1; check_id < cur_platform_devices_struct_vec.size(); ++check_id){
                cur_platform_devices_struct_vec[cur_id].delete_same_devices(cur_platform_devices_struct_vec[check_id]);
            }
        }

        //platforms with no devices are deleted
        for (int i = 0; i < cur_platform_devices_struct_vec.size(); ++i){
            if (cur_platform_devices_struct_vec[i].devices.size() == 0){
                cur_platform_devices_struct_vec.erase(cur_platform_devices_struct_vec.begin()+i);
                --i;
            }
        }
    }
}

void initCommon::init_contexts(){

    std::vector<cl_context>* all_contexts[] = {
    &this->CPU_contexts, &this->GPU_contexts, &this->ACU_contexts};

    std::vector<platform_devices_struct>* all_platform_devices_struct_vecs [] = {
    &this->CPU_platform_devices_struct_vec, &this->GPU_platform_devices_struct_vec, &this->ACU_platform_devices_struct_vec};

    for (int device_type_id = 0; device_type_id < 3; ++device_type_id){
        std::vector<cl_context>& cur_type_context_vec = *all_contexts[device_type_id];
        std::vector<platform_devices_struct>& cur_platform_devices_struct_vec = *all_platform_devices_struct_vecs[device_type_id];

        for (int i = 0; i<cur_platform_devices_struct_vec.size(); ++i){
            platform_devices_struct cur_platform_devices_struct = cur_platform_devices_struct_vec[i];
            cl_context_properties context_props[] = {CL_CONTEXT_PLATFORM, (cl_context_properties)cur_platform_devices_struct.platform,0};
            cl_int err;
            cl_context cur_context = clCreateContext(context_props, 
            (cl_uint)cur_platform_devices_struct.devices.size(), cur_platform_devices_struct.devices.data(),NULL,NULL,&err);
            cur_type_context_vec.push_back(cur_context);
        }
    }
}



void initCommon::print_all_platform_and_devices () const{
    std::cout<<"printing platforms and devices by device type"<<std::endl;
    std::vector<std::string> type_names = {"CPU: ", "GPU: ", "ACU: "};    
    const std::vector<platform_devices_struct>* all_platform_devices_struct_vecs [] = {
    &this->CPU_platform_devices_struct_vec, &this->GPU_platform_devices_struct_vec, &this->ACU_platform_devices_struct_vec};

    for (int device_type_id = 0; device_type_id < 3; ++device_type_id){
        std::string cur_type= type_names[device_type_id];
        std::vector<platform_devices_struct> cur_platform_devices_struct_vec = *all_platform_devices_struct_vecs[device_type_id];        
        
        std::cout<<cur_type<<std::endl;
        for (platform_devices_struct cur_platform_devices_struct : cur_platform_devices_struct_vec){
            cur_platform_devices_struct.print_struct();
        }
    }
}

void initCommon::print_all_contexts() const{
    std::cout<<"printing contexts and associated devices"<<std::endl;
    std::vector<std::string> type_names = {"CPU: ", "GPU: ", "ACU: "};    
    const std::vector<cl_context>* all_contexts[] = {
    &this->CPU_contexts, &this->GPU_contexts, &this->ACU_contexts};

    for (int device_type_id = 0; device_type_id < 3; ++device_type_id){
        std::cout<<type_names[device_type_id]<<std::endl;
        std::vector<cl_context> cur_context_vec = *all_contexts[device_type_id];
        for (int context_id = 0; context_id< cur_context_vec.size(); ++context_id){
            std::cout<<"context "<<context_id<<std::endl;
            std::cout<<"total memory (mb): "<<commonUtil::get_context_memory(cur_context_vec[context_id])/(1024*1024)<<std::endl;
            std::cout<<"total compute units: "<<commonUtil::get_context_compute_units(cur_context_vec[context_id])<<std::endl;
            std::cout<<"devices: "<<std::endl;
            cl_device_id cur_devices[100];
            size_t num_devices_bytes;
            clGetContextInfo(cur_context_vec[context_id],CL_CONTEXT_DEVICES,sizeof(cur_devices), cur_devices, &num_devices_bytes);
            for (size_t i = 0; i < num_devices_bytes/sizeof(cl_device_id); ++i){
                std::cout<<commonUtil::get_device_name(cur_devices[i])<<std::endl;
            }
        }
    }
}

void initCommon::sort_contexts_by_memory(){
    std::vector<cl_context>* all_contexts[] = {
    &this->CPU_contexts, &this->GPU_contexts, &this->ACU_contexts};

    for (int device_type_id = 0; device_type_id < 3; ++device_type_id){
        std::vector<cl_context>& cur_context_vec = *all_contexts[device_type_id];
        for (int cur_context_id = 0; cur_context_id< cur_context_vec.size(); ++cur_context_id){
            for (int check_context_id = cur_context_id +1; check_context_id< cur_context_vec.size(); ++check_context_id){
                cl_ulong cur_context_memory = commonUtil::get_context_memory(cur_context_vec[cur_context_id]);
                cl_ulong check_context_memory = commonUtil::get_context_memory(cur_context_vec[check_context_id]);
                if (check_context_memory > cur_context_memory){
                    std::swap(cur_context_vec[cur_context_id],cur_context_vec[check_context_id]);
                }
            }
        }
    }
}