// dog.hpp

#include "sdl_object.hpp"

class dog : public wrapper::sdl_object {
private:
public:
  dog();
  virtual ~dog();
  void update() override;
};
