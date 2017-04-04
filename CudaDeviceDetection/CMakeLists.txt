project(CudaDeviceDetection)
cmake_minimum_required(VERSION 3.5)

option(ENABLE_CUDA "Enable the cuda build" ON)

# depending on gcc version
# ;-std=c++11 => Ubuntu 14.04 check gcc versions
#set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS};-std=c++11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") #  -Wall

# LINUX
if(CMAKE_COMPILER_IS_GNUCXX)
    # optimizations
    add_definitions(-O2)
endif()

# CUDA
FIND_PACKAGE(CUDA REQUIRED)
#set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS};-gencode arch=compute_50,code=sm_50;)
if(CUDA_FOUND)
message("CUDA FOUND")
else()
message("CUDA NOT FOUND")
endif()

file(GLOB SRC_LIST
    *.cpp )
file(GLOB HEADERS
    *.h
    )

message("-- CXXFLAGS: ${CMAKE_CXX_FLAGS}")
message("-- LIBS: ${LIBS}")

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CUDA_INCLUDE_DIRS})

# this is NVIDIA driver specific
link_directories(/usr/lib/nvidia-375/)

CUDA_ADD_EXECUTABLE(${PROJECT_NAME} ${SRC_LIST} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${LIBS} ${CUDA_LIBRARIES})
# nvml
target_link_libraries(${PROJECT_NAME} nvidia-ml )

