cmake_minimum_required(VERSION 3.15)
project(SFML_Example LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

# Use VCPKG to find the following libs,
# -> SFML (used for windowing, drawing and general media
# -> FMT  (used for general stdout)
find_package(SFML REQUIRED COMPONENTS Window Graphics Network Audio)
find_package(fmt CONFIG REQUIRED)

# GLOB source and headers
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.hpp")

add_executable(SFML_Example ${SOURCES} ${HEADERS})

target_link_libraries(SFML_Example PRIVATE SFML::Window SFML::Graphics SFML::Network SFML::Audio)
target_link_libraries(SFML_Example PRIVATE fmt::fmt)

