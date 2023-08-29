# 浅析基本数据结构

#### 2023/07/28

## 堆（heap）

### 应用

许多应用程序需要处理有序元素，但不一定要求他们全部有序，或是不一定要一次就将他们排序。很多情况下，收集一些元素，处理当前最大元素，然后再收集更多元素，再处理最大元素。比如，电脑中运行多个程序，为每个应用分配一个优先级，并总是处理优先级最高的事件。例如，手机来电优先级，比手机游戏优先级高。

处理以上情况，一个合理的数据结构，应该支持两种基本操作：删除最大元素，插入元素。

这种有序的操作，能很自然的就可以实现排序，比如，插入一列元素，然后删除其中最小元素，就可以实现排序。堆排序就是基于优先队列实现。

### 概述

如果用list作为优先队列（priority queue）底层机制，元素插入可以常数时间，但如果要找极值，需要对整个list线性扫描。

如果变通一下，让元素插入的时候先排序，找极值就简单很多，但插入只有线性表现。

有没有插入和找极值，效率都不错的数据结构呢？

还可以用完全二叉树（complete binary tree），即 binary heap 除了最底层叶子节点之外，都是填满的。且叶子节点从左至右，不得有空隙。

![complete binary tree](./2023_7_28_basic_data_structures/complete_binary_tree.png)

### 实现

由于完全二叉树没有空隙，我们就可以用array来存储所有节点。将array的索引0保留，当完全二叉树的某个节点位于i，其左节点必位于2i，右节点位于2i+1。反过来推断，i的父节点，必位于`floor(i/2)`。

通过这个简单的规则，就可以用array实现出 complete binary tree。以array表述tree的方式，称之为隐式表示（implicit representation）

![complete binary tree array](./2023_7_28_basic_data_structures/complete_binary_tree_array.png)

一个array 和一组 heap 算法（插入、删除、取极值，将数据排列为 heap），就可以实现完全二叉树。然后通过完全二叉树实现heap。

heap可以分为 `max-heap` 和 `min-heap`，`max-heap`的最大值在根节点，每个节点的值大于或等于子节点。`min-heap`反之。

### push head 算法

新加入的元素，放到最下一层作为叶子节点，填补 array 从左至右的第一个空格，即在 array 的末尾。

为了满足 `max-heap` 条件，每个节点的值，大于或等于子节点的值。需要执行上溯程序：新节点的值大于父节点，就父子交换位置。一直上溯，直到不需要交换，或者到了跟节点。

``` cpp
// heap
// heap push 函数
template <class RandomAccessIterator, class Distance, class T>
inline void __push_heap(RandomAccessIterator first, Distance holdIndex,
                        Distance topIndex, T value) {
    Distance parent = (holdIndex - 1) / 2; // 找到父节点
    while (holdIndex > topIndex && *(first + parent) < value) {
        // 未到达顶端，且父节点小于新值（不符合heap次序）
        // 此处实现的为 max-heap，大者为父
        *(first + holdIndex) = *(first + parent); // 令洞值为父值
        holdIndex = parent; // percolate up，调整洞号，向上提升至父节点
        parent = (holdIndex - 1) / 2; // 新洞的父节点
    } // 持续至顶端，到满足 heap 次序为止
    *(first + holdIndex) = value; // 令洞为新值，完成插入操作
}

template <class RandomAccessIterator, class Distance, class T>
inline void __push_heap_aux(RandomAccessIterator first,
                            RandomAccessIterator last, Distance*, T*) {
    // 根据 implicit representation heap 的结构特性：新值必置于底部
    // 容器的最尾端，此即第一个洞号：(last - first) -1
    __push_heap(first, Distance((last - first) - 1),Distance(0),
                T(*(last - 1)));
}

template <class RandomAccessIterator>
inline void push_heap(RandomAccessIterator first,
                      RandomAccessIterator last) {
    // 注意，此函数调用时，新元素应已置于底部容器的最尾端
    __push_heap_aux(first, last, distance_type(first), value_type(first));
}
```

## log

- 2023/08/28 初稿
- 2023/08/29 heap 初稿
