#include "cactus/factory.h"

namespace cactus {

Factory::~Factory() {}

Factory::Factory() {}

bool Factory::Contains(const std::string& classname) {
  std::lock_guard<std::mutex> guard(mutex_);
  return producers_.count(classname) > 0;
}

bool Factory::Empty() {
  std::lock_guard<std::mutex> guard(mutex_);
  return producers_.empty();
}

std::vector<std::string> Factory::GetObjectNames() {
  std::lock_guard<std::mutex> guard(mutex_);
  std::vector<std::string> ret;
  for (const auto& producer : producers_) {
    ret.emplace_back(producer.first);
  }
  return ret;
}

void Factory::Clear() {
  std::lock_guard<std::mutex> guard(mutex_);
  producers_.clear();
}

}  // namespace cactus
