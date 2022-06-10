cmake_minimum_required(VERSION 3.0)
#set(CMAKE_VERBOSE_MAKEFILE ON)

# add libcross2d library
add_subdirectory(external/libcross2d)

project(retromenu)

set(PROJECT_AUTHOR "Cpasjuste")
set(VERSION_MAJOR "1")
set(VERSION_MINOR "0")

#############
# code
#############
set(INCLUDES ${CMAKE_SOURCE_DIR}/source)
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/source/*.cpp)
set(CFLAGS
        -DVERSION_MAJOR="${VERSION_MAJOR}"
        -DVERSION_MINOR="${VERSION_MINOR}")
set(LDFLAGS)

############
# deps
############
list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
find_package(TinyXML2 REQUIRED)
list(APPEND INCLUDES  ${TinyXML2_INCLUDE_DIRS})
list(APPEND LDFLAGS  ${TinyXML2_LIBRARIES})

#############
# executable
#############
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDES})
target_compile_options(${PROJECT_NAME} PRIVATE ${CFLAGS})
target_link_libraries(${PROJECT_NAME} cross2d ${LDFLAGS})

#############
# targets
#############
include(${CMAKE_SOURCE_DIR}/external/libcross2d/cmake/targets.cmake)
