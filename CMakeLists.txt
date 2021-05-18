cmake_minimum_required(VERSION 3.10)

# set the project name
project(R3DVoxel)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

IF(DEFINED ENV{VULKAN_SDK})
    MESSAGE(STATUS "VULKAN PATH: $ENV{VULKAN_SDK}")
ELSE()
    MESSAGE(STATUS "VULKAN PATH NOT FOUND")
ENDIF()

# add includes directory
include_directories("$ENV{VULKAN_SDK}/Include")
include_directories("${PROJECT_SOURCE_DIR}/R3DEngine/Include")
link_directories("${PROJECT_SOURCE_DIR}/R3DEngine/Libs/Debug")

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "R3DVoxel/*.cpp")

# add the executable
add_executable(R3DVoxel ${SOURCES})

target_link_libraries(R3DVoxel "${PROJECT_SOURCE_DIR}/R3DEngine/Libs/Debug/Engine.lib")
target_link_libraries(R3DVoxel "${PROJECT_SOURCE_DIR}/R3DEngine/Libs/Debug/glfw3.lib")
target_link_libraries(R3DVoxel "${PROJECT_SOURCE_DIR}/R3DEngine/Libs/Debug/glew32.lib")
target_link_libraries(R3DVoxel "${PROJECT_SOURCE_DIR}/R3DEngine/Libs/Debug/assimp-vc142-mtd.lib")
target_link_libraries(R3DVoxel "$ENV{VULKAN_SDK}/Lib/vulkan-1.lib")


target_include_directories(R3DVoxel PUBLIC "${PROJECT_BINARY_DIR}")
target_include_directories(R3DVoxel PUBLIC "${PROJECT_SOURCE_DIR}/R3DEngine/Include")
target_include_directories(R3DVoxel PUBLIC "${PROJECT_SOURCE_DIR}/R3DVoxel")
