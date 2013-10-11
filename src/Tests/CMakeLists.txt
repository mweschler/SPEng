project(Eng-Tests CXX)
set(TESTS mytest.cpp)


#setup Gtest
if(WIN32)
	add_definitions(-D_VARIADIC_MAX=10)
endif()
add_subdirectory(gtest-1.7.0)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

#tests
if(WIN32)
	add_definitions( /OPT:NOREF)
endif()

include_directories(${CMAKE_SOURCE_DIR}/Eng-PIL 
${CMAKE_SOURCE_DIR}/Eng-Core
${CMAKE_SOURCE_DIR}/Eng-Gameplay
${CMAKE_SOURCE_DIR}/Eng-Control
)

add_executable( runEngTests ${TESTS})
target_link_libraries(runEngTests gtest Eng-Control)
add_test( runEngTests runEngTests)