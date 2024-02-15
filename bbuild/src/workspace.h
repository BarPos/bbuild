#pragma once

#include <yaml-cpp/yaml.h>

#include <iostream>
#include <vector>

namespace bbuild {
struct WORKSPACE {
  std::string name;
  std::string defProject;
  std::vector<std::string> projects;
};

WORKSPACE loadWorkspace(const std::string& path);
void printWorkspace(const WORKSPACE& w);
}  // namespace bbuild
