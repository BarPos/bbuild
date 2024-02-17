#include "system.h"

#include <stdio.h>

namespace bbuild {
std::string runCommand(const char *command) {
  char tmpname[L_tmpnam];
  tmpnam_s(tmpname, L_tmpnam);
  std::string scommand = command;
  std::string cmd = scommand + " >> " + tmpname;
  system(cmd.c_str());
  std::ifstream file(tmpname, std::ios::in | std::ios::binary);
  std::string result;
  if (file) {
    while (!file.eof()) result.push_back(file.get());
    file.close();
  }
  remove(tmpname);
  return result;
}
}  // namespace bbuild
