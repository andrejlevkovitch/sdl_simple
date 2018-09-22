// sdl_object.cpp

#include "sdl_object.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

wrapper::sdl_object::sdl_object()
    : texture_{}, width_{}, height_{}, row_{}, column_{}, x_pos_{}, y_pos_{},
      angle_{}, center_{nullptr}, flip_{SDL_FLIP_NONE} {}

wrapper::sdl_object::~sdl_object() {
  if (center_) {
    delete center_;
  }
  if (texture_) {
    ::SDL_DestroyTexture(texture_);
  }
}

void wrapper::sdl_object::set_file_name(const std::string &file_name) {
  file_name_ = file_name;
}

const std::string &wrapper::sdl_object::get_file_name() const {
  return file_name_;
}

void wrapper::sdl_object::set_size(int width, int height) {
  width_ = width;
  height_ = height;
}

std::pair<int, int> wrapper::sdl_object::get_size() const {
  return std::make_pair(width_, height_);
}

void wrapper::sdl_object::set_pos(int x_pos, int y_pos) {
  x_pos_ = x_pos;
  y_pos_ = y_pos;
}

std::pair<int, int> wrapper::sdl_object::get_pos() const {
  return std::make_pair(x_pos_, y_pos_);
}

void wrapper::sdl_object::set_frame(int row, int column) {
  row_ = row;
  column_ = column;
}

std::pair<int, int> wrapper::sdl_object::get_frame() const {
  return std::make_pair(row_, column_);
}

void wrapper::sdl_object::set_angle(double angle) { angle_ = angle; }

double wrapper::sdl_object::get_angle() const { return angle_; }

void wrapper::sdl_object::set_center(::SDL_Point *center) {
  if (center_) {
    delete center_;
  }
  center_ = center;
}

const ::SDL_Point *wrapper::sdl_object::get_center() const { return center_; }

void wrapper::sdl_object::set_flip(int flip) { flip_ = flip; }

int wrapper::sdl_object::get_flip() const { return flip_; }

bool wrapper::sdl_object::load(::SDL_Renderer *renderer) {
  auto surface = ::IMG_Load(file_name_.c_str());
  if (surface) {
    texture_ = ::SDL_CreateTextureFromSurface(renderer, surface);
    ::SDL_FreeSurface(surface);
    if (texture_) {
      if (!width_ || !height_) {
        ::SDL_QueryTexture(texture_, 0, 0, &width_, &height_);
      }
      return true;
    }
  }
  return false;
}

void wrapper::sdl_object::draw(::SDL_Renderer *renderer) const {
  ::SDL_Rect src_rect;
  ::SDL_Rect des_rect;

  src_rect.x = width_ * column_;
  src_rect.y = height_ * row_;

  des_rect.x = x_pos_;
  des_rect.y = y_pos_;
  des_rect.w = src_rect.w = width_;
  des_rect.h = src_rect.h = height_;

  ::SDL_RenderCopyEx(renderer, texture_, &src_rect, &des_rect, angle_, center_,
                     static_cast<::SDL_RendererFlip>(flip_));
}
