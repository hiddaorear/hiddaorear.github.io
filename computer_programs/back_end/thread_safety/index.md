# 线程安全

#### 2023/09/08

## 定义

线程安全有不止一种定义，而且互不兼容。

### 定义一
定义一：根据《Java Concurrency in Practice》的定义，线程安全的class应当满足三个条件：
 - 多个线程同时访问时，表现出正确的行为；
 - 无论操作系统如何调度这些线程，无论这些线程的执行顺序如何交织（interleaving）
 - 调用端代码无须额外的同步，或者协调操作
总之，多线程并发时，能过正常工作。

以此为标准：
 - C++ 标准容器库中大多数class都不是线程安全的，含：`string, vector, map, shared_ptr`等等。
 - 而C系统库大多数函数是线程安全的，含：`malloc, free, printf, gettimeofday`

### 定义二
定义二：一般称之为：thread compatible
 - 同一类型的多个对象，能分别被各自所属的不同线程并发访问。
以此为标准:
 - C++ 标准库容器和基本类型，都是"线程安全的"。

### 可重入（reentrant）

还有一个相关概念：可重入（reentrant）
定义：不仅在多线程并发时能正常工作，而且要在 signal handler（软中断）函数中被调用，依然能正常工作。
没有较正式的定义，wiki上："A computer program or routine is described as reentrant if it can be safely executed concurrently; that is, the routine can be re-entered while it is already running."

所谓的重入：通常来说，程序执行到某函数foo()时，收到信号，于是暂停目前正在执行的函数，转到信号处理函数，而这个信号处理函数执行过程中，有恰好进入刚刚执行的函数foo()。
如果此时foo()还能够正确的运行，而且处理完成后，之前暂停的foo()也能正确运行，则说明他是可重入的。

可重入函数一定是线程安全函数，但线程安全函数，不一定是可重入函数。

#### 可重入条件
- 不在函数内部使用静态或全局变量
- 不返回静态或全局数据
- 所有数据由函数调用者提供，使用本地数据，或者通过复制全局数据来保护全局数据
- 不调用不可重入函数

函数increment_counter是线程安全的，但不可重入：
```c 
#include <pthread.h>

int increment_counter()
{
    static int counter = 0;
    static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&mutex);
    // only allow one thead to increment at a time
    ++counter;
    int result = counter;
    pthread_mutex_unlock(&mutex);
    return result;
}
```
increment_counter有一个互斥锁mutex来同步共享变量counter的访问，因此可以在多个线程中被调用。
但这个函数，在`pthread_mutex_lock(&mutex)`和;`pthread_mutex_unlock(&mutex)`之间，被第二个函数调用，此时increment_counter中断，执行第二个函数的调用。由于mutex已经被lock，第二次会在`pthread_mutex_lock(&mutex)`阻塞，由于mutex没有机会被unlock，阻塞会永远持续下去。这里主要问题在于，pthread的mutex不可重入。


C++11 中的源自变量，提供了一个可使此函数，既可线程安全，又可重入的方案：
```cpp
#include <atomic>

int increment_counter()
{
    static std::atomic<int> counter(0);
    // increment is guaranteed to be done atomically
    int result = ++counter;
    return result;
}
```

## 实现线程安全的方法

要实现线程安全，主要需要考虑线程之间的共享变量。属于同一进程的不同线程，会共享内存空间中全局去和堆，而私有线程空间则主要有栈和寄存器。
因此，同一个进程的不同线程，每一线程的局部变量都是私有的，而全局变量、局部静态变量、分配对堆的变量，都是共享的。在对这些共享变量进行访问时，如需保证线程安全，需要通过加锁等方式。

## 线程安全的数据结构