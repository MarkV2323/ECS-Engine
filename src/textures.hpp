#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <map>
#include <string>

#include "utils.hpp"

namespace ecs {
class TextureMan {
 private:
  // texture location
  constexpr static std::string TEXTURE_PATH = "assests";

  // Contains file path + name of our texture path
  const fs::path textPath = CWD / TEXTURE_PATH;

  // global texture map, names -> texture
  std::map<std::string, sf::Texture> textureMap{};

 public:
  // Retreive a texture from the map
  const sf::Texture& GetTexture(std::string t) { return textureMap[t]; }

  // Load textures into the texture map from a file directory
  void LoadTextures() {
    using namespace ecs;

    fmt::print(fg(INFO_COLOR), "{:>11}", "TEXTURE_FILE_PATH: ");
    fmt::print(fg(VAL_COLOR), "{}\n", textPath.string());

    // for each asset in the directory we want to
    // 1) map the file name as a string to the sf::texture
    fs::path fpath{};
    std::string fname{};
    for (const fs::directory_entry& entry : fs::directory_iterator(textPath)) {
      fpath = entry.path();
      fname = fpath.stem().filename();

      fmt::print(fg(INFO_COLOR), "{:>11}", "Asset Info: ");
      fmt::print(fg(VAL_COLOR), "{}\n", fpath.string() + " " + fname);

      // create the texture and the mapping
      // will not overrite existing mappings
      textureMap.try_emplace(fname, sf::Texture(fpath));
    }
  }

  // Quick printing of loaded textures in the map
  void PrintLoadedTextures() {
    using namespace ecs;

    fmt::print(fg(INFO_COLOR), "{:>11}\n", "Texture Map Items: ");
    std::string val_result{};
    for (const auto& [key, val] : textureMap) {
      // check for the loaded texture first.
      if (val.getSize().x == 0 || val.getSize().y == 0) {
        val_result = "Texture NOT loaded";
      } else {
        val_result = "Texture loaded, X: " + std::to_string(val.getSize().x) +
                     " Y: " + std::to_string(val.getSize().y);
      }
      fmt::print(fg(VAL_COLOR), "{}\n",
                 "Key: " + key + " | Val: " + val_result);
    }
  }
};
}  // namespace ecs
