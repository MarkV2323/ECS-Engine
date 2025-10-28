#pragma once

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>

#include "utils.hpp"
#include "entity_manager.hpp"

namespace fs = std::filesystem;

namespace ecs {

// Contains working directory of binary
fs::path cwd = fs::current_path();
constexpr std::string CONFIG_FILE = "config.txt";
fs::path config = cwd / CONFIG_FILE;

// Checks config file, creates one if missing
void checkConfig() {
  if (fs::exists(config))
    return;
  fmt::print(fg(INFO_COLOR), "{:>11} ", "CREATING CONFIG");
  fmt::print(fg(VAL_COLOR), "{}\n", config.string());
  std::ofstream out(config);
}

void marshalEntity(Entity& e, std::ofstream& conf) {
  conf << e.marshal() << std::endl;
}

// Will record all saved entities into a file
void ProcessMarshalEntityMan(EntityMan& eman) {
  checkConfig();

  std::ofstream conf(config);

  for (auto& e : eman.entities) {
    marshalEntity(e, conf);
  }
}

}  // namespace ecs
