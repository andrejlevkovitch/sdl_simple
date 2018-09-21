# cmake model

set(SDL_MODEL_LBR "sdl_model")
file(GLOB SDL_MODEL_SRC "sources/*.cpp")
set(LIST_TARGETS "${LIST_TARGETS};${SDL_MODEL_LBR}" CACHE STRING "add target" FORCE)

add_library(${SDL_MODEL_LBR} ${SDL_MODEL_SRC})

target_include_directories(${SDL_MODEL_LBR} PUBLIC "include")
