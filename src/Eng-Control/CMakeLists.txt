set(CONTROL_SOURCE coregameapp.cpp)
set(CONTROL_HEADER coregameapp.h)

include_directories(${CMAKE_SOURCE_DIR}/Eng-Pil
${CMAKE_SOURCE_DIR}/Eng-Core
${CMAKE_SOURCE_DIR}/Eng-Gameplay
${CMAKE_SOURCE_DIR}/Lua
)

add_library (Eng-Control STATIC ${CONTROL_SOURCE} ${CONTROL_HEADER})

target_link_libraries(Eng-Control Eng-Gameplay Eng-Core Eng-PIL)