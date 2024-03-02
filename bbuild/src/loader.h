#pragma once

#include <iostream>
#include <map>
#include <vector>

#include "config.h"
#include "project.h"
#include "system.h"
#include "workspace.h"

namespace bbuild {
bool load(const CONFIG* c);
bool setupBuildOutput(std::string path, const CONFIG* c);
bool buildProject(const PROJECT& p, const CONFIG* c);
}  // namespace bbuild
