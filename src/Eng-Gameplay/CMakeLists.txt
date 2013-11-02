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
${CMAKE_SOURCE_DIR}/Lua
)

add_library (Eng-Gameplay STATIC ${GAMEPLAY_SOURCE} ${GAMEPLAY_HEADER})

target_link_libraries(Eng-Gameplay Eng-Core Eng-PIL Lua)