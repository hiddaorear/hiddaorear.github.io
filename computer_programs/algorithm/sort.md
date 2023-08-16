# 浅析排序算法

##  排序算法谱系

![排序算法谱系](./sort/sort.outline.jpg)

## 朴素排序算法

### 冒泡排序

``` cpp

#include <iostream>
using namespace std;
template<typename T>
void bubble_sort(T arr[], int len) {
    int i, j;
    for (i = 0; i < len -1; i++) {
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

## 阅读资料

- [打造 Go 语言最快的排序算法](https://blog.csdn.net/ByteDanceTech/article/details/124464192)

## log

- 2023/8/16  初稿
