# 浅析基本数据结构

#### 2023/07/28

## heap

### 应用

许多应用程序需要处理有序元素，但不一定要求他们全部有序，或是不一定要一次就将他们排序。很多情况下，收集一些元素，处理当前最大元素，然后再收集更多元素，再处理最大元素。比如，电脑中运行多个程序，为每个应用分配一个优先级，并总是处理优先级最高的事件。例如，手机来电优先级，比手机游戏优先级高。

处理以上情况，一个合理的数据结构，应该支持两种基本操作：删除最大元素，插入元素。

同时，这种有序的操作，能很自然的就可以实现排序，比如，插入一列元素，然后删除其中最小元素，就可以实现排序。堆排序就是基于优先队列实现。

### 概述

如果用list作为优先队列（priority queue）底层机制，元素插入可以常数时间，但如果要找极值，需要对整个list线性扫描。

如果变通一下，让元素插入的时候先排序，找极值就简单很多，但插入只有线性表现。

还可以用完全二叉树（complete binary tree），即 binary heap 除了最底层叶子节点之外，都是填满的。且叶子节点从左至右，不得有空隙。

![complete binary tree](./2023_7_28_basic_data_structures/complete_binary_tree.png)

### 实现

由于完全二叉树没有空隙，我们就可以用array来存储所有节点。将array的索引0保留，当完全二叉树的某个节点位于i，其左节点必位于2i，右节点位于2i+1。反过来推断，i的父节点，必位于`floor(i/2)`。

通过这个简单的规则，就可以用array实现出 complete binary tree。以array表述tree的方式，称之为隐式表示（implicit representation）

![complete binary tree array](./2023_7_28_basic_data_structures/complete_binary_tree_array.png)

一个array 和一组 heap 算法（插入、删除、取极值，将数据排列为 heap），就可以实现完全二叉树。然后通过完全二叉树实现heap。

heap可以分为 `max-heap` 和 `min-heap`，`max-heap`的最大值在根节点，每个节点的值大于或等于子节点。`min-heap`反之。

## log

- 2023/07/28 初稿
