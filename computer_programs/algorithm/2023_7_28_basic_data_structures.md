# 浅析基本数据结构

#### 2023/07/28

![ouline](./2023_7_28_basic_data_structures/basic_data_structures_outline.png)

> 容器，置物之所也。

> 研究特定的排列结构，以利于搜索或排序或其他目的，这一专门学科，称之为数据结构（Data Structure）。因此，几乎特定的数据结构，都是为了实现特定的算法。

> 根据数据在容器的排列特性，把数据结构分为序列式（sequence）和关联式（associate）两种。所谓序列式容器，其中元素都可排序（ordered），但未必有序（sored），如：array，vector，list等等。所谓关联式容器，主要有两大类，set集合和map映射表。每个元素有一个键值（key）和一个实值（value），容器内部（可能是BR-tree或hash-table），按照键值大小，以某种特定规则将这个元素放到适当位置。关联式容器内部结构一般是 balanced binary tree（平衡二叉树），以满足良好的搜索效率。

## C和lisp的两种基本容器：数据和列表

## vector

## list

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

### pop heap 算法

`max-heap`最大值，必然在根节点。pop取走根节点，实际是移走容器vector最后一个元素。为了满足 complete binary tree 条件【满树，且父节点必大于或等于子节点。此时不是满树】，必须将最下一层【叶子节点】的最右边的叶子节点拿掉【为什么是最右边的叶子节点呢？直接把根节点的子节点上移可以不？不行，因为这样不满足满树的要求。最容易满足满树要求，就是去最右边的叶子节点，填到根节点，但这样不满足顺序要求，就需要调整顺序】。接下来，把这个节点调整到适当位置即可。

调整算法：执行下溯（percolate down）程序，将根节点填入最右边的叶子节点，在将其和两个字节点比较，与较大子节点调整位置。依此，直到此叶子节点值大于左右两个子节点，或到达叶子节点为止。

注意：`pop_heap`之后，最大元素只是被置于容器最尾端，并未取走。如果要取值，需要执行容器（vector）的 `back()`操作函数，如果是移除，则需要执行 `pop_back()`操作函数。

``` cpp
// pop heap
template <class RandomAccessIterator, class Distance, class T>
inline void __adjust_heap(RandomAccessIterator first, Distance holdIndex,
                          Distance len, T value) {
    Distance topIndex = holdIndex;
    Distance secondChild = 2 * holdIndex + 2; // 洞节点之右子节点
    while (secondChild < len) {
        if (*(first + secondChild) < *(first + (secondChild - 1))) {
            // 比较洞节点之左右两个子值，然后以 secondChild 代表较大子节点
            secondChild--;
        }
        // Percolate down：令较大子值为洞值，再令洞号下移至较大子节点处
        *(first + holdIndex) = *(first + secondChild);
        holdIndex = secondChild;
        // 找出新洞节点的右子节点
        secondChild = 2 * (secondChild + 1);
    }
    if (secondChild == len) { // 没有右子节点，只有左子节点
        // Percolate down：令左子值为洞值，再令洞号下移至左子节点处
        *(first + holdIndex) = *(first + (secondChild - 1));
        holdIndex = secondChild - 1;
    }
    // 将欲调整值填入目前洞号里。注意，此时肯定满足次序特性
    // 侯捷说：下面这一句，可以改成： *(first + holdIndex) = value;
    __push_heap(first, holdIndex, topIndex, value);
}

template <class RandomAccessIterator, class T, class Distance>
inline void __pop_heap(RandomAccessIterator first,
                       RandomAccessIterator last,
                       RandomAccessIterator result,
                       T value, Distance*) {
    *result = *first; // 设定尾值为首值，于是尾值为欲求之结果
    // 稍后可以再以底层容器之 pop_back() 取出尾值
    // 以上欲重新调整 heap，洞号为0（即树根处），欲调整值为 value（原尾值）
    __adjust_heap(first, Distance(0), Distance(last - first), value);
}

template <class RandomAccessIterator, class T>
inline void __pop_heap_aux(RandomAccessIterator first,
                           RandomAccessIterator last, T*) {
    // 跟进 implicit representation heap 的次序，pop操作的结果
    // 应为容器底部的第一个元素。因此，首先设定欲调整值为尾值，然后将首值调至尾节点（所以以上迭代器result设为 last - 1）【更详细理解，见文章】
    // 然后重整 [first, last -1)，使之重新成为一个合格的 heap
    __pop_heap(first, last - 1, last - 1, T(*(last - 1)), distance_type(first));
}

template <class RandomAccessIterator>
inline void my_pop_heap(RandomAccessIterator first,
                     RandomAccessIterator last) {
    __pop_heap_aux(first, last, value_type(first));
}
```

