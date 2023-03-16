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

bool FileExists(const std::string& file_path) {
  if (FILE* f = fopen(file_path.c_str(), "r")) {
    fclose(f);
    return true;
  }
  return false;
}

std::vector<std::string> StrSplit(const std::string& str,
                                  const std::string& delimiter) {
  std::vector<std::string> res;
  size_t pos = 0;
  size_t index = 0;
  std::string token;
  while ((pos = str.find(delimiter, index)) != std::string::npos) {
    token = str.substr(index, pos - index);
    res.emplace_back(token);
    index = pos + delimiter.length();
  }
  token = str.substr(index);
  res.emplace_back(token);
  return res;
}

std::string StrToUpper(const std::string& s) {
  std::string ret = s;
  std::transform(s.begin(), s.end(), ret.begin(),
                 [](auto t) { return std::toupper(t); });
  return ret;
}

std::string StrToLower(const std::string& s) {
  std::string ret = s;
  std::transform(s.begin(), s.end(), ret.begin(),
                 [](auto t) { return std::tolower(t); });
  return ret;
}

std::string GetTimeStr() {
  time_t now = time(0);
  tm* ltm = localtime(&now);
  return std::to_string(1900 + ltm->tm_year) + "-" +
         std::to_string(1 + ltm->tm_mon) + "-" + std::to_string(ltm->tm_mday) +
         " " + std::to_string(ltm->tm_hour) + ":" +
         std::to_string(ltm->tm_min) + ":" + std::to_string(ltm->tm_sec);
}

}  // namespace cactus
