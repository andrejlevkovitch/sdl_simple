// main.cpp

#include "sdl_view.hpp"
#include "sdl_model.hpp"
#include <cstdlib>
#include <iostream>
#include "dog.hpp"

int main(int argc, char *argv[]) {
  wrapper::sdl_view view;
  wrapper::sdl_model model;
  view.set_model(&model);

  dog *dog = new class dog;
  model.add_item(dog);

  return (view.show()) ? EXIT_SUCCESS : EXIT_FAILURE;
}
