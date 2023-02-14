#include <gtest/gtest.h>

#include <cassert>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "cactus/cactus.h"

class TestRWLock : public testing::Test {
 public:
  static void SetUpTestCase();     // 在第一个case之前执行
  static void TearDownTestCase();  // 在最后一个case之后执行
  void SetUp() override;           // 在每个case之前执行
  void TearDown() override;        // 在每个case之后执行
};

void TestRWLock::SetUpTestCase() {}
void TestRWLock::TearDownTestCase() {}
void TestRWLock::TearDown() {}
void TestRWLock::SetUp() {}

class Zoo {
 public:
  void Eat() {
    std::thread t1(&Zoo::Cat, this);
    std::thread t2(&Zoo::Dog, this);
    std::thread t3(&Zoo::Mouse, this);
    t1.join();
    t2.join();
    t3.join();
  }

 private:
  void Cat() {
    // /// 1.多线程不加锁: 程序崩溃
    // std::cout << "Cat Eat." << std::endl;
    // food.clear();
    // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    // food.emplace_back(1);
    // food.emplace_back(99);
    // std::cout << "Cat End." << std::endl;

    // /// 2.多线程加互斥锁: 程序不崩溃, 但是读取数据时, 影响别的线程读取数据
    // {
    //   std::unique_lock<std::mutex> lock(mutex_);
    //   std::cout << "Cat Eat." << std::endl;
    //   food.clear();
    //   std::this_thread::sleep_for(std::chrono::milliseconds(100));
    //   food.emplace_back(1);
    //   food.emplace_back(99);
    //   std::cout << "Cat End." << std::endl;
    // }

    /// 3.多线程加读写锁: 程序不崩溃, 所有读锁不互斥 && 读锁和写锁互斥
    {
      cactus::WriteLockGuard<cactus::AtomicRWLock> lck(rw_lock_);
      std::cout << "Cat Eat." << std::endl;
      food.clear();
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      food.emplace_back(1);
      food.emplace_back(99);
      std::cout << "Cat End." << std::endl;
    }
  }

  void Dog() {
    // /// 1.多线程不加锁: 程序崩溃
    // std::cout << "Dog Eat." << std::endl;
    // std::cout << "Dog ...  " << food.at(1) << std::endl;
    // std::cout << "Dog End." << std::endl;

    // /// 2.多线程加互斥锁: 程序不崩溃, 但是读取数据时, 影响别的线程读取数据
    // {
    //   std::unique_lock<std::mutex> lock(mutex_);
    //   std::cout << "Dog Eat." << std::endl;
    //   std::cout << "Dog ...  " << food.at(1) << std::endl;
    //   std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    //   std::cout << "Dog End." << std::endl;
    // }

    /// 3.多线程加读写锁: 程序不崩溃, 所有读锁不互斥 && 读锁和写锁互斥
    {
      cactus::ReadLockGuard<cactus::AtomicRWLock> lck(rw_lock_);
      std::cout << "Dog Eat." << std::endl;
      std::cout << "Dog ...  " << food.at(1) << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      std::cout << "Dog End." << std::endl;
    }
  }

  void Mouse() {
    // /// 1.多线程不加锁: 程序崩溃
    // std::cout << "Mouse Eat." << std::endl;
    // std::cout << "Mouse ...  " << food.at(1) << std::endl;
    // std::cout << "Mouse End." << std::endl;

    // /// 2.多线程加互斥锁: 程序不崩溃, 但是读取数据时, 影响别的线程读取数据
    // {
    //   std::unique_lock<std::mutex> lock(mutex_);
    //   std::cout << "Mouse Eat." << std::endl;
    //   std::cout << "Mouse ...  " << food.at(1) << std::endl;
    //   std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    //   std::cout << "Mouse End." << std::endl;
    // }

    /// 3.多线程加读写锁: 程序不崩溃, 所有读锁不互斥 && 读锁和写锁互斥
    {
      cactus::ReadLockGuard<cactus::AtomicRWLock> lck(rw_lock_);
      std::cout << "Mouse Eat." << std::endl;
      std::cout << "Mouse ...  " << food.at(1) << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      std::cout << "Mouse End." << std::endl;
    }
  }
  std::vector<int> food{1, 2, 3};  // 共享资源
  std::mutex mutex_;               // 互斥锁
  cactus::AtomicRWLock rw_lock_;   // 读写锁
};

TEST_F(TestRWLock, Test) {
  Zoo zoo;
  zoo.Eat();
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
