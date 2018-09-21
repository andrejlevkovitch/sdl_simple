// sdl_model.hpp

#include <list>

struct SDL_Renderer;

namespace wrapper {
class sdl_object;
class sdl_view;

class sdl_model {
  friend sdl_view;

private:
  /**\brief list with all objects in this model. Every item push back*/
  std::list<sdl_object *> item_list_;
  std::list<sdl_object *>::iterator first_not_load_obj_;

public:
  sdl_model();
  virtual ~sdl_model();
  /**\brief add item in the model
   * \warning set ownershiep of the item
   * \return true if item was be added, and false if not*/
  bool add_item(sdl_object *item);
  /**\brief remove item from the model
   * \warning free memory of the item!*/
  void erase_item(sdl_object *item);
  /**\brief draw all items in the model*/
  void draw_all(::SDL_Renderer *renderer);
  void update_all();
  void load_all(::SDL_Renderer *renderer);
};
}; // namespace wrapper
