#include "cactus/factory.h"

namespace cactus {

Factory::~Factory() {}

Factory::Factory() {}

void Factory::Shutdown() {
  std::lock_guard<std::mutex> guard(mutex_);
  std::cout << "Factory CleanUp..." << std::endl;
  // for (auto producer : producers_) {
  //   free(producer.second);
  // }
}

bool Factory::Register(const std::string& id, void* creator) {
  std::lock_guard<std::mutex> guard(mutex_);
  return producers_.emplace(std::make_pair(id, creator)).second;
}

bool Factory::Contains(const std::string& id) const {
  return producers_.count(id) > 0;
}

bool Factory::Unregister(const std::string& id) {
  std::lock_guard<std::mutex> guard(mutex_);
  return producers_.erase(id) == 1;
}

void Factory::Clear() {
  std::lock_guard<std::mutex> guard(mutex_);
  producers_.clear();
}

bool Factory::Empty() const { return producers_.empty(); }

}  // namespace cactus
