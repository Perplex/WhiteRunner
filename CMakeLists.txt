cmake_minimum_required(VERSION 3.9)
project(WhiteRunner)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenCV REQUIRED)

INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS})

add_executable(WhiteRunner
        main.cpp WRBot.cpp WRBot.h LootManager.cpp LootManager.h PathManager.cpp PathManager.h MemoryTools.cpp MemoryTools.h ButtonManager.cpp ButtonManager.h common.h ACD.h SymbolTable.h ACD.cpp d3_typeenums.h vector3.cpp vector3.h)

TARGET_LINK_LIBRARIES(WhiteRunner ${OpenCV_LIBS} gdi32)
