#include <unistd.h>

#include <iostream>

#include "include/threadpool.h"

class TestTask : public Practice::Task {
 public:
  virtual void run();
};

class TestTaskB : public Practice::Task {
 public:
  virtual void run();
};

void TestTask::run() {
  int i = 0;
  for (int i = 0; i < 20; i++) {
    std::cout << i << '\n';
    sleep(0.1);
  }
}

void TestTaskB::run() {
  int i = 0;
  for (int i = 20; i < 40; i++) {
    std::cout << i << '\n';
    sleep(0.1);
  }
}

int main(int, char **) {
  // std::cout << "Hello, world!\n";
  // Practice::ThreadPool *pool = new Practice::ThreadPool();
  // pool->init(5);
  // TestTask *t = new TestTask();
  // TestTaskB *tb = new TestTaskB();
  // pool->addTask(t);
  // pool->addTask(tb);
  // sleep(5);
  // delete t;
  // delete tb;
  // delete pool;
  return 0;
}
