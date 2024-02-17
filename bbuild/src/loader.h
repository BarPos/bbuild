#pragma once

#include <iostream>
#include <map>
#include <vector>

#include "project.h"
#include "system.h"
#include "workspace.h"

namespace bbuild {
bool load();
bool setupBuildOutput(std::string path);
bool buildProject(const PROJECT& p);
}  // namespace bbuild
