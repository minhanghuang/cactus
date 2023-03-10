#ifndef CACTUS_MACROS_H_
#define CACTUS_MACROS_H_
#include <iostream>
#include <memory>
#include <mutex>
#include <type_traits>

#define CACTUS_DEFINE_TYPE_TRAIT(name, func)              \
  template <typename T>                                   \
  struct name {                                           \
    template <typename Class>                             \
    static constexpr bool Test(decltype(&Class::func)*) { \
      return true;                                        \
    }                                                     \
    template <typename>                                   \
    static constexpr bool Test(...) {                     \
      return false;                                       \
    }                                                     \
                                                          \
    static constexpr bool value = Test<T>(nullptr);       \
  };                                                      \
                                                          \
  template <typename T>                                   \
  constexpr bool name<T>::value;

CACTUS_DEFINE_TYPE_TRAIT(HasShutdown, Shutdown)

template <typename T>
typename std::enable_if<HasShutdown<T>::value>::type CallShutdown(T* instance) {
  instance->Shutdown();
}

template <typename T>
typename std::enable_if<!HasShutdown<T>::value>::type CallShutdown(
    T* instance) {
  (void)instance;
}

#define CACTUS_DISALLOW_COPY_AND_ASSIGN(classname) \
  classname(const classname&) = delete;            \
  classname& operator=(const classname&) = delete;

#define CACTUS_DECLARE_SINGLETON(classname)                               \
 public:                                                                  \
  static classname* Instance(bool create_if_needed = true) {              \
    static classname* instance = nullptr;                                 \
    if (!instance && create_if_needed) {                                  \
      static std::once_flag flag;                                         \
      std::call_once(flag,                                                \
                     [&] { instance = new (std::nothrow) classname(); }); \
    }                                                                     \
    return instance;                                                      \
  }                                                                       \
                                                                          \
  static void CleanUp() {                                                 \
    auto instance = Instance(false);                                      \
    if (instance != nullptr) {                                            \
      CallShutdown(instance);                                             \
    }                                                                     \
  }                                                                       \
                                                                          \
 private:                                                                 \
  classname();                                                            \
  CACTUS_DISALLOW_COPY_AND_ASSIGN(classname)

#endif  // CACTUS_MACROS_H_
