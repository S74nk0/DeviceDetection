project(AMDOpenCLDeviceDetection)
cmake_minimum_required(VERSION 3.5)

# depending on gcc version
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") #  -Wall

# set AMD APP SDK
set(OPENCL_LIBRARY "/opt/AMDAPPSDK-3.0/lib/x86_64/sdk/libOpenCL.so")
set(OPENCL_INCLUDE_DIRECTORY "/opt/AMDAPPSDK-3.0/include")

# LINUX
if(CMAKE_COMPILER_IS_GNUCXX)
    # optimizations
    add_definitions(-O2)
endif()

include_directories(${OPENCL_INCLUDE_DIRECTORY})

file(GLOB SRC_LIST
    *.cpp )
file(GLOB HEADERS
    *.h
    *.hpp
    )

message("-- CXXFLAGS: ${CMAKE_CXX_FLAGS}")
message("-- LIBS: ${LIBS}")

set(LIBS ${LIBS} ${Boost_LIBRARIES} ${OPENCL_LIBRARY})

add_executable(${PROJECT_NAME} ${SRC_LIST} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${LIBS} ${CMAKE_THREAD_LIBS_INIT})

