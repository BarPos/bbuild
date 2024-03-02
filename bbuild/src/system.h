#pragma once

#include <stdio.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace bbuild {
std::string runCommand(const char *command);
std::string getUUID();
}  // namespace bbuild
