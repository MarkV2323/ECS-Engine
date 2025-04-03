cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

project(ecs_engine)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Grab SFML from github
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# Core
set (CORE_FILES
    src/Ecs/Core/game_vector.h
    src/Ecs/Core/entity.h
    src/Ecs/Core/entity_manager.h
)

# Components
set (COMPONENT_FILES
    src/Ecs/Component/circle_shape.h
    src/Ecs/Component/rectangle_shape.h
    src/Ecs/Component/input.h
    src/Ecs/Component/lifespan.h
    src/Ecs/Component/score.h
    src/Ecs/Component/transform.h
    src/Ecs/Component/collision.h
)

# Set Sources
set(SOURCES
    ${CORE_FILES}
    ${COMPONENT_FILES}
    src/main.cc
)

# Setup target & link
add_executable(ECS_ENGINE ${SOURCES})
target_include_directories(ECS_ENGINE PRIVATE ${PROJECT_SOURCE_DIR}/src/Ecs)
target_link_libraries(ECS_ENGINE PRIVATE sfml-graphics sfml-system)
target_compile_features(ECS_ENGINE PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET ECS_ENGINE
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:ECS_ENGINE>
        VERBATIM)
endif()

install(TARGETS ECS_ENGINE)