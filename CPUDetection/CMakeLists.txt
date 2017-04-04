project(CPUDetection)
cmake_minimum_required(VERSION 3.5)

# depending on gcc version
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") #  -Wall

# set AMD APP SDK
set(LIBCPUID_LIBRARY "/home/s74nk0/bin/libcpuid-0.4.0/libcpuid/.libs/libcpuid.a")
set(LIBCPUID_INCLUDE_DIRECTORY "/home/s74nk0/bin/libcpuid-0.4.0/libcpuid")

add_definitions(-DHAVE_STDINT_H)

# LINUX
if(CMAKE_COMPILER_IS_GNUCXX)
    # optimizations
    add_definitions(-O2)
endif()

include_directories(${LIBCPUID_INCLUDE_DIRECTORY})

file(GLOB SRC_LIST
    *.cpp )
file(GLOB HEADERS
    *.h
    *.hpp
    )

message("-- CXXFLAGS: ${CMAKE_CXX_FLAGS}")
message("-- LIBS: ${LIBS}")

set(LIBS ${LIBS} ${Boost_LIBRARIES} ${LIBCPUID_LIBRARY})

add_executable(${PROJECT_NAME} ${SRC_LIST} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${LIBS} ${CMAKE_THREAD_LIBS_INIT})

