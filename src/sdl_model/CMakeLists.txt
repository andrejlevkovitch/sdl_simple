# cmake model

set(SDL_MODEL_LBR "sdl_model" CACHE STRING "set in cache" FORCE)
file(GLOB SDL_MODEL_SRC "sources/*.cpp")
set(LIST_TARGETS "${LIST_TARGETS};${SDL_MODEL_LBR}" CACHE STRING "add target" FORCE)

add_library(${SDL_MODEL_LBR} ${SDL_MODEL_SRC})

target_include_directories(${SDL_MODEL_LBR} PUBLIC "include")

if(BUILD_TESTING)
  find_package(Boost COMPONENTS unit_test_framework)
  if(Boost_FOUND)
    find_package(SDL2 REQUIRED)
    set(TEST_OBJ "obj_test")
    set(TEST_OBJ_SRC "test/boost_test_obj.cpp")
    add_executable(${TEST_OBJ} ${TEST_OBJ_SRC})
    target_link_libraries(${TEST_OBJ} ${SDL_MODEL_LBR} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})
    add_test(NAME ${TEST_OBJ} COMMAND ${TEST_OBJ})

    set(TEST_MODEL "model_test")
    set(TEST_MODEL_SRC "test/boost_test_model.cpp")
    add_executable(${TEST_MODEL} ${TEST_MODEL_SRC})
    target_link_libraries(${TEST_MODEL} ${SDL_MODEL_LBR} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})
    add_test(NAME ${TEST_MODEL} COMMAND ${TEST_MODEL})
  else()
    message(WARNING "for testing Boost required!")
  endif()
endif()
