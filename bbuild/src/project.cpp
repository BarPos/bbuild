#include "project.h"

#include <iostream>
#include <string>
#include <vector>

#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/parse.h"

namespace bbuild {
PROJECT loadProject(const std::string& path) {
  PROJECT p = {};
  YAML::Node project = YAML::LoadFile(path + "bbuild.project.yaml");

  if (!project["project"]) {
    printf("'project' does not exist!\n");
    return p;
  }
  if (!project["project"]["name"]) {
    printf("'project/name' does not exist!\n");
    return p;
  }
  if (!project["project"]["type"]) {
    printf("'project/type' does not exist!\n");
    return p;
  }

  if (!project["project"]["output"]) {
    printf("'project/output' does not exist!\n");
    return p;
  }
  if (!project["project"]["source"].IsSequence()) {
    printf("'project/source' does not exist!\n");
    return p;
  }
  if (!project["project"]["include"].IsSequence()) {
    printf("'project/include' does not exist!\n");
    return p;
  }

  if (!project["project"]["depends"].IsSequence()) {
    printf("'project/depends' does not exist!\n");
    return p;
  }
  if (!project["project"]["link"].IsSequence()) {
    printf("'project/link' does not exist!\n");
    return p;
  }

  std::string type = project["project"]["type"].as<std::string>();
  if (type == "exec")
    p.type = PROJECT_TYPE::EXEC;
  else if (type == "lib")
    p.type = PROJECT_TYPE::LIB;
  else {
    printf("'project/type' incorrect!\n");
    return p;
  }

  p.name = project["project"]["name"].as<std::string>();
  p.path = path;

  for (size_t i = 0; i < project["project"]["source"].size(); i++) {
    p.source.push_back(project["project"]["source"][i].as<std::string>());
  }
  for (size_t i = 0; i < project["project"]["include"].size(); i++) {
    p.include.push_back(project["project"]["include"][i].as<std::string>());
  }
  for (size_t i = 0; i < project["project"]["depends"].size(); i++) {
    p.depends.push_back(project["project"]["depends"][i].as<std::string>());
  }
  for (size_t i = 0; i < project["project"]["link"].size(); i++) {
    p.link.push_back(project["project"]["link"][i].as<std::string>());
  }

  return p;
}

void printProject(const PROJECT& p) {
  printf("Name: %s\n", p.name.c_str());
  printf("Type: %s\n", (p.type == PROJECT_TYPE::EXEC ? "exec" : "lib"));
  printf("Output: %s\n", p.path.c_str());
  printf("Sources:\n");
  for (auto& s : p.source) {
    printf(" - %s\n", s.c_str());
  }
  printf("Includes:\n");
  for (auto& s : p.include) {
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
