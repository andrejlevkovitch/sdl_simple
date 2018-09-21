// boost_test_draw.cpp

#define BOOST_TEST_MODULE test_draw
#include <boost/test/included/unit_test.hpp>

#include "config.h"
#include "sdl_model.hpp"
#include "sdl_object.hpp"
#include "sdl_view.hpp"

BOOST_AUTO_TEST_SUITE(test_draw)

struct fixture_obj : public wrapper::sdl_object {
  int changed_angle_;
  fixture_obj() : wrapper::sdl_object{}, changed_angle_{1} {};
  void update() override {
    if (get_angle() > 360 || get_angle() < 0) {
      changed_angle_ = -changed_angle_;
      if (get_flip() == SDL_FLIP_HORIZONTAL) {
        set_flip(SDL_FLIP_NONE);
      } else {
        set_flip(SDL_FLIP_HORIZONTAL);
      }
    }
    set_angle(get_angle() + changed_angle_);
    set_frame(0, static_cast<int>(::SDL_GetTicks() / 100) % 6);
  };
};

BOOST_FIXTURE_TEST_CASE(test_draw_void_obj, fixture_obj) {
  this->set_file_name("not_valid_name");
  wrapper::sdl_view view;
  view.set_window();
  view.set_renderer();
  view.set_render_color();
  BOOST_CHECK_NO_THROW(this->load(view.get_renderer()));
  BOOST_CHECK_NO_THROW(this->draw(view.get_renderer()));
}

BOOST_FIXTURE_TEST_CASE(test_load_valid_obj, fixture_obj) {
  this->set_file_name(way_to_images + "dog.png");
  wrapper::sdl_view view;
  view.set_window();
  view.set_renderer();
  view.set_render_color();
  BOOST_CHECK(this->load(view.get_renderer()));
}

BOOST_AUTO_TEST_CASE(complete_test) {
  fixture_obj *obj = new fixture_obj;
  int width{128};
  int height{82};
  obj->set_file_name(way_to_images + "dog.png");
  obj->set_size(width, height);
  obj->set_pos(50, 50);
  ::SDL_Point *center = new SDL_Point;
  center->x = width / 2;
  center->y = height;
  obj->set_center(center);

  wrapper::sdl_view view;
  wrapper::sdl_model model;
  view.set_model(&model);

  model.add_item(obj);
  BOOST_CHECK(view.show());
}

BOOST_AUTO_TEST_SUITE_END()
