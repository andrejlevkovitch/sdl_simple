// boost_test_view.cpp

#define BOOST_TEST_MODULE test_view
#include <boost/test/included/unit_test.hpp>

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
