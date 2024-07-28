cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER C:/dev/msys64/mingw64/bin/gcc.exe)
set(CMAKE_CXX_COMPILER C:/dev/msys64/mingw64/bin/g++.exe)

project(spellcraft)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wno-ignored-attributes)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

set(PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)
set (DEPENDENCY_ROOT_DIR ${PROJECT_ROOT_DIR}/cmake/dependencies)
set (SRC_ROOT_DIR ${PROJECT_ROOT_DIR}/src)
set (SPELLCRAFT_ROOT_DIR ${PROJECT_ROOT_DIR}/spellCraft)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

add_definitions(-DCL_HPP_TARGET_OPENCL_VERSION=300)

set (HEADERS
  ${DEPENDENCY_ROOT_DIR}/SDL_setup/x86_64-w64-mingw32/include
  ${DEPENDENCY_ROOT_DIR}/openCL_setup/inc  

  ${SPELLCRAFT_ROOT_DIR}/common/common_inc
  ${SPELLCRAFT_ROOT_DIR}/ML/ML_inc
  ${SPELLCRAFT_ROOT_DIR}/SIM/SIM_inc
  ${SPELLCRAFT_ROOT_DIR}/UI/UI_inc
  )
include_directories(${HEADERS})


link_directories(${DEPENDENCY_ROOT_DIR}/SDL_setup/x86_64-w64-mingw32/lib)
link_directories(${DEPENDENCY_ROOT_DIR}/openCL_setup/nvidia/lib/x64)

set(LIBS
  mingw32
  SDL2main
  SDL2
  OpenCL
  #oclUtils64D
  #oclUtils64
)


file(GLOB_RECURSE SPELLCRAFT_COMMON_SRC ${SPELLCRAFT_ROOT_DIR}/common/common_src/*.cpp)
file(GLOB_RECURSE SPELLCRAFT_ML_SRC ${SPELLCRAFT_ROOT_DIR}/ML/ML_src/*.cpp)
file(GLOB_RECURSE SPELLCRAFT_SIM_SRC ${SPELLCRAFT_ROOT_DIR}/SIM/SIM_src/*.cpp)
file(GLOB_RECURSE SPELLCRAFT_UI_SRC ${SPELLCRAFT_ROOT_DIR}/UI/UI_src/*.cpp)

set(SOURCES
  ${SRC_ROOT_DIR}/main.cpp
  ${SPELLCRAFT_COMMON_SRC}
  ${SPELLCRAFT_ML_SRC}
  ${SPELLCRAFT_SIM_SRC}
  ${SPELLCRAFT_UI_SRC}
)

add_executable(main ${SOURCES})
target_link_libraries(main ${LIBS})

add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${DEPENDENCY_ROOT_DIR}/SDL_setup/x86_64-w64-mingw32/bin/sdl2.dll
    $<TARGET_FILE_DIR:main>)

#commands to build this:
# (in cmake folder)
#mkdir build
#cd build
#cmake -G Ninja ..
#ninja
