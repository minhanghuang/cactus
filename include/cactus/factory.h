#ifndef CACTUS_FACTORY_H_
#define CACTUS_FACTORY_H_
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <utility>

#include "cactus/macros.h"

namespace cactus {

class Factory {
 public:
  ~Factory();
  void Shutdown();
  bool Register(const std::string& id, void* creator);
  bool Contains(const std::string& id) const;
  bool Unregister(const std::string& id);
  void Clear();
  bool Empty() const;

  template <typename Class>
  std::unique_ptr<Class> GetObject(const std::string& id) {
    std::lock_guard<std::mutex> guard(mutex_);
    auto id_iter = producers_.find(id);
    if (id_iter != producers_.end()) {
      return std::unique_ptr<Class>(static_cast<Class*>(id_iter->second));
    }
    return nullptr;
  }

 private:
  std::mutex mutex_;
  std::unordered_map<std::string, void*> producers_;
  CACTUS_DECLARE_SINGLETON(Factory)  // 声明单例
};

}  // namespace cactus

#define CACTUS_REGISTERS_TO_FACTORY(id, creator) \
  cactus::Factory::Instance()->Register(id, creator);

#endif  // CACTUS_FACTORY_H_
