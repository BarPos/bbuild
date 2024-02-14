#pragma once

#include <yaml-cpp/yaml.h>

#include <iostream>
#include <vector>

namespace bbuild {
struct WORKSPACE {
  std::string name;
  std::vector<std::string> projects;
};
}  // namespace bbuild
