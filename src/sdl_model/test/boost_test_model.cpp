// boost_test_model.cpp

#define BOOST_TEST_MODULE test_model
#include <boost/test/included/unit_test.hpp>

#include "sdl_model.hpp"
#include "sdl_object.hpp"

BOOST_AUTO_TEST_SUITE(test_model)

struct fixture_model : public wrapper::sdl_model {
  fixture_model() : wrapper::sdl_model{} {};
};

const std::string update_str{"updated"};
struct object : public wrapper::sdl_object {
  object() : wrapper::sdl_object{} {};
  void update() override{this->set_file_name(update_str);};
};

BOOST_FIXTURE_TEST_CASE(test_add_erase_one_item, fixture_model) {
  object *obj = new object;
  BOOST_CHECK(this->add_item(obj));
  BOOST_CHECK(this->item_count() == 1);
  BOOST_CHECK(this->add_item(obj));
  BOOST_CHECK(this->item_count() == 2);
  this->erase_item(obj);
  BOOST_CHECK(this->empty());
}

BOOST_FIXTURE_TEST_CASE(test_add_erase_items, fixture_model) {
  object *obj = new object;
  object *obj1 = new object;
  BOOST_CHECK(this->add_item(obj));
  BOOST_CHECK(this->item_count() == 1);
  BOOST_CHECK(this->add_item(obj1));
  BOOST_CHECK(this->item_count() == 2);
  this->erase_item(obj);
  BOOST_CHECK(this->item_count() == 1);
}

BOOST_FIXTURE_TEST_CASE(test_erase_not_valid_item, fixture_model) {
  object *obj = new object;
  this->erase_item(obj);
  delete obj;
}

BOOST_FIXTURE_TEST_CASE(test_update, fixture_model) {
  object *obj = new object;
  object *obj1 = new object;
  this->add_item(obj);
  this->add_item(obj1);
  this->update_all();
  BOOST_CHECK(obj->get_file_name() == update_str);
  BOOST_CHECK(obj1->get_file_name() == update_str);
}

BOOST_AUTO_TEST_SUITE_END()
