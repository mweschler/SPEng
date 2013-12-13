set(DEMO_SOURCE 
main.cpp
engdemo.cpp
modelComponent.cpp
renderList.cpp
ScriptComponent.cpp
)
set(DEMO_HEADER engdemo.h
modelComponent.h
renderList.h
ScriptComponent.h
)

include_directories(${CMAKE_SOURCE_DIR}/Eng-Pil
${CMAKE_SOURCE_DIR}/Eng-Core
${CMAKE_SOURCE_DIR}/Eng-Gameplay
${CMAKE_SOURCE_DIR}/Eng-Control
${CMAKE_SOURCE_DIR}/Lua
)

add_executable (EngDemo ${DEMO_SOURCE} ${DEMO_HEADER})

if(WIN32)
add_custom_command(
		TARGET EngDemo POST_BUILD        
		COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
		"${CMAKE_SOURCE_DIR}/../3rdparty/glew-1.10.0/bin/Release/Win32/glew32.dll"      # <--this is in-file
		$<TARGET_FILE_DIR:EngDemo>)                 # <--this is out-file path
	#Copies openal32.dll file to executable path
	add_custom_command(
		TARGET EngDemo POST_BUILD        # Adds a post-build event to runEngTests
		COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
		"${CMAKE_SOURCE_DIR}/../3rdparty/SFML-2.1/bin/openal32.dll"      # <--this is in-file
		$<TARGET_FILE_DIR:EngDemo>)                 # <--this is out-file path
	#Copies libsnd.dll file to exceutable path
	add_custom_command(
		TARGET EngDemo POST_BUILD        # Adds a post-build event to runEngTests
		COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
		"${CMAKE_SOURCE_DIR}/../3rdparty/SFML-2.1/bin/libsndfile-1.dll"      # <--this is in-file
		$<TARGET_FILE_DIR:EngDemo>)                 # <--this is out-file path
	add_custom_command(
		TARGET EngDemo POST_BUILD        # Adds a pre-build event to runEngTests
		COMMAND ${CMAKE_COMMAND} -E copy_directory  # which executes "cmake - E copy_directory..."
		"${CMAKE_SOURCE_DIR}/../resources"      # <--this is in-directory
		"${PROJECT_BINARY_DIR}/EngDemo")    # <--this is out-file path
endif(WIN32)

target_link_libraries(EngDemo Eng-Control Eng-Gameplay Eng-Core Eng-PIL Lua ${CMAKE_SOURCE_DIR}/../3rdparty/SFML-2.1/lib/sfml-audio-s-d.lib ${CMAKE_SOURCE_DIR}/../3rdparty/SFML-2.1/lib/sfml-system-s-d.lib ${CMAKE_SOURCE_DIR}/../3rdparty/SFML-2.1/lib/sfml-window-s-d.lib ${CMAKE_SOURCE_DIR}/../3rdparty/SFML-2.1/lib/sfml-graphics-s-d.lib)