# 浅析排序算法

##  排序算法谱系

![排序算法谱系](./sort/sort.outline.jpg)

## 朴素排序算法

### 冒泡排序

![bubble](./sort/bubble_sort.png)

冒泡排序比较原始，不断调整相邻元素的顺序来排序。算法得名于，大的元素会经过交换，慢慢像泡泡一样“浮”到数列的顶端。
冒泡排序的比较和移动操作，都很多，是很慢的排序算法。


C++ 冒泡排序：
``` cpp

#include <iostream>
using namespace std;
template<typename T>
void bubble_sort(T arr[], int len) {
    int i, j;
    for (i = 0; i < len - 1; i++) {
        for (j = 0; j < len - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    int arr[] = {19, 93, 3, 25};
    int len = (int) sizeof(arr) / sizeof(*arr);
    bubble_sort(arr, len);
    for (int i = 0; i < len; i++) {
        cout << arr[i] << ' ';
    }
    cout << endl;
    return 0;
}

```

### 选择排序

![selection_sort](./sort/selection_sort.png)

选择排序就是不断选出，剩下元素中的最值，来实现排序。选择排序的数据移动是精准操作，比冒泡排序好。

C++ 选择排序：

``` cpp

#include <iostream>
using namespace std;

template<typename T>
void selection_sort(T arr[], int len) {
    int i, j;
    for (i = 0; i < len - 1; i++) {
        int min = i;
        for (j = i; j < len - 1; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        if (min != i) {
            swap(arr[min], arr[i]);
        }
    }
}

int main(int argc, const char * argv[]) {
    int arr[] = {19, 93, 3, 25};
    int len = (int) sizeof(arr) / sizeof(*arr);
    selection_sort(arr, len);
    for (int i = 0; i < len; i++) {
        cout << arr[i] << ' ';
    }
    cout << endl;
    return 0;
}


```

### 插入排序

![insertion](./sort/insertion_sort.png)

新元素在已排序的列里，找到合适的位置插入。插入的位置，可以通过二分查找优化，插入排序的比较次数，远小于冒泡排序和选择排序。数据移动次数，也占优。不过顺序数据移动的开销，远不及比较操作。朴素排序算法中，插入排序，一般最快。

C++ 插入排序：

``` cpp
#include <iostream>
using namespace std;

template<typename T>
void insertion_sort(T arr[], int len) {
    int i, j;
    T key;
    // 从1开始，因为下标0默认是有序列的开始
    for (i = 1; i < len; i++) {
        // 记录要插入的元素
        key = arr[i];
        // 从已经排序的最右边开始比较，找到比其小的元素
        j = i;
        while (j > 0 && key < arr[j - 1]) {
            arr[j] = arr[j - 1];
            j--;
        }
        // 存在比其小的元素，插入
        if (j != i) {
            arr[j] = key;
        }
    }
}

int main(int argc, const char * argv[]) {
    int arr[] = {19, 93, 3, 25};
    int len = (int) sizeof(arr) / sizeof(*arr);
    insertion_sort(arr, len);
    for (int i = 0; i < len; i++) {
        cout << arr[i] << ' ';
    }
    cout << endl;
    return 0;
}

```

#### 折半插入排序

插入排序还可以通过二分查找算法优化性能。但基本思想和插入排序一样，仅对时间复杂度中的常数优化。

``` cpp
void insertion_sort(int arr[], int len) {
    if (len < 2) return;
    for (int i = 1; i != len; i++) {
        int key = arr[i];
		// 指定范围内查找大于目标值的第一个元素
        auto index = upper_bound(arr, arr + i, key) - arr;
        // 使用 memmove 移动元素，比使用 for 循环速度更快，时间复杂度仍为 O(n)
        memmove(arr + index + 1, arr + index, (i - index) * sizeof(int));
        arr[index] = key;
    }
}

```

## 高级排序算法

### 快速排序

![quick sort](./sort/quick_sort.png)

快速排序可以理解为一种批量的冒泡排序。每一个元素的浮沉，不再取决于相邻元素的比较，而是取决于中枢元素的比较，且每次沉浮不再是一个身位，而是直接到达上下半区。快速排序通常很快。

### 堆排序

### 归并排序


## 常见工业排序算法

### Dual-Pivot Quicksort（双枢三分快排）

### BlockQuicksort

### Pattern-defeating Quicksort

## 阅读资料

- [打造 Go 语言最快的排序算法](https://blog.csdn.net/ByteDanceTech/article/details/124464192)

## log

- 2023/8/16  初稿
