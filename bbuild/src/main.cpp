#include <stdio.h>
#include <string.h>
#include <yaml-cpp/yaml.h>

#include "help.h"
#include "project.h"
#include "workspace.h"

int main(int argc, char **argv) {
  if (argc == 1) {
    printf("Use '%s help' to see ussage.\n", argv[0]);
    return 1;
  }
  if (strcmp(argv[1], "help") == 0) {  // HELP COMMAND
    printf("%s", HELP_TEXT);
    return 0;
  } else if (strcmp(argv[1], "testp") == 0) {  // TEST PROJECT LOADING COMMAND
    std::string arg = "";
    if (argc == 3) {
      arg = argv[2];
    } else {
      arg = "./";
    }
    printf("Loading project: %sbbuild.project.yaml\n", argv[2]);
    bbuild::PROJECT p = bbuild::loadProject(argv[2]);
    bbuild::printProject(p);
    return 0;
  } else if (strcmp(argv[1], "testw") == 0) {  // TEST WORKSPACE LOADING COMMAND
    std::string arg = "";
    if (argc == 3) {
      arg = argv[2];
    } else {
      arg = "./";
    }
    printf("Loading workspace: %sbbuild.workspace.yaml\n", arg.c_str());
    bbuild::WORKSPACE w = bbuild::loadWorkspace(arg.c_str());
    bbuild::printWorkspace(w);
    return 0;
  } else if (strcmp(argv[1], "build") == 0) {  // BUILD COMMAND
  } else {                                     // INCORRECT COMMAND
    printf("Use '%s help' to see ussage.\n", argv[0]);
    return 1;
  }
  return 0;
}