### sort heap 堆排序

每次 `pop_heap` 可获得heap中最大元素，持续如此，每次操作，将范围向前缩减一个元素【注意，`pop_heap`会把最大值放到容器的最尾端，并没有移走，所以这里复用的同一个容器，不需要新增容器缓存值】，执行完毕，则就有一个递增序列【注意，这算法是倒着排序的，从尾部调整到头部，执行完毕，从头部看，就是一个递增的顺序】。

``` cpp
// sort heap 堆排序
template <class RandomAccessIterator>
void my_sort_heap(RandomAccessIterator first,
               RandomAccessIterator last) {
    // 每次执行 pop_heap，极值就被放在尾端。扣除尾端，再执行pop_heap，次极值又被放到尾端。依此，可得排序结果
    while (last - first > 1) {
        pop_heap(first, last--); // 每操作一次，pop_heap()一次，操作范围退缩一格【直接修改的原来的 array，不需要新增一个array】
    }
}
```

### make heap

将数据转换为heap。heap用的是隐式表达（implicit representation）的完全二叉树（complete binary tree）。

``` cpp

// make heap
template <class RandomAccessIterator, class T, class Distance>
void __make_heap(RandomAccessIterator first,
                 RandomAccessIterator last, T*, Distance*) {
    if (last - first < 2) return; // 长度为 0 或 1， 不必重新排列
    Distance len = last - first;
    // 找出第一个需要重排的子树头部，以 parent 标示出，由于任何叶子节点都不需执行 Percolate down，所以有以下计算
    Distance holeIndex = (len - 2) / 2;
    while (true) {
        // 重排以 holdIndex 为首的子树。len 是为了让__adjust_heap 判断操作范围
        __adjust_heap(first, holeIndex, len, T(*(first + holeIndex)));
        if (holeIndex == 0) return; // 走完根节点，就结束
        holeIndex--; // 即将重排之子树，头部向前一个节点
    }
}

template <class RandomAccessIterator>
inline void my_make_heap(RandomAccessIterator first,
                      RandomAccessIterator last) {
    __make_heap(first, last, value_type(first), distance_type(first));
}
```

### 测试 heap

``` cpp
#include <iostream>
#include "stl_algo.h"

int main() {
    int arr[9] = {0, 1, 2, 3, 4, 8, 9, 3, 5};
    std::vector<int> ivec(arr, arr + 9);

    my_make_heap(ivec.begin(), ivec.end());
    for (int i = 0; i < ivec.size(); ++i) {
        std::cout << ivec[i] << ' ';
    }
    std::cout << std::endl; // 9 5 8 3 4 0 2 3 1

    ivec.push_back(7);
    my_push_heap(ivec.begin(), ivec.end());
    for (int i = 0; i < ivec.size(); ++i) {
        std::cout << ivec[i] << ' ';
    }
    std::cout << std::endl; // 9 7 8 3 5 0 2 3 1 4

    my_pop_heap(ivec.begin(), ivec.end());
    std::cout << ivec.back() << std::endl; // 9
    ivec.pop_back();

    for(int i = 0; i < ivec.size(); ++i) {
        std::cout << ivec[i] << ' ';
    }
    std::cout << std::endl; // 8 7 4 3 5 0 2 3 1

    my_sort_heap(ivec.begin(), ivec.end());
    for (int i = 0; i < ivec.size(); ++i) {
        std::cout << ivec[i] << ' ';
    }
    std::cout << std::endl; // 0 1 2 3 3 4 5 7 8

    return 0;
}
```


## RB-tree 红黑树

## set

## map

## hashtable


## log

- 2023/08/28 初稿
- 2023/08/29 heap 初稿
- 2023/08/30 完成 heap 初稿。并列提纲
