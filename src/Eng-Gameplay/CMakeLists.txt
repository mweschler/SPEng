set(GAMEPLAY_SOURCE 
gptemp.cpp
)
set(GAMEPLAY_HEADER 
gptemp.h
)

include_directories(${CMAKE_SOURCE_DIR}/Eng-Pil
${CMAKE_SOURCE_DIR}/Eng-Core
)
#link_directories(${ENG_BINARY_DIR}/Eng-Pil)

add_library (Eng-Gameplay STATIC ${GAMEPLAY_SOURCE} ${GAMEPLAY_HEADER})

target_link_libraries(Eng-Gameplay Eng-Core Eng-PIL)