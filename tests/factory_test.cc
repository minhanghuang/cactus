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
  Cat() : Animal("animal") {}
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
  CACTUS_REGISTERS_TO_FACTORY(Cat);
  auto factory = cactus::Factory::Instance();
  {
    std::shared_ptr<Cat> cat = factory->GetObject<Cat>();
    ASSERT_TRUE(nullptr != cat);
  }
  {
    auto ret = factory->Register<Cat>("Cat1");
    ASSERT_TRUE(ret);
    ret = factory->Register<Cat>("Cat1");
    ASSERT_TRUE(!ret);
    std::shared_ptr<Cat> cat = factory->GetObject<Cat>("Cat1");
    ASSERT_TRUE(cat != nullptr);
    std::shared_ptr<Cat> cat2 = factory->GetObject<Cat>();
    ASSERT_TRUE(cat2 != nullptr);
  }
  {
    std::shared_ptr<Cat> cat = CACTUS_GETOBJECT_FROM_FACTORY(Cat);
    ASSERT_TRUE(cat != nullptr);
  }
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
