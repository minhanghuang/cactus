#ifndef CACTUS_H_
#define CACTUS_H_
#include <string>

#include "cactus/factory.h"
#include "cactus/macros.h"
#include "cactus/rw_lock.h"
#include "cactus/version.h"

namespace cactus {

static std::string GetVersion();

static std::string GetEnv(const std::string& var_name,
                          const std::string& default_value = "");

}  // namespace cactus

#endif  // CACTUS_H_
