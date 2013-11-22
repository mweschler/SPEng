set(CONTROL_SOURCE 
main.cpp
renderdemo.cpp)
set(CONTROL_HEADER renderdemo.h)

include_directories(${CMAKE_SOURCE_DIR}/Eng-Pil
${CMAKE_SOURCE_DIR}/Eng-Core
${CMAKE_SOURCE_DIR}/Eng-Gameplay
${CMAKE_SOURCE_DIR}/Eng-Control
${CMAKE_SOURCE_DIR}/Lua
)

add_executable (RenderDemo ${CONTROL_SOURCE} ${CONTROL_HEADER})

target_link_libraries(RenderDemo Eng-Control Eng-Gameplay Eng-Core Eng-PIL)