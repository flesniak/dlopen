#include "plugin_base.h"

class B : public Base {
public:
  B() : Base("ImplementationB") {};
  int getX() { return 2; };
};

extern "C" Base* plugin_create() {
  return new B;
}

extern "C" void plugin_destroy(Base* b) {
  delete b;
}
