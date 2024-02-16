#include "loader.h"

#include "project.h"
#include "workspace.h"

namespace bbuild {
WORKSPACE workspace;
std::vector<PROJECT> projects;

void load() {
  loadWorkspace("./", &workspace);
  for (const auto& ps : workspace.projects) {
    PROJECT p;
    loadProject(ps + "/", &p);
    projects.push_back(p);
  }

  printWorkspace(workspace);
  for (const auto& p : projects) {
    printProject(p);
  }
}
}  // namespace bbuild
