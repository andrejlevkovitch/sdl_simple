// texture_manager.cpp

#include "texture_manager.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

wrapper::texture_manager &wrapper::texture_manager::instance() {
  static texture_manager retval;
  return retval;
}

wrapper::texture_manager::texture_manager() : last_id_{} {}

wrapper::texture_manager::~texture_manager() {
  for (auto &i : texture_map_) {
    ::SDL_DestroyTexture(i.second);
  }
}

Uint32 wrapper::texture_manager::load(const std::string &file_name,
                                      SDL_Renderer *renderer) {
  ++last_id_;
  auto surface = ::IMG_Load(file_name.c_str());
  if (surface) {
    auto texture = ::SDL_CreateTextureFromSurface(renderer, surface);
    ::SDL_FreeSurface(surface);
    if (texture) {
      if (texture_map_.insert(std::make_pair(last_id_, texture)).second) {
        return last_id_;
      }
    }
  }
  return 0;
}

void wrapper::texture_manager::draw(::SDL_Renderer *renderer,
                                    Uint32 id, int x_pos, int y_pos,
                                    int width, int height, double angle,
                                    const ::SDL_Point *const center,
                                    ::SDL_RendererFlip flip) const {
  ::SDL_Rect src_rect;
  ::SDL_Rect des_rect;

  src_rect.x = 0;
  src_rect.y = 0;
  des_rect.x = x_pos;
  des_rect.y = y_pos;
  des_rect.w = src_rect.w = width;
  des_rect.h = src_rect.h = height;

  ::SDL_RenderCopyEx(renderer, texture_map_.at(id), &src_rect, &des_rect, angle,
                     center, flip);
}

void wrapper::texture_manager::draw_sprite(::SDL_Renderer *renderer,
                                           Uint32 id, int x_pos,
                                           int y_pos, int width, int height,
                                           int row, int column, double angle,
                                           const ::SDL_Point *const center,
                                           SDL_RendererFlip flip) const {
  ::SDL_Rect src_rect;
  ::SDL_Rect des_rect;

  src_rect.x = width * column;
  src_rect.y = height * row;

  des_rect.x = x_pos;
  des_rect.y = y_pos;
  des_rect.w = src_rect.w = width;
  des_rect.h = src_rect.h = height;

  try {
    ::SDL_RenderCopyEx(renderer, texture_map_.at(id), &src_rect, &des_rect,
                       angle, center, flip);
  } catch (std::out_of_range &) {
    std::cerr << "out of range" << std::endl;
    std::cerr << id << " not have this alias" << std::endl;
  }
}

std::pair<int, int>
wrapper::texture_manager::get_texture_size(Uint32 id) const {
  int width{};
  int height{};
  try {
    ::SDL_QueryTexture(texture_map_.at(id), 0, 0, &width, &height);
  } catch (std::out_of_range &) {
    std::cerr << "out of range" << std::endl;
    std::cerr << id << " not have this alias" << std::endl;
  }
  return std::make_pair(width, height);
}
