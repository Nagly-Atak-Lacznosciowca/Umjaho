cmake_minimum_required(VERSION 3.27)
project(Umjaho)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(libs/SDL EXCLUDE_FROM_ALL)

file(GLOB_RECURSE HEADERS "include/*.h")
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(Umjaho WIN32 ${SOURCES} ${HEADERS})

target_include_directories(Umjaho PRIVATE include)

target_link_libraries(Umjaho PRIVATE SDL3::SDL3)
