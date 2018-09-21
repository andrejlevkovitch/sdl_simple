// sdl_view.cpp

#include "sdl_view.hpp"
#include "sdl_model.hpp"
#include <SDL2/SDL.h>
#include <stdexcept>

wrapper::sdl_view::sdl_view(Uint32 flags)
    : window_{nullptr}, renderer_{nullptr}, model_{nullptr}, break_loop_{
                                                                 false} {
  ::SDL_Init(flags);
}

wrapper::sdl_view::~sdl_view() {
  ::SDL_DestroyWindow(window_);
  ::SDL_DestroyRenderer(renderer_);
}

bool wrapper::sdl_view::set_window(const char *title, int x_pos, int y_pos,
                                   int width, int height, Uint32 flags) {
  if (window_) {
    ::SDL_DestroyWindow(window_);
    ::SDL_DestroyRenderer(renderer_);
    renderer_ = nullptr;
  }
  window_ = ::SDL_CreateWindow(title, x_pos, y_pos, width, height, flags);
  return (window_) ? true : false;
}

bool wrapper::sdl_view::set_renderer(int index, Uint32 flags) {
  if (!window_) {
    throw(std::logic_error{"you can`t set render before you set window"});
  }
  if (renderer_) {
    ::SDL_DestroyRenderer(renderer_);
  }
  renderer_ = ::SDL_CreateRenderer(window_, index, flags);
  set_render_color();
  return (renderer_) ? true : false;
}

bool wrapper::sdl_view::set_render_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
  if (!renderer_) {
    throw(
        std::logic_error{"you can't set render color before you set renderer"});
  }
  return ::SDL_SetRenderDrawColor(renderer_, r, g, b, a) == 0;
}

bool wrapper::sdl_view::set_model(wrapper::sdl_model *model) {
  model_ = model;
  return (model_) ? true : false;
}

bool wrapper::sdl_view::show() {
  if (!renderer_) {
    if (!window_) {
      if (!set_window()) {
        return false;
      }
    }
    if (!set_renderer()) {
      return false;
    }
    if (!set_render_color()) {
      return false;
    }
  }

  while (!break_loop_) {
    ::SDL_RenderClear(renderer_);
    this->event_handler();
    model_->draw_all(renderer_);
    model_->update_all();
    ::SDL_RenderPresent(renderer_);
    ::SDL_Delay(50);
  }

  return true;
}

::SDL_Renderer *wrapper::sdl_view::get_renderer() const { return renderer_; }

::SDL_Window *wrapper::sdl_view::get_window() const { return window_; }

void wrapper::sdl_view::event_handler() {
  while (true) {
    ::SDL_Event event;
    if (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        break_loop_ = true;
        break;
      default:
        break;
      }
    } else {
      return;
    }
  }
}
