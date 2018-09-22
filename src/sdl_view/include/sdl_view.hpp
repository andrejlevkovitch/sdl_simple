// sdl_view.hpp

#pragma once

#include <cstdint>

struct SDL_Window;
struct SDL_Renderer;

namespace wrapper {
class sdl_model;

class sdl_view {
public:
  explicit sdl_view(uint32_t flags);
  virtual ~sdl_view();
  /**\brief set custom window
   * \param title title of window
   * \param x_pos position of left-up corner of the window, on x-axis
   * \param y_pos position of left-up corner of the window, on y-axis
   * \param flags sdl-window flags*/
  bool set_window(const char *title = "Widget",
                  int x_pos = 0,
                  int y_pos = 0, int width = 620,
                  int height = 480, uint32_t flags = 0);
  /**\brief set renderer and default render_color
   * \warning if you want set renderer manually, you have to set window first
   * \exception throw logic_error if you set renderer before you set window*/
  bool set_renderer(int index = -1, uint32_t flags = 0);
  /**\brief set render draw color. Default blue.
   * \warning if you want set draw color manually, you have to set render
   * first
   * \exception throw logic_error if you set render_color before you set
   * renderer*/
  bool set_render_color(uint8_t r = 0, uint8_t g = 0, uint8_t b = 255,
                        uint8_t a = 255);
  /**\brief set model to view
   * \warning not set ownershiep of the model!
   * \return true if model set correctly, and false if not*/
  bool set_model(wrapper::sdl_model *model);
  /**\brief start general loop
   * \return if case any problems with initialization of window of renderer
   * return false*/
  bool show();
  /**\return current renderer*/
  ::SDL_Renderer *get_renderer() const;
  /**\return current window*/
  ::SDL_Window *get_window() const;
  void event_handler();

private:
  ::SDL_Window *window_;
  ::SDL_Renderer *renderer_;
  wrapper::sdl_model *model_;
  bool break_loop_;
};
}; // namespace wrapper
