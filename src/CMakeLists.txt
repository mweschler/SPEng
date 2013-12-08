cmake_minimum_required (VERSION 2.8)
project(Eng)

option(ENG_BUILD_TESTS "Build the tests for the eninge" ON)
option(ENG_ASSERTIONS_ENABLED "Should the library block on assertion failures" ON)
option(ENG_BUILD_DOCUMENTATION "Builds doxygen documentation" OFF)
option(ENG_BUILD_RENDER_DEMO "Builds the render demo" OFF)
option(ENG_BUILD_DEMO "Builds the demonstration application" ON)

#include sfml header files
include_directories(${CMAKE_SOURCE_DIR}/../3rdparty/SFML-2.1/include)
#setup 3rdparty libraries
if(MSVC)
	set(GLEW_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/../3rdparty/glew-1.10.0/lib/Release/Win32)
	set(GLEW_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/../3rdparty/glew-1.10.0/include)
	set(GLEW_LIBRARY glew32)
endif(MSVC)
#add_definitions(-DGLEW_STATIC)
#Add pre-processor definition for sfml audio library
add_definitions(-DSFML_STATIC)
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})
link_directories(${GLEW_LIBRARY_DIR})

if(ENG_BUILD_DOCUMENTATION)
find_package(Doxygen)

set(DOXYGEN_INPUT ${CMAKE_SOURCE_DIR}/spengdox)
set(DOXYGEN_OUTPUT /Documentation)

if(WIN32)
	set(DOXYGEN_EXECUTABLE ${CMAKE_SOURCE_DIR}/../tools/doxygen/bin/windows/doxygen.exe)
	#set(DOXYGEN_FOUND)
endif(WIN32)

if(DOXYGEN_FOUND)
	add_custom_command(
		OUTPUT ${DOXYGEN_OUTPUT}
		COMMAND ${CMAKE_COMMAND} -E echo_append "Building documentation..."
		COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_INPUT}
		COMMAND ${CMAKE_COMMAND} -E echo "Finished building documentation."
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
		DEPENDS ${DOXYGEN_INPUT}
	)
	
	add_custom_target(apidoc ALL DEPENDS ${DOXYGEN_OUTPUT})
	
endif(DOXYGEN_FOUND)
endif(ENG_BUILD_DOCUMENTATION)	

if(MSVC)
	add_definitions(/MDd)
endif(MSVC)

include_directories(${CMAKE_SOURCE_DIR}/../3rdparty/glm)

if(ENG_ASSERTIONS_ENABLED)
	add_definitions(-DASSERTIONS_ENABLED)
endif(ENG_ASSERTIONS_ENABLED)

add_subdirectory(Eng-Pil)
add_subdirectory(Eng-Core)
add_subdirectory(Eng-Gameplay)
add_subdirectory(Eng-Control)
add_subdirectory(Lua)

if(ENG_BUILD_TESTS)
	add_subdirectory(Tests)
endif(ENG_BUILD_TESTS)

if(ENG_BUILD_RENDER_DEMO)
	add_subdirectory(RenderDemo)
endif(ENG_BUILD_RENDER_DEMO)

if(ENG_BUILD_DEMO)
	add_subdirectory(EngDemo)
endif(ENG_BUILD_DEMO)