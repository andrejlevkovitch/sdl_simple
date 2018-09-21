// boost_test_obj.cpp

#define BOOST_TEST_MODULE test_obj
#include <boost/test/included/unit_test.hpp>

#include "sdl_object.hpp"
#include <string>

BOOST_AUTO_TEST_SUITE(obj_test)
struct fixture_obj : public wrapper::sdl_object {
public:
  fixture_obj() : sdl_object{} {};
  void update() override{};
};

BOOST_FIXTURE_TEST_CASE(test_file_name, fixture_obj) {
  std::string file_name{"any_string"};
  this->set_file_name(file_name);
  BOOST_CHECK(file_name == this->get_file_name());
}

BOOST_FIXTURE_TEST_CASE(test_size, fixture_obj) {
  int width{10};
  int heidht{20};
  this->set_size(width, heidht);
  BOOST_CHECK(std::make_pair(width, heidht) == this->get_size());
}

BOOST_FIXTURE_TEST_CASE(test_pos, fixture_obj) {
  int x_pos{56};
  int y_pos{24};
  this->set_pos(x_pos, y_pos);
  BOOST_CHECK(std::make_pair(x_pos, y_pos) == this->get_pos());
}

BOOST_FIXTURE_TEST_CASE(test_frame, fixture_obj) {
  int row{5};
  int column{7};
  this->set_frame(row, column);
  BOOST_CHECK(std::make_pair(row, column) == this->get_frame());
}

BOOST_FIXTURE_TEST_CASE(test_angle, fixture_obj) {
  double angle{15.15};
  this->set_angle(angle);
  BOOST_CHECK_CLOSE_FRACTION(angle, this->get_angle(), 0.01);
}

BOOST_AUTO_TEST_SUITE_END()
