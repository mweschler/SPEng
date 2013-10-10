project(Eng-Tests)
set(TESTS mytest.cpp)


#setup Gtest
add_subdirectory(gtest-1.7.0)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

#tests
include_directories(${CMAKE_SOURCE_DIR}/Eng-PIL 
${CMAKE_SOURCE_DIR}/Eng-Core)
add_executable( runEngTests ${TESTS})
target_link_libraries(runEngTests gtest gtest_main Eng-Core)
add_test( runEngTests runEngTests)