cmake_minimum_required(VERSION 3.14)
project(SpaceBattle VERSION 0.1.0 LANGUAGES C CXX)

# include(CTest)
# enable_testing()
option(MYLIB_BUILD_TESTS "Build mylib tests" ON)

set(sources
    src/MovableAdapter/MovableAdapter.cpp
    src/Move/Move.cpp
    src/RotableAdapter/RotableAdapter.cpp
    src/Rotate/Rotate.cpp
    src/Types/Direction.cpp)
    
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

add_library(${CMAKE_PROJECT_NAME} ${sources})
add_library(${CMAKE_PROJECT_NAME}::${CMAKE_PROJECT_NAME} ALIAS ${CMAKE_PROJECT_NAME})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

if(MYLIB_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
