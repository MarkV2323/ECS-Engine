#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "entity_manager.hpp"
#include "utils.hpp"

namespace fs = std::filesystem;

namespace ecs {

// Contains working directory of binary
fs::path cwd = fs::current_path();
constexpr std::string CONFIG_FILE = "config.txt";
fs::path config = cwd / CONFIG_FILE;

// Checks config file, creates one if missing
void checkConfig() {
  if (fs::exists(config)) return;
  fmt::print(fg(INFO_COLOR), "{:>11} ", "CREATING CONFIG");
  fmt::print(fg(VAL_COLOR), "{}\n", config.string());
  std::ofstream out(config);
}

void unmarshalEntity(EntityMan& eman, std::string line) {
  Entity e{};
  if (e.unmarshal(line)) eman.AddEntity(e);
}

void processUnmarshalEntityMan(EntityMan& eman) {
  checkConfig();

  std::ifstream conf(config);
  std::string line{""};
  while (std::getline(conf, line)) unmarshalEntity(eman, line);
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
