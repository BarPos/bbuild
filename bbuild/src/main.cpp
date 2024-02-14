#include <stdio.h>
#include <string.h>
#include <yaml-cpp/yaml.h>

#include "help.h"
#include "project.h"

int main(int argc, char **argv) {
  if (argc == 1) {
    printf("Use '%s help' to see ussage.\n", argv[0]);
    return 1;
  }
  if (strcmp(argv[1], "help") == 0) {
    printf("%s", HELP_TEXT);
    return 0;
  } else if (strcmp(argv[1], "test") == 0 && argc == 3) {
    printf("Loading project: %sbbuild.project.yaml\n", argv[2]);
    bbuild::PROJECT p = bbuild::loadProject(argv[2]);
    bbuild::printProject(p);
    return 0;
  } else {
    printf("Use '%s help' to see ussage.\n", argv[0]);
    return 1;
  }
  return 0;
}
