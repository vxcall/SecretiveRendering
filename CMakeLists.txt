cmake_minimum_required(VERSION 3.16)
project(StreamProofRendering)

set(CMAKE_CXX_STANDARD 17)

#Directx9
include_directories($ENV{DXSDK_DIR}/Include)
link_directories($ENV{DXSDK_DIR}/Lib/x86)

FILE(GLOB_RECURSE MAIN_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/*.cpp)
FILE(GLOB_RECURSE MAIN_HEADERS CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/*.h)

add_library(${PROJECT_NAME} SHARED ${MAIN_SOURCES} ${MAIN_HEADERS})

target_link_libraries(${PROJECT_NAME} d3d9 d3dx9)