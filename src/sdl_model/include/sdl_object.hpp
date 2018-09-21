// sdl_object.hpp

#pragma once

#include <SDL2/SDL.h>
#include <string>

namespace wrapper {
class sdl_model;

/**\brief abstract base class for some graphical objects*/
class sdl_object {
  friend sdl_model;

private:
  std::string file_name_;
  ::SDL_Texture *texture_;
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
  /**\return complete file name of image, which was be load*/
  const std::string &get_file_name() const;
  /**\brief set size of the texture. By default width and height will be set
   * equal size of image
   * \warning if width or height will be set 0 before load, then size will be
   * set automaticly equal size of image*/
  void set_size(int width, int height);
  /**\return pair<width, height> of the object*/
  std::pair<int, int> get_size() const;
  /**\brief set position of the texture in window (left-up corner)*/
  void set_pos(int x_pos, int y_pos);
  /**\return pair<x_pos, y_pos> left-up corner of the object*/
  std::pair<int, int> get_pos() const;
  /**\brief set current row and column
   * \warning only for sprites!*/
  void set_frame(int row, int column);
  /**\return pair<row, column> of current frame. If it isn't sprite always
   * return 0,0*/
  std::pair<int, int> get_frame() const;
  /**\brief set angle of rotation*/
  void set_angle(double angle);
  /**\return current rotate angle of the object in degrees*/
  double get_angle() const;
  /**\brief set center of rotation
   * \warning only dynamic memory!
   * \warning set ownershiep of the object*/
  void set_center(::SDL_Point *center);
  /**\return pointer to structure, which point to center of object. If center
   * equal width/2, height/2 return nullptr*/
  const ::SDL_Point *get_center() const;
  void set_flip(::SDL_RendererFlip flip);
  ::SDL_RendererFlip get_flip() const;

protected:
  /**\brief load image
   * \warning if width or height eqal 0, than this values will be set equal
   * image size*/
  bool load(::SDL_Renderer *renderer);
  /**\brief draw the object in window*/
  virtual void draw(::SDL_Renderer *renderer) const;

public:
  /**\brief set here all functioanality, which change object during game. You
   * have to define this method*/
  virtual void update() = 0;
};
}; // namespace wrapper
