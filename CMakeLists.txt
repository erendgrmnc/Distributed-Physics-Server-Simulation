cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

set(CMAKE_SYSTEM_VERSION 10.0 CACHE STRING "" FORCE)

project(DistributedPhysicsSystem CXX)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-std=c++20)

set(CMAKE_DISTRIBUTED_SYSTEM_ACTIVE "true")
set(CMAKE_BUILD_FOR_DISTRIBUTED_MANAGER "false")
set(CMAKE_BUILD_FOR_PHYSICS_MIDWARE "true")
if(NOT CMAKE_VS_PLATFORM_NAME)
    set(CMAKE_VS_PLATFORM_NAME "x64")
endif()
message("${CMAKE_VS_PLATFORM_NAME} architecture in use")

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    add_compile_definitions(USEGL)
    if("${CMAKE_DISTRIBUTED_SYSTEM_ACTIVE}" STREQUAL "true")
        add_compile_definitions(DISTRIBUTEDSYSTEMACTIVE)
        if("${CMAKE_BUILD_FOR_DISTRIBUTED_MANAGER}" STREQUAL "true")
            add_compile_definitions(BUILDFORDISTRIBUTEDMANAGER)
        elseif("${CMAKE_BUILD_FOR_PHYSICS_MIDWARE}" STREQUAL "true")
            add_compile_definitions(BUILDFORPHYSICSMIDWARE)
       endif()
    endif()
    
endif()

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Prospero")
    add_compile_definitions(USEPROSPERO)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -frtti")
    add_compile_options(-Wno-pragma-once-outside-header)
endif()

################################################################################
# Use solution folders feature
################################################################################
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(COMPILE_ASSET_ROOT "${CMAKE_SOURCE_DIR}/Assets/" CACHE STRING "")

set(DEBUG_ASSET_ROOT "${CMAKE_SOURCE_DIR}/Assets/" CACHE STRING "")
set(RELEASE_ASSET_ROOT "${CMAKE_SOURCE_DIR}/Assets/" CACHE STRING "")

add_compile_definitions(ASSETROOTLOCATION="${DEBUG_ASSET_ROOT}") 

if(MSVC) 
    add_compile_definitions("NOMINMAX")
    add_compile_definitions("WIN32_LEAN_AND_MEAN") 
endif()


add_compile_definitions("USEAGC") 


 
################################################################################
# Sub-projects
################################################################################

add_subdirectory(CSC8503)
add_subdirectory(DistributedGameServer)
add_subdirectory(PhysicsServerMidware)
add_subdirectory(CSC8503CoreClasses)
add_subdirectory(DistributedPhysicsManager)
add_subdirectory(NCLCoreClasses)
add_subdirectory(EntryPoint)
add_subdirectory(Detour)
add_subdirectory(Recast)
add_subdirectory(DebugUtils)
add_subdirectory(DetourTileCache)


if ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    add_subdirectory(OpenGLRendering)
endif()

if ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Prospero")
    add_subdirectory(GLTFLoader)
    add_subdirectory(PS5Core)
    #add_subdirectory(PS5Starter)
endif()

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT EntryPoint)
