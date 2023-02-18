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

TEST_F(TestFactory, TestRegister) {
  auto factory = cactus::Factory::Instance();
  ASSERT_EQ(0, factory->GetClassNames().size());
  CACTUS_REGISTERS_TO_FACTORY(Cat);
  ASSERT_EQ(1, factory->GetClassNames().size());
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

TEST_F(TestFactory, TestUnregister) {
  auto factory = cactus::Factory::Instance();
  ASSERT_EQ(2, factory->GetClassNames().size());
  auto cat = CACTUS_GETOBJECT_FROM_FACTORY(Cat);
  ASSERT_TRUE(nullptr != cat);
  ASSERT_EQ("animal", cat->name());
  CACTUS_UNREGISTER_FROM_FACTORY(Cat);
  ASSERT_EQ(1, factory->GetClassNames().size());
  ASSERT_TRUE(nullptr != cat);
  ASSERT_EQ("animal", cat->name());
}

TEST_F(TestFactory, TestAppendObject) {
  auto factory = cactus::Factory::Instance();
  ASSERT_EQ(1, factory->GetClassNames().size());

  // append new cat
  Cat* cat = new Cat();
  cat->set_name("star_cat");
  CACTUS_APPENDOBJECT_TO_FACTORY(Cat, cat);
  ASSERT_EQ(2, factory->GetClassNames().size());
  std::shared_ptr<Cat> get_cat = CACTUS_GETOBJECT_FROM_FACTORY(Cat);
  ASSERT_EQ("star_cat", get_cat->name());

  // append cat object
  Cat obj_cat;
  obj_cat.set_name("obj_cat");
  CACTUS_APPENDOBJECT_TO_FACTORY(Cat, obj_cat);
  ASSERT_EQ(2, factory->GetClassNames().size());
  get_cat = CACTUS_GETOBJECT_FROM_FACTORY(Cat);
  ASSERT_EQ("obj_cat", get_cat->name());

  // append shared cat
  std::shared_ptr<Cat> shared_cat = std::make_shared<Cat>();
  shared_cat->set_name("shared_cat");
  CACTUS_APPENDOBJECT_TO_FACTORY(Cat, shared_cat.get());
  ASSERT_EQ(2, factory->GetClassNames().size());
  get_cat = CACTUS_GETOBJECT_FROM_FACTORY(Cat);
  ASSERT_EQ("shared_cat", get_cat->name());
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
