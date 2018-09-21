// sdl_view.hpp

#include <SDL2/SDL.h>

namespace wrapper {
class sdl_model;

class sdl_view {
private:
  ::SDL_Window *window_;
  ::SDL_Renderer *renderer_;
  wrapper::sdl_model *model_;
  bool break_loop_;

public:
  sdl_view(Uint32 flags = SDL_INIT_EVERYTHING);
  ~sdl_view();
  /**\brief set custom window
   * \param title title of window
   * \param x_pos position of left-up corner of the window, on x-axis
   * \param y_pos position of left-up corner of the window, on y-axis
   * \param flags sdl-window flags*/
  bool set_window(const char *title = "Widget",
                  int x_pos = SDL_WINDOWPOS_CENTERED,
                  int y_pos = SDL_WINDOWPOS_CENTERED, int width = 620,
                  int height = 480, Uint32 flags = 0);
  /**\brief set renderer and default render_color
   * \warning if you want set renderer manually, you have to set window first
   * \exception throw logic_error if you set renderer before you set window*/
  bool set_renderer(int index = -1, Uint32 flags = 0);
  /**\brief set render draw color. Default blue.
   * \warning if you want set draw color manually, you have to set render
   * first
   * \exception throw logic_error if you set render_color before you set
   * renderer*/
  bool set_render_color(Uint8 r = 0, Uint8 g = 0, Uint8 b = 255, Uint8 a = 255);
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

private:
  void event_handler();
};
}; // namespace wrapper
