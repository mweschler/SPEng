project(Eng-Tests CXX)
set(TESTS mytest.cpp
	ConfigManagerTest.cpp
	guitest.cpp
	MessageSystemTest.cpp
	gameplay-world.cpp
	rendermgrtest.cpp
	LoggerTests.cpp
	AudioManagerTest.cpp
	)

#setup Gtest
if(MSVC)
	add_definitions(-D_VARIADIC_MAX=10)
endif()
add_subdirectory(gtest-1.7.0)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

#tests
if(MSVC)
	add_definitions( /OPT:NOREF)
endif()

include_directories(${CMAKE_SOURCE_DIR}/Eng-PIL 
${CMAKE_SOURCE_DIR}/Eng-Core
${CMAKE_SOURCE_DIR}/Eng-Gameplay
${CMAKE_SOURCE_DIR}/Eng-Control
)

add_executable( runEngTests ${TESTS})

if(WIN32)
	add_custom_command(
		TARGET runEngTests POST_BUILD        # Adds a post-build event to MyTest
		COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
		"${CMAKE_SOURCE_DIR}/../3rdparty/portaudio/lib/windows/portaudio_x86.dll"      # <--this is in-file
		$<TARGET_FILE_DIR:runEngTests>)                 # <--this is out-file path
endif(WIN32)

target_link_libraries(runEngTests gtest Eng-Control)
add_test( runEngTests runEngTests)