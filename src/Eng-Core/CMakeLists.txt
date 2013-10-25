set(CORE_SOURCE core.cpp 
    Logger.cpp
	AssetManager.cpp
	Asset.cpp 
)
set(CORE_HEADER core.h
	Logger.h
	AssetManager.h
	Asset.h

)

include_directories(${CMAKE_SOURCE_DIR}/Eng-Pil)
#link_directories(${ENG_BINARY_DIR}/Eng-Pil)

add_library (Eng-Core ${CORE_SOURCE} ${CORE_HEADER})

target_link_libraries(Eng-Core Eng-PIL)