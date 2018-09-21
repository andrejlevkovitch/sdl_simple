// boost_test_view.cpp

#define BOOST_TEST_MODULE test_view
#include <boost/test/included/unit_test.hpp>

#include "config.h"
#include "sdl_model.hpp"
#include "sdl_object.hpp"
#include "sdl_view.hpp"
#include <stdexcept>

BOOST_AUTO_TEST_SUITE(test_view)

struct fixture_view : public wrapper::sdl_view {
  fixture_view() : sdl_view{} {};
};

BOOST_FIXTURE_TEST_CASE(test_exceptions, fixture_view) {
  BOOST_CHECK_THROW(this->set_render_color(), std::logic_error);
  BOOST_CHECK_THROW(this->set_renderer(), std::logic_error);
}

BOOST_FIXTURE_TEST_CASE(test_no_exeptions, fixture_view) {
  BOOST_CHECK_NO_THROW(this->set_window());
  BOOST_CHECK_NO_THROW(this->set_renderer());
  BOOST_CHECK_NO_THROW(this->set_render_color());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(test_draw)

struct fixture_obj : public wrapper::sdl_object {
  fixture_obj() : wrapper::sdl_object{} {};
  void update() override{};
};

struct dog : public wrapper::sdl_object {
  int changed_angle_;
  dog() : wrapper::sdl_object{}, changed_angle_{1} {
    this->set_file_name(way_to_images + "dog.png");
    this->set_size(128, 82);
  };
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

struct planet : public wrapper::sdl_object {
  planet() : wrapper::sdl_object{} {
    this->set_file_name(way_to_images + "globus.png");
    this->set_size(160, 160);
  };
  void update() override{};
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
  planet *obj = new planet;
  obj->set_pos(200, 200);

  dog *obj1 = new dog;
  int x_pos = obj->get_pos().first + obj->get_size().first / 2 -
              obj1->get_size().first / 2;
  int y_pos = obj->get_pos().second - obj1->get_size().second;
  obj1->set_pos(x_pos, y_pos);
  ::SDL_Point *center = new SDL_Point;
  center->x = obj1->get_size().first / 2;
  center->y = obj1->get_size().second + obj->get_size().second / 2;
  obj1->set_center(center);

  wrapper::sdl_view view;
  wrapper::sdl_model model;
  view.set_model(&model);

  model.add_item(obj);
  model.add_item(obj1);
  BOOST_CHECK(view.show());
}

BOOST_AUTO_TEST_SUITE_END()
