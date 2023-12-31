cmake_minimum_required(VERSION 3.14)
project(SpaceBattle VERSION 0.1.0 LANGUAGES C CXX)

# include(CTest)
# enable_testing()
option(MYLIB_BUILD_TESTS "Build mylib tests" ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(sources
    src/Adapters/FuelAdapters/BurnFuelAdapter.cpp
    src/Adapters/FuelAdapters/CheckFuelAdapter.cpp
    src/Adapters/MoveAdapters/MovableAdapter.cpp
    src/Adapters/MoveAdapters/RotableAdapter.cpp
    src/Adapters/MoveAdapters/ChangeVelocityAdapter.cpp
    src/Commands/Move/Move.cpp
    src/Commands/Rotate/Rotate.cpp
    src/Commands/LogException/LogException.cpp
    src/Commands/RepeatCommand/RepeatCommand.cpp
    src/Commands/BurnFuel/BurnFuel.cpp
    src/Commands/CheckFuel/CheckFuel.cpp
    src/Commands/ChangeVelocity/ChangeVelocity.cpp
    src/Commands/MacroCommand/MacroCommand.cpp
    src/Exceptions/ExceptionHandler.cpp
    src/Types/Direction.cpp)
    
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

add_library(${CMAKE_PROJECT_NAME} ${sources})
add_library(${CMAKE_PROJECT_NAME}::${CMAKE_PROJECT_NAME} ALIAS ${CMAKE_PROJECT_NAME})

target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

if(MYLIB_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
