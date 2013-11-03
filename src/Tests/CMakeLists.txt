project(Eng-Tests CXX)
set(TESTS mytest.cpp
	ConfigManagerTest.cpp
	guitest.cpp
	MessageSystemTest.cpp
	gameplay-world.cpp
	rendermgrtest.cpp
	LoggerTests.cpp
	AudioManagerTest.cpp
	ShaderTests.cpp
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

#Copies necessary .dll files for sfml api to executable path
if(WIN32)
	#Copies openal32.dll file to executable path
	add_custom_command(
		TARGET runEngTests POST_BUILD        # Adds a post-build event to runEngTests
		COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
		"${CMAKE_SOURCE_DIR}/../3rdparty/SFML-2.1/bin/openal32.dll"      # <--this is in-file
		$<TARGET_FILE_DIR:runEngTests>)                 # <--this is out-file path
	#Copies libsnd.dll file to exceutable path
	add_custom_command(
		TARGET runEngTests POST_BUILD        # Adds a post-build event to runEngTests
		COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
		"${CMAKE_SOURCE_DIR}/../3rdparty/SFML-2.1/bin/libsndfile-1.dll"      # <--this is in-file
		$<TARGET_FILE_DIR:runEngTests>)                 # <--this is out-file path
	#Copies contents of resources directory to working directory
	add_custom_command(
		TARGET runEngTests PRE_BUILD        # Adds a pre-build event to runEngTests
		COMMAND ${CMAKE_COMMAND} -E copy_directory  # which executes "cmake - E copy_directory..."
		"${CMAKE_SOURCE_DIR}/../resources"      # <--this is in-directory
		"${PROJECT_BINARY_DIR}")    # <--this is out-file path
endif(WIN32)

target_link_libraries(runEngTests gtest Eng-Control ${CMAKE_SOURCE_DIR}/../3rdparty/SFML-2.1/lib/sfml-audio-s-d.lib ${CMAKE_SOURCE_DIR}/../3rdparty/SFML-2.1/lib/sfml-system-s-d.lib) #Links sfml libraries necessary for debug environment
add_test( runEngTests runEngTests)