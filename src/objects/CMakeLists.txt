# objects

configure_file("config.h.cmake" "${CMAKE_CURRENT_SOURCE_DIR}/include/config.h")

set(OBJ_LBR "objs")
file(GLOB OBJ_SRC "sources/*.cpp")
set(LIST_TARGETS "${LIST_TARGETS};${OBJ_LBR}" CACHE STRING "add target" FORCE)

add_library(${OBJ_LBR} ${OBJ_SRC})

target_include_directories(${OBJ_LBR} PUBLIC "include")
target_include_directories(${OBJ_LBR} PRIVATE "../sdl_model/include")

if(BUILD_TESTING)
  find_package(Boost COMPONENTS unit_test_framework)
  if(Boost_FOUND AND NOT WITHOUT_SCREEN)
    find_package(SDL2 REQUIRED)
    set(TEST_DRAW "draw_test")
    set(TEST_DRAW_SRC "test/boost_test_draw.cpp")
    add_executable(${TEST_DRAW} ${TEST_DRAW_SRC})
    target_link_libraries(${TEST_DRAW} ${SDL_VIEW_LBR} ${SDL_MODEL_LBR} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})
    target_include_directories(${TEST_DRAW} PRIVATE "include")
    add_test(NAME ${TEST_DRAW} COMMAND ${TEST_DRAW})
  else()
    message(WARNING "for testing Boost and Screen required!")
  endif()
endif()
