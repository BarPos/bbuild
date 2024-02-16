#include "workspace.h"

#include <filesystem>

namespace bbuild {
bool loadWorkspace(const std::string& path, WORKSPACE* r) {
  WORKSPACE w = {};

  if (!std::filesystem::exists(path + "bbuild.workspace.yaml")) {
    fprintf(stderr, "'%sbbuild.workspace.yaml' does not exist!\n",
            path.c_str());
    return false;
  }

  YAML::Node workspace = YAML::LoadFile(path + "bbuild.workspace.yaml");

  if (!workspace["workspace"]) {
    fprintf(stderr, "'workspace' does not exist!\n");
    return false;
  }
  if (!workspace["workspace"]["name"]) {
    fprintf(stderr, "'workspace/name' does not exist!\n");
    return false;
  }
  if (!workspace["workspace"]["default"]) {
    fprintf(stderr, "'workspace/default' does not exist!\n");
    return false;
  }
  if (!workspace["workspace"]["projects"].IsSequence()) {
    fprintf(stderr, "'workspace/projects' does not exist!\n");
    return false;
  }

  w.name = workspace["workspace"]["name"].as<std::string>();
  w.defProject = workspace["workspace"]["default"].as<std::string>();

  for (size_t i = 0; i < workspace["workspace"]["projects"].size(); i++) {
    w.projects.push_back(
        workspace["workspace"]["projects"][i].as<std::string>());
  }

  *r = w;
  return true;
}

void printWorkspace(const WORKSPACE& w) {
  printf("Workspace: %s\n", w.name.c_str());
  printf("Default project: %s\n", w.defProject.c_str());
  printf("Projects:\n");
  for (const auto& p : w.projects) {
    printf(" - %s\n", p.c_str());
  }
}
}  // namespace bbuild
