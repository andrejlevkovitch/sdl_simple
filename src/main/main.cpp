// main.cpp

#include "sdl_view.hpp"
#include "sdl_model.hpp"
#include <cstdlib>
#include <iostream>
#include <SDL2/SDL.h>

int main(int argc, char *argv[]) {
  wrapper::sdl_view view{SDL_INIT_EVERYTHING};
  wrapper::sdl_model model;
  view.set_model(&model);

  return (view.show()) ? EXIT_SUCCESS : EXIT_FAILURE;
}
