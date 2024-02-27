#pragma once

#include <yaml-cpp/yaml.h>

#include <filesystem>
#include <iostream>
#include <vector>

namespace bbuild {
struct CONFIG {
  std::string output = "build";
};

bool loadConfig(CONFIG* c);
}  // namespace bbuild
