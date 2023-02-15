#include "cactus/cactus.h"

namespace cactus {

std::string GetVersion() {
  return std::to_string(CACTUS_VERSION_MAJOR) + "." +
         std::to_string(CACTUS_VERSION_MINOR) + "." +
         std::to_string(CACTUS_VERSION_PATCH);
}

std::string GetEnv(const std::string& var_name,
                   const std::string& default_value) {
  const char* var = std::getenv(var_name.c_str());
  if (var == nullptr) {
    return default_value;
  }
  return std::string(var);
}

}  // namespace cactus
