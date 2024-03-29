#pragma once

#include <yaml-cpp/yaml.h>

#include <filesystem>
#include <iostream>
#include <vector>

#include "config.h"

namespace bbuild {
struct WORKSPACE {
  std::string name;
  std::string defProject;
  std::vector<std::string> projects;
};

bool loadWorkspace(const std::string& path, WORKSPACE* r, const CONFIG* c);
void printWorkspace(const WORKSPACE& w);
}  // namespace bbuild
