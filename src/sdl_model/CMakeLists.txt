# cmake model

find_package(SDL2 REQUIRED)

set(SDL_MODEL_LBR "sdl_model")
file(GLOB SDL_MODEL_SRC "sources/*.cpp")
set(LIST_TARGETS "${LIST_TARGETS};${SDL_MODEL_LBR}" CACHE STRING "add target" FORCE)

add_library(${SDL_MODEL_LBR} ${SDL_MODEL_SRC})

target_link_libraries(${SDL_MODEL_LBR} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})
target_include_directories(${SDL_MODEL_LBR} PUBLIC "include")
