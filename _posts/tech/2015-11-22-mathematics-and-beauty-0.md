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

> No technology can turn a bad stroy to a good story. --Steve Jobs

> I do not belive it is a problem that has a technological answer, I believe it is a problem that has a human answer.  --Steve Jobs

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

### 数据结构与算法

数据结构是算法的基本工具，采用什么样的数据结构由算法的数学模型决定，但是各不相同的数据结构自身的一些特点也会影响数学模型的选择。



### 参考资料:
《算法的乐趣》王晓华

hid say: 简化。



