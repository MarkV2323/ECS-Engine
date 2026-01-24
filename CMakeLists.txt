cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_TOOLCHAIN_FILE "/opt/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE PATH "vcpkg toolchain file")

project(SFML_Example LANGUAGES CXX)

# Use VCPKG to find the following libs,
# -> SFML (used for windowing, drawing and general media
# -> FMT  (used for general stdout)
find_package(SFML CONFIG REQUIRED COMPONENTS Window Graphics Network Audio)
find_package(fmt CONFIG REQUIRED)

# GLOB source and headers
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.hpp")

add_executable(Ecs ${SOURCES} ${HEADERS})

target_include_directories(Ecs PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(Ecs PRIVATE SFML::Window SFML::Graphics SFML::Network SFML::Audio)
target_link_libraries(Ecs PRIVATE fmt::fmt)
