#pragma once

#include <yaml-cpp/yaml.h>

#include <iostream>
#include <vector>

namespace bbuild {
enum PROJECT_TYPE { EXEC = 1, LIB = 2 };

struct PROJECT {
  std::string path;
  std::string name;
  PROJECT_TYPE type;
  std::vector<std::string> sources;
  std::vector<std::string> include;
  std::vector<std::string> depends;
  std::vector<std::string> link;
};
}  // namespace bbuild