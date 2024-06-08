#pragma once

#include <map>
#include <string>

#include <cc/controllers/controller.hh>

class ControllerMap {
  public:
    void add_controller(std::string& name, std::string& type, std::string& topic) {

    }

    void remove_controller(std::string& name) {

    }

  private:
    std::map<std::string, cc::Controller> controller_map;
}
