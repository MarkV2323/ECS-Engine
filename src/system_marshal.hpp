#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "entity_manager.hpp"
#include "utils.hpp"

namespace fs = std::filesystem;

namespace ecs {

// Contains the name of our config file
constexpr std::string CONFIG_FILE = "config.txt";

// Contains file path + name of our config file
const fs::path config = CWD / CONFIG_FILE;

// Checks config file, creates one if missing
inline void CheckConfig() {
  if (fs::exists(config)) return;
  fmt::print(fg(INFO_COLOR), "{:>11} ", "CREATING CONFIG");
  fmt::print(fg(VAL_COLOR), "{}\n", config.string());
  std::ofstream out(config);
}

inline void UnmarshalEntity(EntityMan& eman, std::string line) {
  Entity e{};
  if (e.Unmarshal(line)) eman.AddEntity(e);
}

inline void ProcessUnmarshalEntityMan(EntityMan& eman) {
  CheckConfig();

  std::ifstream conf(config);
  std::string line{""};
  while (std::getline(conf, line)) UnmarshalEntity(eman, line);
}

inline void MarshalEntity(Entity& e, std::ofstream& conf) {
  conf << e.Marshal() << std::endl;
}

// Will record all saved entities into a file
inline void ProcessMarshalEntityMan(EntityMan& eman) {
  CheckConfig();

  std::ofstream conf(config);

  for (auto& e : eman.entities) {
    MarshalEntity(e, conf);
  }
}

}  // namespace ecs
