#include "cactus/macros.h"

#include <gtest/gtest.h>

#include <cassert>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "cactus/cactus.h"

class TestMacros : public testing::Test {
 public:
  static void SetUpTestCase();     // 在第一个case之前执行
  static void TearDownTestCase();  // 在最后一个case之后执行
  void SetUp() override;           // 在每个case之前执行
  void TearDown() override;        // 在每个case之后执行
};

void TestMacros::SetUpTestCase() {}
void TestMacros::TearDownTestCase() {}
void TestMacros::TearDown() {}
void TestMacros::SetUp() {}

class Cat {
 public:
  ~Cat() = default;
  std::string name() const { return name_; }
  int age() const { return age_; }
  void set_name(const std::string& name) { name_ = name; }
  void set_age(int age) { age_ = age; }

 private:
  std::string name_;
  int age_;
  CACTUS_DECLARE_SINGLETON(Cat)  // 声明单例
};

Cat::Cat() {}

TEST_F(TestMacros, TestSingleton) {
  Cat::Instance()->set_age(1);
  ASSERT_EQ(1, Cat::Instance()->age());
  Cat::Instance()->set_age(2);
  ASSERT_EQ(2, Cat::Instance()->age());
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
