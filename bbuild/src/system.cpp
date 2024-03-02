#include "system.h"

#include <Windows.h>
#include <rpcdce.h>
#include <stdio.h>

#include <filesystem>

namespace bbuild {
std::string runCommand(const char* command) {
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
std::string getUUID() {
#pragma comment(lib, "rpcrt4.lib")
  UUID uuid;
  UuidCreate(&uuid);
  char* tmp;
  UuidToStringA(&uuid, (RPC_CSTR*)&tmp);
  std::string r = (std::string)tmp;
  RpcStringFreeA((RPC_CSTR*)&tmp);
  return r;
}
}  // namespace bbuild
