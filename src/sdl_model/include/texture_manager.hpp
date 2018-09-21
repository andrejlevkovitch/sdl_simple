// texture_manager.hpp

#include <SDL2/SDL.h>
#include <map>
#include <string>

namespace wrapper {
/// brief simple texture manager rof work with images. It is singleton
class texture_manager {
private:
  std::map<Uint32, SDL_Texture *> texture_map_;
  Uint32 last_id_;
  texture_manager();

public:
  /**\brief get instance of the manager*/
  static texture_manager &instance();
  texture_manager(const texture_manager &) = delete;
  texture_manager &operator=(const texture_manager &) = delete;
  ~texture_manager();
  /**\brief load image files in texture manager
   * \param file_name way and name of file
   * \return id_ of load object*/
  Uint32 load(const std::string &file_name, SDL_Renderer *renderer);
  /**\brief this method draw texture, which was created from image
   * \param id alias of texture
   * \param x_pos x_coord of the window
   * \param y_pox y_coord of the window
   * \param width width of the texture
   * \param height height of the texture
   * \param angle rotade angle for texture
   * \return id object or 0 if object wasn't be loaded*/
  void draw(::SDL_Renderer *renderer, Uint32 id, int x_pos,
            int y_pos, int width, int height, double angle_ = 0,
            const ::SDL_Point *const center = nullptr,
            SDL_RendererFlip flip = SDL_FLIP_NONE) const;
  /**\brief this method is analugue of method draw, but work with sprites
   * \param row y_coord of sprite
   * \param column x_coord of sprite
   * \warning numeration row and column begin from 0*/
  void draw_sprite(::SDL_Renderer *renderer, Uint32 id, int x_pos,
                   int y_pos, int width, int height, int row, int column,
                   double angle_ = 0, const ::SDL_Point *const center = nullptr,
                   SDL_RendererFlip flip = SDL_FLIP_NONE) const;
  std::pair<int, int> get_texture_size(Uint32 id) const;
};
} // namespace wrapper
