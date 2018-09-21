# view

set(SDL_VIEW_LBR "sdl_view")
file(GLOB SDL_VIEW_SRC "sources/*.cpp")
set(LIST_TARGETS "${LIST_TARGETS};${SDL_VIEW_LBR}" CACHE STRING "add target" FORCE)

add_library(${SDL_VIEW_LBR} ${SDL_VIEW_SRC})

target_include_directories(${SDL_VIEW_LBR} PUBLIC "include")
target_include_directories(${SDL_VIEW_LBR} PRIVATE "../sdl_model/include")
