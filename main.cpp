#include <unistd.h>

#include <iostream>

#include "include/threadpool.h"

class TestTask : public Practice::Task {
 public:
 TestTask() {}
 ~TestTask() {}
  virtual void run();
};

class TestTaskB : public Practice::Task {
 public:
  TestTaskB() {}
  ~TestTaskB() {}
  virtual void run();
};

class TestTaskC : public Practice::Task {
 public:
  TestTaskC() {}
  ~TestTaskC() {}
  virtual void run();
};

void TestTask::run() {
  int i = 0;
  for (int i = 0; i < 20; i++) {
    std::cout << i << '\n';
    sleep(0.2);
  }
}

void TestTaskB::run() {
  int i = 0;
  for (int i = 20; i < 40; i++) {
    std::cout << i << '\n';
    sleep(0.2);
  }
}

void TestTaskC::run() {
  int i = 0;
  for (int i = 40; i < 60; i++) {
    std::cout << i << '\n';
    sleep(0.2);
  }
}

int main(int, char **) {
  std::cout << "Hello, world!\n";
  Practice::ThreadPool *pool = new Practice::ThreadPool(2,2);
  TestTask *t = new TestTask();
  TestTaskB *tb = new TestTaskB();
  TestTaskC *tc = new TestTaskC();
  pool->addTask(t);
  pool->addTask(tb);
  pool->addTask(tc);
  sleep(10);
  delete t;
  delete tb;
  delete tc;
  delete pool;
  return 0;
}
