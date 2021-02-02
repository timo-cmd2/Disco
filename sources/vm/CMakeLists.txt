file(GLOB lily_SOURCES *.c *.h)

# The goal is to have a rift executable that's standalone, and a shared librift
# library. The two use the same sources, put together in an object library.
add_library(librift_obj OBJECT ${rift_SOURCES})
add_library(librift SHARED $<TARGET_OBJECTS:librift_obj>)

if(NOT MSVC)
    if(RIFT_NEED_DL)
        target_link_libraries(librift dl)
    endif()
    # -fPIC is needed for it to work properly as a shared library.
    set_target_properties(librift_obj PROPERTIES COMPILE_FLAGS "-fPIC")
    set_target_properties(librift PROPERTIES PREFIX "")
endif()

install(TARGETS librift
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	COMPONENT library)

install(FILES rift.h
              rift_int_code_iter.h
              rift_int_opcode.h
        DESTINATION "include/rift")
