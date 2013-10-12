set(CORE_SOURCE
    IObserver.cpp
    Subject.cpp
	RenderManager.cpp
	)
set(CORE_HEADER
	IObserver.h
    Subject.h
	Rendermanager.h
	)


include_directories(${CMAKE_SOURCE_DIR}/Eng-Pil)
#link_directories(${ENG_BINARY_DIR}/Eng-Pil)

add_library (Eng-Core STATIC ${CORE_SOURCE} ${CORE_HEADER})

target_link_libraries(Eng-Core Eng-PIL)