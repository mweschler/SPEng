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
	)


include_directories(${CMAKE_SOURCE_DIR}/Eng-Pil)
#link_directories(${ENG_BINARY_DIR}/Eng-Pil)

add_library (Eng-Core STATIC ${CORE_SOURCE} ${CORE_HEADER})

target_link_libraries(Eng-Core Eng-PIL)