// sdl_object.hpp

#include <SDL2/SDL.h>
#include <string>

namespace wrapper {
class sdl_model;

/**\brief abstract base class for some graphical objects*/
class sdl_object {
  friend sdl_model;

private:
  std::string file_name_;
  Uint32 id_;
  int width_;
  int height_;
  /**\brief only for sprites. Numeration from 0. Default 0*/
  int row_;
  /**\brief only for sprites. Numeration from 0. Default 0*/
  int column_;
  int x_pos_;
  int y_pos_;
  double angle_;
  /**\brief this point set center of rotation. Default this is center of the
   * texture (nullptr)
   * \warning only dynamic memory! destructor destroy it automaticly*/
  ::SDL_Point *center_;
  /**\brief default SDL_FLIP_NONE*/
  ::SDL_RendererFlip flip_;

public:
  sdl_object();
  virtual ~sdl_object();
  /**\brief set file_name*/
  void set_file_name(const std::string &file_name);
  /**\brief set size of the texture. By default width and height will be set
   * equal size of image
   * \warning if width of height will be set 0, then size will be set
   * automaticly equal size of image*/
  void set_size(int width, int height);
  /**\brief set position of the texture in window*/
  void set_pos(int x_pos, int y_pos);
  /**\brief set current row and column
   * \warning only for sprites!*/
  void set_frame(int row, int column);
  /**\brief set angle of rotation*/
  void set_angle(double angle);
  /**\brief set center of rotation
   * \warning only dynamic memory!
   * \warning set ownershiep of the object*/
  void set_center(::SDL_Point *center);
  void set_flip(::SDL_RendererFlip flip);

private:
  /**\brief load image*/
  bool load(::SDL_Renderer *renderer);
  /**\brief draw the object in window*/
  virtual void draw(::SDL_Renderer *renderer) const;
  /**\brief set here all functioanality, which change object during game. You
   * have to define this method*/
public:
  virtual void update() = 0;
};
}; // namespace wrapper
