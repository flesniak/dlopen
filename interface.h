#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>

class Base {
public:
  Base(const std::string name) : _name(name) {};
  virtual ~Base() {};
  virtual std::string& getName() { return _name; };
  virtual int getX() = 0;
private:
  std::string _name;
};

typedef Base* (*plugin_create_t)();
typedef void (*plugin_destroy_t)(Base*);

#endif // INTERFACE_H
