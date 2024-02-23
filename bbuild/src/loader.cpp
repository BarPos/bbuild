#include "loader.h"

#include <filesystem>

#include "project.h"
#include "system.h"
#include "workspace.h"

namespace bbuild {
WORKSPACE workspace;
std::map<std::string, PROJECT> projects;

bool load() {
  if (!loadWorkspace("./", &workspace)) {
    fprintf(stderr, "Failed to load './bbuild.workspace.yaml'!\n");
    return false;
  }
  for (const auto& ps : workspace.projects) {
    PROJECT p;
    if (!loadProject(ps + "/", &p)) {
      fprintf(stderr, "Failed to load project '%s/bbuild.project.yaml'!\n",
              ps.c_str());
      return false;
    }
    projects.insert({p.name, p});
  }

  // printWorkspace(workspace);
  // for (const auto& p : projects) {
  //   printProject(p.second);
  // }

  if (!projects.count(workspace.defProject)) {
    fprintf(stderr, "'%s' is not an exisint project!\n",
            workspace.defProject.c_str());
    return false;
  }

  PROJECT dp = projects.at(workspace.defProject);
  printf("Building '%s'\n", dp.name.c_str());
  if (!buildProject(dp)) {
    fprintf(stderr, "Failed to load '%s'!\n", dp.name.c_str());
    return false;
  }

  return true;
}

bool buildProject(const PROJECT& p) {
  setupBuildOutput(p.name);

  printf("Checking for dependencies for '%s'\n", p.name.c_str());
  for (const auto& pp : p.depends) {
    if (!projects.count(pp)) {
      fprintf(stderr, "'%s' does not exist!\n", pp.c_str());
      return false;
    }
    PROJECT dp = projects.at(pp);
    printf("Depends on %s\n", dp.name.c_str());
    buildProject(dp);
  }

  std::string objectCommand =
      "cd build/" + p.name + " && clang -xc++ -c -Wall -std=c++20 ";
  for (const auto& i : p.include) {
    objectCommand += "-I../../" + p.path + i + " ";
  }
  for (const auto& d : p.defines) {
    objectCommand += "-D" + d + " ";
  }
  for (const auto& s : p.source) {
    objectCommand += "../../" + p.path + s + " ";
  }

  printf("Object command: %s\n", objectCommand.c_str());
  std::string oco = runCommand(objectCommand.c_str());
  printf("Object command output: %s\n", oco.c_str());

  for (const auto& s : p.sourceDirs) {
    if (std::filesystem::is_directory(p.path + s)) {
      for (const auto& f :
           std::filesystem::recursive_directory_iterator(p.path + s)) {
        if (f.path().filename().extension().string() == ".cpp") {
          std::string oc =
              "cd build/" + p.name + " && clang -xc++ -c -Wall -std=c++20 ";
          for (const auto& i : p.include) {
            oc += "-I../../" + p.path + i + " ";
          }
          for (const auto& d : p.defines) {
            oc += "-D" + d + " ";
          }
          oc += "../../" + p.path + s + f.path().filename().string() + " ";
          oc += "-o " + f.path().filename().stem().string() + ".o";

          printf("Object: %s\n", oc.c_str());
          std::string o = runCommand(oc.c_str());
          printf("%s\n", o.c_str());
        }
      }
    }
  }

  std::string linkCommand = "cd build/" + p.name + " && ";

  switch (p.type) {
    case EXEC:
      linkCommand += "clang ";
      for (const auto& l : p.link) {
        linkCommand += "-l../../" + p.path + l + " ";
      }
      linkCommand += "*.o -o " + p.name + ".exe ";
      break;
    case LIB:
      linkCommand += "llvm-ar rc " + p.name + ".lib *.o ";
      break;
  }

  printf("Link command: %s\n", linkCommand.c_str());
  std::string lco = runCommand(linkCommand.c_str());
  printf("Link command output: %s\n", lco.c_str());

  return true;
}

bool setupBuildOutput(std::string path) {
  printf("Generating output folder for 'build/%s'\n", path.c_str());
  if (!std::filesystem::exists("build/")) {
    std::filesystem::create_directory("build/");
  }

  if (std::filesystem::exists("build/" + path))
    if (!std::filesystem::is_empty("build/" + path)) {
      std::filesystem::remove_all("build/" + path);
    }

  if (!std::filesystem::exists("build/" + path)) {
    std::filesystem::create_directory("build/" + path);
  }

  return true;
}
}  // namespace bbuild
