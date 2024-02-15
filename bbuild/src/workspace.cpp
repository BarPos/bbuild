#include "workspace.h"

namespace bbuild {
WORKSPACE loadWorkspace(const std::string& path) {
  WORKSPACE w = {};
  YAML::Node workspace = YAML::LoadFile(path + "bbuild.workspace.yaml");

  if (!workspace["workspace"]) {
    printf("'workspace' does not exist!\n");
    return w;
  }
  if (!workspace["workspace"]["name"]) {
    printf("'workspace/name' does not exist!\n");
    return w;
  }
  if (!workspace["workspace"]["default"]) {
    printf("'workspace/default' does not exist!\n");
    return w;
  }
  if (!workspace["workspace"]["projects"].IsSequence()) {
    printf("'workspace/projects' does not exist!\n");
    return w;
  }

  w.name = workspace["workspace"]["name"].as<std::string>();
  w.defProject = workspace["workspace"]["default"].as<std::string>();

  for (size_t i = 0; i < workspace["workspace"]["projects"].size(); i++) {
    w.projects.push_back(
        workspace["workspace"]["projects"][i].as<std::string>());
  }

  return w;
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
