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

// register object macro
#define REGISTER_OBJECT_FACTORY_INTERNAL1(ClassName, UniqueId) \
  cactus::RegisterAction<ClassName>(std::make_shared<ClassName>(), #UniqueId);

#define REGISTER_OBJECT_FACTORY_INTERNAL(ClassName) \
  REGISTER_OBJECT_FACTORY_INTERNAL1(ClassName, g_##ClassName##__COUNTER__)

namespace cactus {

class Factory {
 public:
  ~Factory();
  bool Contains(const std::string& unique_id);
  bool Empty();
  void Clear();
  std::vector<std::string> GetObjectNames();

  template <typename Class>
  bool Register(const std::string& unique_id, bool force = false) {
    std::lock_guard<std::mutex> guard(mutex_);
    if (!force && producers_.count(unique_id)) {
      return false;
    }
    producers_.emplace(std::make_pair(unique_id, std::make_shared<Class>()));
    return true;
  }

  template <typename Class>
  bool Register(const Class* object, const std::string& unique_id,
                bool force = false) {
    std::lock_guard<std::mutex> guard(mutex_);
    if (!force && producers_.count(unique_id)) {
      return false;
    }
    producers_[unique_id] = std::make_shared<Class>(*object);
    return true;
  }

  template <typename Class>
  bool Register(const std::shared_ptr<Class>& object,
                const std::string& unique_id, bool force = false) {
    std::cout << "左值引用" << std::endl;
    std::lock_guard<std::mutex> guard(mutex_);
    if (!force && producers_.count(unique_id)) {
      return false;
    }
    producers_[unique_id] = object;
    return true;
  }

  template <typename Class>
  bool Register(std::shared_ptr<Class>&& object, const std::string& unique_id,
                bool force = false) {
    std::lock_guard<std::mutex> guard(mutex_);
    if (!force && producers_.count(unique_id)) {
      return false;
    }
    producers_[unique_id] = std::move(object);
    return true;
  }

  template <typename Class>
  bool Unregister(const std::string& unique_id) {
    std::lock_guard<std::mutex> guard(mutex_);
    if (producers_.count(unique_id)) {
      producers_.erase(unique_id);
      return true;
    }
    return false;
  }

  template <typename Class>
  std::shared_ptr<Class> GetObject(const std::string& unique_id) {
    std::lock_guard<std::mutex> guard(mutex_);
    auto id_iter = producers_.find(unique_id);
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

template <typename T>
class RegisterAction {
 public:
  RegisterAction(const std::shared_ptr<T>& object,
                 const std::string& unique_id) {
    cactus::Factory::Instance()->Register(object, unique_id, true);
  }
};

}  // namespace cactus

#endif  // CACTUS_FACTORY_H_
