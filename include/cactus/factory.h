#ifndef CACTUS_FACTORY_H_
#define CACTUS_FACTORY_H_
#include <memory>
#include <mutex>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

#include "cactus/macros.h"

namespace cactus {

class Factory {
 public:
  ~Factory();
  bool Contains(const std::string& classname) const;
  bool Empty() const;
  std::vector<std::string> GetClassNames();

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
    std::string class_name = typeid(Class).name();
    return Register<Class>(class_name);
  }

  template <typename Class>
  bool Unregister(const std::string& class_name) {
    std::lock_guard<std::mutex> guard(mutex_);
    if (producers_.count(class_name)) {
      producers_.erase(class_name);
      return true;
    }
    return false;
  }

  template <typename Class>
  bool Unregister() {
    std::string class_name = typeid(Class).name();
    return Unregister<Class>(class_name);
  }

  template <typename Class>
  bool AppendObject(Class* object, const std::string& class_name) {
    std::lock_guard<std::mutex> guard(mutex_);
    producers_[class_name] = std::shared_ptr<void>(object);
    return true;
  }

  template <typename Class>
  bool AppendObject(Class* object) {
    std::string class_name = typeid(Class).name();
    return AppendObject<Class>(object, class_name);
  }

  template <typename Class>
  bool AppendObject(const Class& object, const std::string& class_name) {
    std::lock_guard<std::mutex> guard(mutex_);
    producers_[class_name] = std::make_shared<Class>(object);
    return true;
  }

  template <typename Class>
  bool AppendObject(const Class& object) {
    std::string class_name = typeid(Class).name();
    return AppendObject<Class>(object, class_name);
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

  template <typename Class>
  std::shared_ptr<Class> GetObject() {
    std::string class_name = typeid(Class).name();
    return GetObject<Class>(class_name);
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

#define CACTUS_UNREGISTER_FROM_FACTORY(classname) \
  cactus::Factory::Instance()->Unregister<classname>();

#define CACTUS_APPENDOBJECT_TO_FACTORY(classname, object) \
  cactus::Factory::Instance()->AppendObject<classname>(object);

#endif  // CACTUS_FACTORY_H_
