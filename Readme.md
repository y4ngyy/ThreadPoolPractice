# ThreadPool

## 描述

C++封装的pthread线程池

## 功能描述

- 初始化指定数量的工作线程
- 添加任务到空闲的工作线程
- 池中线程均为busy状态时动态增加池中线程数，直到最大值
- 当池中线程数达到最大值时，再添加任务则进入任务队列中等待
- 线程池销毁时依次销毁池中线程
    - 强制销毁
    - 等待销毁
- 工作线程空闲时发送信号给管理线程获取任务队列中的队列

## Future Feature (有时间再说)

- 线程池单例模式
- 动态线程回收
- 更严谨的安全退出
- raise异常 (大工程做法)

## 需要考虑的问题

- 如何安全销毁线程池
- 需要检查管理线程在分配任务和等待任务的时候锁安全问题