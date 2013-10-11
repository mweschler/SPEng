cmake_minimum_required (VERSION 2.8)
project(Eng)

option(ENG_BUILD_TESTS "Build the tests for the eninge" ON)

if(WIN32)
	add_definitions(/MTd)
endif()

add_subdirectory(Eng-Pil)
add_subdirectory(Eng-Core)
add_subdirectory(Eng-Gameplay)
add_subdirectory(Eng-Control)

if(ENG_BUILD_TESTS)
	add_subdirectory(Tests)
endif()