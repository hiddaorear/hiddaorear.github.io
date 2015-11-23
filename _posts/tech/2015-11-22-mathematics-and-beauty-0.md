---
layout: post
title:  Mathematics & Thinking(0)
category: 技术
tags: [Mathematics Thinking]
keywords: Mathematics
description:
---

##### Sunday, 22 November 2015

### Thinking in Mathematics

![Jobs](/../../assets/img/tech/2015/jobs_5.jpg)

> This was a very typical time. All you needed was a cup of tea, a light, and your stereo, you know, and that's what I had. --Steve Jobs

> The art challenges the technology, and the technology inspires the art.

> I don't have faith in tools, I have faith in people. --Steve Jobs

> No technology can turn a bad story to a good story. --Steve Jobs

> I do not belive it is a problem that has a technological answer, I believe it is a problem that has a human answer.  --Steve Jobs

> 解释古事、批评古人，也不是绝对不可以，不过要谨慎，限于可能的范围以内罢了。谨守着个范围，我们能说的话，实在很少。然而在这些话中，却多少见得一点事实的真相，其意义，要比演义等假设之以满足人的感悟的深长得多。  --吕思勉


## 硬件

### 堆与栈

- stack: 连续的内存区域，编译器自动分配释放，速度较快，无法由程序员控制。操作方式类似数据结构中的stack。
- heap: 不连续的内存区域(链表存储)，程序员分配释放，由new分配，速度慢，容易产生碎片。


## 编程技巧

### 环形队列

类似固定长度缓冲区的读写，环形队列通常是最好的选择，避免移动操作。

设模拟环形队列的线性列表的长度是N，对头指针是head，队尾指针是tail，则：
`tail = (tail + 1) % N`
可以计算新的队尾指针。
当tail+1等于head的时候，队列已满，head向后移动一位即可。

### 单循环遍历而二维数组
遍历9宫格：

````c

for (var i = 0; i < 9; i++)
{
  int row = i / 3;
  int col = i % 3;
  game->cells[row][col].fixed = false;
}

````


### 函数表

过长的分支结构，常被视为不良的结构，其违背了OCP原则（开放封闭原则），每当需要新增一种条件判断处理时，就要新增一个if-else结构。函数表可以避免过长的多分支的结构。

求解“农夫，狼，羊和菜过河问题”，农夫一共可以采用8种动作。

````c

typedef bool (*ProcessNextFunPtr)(const ItemState& current, ItemState& next);
struct ActionProcess
{
  Atction           act;
  ProcessNextFunPtr processFunc;
}

ActionProcess actMap[] =
{
  {FARMER_GO,                  ProcessFarmeGo},
  {FARMER_GO_TAKE_WOLF,        processFarmeGoTakeWolf},
  {FARMER_GO_TAKE_SHEEP,       processFarmeGoTakeSheep},
  {FARMER_GO_TAKE_VEGETABLE,   processFarmeGoTakeVegetable},
  {FARMER_BACK,                processFarmeBack},
  {FARMER_BACK_TAKE_WOLF,      processFarmeBackTakeWolf},
  {FARMER_BACK_TAKE_SHEEP,     processFarmeBackTakeSheep},
  {FARMER_BACK_TALE_VEGETABLE, processFarmeBackTakeVegetable}
}

ItemState next;
for(int i = 0; i < sizeof(actMap)/sizeof(actMap[0]); i++)
{
  if(actMap[i].act == action)
  {
    actMap[i].processFunc(current, next);
    break;
  }
}

````

## Thinking

算法思想的背后，隐隐约约藏着数学归纳法。

> 数学归纳原理：设P(n)是关于自然数的一个性质。假设P(0)是真的，并假设只要P(n)是真的，则P(n++)也是真的，那么对于每个自然数n，P(n)都是真的。
一个逻辑学注释：由于这个公理不仅说及变量，同时也说及性质，与其他公理具有不同的本质。在技术上与其叫公理，不如叫作公理框架(axiom schema)，他是一个产生无限多个公理的模板。
《Analysis》--陶哲轩

### 数据结构与算法

数据结构是算法的基本工具，采用什么样的数据结构由算法的数学模型决定，但是各不相同的数据结构自身的一些特点也会影响数学模型的选择。

### 设计思想之贪婪(greedy algorithm)
选取当前状况下最有利的选择，不考虑整体情况。

### 设计思想之分治(divide and conquere)
将大问题分解成一系列的规模较小的相同问题，然后逐步解决。

### 设计思想之动态规划(dynamic programming)
将复杂问题沿决策阶段划分子问题，子问题有关联，求解小问题然后反推原问题的结果。

动态规划通过将问题细分为一系列子问题，从而隐含地探查了所有可行解的空间，于是我们可以在某种程度上把动态规划看作接近暴力搜索边缘的危险操作。所以，动态规划不是一种多项式时间的方法，而是一种穷举。

### 设计思想之穷举
在有限的解空间，按照一定策略进行查找。

### 妖怪与和尚过河问题

避免出现过多的if语句技巧（动作列表）


### 参考资料:
《算法的乐趣》王晓华

hid say: 简化。



