// sdl_object.cpp

#include "sdl_object.hpp"
#include "texture_manager.hpp"
#include <SDL2/SDL.h>

wrapper::sdl_object::sdl_object()
    : id_{}, width_{}, height_{}, row_{}, column_{}, x_pos_{}, y_pos_{},
      angle_{}, center_{nullptr}, flip_{SDL_FLIP_NONE} {}

wrapper::sdl_object::~sdl_object() {
  if (center_) {
    delete center_;
  }
}

void wrapper::sdl_object::set_file_name(const std::string &file_name) {
  file_name_ = file_name;
}

void wrapper::sdl_object::set_size(int width, int height) {
  width_ = width;
  height_ = height;
}

void wrapper::sdl_object::set_pos(int x_pos, int y_pos) {
  x_pos_ = x_pos;
  y_pos_ = y_pos;
}

void wrapper::sdl_object::set_frame(int row, int column) {
  row_ = row;
  column_ = column;
}

void wrapper::sdl_object::set_angle(double angle) { angle_ = angle; }

void wrapper::sdl_object::set_center(::SDL_Point *center) {
  if (center_) {
    delete center_;
  }
  center_ = center;
}

void wrapper::sdl_object::set_flip(::SDL_RendererFlip flip) {
  flip_ = flip;
}

bool wrapper::sdl_object::load(::SDL_Renderer *renderer) {
  if ((id_ = texture_manager::instance().load(file_name_, renderer)) > 0) {
    if (!width_ || !height_) {
      auto size_pair = texture_manager::instance().get_texture_size(id_);
      width_ = size_pair.first;
      height_ = size_pair.second;
    }
    return true;
  }
  return false;
}

void wrapper::sdl_object::draw(::SDL_Renderer *renderer) const {
  texture_manager::instance().draw_sprite(renderer, id_, x_pos_, y_pos_, width_,
                                          height_, row_, column_, angle_,
                                          center_, flip_);
}
