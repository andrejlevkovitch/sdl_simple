// main.cpp

#include "sdl_view.hpp"
#include "sdl_model.hpp"
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[]) {
  wrapper::sdl_view view;
  wrapper::sdl_model model;
  view.set_model(&model);

  return (view.show()) ? EXIT_SUCCESS : EXIT_FAILURE;
}
