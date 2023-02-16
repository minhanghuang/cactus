#include "cactus/factory.h"

#include <gtest/gtest.h>

#include <cassert>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "cactus/cactus.h"
#include "cactus/macros.h"

class TestFactory : public testing::Test {
 public:
  static void SetUpTestCase();     // 在第一个case之前执行
  static void TearDownTestCase();  // 在最后一个case之后执行
  void SetUp() override;           // 在每个case之前执行
  void TearDown() override;        // 在每个case之后执行
};

void TestFactory::SetUpTestCase() {}
void TestFactory::TearDownTestCase() {}
void TestFactory::TearDown() {}
void TestFactory::SetUp() {}

class Animal {
 public:
  Animal(const std::string& name) : name_(name) {}
  virtual ~Animal() = default;
  std::string name() const { return name_; }

 private:
  std::string name_;
};

class Cat : public Animal {
 public:
  ~Cat() = default;
  Cat(const std::string& name) : Animal(name) {}
  std::string c() const { return "c"; }
};

class Dog : public Animal {
 public:
  ~Dog() = default;
  Dog(const std::string& name) : Animal(name) {}
  std::string d() const { return "d"; }
};

TEST_F(TestFactory, TestRegister) {
  auto factory = cactus::Factory::Instance();
  factory->Register("Cat", new Cat("Tom"));
  {
    std::unique_ptr<Cat> cat = factory->GetObject<Cat>("Cat");
    ASSERT_TRUE(nullptr != cat);
  }
  {
    std::unique_ptr<Cat> cat = factory->GetObject<Cat>("Non_Exist_Cat");
    ASSERT_TRUE(nullptr == cat);
  }
}

TEST_F(TestFactory, TestUnregister) {
  auto factory = cactus::Factory::Instance();
  factory->Register("Cat", new Cat("Tom"));
  {
    std::unique_ptr<Cat> cat = factory->GetObject<Cat>("Cat");
    ASSERT_TRUE(nullptr != cat);
  }
  {
    factory->Unregister("Cat");
    std::unique_ptr<Cat> cat = factory->GetObject<Cat>("Cat");
    ASSERT_TRUE(nullptr == cat);
  }
}

TEST_F(TestFactory, TestDefineRegister) {
  CACTUS_REGISTERS_TO_FACTORY("Cat", static_cast<void*>(new Cat("Tom")));
  auto factory = cactus::Factory::Instance();
  {
    std::unique_ptr<Cat> cat = factory->GetObject<Cat>("Cat");
    ASSERT_TRUE(nullptr != cat);
  }
  cactus::Factory::CleanUp();
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
