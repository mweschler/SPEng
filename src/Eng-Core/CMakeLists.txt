set(CORE_SOURCE 
RenderManager.cpp
)
set(CORE_HEADER 
Rendermanager.h
)

include_directories(${CMAKE_SOURCE_DIR}/Eng-Pil)
#link_directories(${ENG_BINARY_DIR}/Eng-Pil)

add_library (Eng-Core STATIC ${CORE_SOURCE} ${CORE_HEADER})

target_link_libraries(Eng-Core Eng-PIL)