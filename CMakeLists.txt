cmake_minimum_required(VERSION 3.0)
#set(CMAKE_VERBOSE_MAKEFILE ON)

####################
# TARGET PLATFORM
####################
set(PLATFORM_LINUX OFF CACHE BOOL "Linux platform target")
set(PLATFORM_WINDOWS OFF CACHE BOOL "Windows platform target (msys/mingw64)")
set(PLATFORM_RPI3 OFF CACHE BOOL "RIP3 platform target")
set(PLATFORM_SWITCH OFF CACHE BOOL "Nintendo Switch platform target")
set(PLATFORM_3DS OFF CACHE BOOL "Nintendo 3DS platform target")
set(PLATFORM_VITA OFF CACHE BOOL "Sony PS Vita platform target")

####################
# BUILD OPTIONS
####################
set(OPTION_SDL1 OFF CACHE BOOL "SDL1 support (software, slow, unsupported)")
set(OPTION_SDL2_GL OFF CACHE BOOL "SDL2 support (OpenGL 3.3)")
set(OPTION_SDL2_GLES2 OFF CACHE BOOL "SDL2 support (OpenGLES 2.0)")
set(OPTION_SDL2_SOFT OFF CACHE BOOL "SDL2 support (software, slow)")
set(OPTION_BUILTIN_LIBCONFIG OFF CACHE BOOL "Build libconfig from sources")
set(OPTION_FREEPLAY OFF CACHE BOOL "Build with FreePlay (CM3/ZERO) support")
set(OPTION_RECALBOX_BUILDROOT OFF CACHE BOOL "Build from recalbox buildroot")
set(OPTION_SCREEN_WIDTH 1280 CACHE STRING "Custom screen width")
set(OPTION_SCREEN_HEIGHT 720 CACHE STRING "Custom screen height")
####################
# BUILD OPTIONS
####################

# add libcross2d library
add_subdirectory(external/libcross2d)
# add sscrap library
add_subdirectory(external/sscrap)

project(retromenu)

set(PROJECT_AUTHOR "Cpasjuste")
set(VERSION_MAJOR "1")
set(VERSION_MINOR "0")
# ps vita
set(TITLE_ID "RETRO0001")

#############
# code
#############
set(INCLUDES ${CMAKE_SOURCE_DIR}/source)
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/source/*.cpp)
set(CUSTOM_CFLAGS
        -DVERSION_MAJOR="${VERSION_MAJOR}"
        -DVERSION_MINOR="${VERSION_MINOR}")
set(CUSTOM_LDFLAGS)

#############
# executable
#############
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDES})
target_compile_options(${PROJECT_NAME} PRIVATE ${CUSTOM_CFLAGS})
target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-std=c++14 -fexceptions>)
target_link_libraries(${PROJECT_NAME} cross2d sscrap ${CUSTOM_LDFLAGS})


#############
# targets
#############
include(${CMAKE_SOURCE_DIR}/external/libcross2d/cmake/targets.cmake)
