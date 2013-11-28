set(CORE_SOURCE
    Logger.cpp
	AssetManager.cpp
	Asset.cpp 
    IObserver.cpp
    Subject.cpp
	RenderManager.cpp
	RenderInternal.cpp
	Material.cpp
	Model.cpp
	GLBuffer.cpp
	ConfigurationManager.cpp
	GLHelper.cpp
	AudioManager.cpp
	Shader.cpp
	ShaderProgram.cpp
	InputHandler.cpp
	AudioContainer.cpp
	Camera.cpp
	Texture.cpp
	)
	
set(CORE_HEADER
    Logger.h
	AssetManager.h
	Asset.h
	IObserver.h
    Subject.h
	ConfigurationManager.h
	VariableContainer.h
	Rendermanager.h
	RenderInternal.h
	Material.h
	Model.h
	GLBuffer.h
	GLHelper.h
	AudioManager.h
	Shader.h
	ShaderProgram.h
	InputHandler.h
	AudioContainer.h
	Camera.h
	Texture.h
	)


set(TINYOBJ_DIR ${CMAKE_SOURCE_DIR}/../3rdparty/tinyobj)

include_directories(${CMAKE_SOURCE_DIR}/Eng-Pil ${TINYOBJ_DIR})
#link_directories(${ENG_BINARY_DIR}/Eng-Pil)

add_library (Eng-Core STATIC ${CORE_SOURCE} ${CORE_HEADER} ${TINYOBJ_DIR}/tiny_obj_loader.cc) 

target_link_libraries(Eng-Core Eng-PIL)