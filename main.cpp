#include <iostream>
#include <string>
#include <vector>

#include <dirent.h>
#include <unistd.h>

#include "plugincontainer.h"

PluginContainer* load_plugin(const std::string& path) {
  return new PluginContainer(path);
}

void getcwd_string(std::string& cwd) {
  int len = 30;
  char* cwd_c = (char*)malloc(len);
  while(getcwd(cwd_c, len) == 0) {
    len += 10;
    cwd_c = (char*)realloc(cwd_c, len);
  }
  cwd.assign(cwd_c);
  free(cwd_c);
}

int main() {
  std::vector<PluginContainer*> plugins;

  // get cwd
  std::string cwd;
  getcwd_string(cwd);
  std::cout << "Loading plugins from: " << cwd << std::endl;

  // search and load plugins
  DIR* dir;
  struct dirent* ent;
  if ((dir = opendir(cwd.c_str())) != 0) {
    while ((ent = readdir(dir)) != 0) {
      std::string name(ent->d_name);
      if (name.length() < 10 ||
        name.substr(0,6) != "plugin" ||
        name.substr(name.length()-3) != ".so")
        continue;
      std::cout << "Loading " << name << std::endl;
      try {
        plugins.push_back(load_plugin(cwd+"/"+name));
      } catch(const std::string& s) {
        std::cerr << "Failed loading plugin " << name << ": " << s << std::endl;
      }
    }
    closedir(dir);
  } else {
    throw "unable to open working directory";
    return EXIT_FAILURE;
  }

  if (plugins.size() == 0) {
    std::cerr << "No plugins loaded" << std::endl;
    return EXIT_FAILURE;
  }

  for(auto plugin : plugins) {
    Base* p = plugin->instance();
    std::cout << "Using plugin " << p->getName() << std::endl;
    std::cout << "getX() = " << p->getX() << std::endl;
  }

  for(auto plugin : plugins) {
    std::cout << "Unloading plugin " << plugin->instance()->getName() << std::endl;
    delete plugin;
  }

  return EXIT_SUCCESS;
}
