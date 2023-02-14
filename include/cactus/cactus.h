#ifndef CACTUS_H_
#define CACTUS_H_
#include <string>

#include "cactus/macros.h"
#include "cactus/rw_lock.h"
#include "cactus/version.h"

namespace cactus {

static std::string GetVersion() {
  return std::to_string(CACTUS_VERSION_MAJOR) + "." +
         std::to_string(CACTUS_VERSION_MINOR) + "." +
         std::to_string(CACTUS_VERSION_PATCH);
}

}  // namespace cactus

#endif  // CACTUS_H_
