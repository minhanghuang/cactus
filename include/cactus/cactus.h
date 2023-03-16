#ifndef CACTUS_H_
#define CACTUS_H_
#include <string>
#include <vector>

#include "cactus/factory.h"
#include "cactus/macros.h"
#include "cactus/rw_lock.h"
#include "cactus/version.h"

namespace cactus {

std::string GetVersion();

std::string GetEnv(const std::string& var_name,
                   const std::string& default_value = "");

bool FileExists(const std::string& file_path);

std::vector<std::string> StrSplit(const std::string& str,
                                  const std::string& delimiter);

std::string StrToUpper(const std::string& s);

std::string StrToLower(const std::string& s);

std::string GetTimeStr();

}  // namespace cactus

#endif  // CACTUS_H_
