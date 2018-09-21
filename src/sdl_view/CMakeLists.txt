# view

set(SDL_VIEW_LBR "sdl_view" CACHE STRING "set in cache" FORCE)
file(GLOB SDL_VIEW_SRC "sources/*.cpp")
set(LIST_TARGETS "${LIST_TARGETS};${SDL_VIEW_LBR}" CACHE STRING "add target" FORCE)

add_library(${SDL_VIEW_LBR} ${SDL_VIEW_SRC})

target_include_directories(${SDL_VIEW_LBR} PUBLIC "include")
target_include_directories(${SDL_VIEW_LBR} PRIVATE "../sdl_model/include")

if(BUILD_TESTING)
  find_package(Boost COMPONENTS unit_test_framework)
  if(Boost_FOUND AND NOT WITHOUT_SCREEN)
    find_package(SDL2 REQUIRED)
    set(TEST_VIEW "view_test")
    set(TEST_VIEW_SRC "test/boost_test_view.cpp")
    add_executable(${TEST_VIEW} ${TEST_VIEW_SRC})
    target_link_libraries(${TEST_VIEW} ${SDL_VIEW_LBR} ${SDL_MODEL_LBR} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})
    add_test(NAME ${TEST_VIEW} COMMAND ${TEST_VIEW})
  else()
    message(WARNING "for testing Boost and Screen required!")
  endif()
endif()
