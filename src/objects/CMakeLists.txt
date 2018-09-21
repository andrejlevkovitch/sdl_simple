# objects

configure_file("config.h.cmake" "${CMAKE_CURRENT_SOURCE_DIR}/include/config.h")

set(OBJ_LBR "objs")
file(GLOB OBJ_SRC "sources/*.cpp")
set(LIST_TARGETS "${LIST_TARGETS};${OBJ_LBR}" CACHE STRING "add target" FORCE)

add_library(${OBJ_LBR} ${OBJ_SRC})

target_include_directories(${OBJ_LBR} PUBLIC "include")
target_include_directories(${OBJ_LBR} PRIVATE "../sdl_model/include")
