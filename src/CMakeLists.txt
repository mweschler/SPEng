cmake_minimum_required (VERSION 2.8)
project(Eng)

option(ENG_BUILD_TESTS "Build the tests for the eninge" ON)
option(ENG_ASSERTIONS_ENABLED "Should the library block on assertion failures" ON)

#setup 3rdparty libraries
if(MSVC)
	set(GLEW_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/../3rdparty/glew-1.10.0/lib/Release/Win32)
	set(GLEW_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/../3rdparty/glew-1.10.0/include)
	set(GLEW_LIBRARY glew32s)
endif(MSVC)
add_definitions(-DGLEW_STATIC)
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})
link_directories(${GLEW_LIBRARY_DIR})


if(MSVC)
	add_definitions(/MDd)
endif(MSVC)

if(ENG_ASSERTIONS_ENABLED)
	add_definitions(-DASSERTIONS_ENABLED)
endif(ENG_ASSERTIONS_ENABLED)

add_subdirectory(Eng-Pil)
add_subdirectory(Eng-Core)
add_subdirectory(Eng-Gameplay)
add_subdirectory(Eng-Control)

if(ENG_BUILD_TESTS)
	add_subdirectory(Tests)
endif(ENG_BUILD_TESTS)