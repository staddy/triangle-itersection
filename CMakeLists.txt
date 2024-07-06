cmake_minimum_required(VERSION 3.16)
project(triangle-intersection)

set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_NAME ${PROJECT_NAME})
add_executable(${EXECUTABLE_NAME})

include_directories(include)

target_sources(${EXECUTABLE_NAME}
PRIVATE
    src/main.cpp
    src/geometry_utils.cpp
    src/triangle.cpp
)

add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/tests $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/)
