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

TEST_F(TestFactory, Test) {}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
