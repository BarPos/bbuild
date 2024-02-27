#include "config.h"

#include <filesystem>

#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/parse.h"

namespace bbuild {
bool loadConfig(CONFIG* c) {
  if (!std::filesystem::exists(".bbuild.config.yaml")) {
    printf("'.bbuild.config.yaml' does not exist! Using default config.\n");
    return false;
  }

  YAML::Node config = YAML::LoadFile(".bbuild.config.yaml");
  if (config["output"]) c->output = config["output"].as<std::string>();

  return true;
}
}  // namespace bbuild
