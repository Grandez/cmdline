#pragma once

#include <unordered_map>

namespace NS2 {
  std::unordered_map<std::string, std::string> processIniConfigFile(char *file);
}