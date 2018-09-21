// dog.cpp

#include "dog.hpp"
#include "config.h"
#include <SDL2/SDL.h>

dog::dog() : wrapper::sdl_object{} {
  set_file_name(way_to_images + "dog.png");
  set_size(128, 82);
  set_pos(15, 20);
  set_angle(20);
  set_flip(SDL_FLIP_HORIZONTAL);
}

dog::~dog() {}

void dog::update() {
  this->set_frame(0, static_cast<int>(::SDL_GetTicks() / 100) % 6);
}
