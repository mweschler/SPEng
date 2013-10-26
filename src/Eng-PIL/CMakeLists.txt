set(PIL_SOURCE 
assertions.cpp
window.cpp
gui.cpp
rendercontext.cpp
devicecontext.cpp
)
set(PIL_HEADER 
assertions.h
window.h
gui.h
)


add_library (Eng-PIL STATIC ${PIL_SOURCE} ${PIL_HEADER})

target_link_libraries(Eng-PIL ${GLEW_LIBRARY})