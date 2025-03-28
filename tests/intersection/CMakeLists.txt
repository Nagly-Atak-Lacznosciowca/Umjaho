cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

file(GLOB_RECURSE HEADERS "${CMAKE_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

message("${CMAKE_SOURCE_DIR}/include/game/Game.h")

add_executable(${TEST_NAME} WIN32
    ${TEST_DIR}/main.cpp
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(${TEST_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
#file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
target_link_libraries(${TEST_NAME} PRIVATE SDL3::SDL3)