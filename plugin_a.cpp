#include "plugin_base.h"

class A : public Base {
public:
  A() : Base("ImplementationA") {};
  int getX() { return 1; };
};

extern "C" Base* plugin_create() {
  return new A;
}

extern "C" void plugin_destroy(Base* a) {
  delete a;
}
