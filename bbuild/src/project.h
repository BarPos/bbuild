#pragma once

#include <yaml-cpp/yaml.h>

#include <filesystem>
#include <iostream>
#include <vector>

namespace bbuild {
enum PROJECT_TYPE { EXEC = 1, LIB = 2 };

struct PROJECT {
  std::string path;
  std::string name;
  PROJECT_TYPE type;
  std::vector<std::string> source;
  std::vector<std::string> include;
  std::vector<std::string> depends;
  std::vector<std::string> link;
};

bool loadProject(const std::string& path, PROJECT* r);
void printProject(const PROJECT& p);
}  // namespace bbuild
