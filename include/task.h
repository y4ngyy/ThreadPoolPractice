#pragma once

namespace Practice {
class Task {  // interface的东西
 public:
  Task();
  ~Task();
  virtual void run() = 0;
};
}  // namespace Practice