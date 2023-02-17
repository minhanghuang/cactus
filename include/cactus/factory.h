#ifndef CACTUS_FACTORY_H_
#define CACTUS_FACTORY_H_
#include <memory>
#include <mutex>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>

#include "cactus/macros.h"

namespace cactus {

class Factory {
 public:
  ~Factory();
  bool Contains(const std::string& classname) const;
  bool Empty() const;

  template <typename Class>
  bool Register(const std::string& class_name) {
    std::lock_guard<std::mutex> guard(mutex_);
    if (producers_.count(class_name) > 0) {
      return false;
    }
    producers_.emplace(std::make_pair(class_name, std::make_shared<Class>()));
    return true;
  }

  template <typename Class>
  bool Register() {
    std::lock_guard<std::mutex> guard(mutex_);
    std::string class_name = typeid(Class).name();
    if (producers_.count(class_name)) {
      return false;
    }
    producers_.emplace(std::make_pair(class_name, std::make_shared<Class>()));
    return true;
  }

  template <typename Class>
  std::shared_ptr<Class> GetObject() {
    std::lock_guard<std::mutex> guard(mutex_);
    std::string class_name = typeid(Class).name();
    auto id_iter = producers_.find(class_name);
    if (id_iter != producers_.end()) {
      return std::static_pointer_cast<Class>(id_iter->second);
    }
    return nullptr;
  }

  template <typename Class>
  std::shared_ptr<Class> GetObject(const std::string& class_name) {
    std::lock_guard<std::mutex> guard(mutex_);
    auto id_iter = producers_.find(class_name);
    if (id_iter != producers_.end()) {
      return std::static_pointer_cast<Class>(id_iter->second);
    }
    return nullptr;
  }

 private:
  std::mutex mutex_;
  std::unordered_map<std::string, std::shared_ptr<void>> producers_;
  CACTUS_DECLARE_SINGLETON(Factory)  // 声明单例
};

}  // namespace cactus

#define CACTUS_REGISTERS_TO_FACTORY(classname) \
  cactus::Factory::Instance()->Register<classname>();

#define CACTUS_GETOBJECT_FROM_FACTORY(classname) \
  cactus::Factory::Instance()->GetObject<classname>();

#endif  // CACTUS_FACTORY_H_
