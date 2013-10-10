set(CORE_SOURCE core.cpp)
set(CORE_HEADER core.h)

include_directories(${CMAKE_SOURCE_DIR}/Eng-Pil)
#link_directories(${ENG_BINARY_DIR}/Eng-Pil)

add_library (ENG-Core ${CORE_SOURCE} ${CORE_HEADER})

target_link_libraries(ENG-Core Eng-PIL)