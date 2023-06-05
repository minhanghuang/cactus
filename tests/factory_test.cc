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
  void set_name(const std::string& name) { name_ = name; }

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

class Mouse : public Animal {
 public:
  ~Mouse() = default;
  Mouse() : Animal("") {}
  Mouse(const std::string& name) : Animal(name) {}
  std::string m() const { return "m"; }
};
REGISTER_OBJECT_FACTORY_INTERNAL_WITHOUT_NAMESPACE(Mouse, "Mouse");

namespace cactus {

class Bird : public Animal {
 public:
  ~Bird() = default;
  Bird() : Animal("") {}
  Bird(const std::string& name) : Animal(name) {}
  std::string m() const { return "b"; }
};
REGISTER_OBJECT_FACTORY_INTERNAL(cactus, Bird, "cactus::Bird");

}  // namespace cactus

TEST_F(TestFactory, TestRegister) {
  auto factory = cactus::Factory::Instance();
  {
    ASSERT_GE(factory->GetObjectNames().size(), 0);
    ASSERT_TRUE(nullptr != factory->GetObject<Mouse>("Mouse"));
    ASSERT_TRUE(nullptr != factory->GetObject<cactus::Bird>("cactus::Bird"));
    ASSERT_TRUE(nullptr == factory->GetObject<cactus::Bird>("Bird"));
    factory->GetObject<cactus::Bird>("cactus::Bird")->set_name("b");
  }
  {
    auto bird = factory->GetObject<cactus::Bird>("cactus::Bird");
    ASSERT_TRUE("b" == bird->name());
  }
  {
    factory->Register<Cat>("Cat");
    ASSERT_TRUE(nullptr != factory->GetObject<Cat>("Cat"));
  }
  {
    auto ret = factory->Register<Cat>("Cat1");
    ASSERT_TRUE(ret);
    ret = factory->Register<Cat>("Cat1");
    ASSERT_TRUE(!ret);
    std::shared_ptr<Cat> cat = factory->GetObject<Cat>("Cat1");
    ASSERT_TRUE(cat != nullptr);
    std::shared_ptr<Cat> cat2 = factory->GetObject<Cat>("Cat");
    ASSERT_TRUE(cat2 != nullptr);
  }
  {
    // 验证重复注册
    ASSERT_EQ(false, factory->Register<Cat>("Cat1"));
    ASSERT_EQ(true, factory->Register<Cat>("Cat1", true));
  }
  {
    // 注册对象
    std::shared_ptr<Cat> s_cat = std::make_shared<Cat>();
    s_cat->set_name("shared_cat");
    auto ret = factory->Register<Cat>("Cat");
    ASSERT_EQ(false, ret);

    auto cat = factory->GetObject<Cat>("Cat");
    ASSERT_TRUE(nullptr != cat);
    ASSERT_EQ("animal", cat->name());
    ASSERT_EQ("shared_cat", s_cat->name());

    ret = factory->Register<Cat>(s_cat.get(), "Cat", true);
    ASSERT_EQ(true, ret);
    cat = factory->GetObject<Cat>("Cat");
    ASSERT_TRUE(nullptr != cat);
    ASSERT_EQ("shared_cat", cat->name());
  }
  {
    Cat cat;
    cat.set_name("tom_cat");
    auto ret = factory->Register<Cat>(&cat, "Cat", true);
    ASSERT_EQ(true, ret);
    auto cat2 = factory->GetObject<Cat>("Cat");
    ASSERT_TRUE(nullptr != cat2);
    ASSERT_EQ("tom_cat", cat2->name());
  }
}

TEST_F(TestFactory, TestUnregister) {
  auto factory = cactus::Factory::Instance();
  factory->Clear();
  ASSERT_EQ(0, factory->GetObjectNames().size());
  factory->Register<Cat>("Cat");
  ASSERT_EQ(1, factory->GetObjectNames().size());
  std::shared_ptr<Cat> cat = factory->GetObject<Cat>("Cat");
  ASSERT_TRUE(nullptr != cat);
  ASSERT_EQ("animal", cat->name());

  factory->Unregister<Cat>("Cat");
  ASSERT_EQ(0, factory->GetObjectNames().size());
  ASSERT_TRUE(nullptr != cat);
  ASSERT_EQ("animal", cat->name());
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
