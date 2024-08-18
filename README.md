# ECS-Engine
This C++ header only library is a Entity-Component-System (ECS) Game Engine utilizing the famous SFML C++ multimedia library.

## Brief Overview
Entity.h is used only internally, you need to use the EntityManager for almost everything related to spawning or removing entities. Components can be thought of as containers for data, with that in mind you can retreive entities from the EntityManager, and then return entity component data to build your game systems however you like. A true engine would probably have these system already in place, maybe in the future I may add my own that I find I use the most.

## Usage
Simply clone the repo and copy the directory, "EcsHeaders" and place in your source code location. Begin use via include statements, ensure your build system knows where to find the EcsHeader directory.

## How to build the test bench
The test bench may contain different iterations of the ECS Engine over time as I add new functionality. It will have a basic Game class and window however. You can build it via the following command,
```
cmake --build .\build\ ; .\build\bin\Debug\ECS_ENGINE.exe
```
