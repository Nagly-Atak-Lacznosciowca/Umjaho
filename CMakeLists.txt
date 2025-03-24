cmake_minimum_required(VERSION 3.27)
project(Umjaho)

enable_testing()

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(libs/SDL EXCLUDE_FROM_ALL)

file(GLOB_RECURSE HEADERS "include/*.h")
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(${CMAKE_PROJECT_NAME} WIN32 ${SOURCES} ${HEADERS})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE include)
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SDL3::SDL3)

include(RunTests)