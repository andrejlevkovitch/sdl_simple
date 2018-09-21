// sdl_model.cpp

#include "sdl_model.hpp"
#include "sdl_object.hpp"
#include <SDL2/SDL.h>
#include <algorithm>
#include <iostream>

wrapper::sdl_model::sdl_model() : first_not_load_obj_{item_list_.end()} {}

wrapper::sdl_model::~sdl_model() {
  for (auto &item : item_list_) {
    delete item;
  }
}

bool wrapper::sdl_model::add_item(sdl_object *item) {
  if (item == nullptr) {
    return false;
  }
  item_list_.push_back(item);
  if (first_not_load_obj_ == item_list_.end()) {
    first_not_load_obj_ = --item_list_.end();
  }
  return true;
}

void wrapper::sdl_model::erase_item(sdl_object *item) {
  auto er_el = std::find(item_list_.begin(), item_list_.end(), item);
  if (er_el == item_list_.end()) {
    return;
  }
  while (first_not_load_obj_ != item_list_.end() &&
         *er_el == *first_not_load_obj_) {
    ++first_not_load_obj_;
  }
  delete *er_el;
  item_list_.erase(std::remove(item_list_.begin(), item_list_.end(), *er_el),
                   item_list_.end());
}

size_t wrapper::sdl_model::item_count() const { return item_list_.size(); }

bool wrapper::sdl_model::empty() const { return item_list_.empty(); }

void wrapper::sdl_model::draw_all(::SDL_Renderer *renderer) {
  if (first_not_load_obj_ != item_list_.end()) {
    load_all(renderer);
  }
  for (auto &item : item_list_) {
    item->draw(renderer);
  }
}

void wrapper::sdl_model::update_all() {
  for (auto &item : item_list_) {
    item->update();
  }
}

void wrapper::sdl_model::load_all(SDL_Renderer *renderer) {
  for (auto item = first_not_load_obj_; item != item_list_.end(); ++item) {
    if (!(*item)->load(renderer)) {
      std::cerr << "file " << (*item)->file_name_ << " not found\n";
    }
  }
  first_not_load_obj_ = item_list_.end();
}
