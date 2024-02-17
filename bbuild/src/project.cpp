#include "project.h"

#include <iostream>
#include <string>
#include <vector>

#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/parse.h"

namespace bbuild {
bool loadProject(const std::string& path, PROJECT* r) {
  PROJECT p = {};

  if (!std::filesystem::exists(path + "bbuild.project.yaml")) {
    fprintf(stderr, "'%sbbuild.project.yaml' does not exist!\n", path.c_str());
    return false;
  }

  YAML::Node project = YAML::LoadFile(path + "bbuild.project.yaml");

  if (!project["project"]) {
    printf("'project' does not exist!\n");
    return false;
  }
  if (!project["project"]["name"]) {
    printf("'project/name' does not exist!\n");
    return false;
  }
  if (!project["project"]["type"]) {
    printf("'project/type' does not exist!\n");
    return false;
  }
  if (!project["project"]["source"].IsSequence()) {
    printf("'project/source' does not exist!\n");
    return false;
  }
  if (!project["project"]["include"].IsSequence()) {
    printf("'project/include' does not exist!\n");
    return false;
  }
  if (!project["project"]["defines"].IsSequence()) {
    printf("'project/defines' does not exist!\n");
    return false;
  }
  if (!project["project"]["depends"].IsSequence()) {
    printf("'project/depends' does not exist!\n");
    return false;
  }
  if (!project["project"]["link"].IsSequence()) {
    printf("'project/link' does not exist!\n");
    return false;
  }

  std::string type = project["project"]["type"].as<std::string>();
  if (type == "exec")
    p.type = PROJECT_TYPE::EXEC;
  else if (type == "lib")
    p.type = PROJECT_TYPE::LIB;
  else {
    printf("'project/type' incorrect!\n");
    return false;
  }

  p.name = project["project"]["name"].as<std::string>();
  p.path = path;

  for (size_t i = 0; i < project["project"]["source"].size(); i++) {
    p.source.push_back(project["project"]["source"][i].as<std::string>());
  }
  for (size_t i = 0; i < project["project"]["include"].size(); i++) {
    p.include.push_back(project["project"]["include"][i].as<std::string>());
  }
  for (size_t i = 0; i < project["project"]["defines"].size(); i++) {
    p.defines.push_back(project["project"]["defines"][i].as<std::string>());
  }
  for (size_t i = 0; i < project["project"]["depends"].size(); i++) {
    p.depends.push_back(project["project"]["depends"][i].as<std::string>());
  }
  for (size_t i = 0; i < project["project"]["link"].size(); i++) {
    p.link.push_back(project["project"]["link"][i].as<std::string>());
  }

  *r = p;
  return true;
}

void printProject(const PROJECT& p) {
  printf("Project: %s\n", p.name.c_str());
  printf("Type: %s\n", (p.type == PROJECT_TYPE::EXEC ? "exec" : "lib"));
  printf("Sources:\n");
  for (auto& s : p.source) {
    printf(" - %s\n", s.c_str());
  }
  printf("Includes:\n");
  for (auto& s : p.include) {
    printf(" - %s\n", s.c_str());
  }
  printf("Defines:\n");
  for (auto& s : p.defines) {
    printf(" - %s\n", s.c_str());
  }
  printf("Depends:\n");
  for (auto& s : p.depends) {
    printf(" - %s\n", s.c_str());
  }
  printf("Link:\n");
  for (auto& s : p.link) {
    printf(" - %s\n", s.c_str());
  }
}
}  // namespace bbuild
