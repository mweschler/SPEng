file(GLOB Source_Files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} [^.]*.c [^.]*.h)

add_library (Lua STATIC ${Source_Files})

SET_TARGET_PROPERTIES(Lua PROPERTIES LINKER_LANGUAGE C)