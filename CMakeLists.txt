cmake_minimum_required(VERSION 3.24)
project(transparancycomparison)

set(CMAKE_CXX_STANDARD 14)

add_executable(transparancycomparison src/main.cpp src/boiler.cpp src/stb_image.h)

find_package(GLEW REQUIRED)
target_link_libraries(transparancycomparison PRIVATE GLEW::GLEW)

# this is heuristically generated, and may not be correct
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(transparancycomparison PRIVATE glfw)

add_custom_command(
        TARGET transparancycomparison
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E
        create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/imgs $<TARGET_FILE_DIR:transparancycomparison>/imgs)
