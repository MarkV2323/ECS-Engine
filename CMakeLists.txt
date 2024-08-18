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

# Set Headers
set (HEADERS
    src/EcsHeaders/CollisionComp.h
    src/EcsHeaders/InputComp.h
    src/EcsHeaders/LifespanComp.h
    src/EcsHeaders/ScoreComp.h
    src/EcsHeaders/ShapeComp.h
    src/EcsHeaders/RectShapeComp.h
    src/EcsHeaders/TransformComp.h
    src/EcsHeaders/Entity.h
    src/EcsHeaders/EntityManager.h
    src/EcsHeaders/GameVector.h
)

# Set Sources
set(SOURCES
    ${HEADERS}
    src/Main.cc
)

# Setup target & link
add_executable(ECS_ENGINE ${SOURCES})
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