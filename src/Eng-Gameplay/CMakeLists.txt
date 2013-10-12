set(GAMEPLAY_SOURCE 
GameObject.cpp
GameWorld.cpp
)
set(GAMEPLAY_HEADER 
GameObject.h
GameWorld.h
IGameplayFoundation.h
IComponent.h
)

include_directories(${CMAKE_SOURCE_DIR}/Eng-Pil
${CMAKE_SOURCE_DIR}/Eng-Core
)
#link_directories(${ENG_BINARY_DIR}/Eng-Pil)

add_library (Eng-Gameplay ${GAMEPLAY_SOURCE} ${GAMEPLAY_HEADER})

target_link_libraries(Eng-Gameplay Eng-Core Eng-PIL)