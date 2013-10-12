set(CORE_SOURCE core.cpp
    CORE_SOURCE IObserver.cpp
	CORE_SOURCE Subject.cpp)
set(CORE_HEADER core.h
	CORE_HEADER IObserver.h
	CORE_HEADER Subject.h)

include_directories(${CMAKE_SOURCE_DIR}/Eng-Pil)
#link_directories(${ENG_BINARY_DIR}/Eng-Pil)

add_library (Eng-Core ${CORE_SOURCE} ${CORE_HEADER})

target_link_libraries(Eng-Core Eng-PIL)