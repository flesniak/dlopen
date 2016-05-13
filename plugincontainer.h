#ifndef PLUGINCONTAINER_H
#define PLUGINCONTAINER_H

#include "plugin_base.h"

class PluginContainer {
public:
  PluginContainer(const std::string& path);
  ~PluginContainer();
  Base* instance();
private:
  void* _library;
  plugin_create_t _create;
  plugin_destroy_t _destroy;
  Base* _instance;
};

#endif // PLUGINCONTAINER_H
