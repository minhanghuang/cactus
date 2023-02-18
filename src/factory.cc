#include "cactus/factory.h"

namespace cactus {

Factory::~Factory() {}

Factory::Factory() {}

bool Factory::Contains(const std::string& classname) const {
  return producers_.count(classname) > 0;
}

bool Factory::Empty() const { return producers_.empty(); }

std::vector<std::string> Factory::GetClassNames() {
  std::vector<std::string> ret;
  for (const auto& producer : producers_) {
    ret.emplace_back(producer.first);
  }
  return ret;
}

}  // namespace cactus
