---
layout: post
title:  Mathematics & Thinking(1)
category: 技术
tags: [Mathematics Thinking]
keywords: Mathematics
description:
---

##### Saturday, 28 November 2015

### Thinking in Mathematics

![Jobs](/../../assets/img/tech/2015/jobs_3.jpg)

> 从前的愚民政策是不许人民受教育，现代愚民政策是只许人民受某一种教育。不受教育的人，因为不识字，上人的当，受教育的人，因为识了字，上印刷品的当。--钱钟书

### 傅立叶变换原理

傅立叶变换是表示信号的函数，在正交的三角函数上的投影。

其实是信号的不同形式的表示。以声音而论，普通的形式是，按照时间记录声音的高低；而傅立叶变换会得到按照利率分布的形式；其实后者更常见，我们的乐谱就是记录音乐的频率，对于有规律的音乐而言，以频率来记录，更为简洁，演奏也方便。

用物理学中的速度与位移来类比。普通的记录物体位移的图像，是以位移时间作为坐标，每个时刻有对应的位移，我们要知道物体运动的特征，这个显然不明显。因为需要将位移对时间求导，才能得到物体的速度。也就是我们很难直观看出物体的运动速度。而速度时间作为坐标，每个时刻有对应的速度，我们就很明显的看出物体运动速度的变化，位移只需对时间积分即可。如果物体是匀速运动，用位移时间坐标系，其图像是一根斜线；用速度时间坐标系，其图像是一根平行于时间轴的直线。傅立叶变换相当与后者。

速度是位移对时间的微分，而傅立叶变换中，频率也是除以周期所得，两者的共同特征是，都是一个量与时间的比值。通过比值，可以得出在时间中的不变量，比如固定的频率，平均的速度。

### 不确定性原理

量子力学中有不确定性原理，是指动量与位置无法同时精确的确定。其实，从数学角度看，动量中速度有一个与时间相关的量，那么测定速度，一定是一段的时间的速度，一段位移的速度，无法说一个点上的速度。而物理上的最小尺度，就是普郎克常量。所以不确定性原理里面，一定会出现普郎克常量。

对于傅立叶变换，也有一个与之相关的不确定性原理。一个函数越“窄”，经傅立叶变换之后就会越“宽”。

> 一个长度为N的离散信号有a个非零数值，而他的傅立叶变换中有b个非零数值，那么a+b >= 2*N^(1/2)

即一个信号和他的傅立叶变换中的非零元素都不能太少。

### 离散傅立叶变换原理

### FFT算法实现关键

#### 蝴蝶变换
其基本的思想是，分治法使用时，每次分离奇数与偶数项，迭代至项数为一。提取偶数的过程，是从低位是否是0,到高位，每次迭代都移动一位即可。如果反过来看，其实就是一个排序的过程，只不过这个排序是低位的权重高于高位。所以把每项的二进制数对称翻转，即可把问题转化为一个排序问题。

#### 分治法根的处理
分治法把项目数减少为为原来的一半，而根的数目依旧是N，这个时候根就多次一半。其实单位根有对称性，而偶数次幂正好全是正数，相当与消去了对称的负数根。所以分治的条件得以成立。

#### 多项式的点值表示
点值表示，相当于直线方程中的两点定线。N次多项式，代入不同的N个点，得到N个值，这个点和值对即表示了多项式。事实上，这是把系数当作变量，而把原来的变量当作值，这样可以逆向求出系数。
为什么要变成点值表示呢？
因为系数表示的情况下，卷积的计算是N^2规模的，而点值表示便于处理。并且插值的时候，可以利用单位根的对称性，大大减少计算量。

### FFT具体实现

````c

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

struct C {
    double r, i;
    C() {}
    C(double _r, double _i) : r(_r), i(_i) {}
    inline C operator + (const C & a) const {
        return C(r + a.r, i + a.i);
    }
    inline C operator - (const C & a) const {
        return C(r - a.r, i - a.i);
    }
    inline C operator * (const C & a) const {
        return C(r*a.r - i*a.i, r*a.i + i*a.r);
    }
};

typedef long long LL;
const double pi = acos(-1.0);
const int N = 50005;
C a[N<<2], b[N<<2];
char num1[N], num2[N];
LL ret[N<<2];

void brc(C *y, int L) {
    int i, j, k;
    for (i=1,j=L>>1; i<L-1; ++i) { // 二进制平摊反转置换 O(NlogN)
        if (i < j) swap(y[i], y[j]);
        k = L>>1;
        while (j >= k) {
            j -= k;
            k >>= 1;
        }
        j += k;
    }
}

void FFT(C *y, int L, int dir) {
    brc(y, L);
    for (int h = 2; h <= L; h <<= 1) { // 枚举所需计算的点数 
        C wn(cos(dir*2*pi/h), sin(dir*2*pi/h)); // h次单位复根 
        for (int j = 0; j < L; j += h) { // 原序列被分成了L/h段h长序列 
            C w(1, 0); // 旋转因子 
            for (int k = j; k < j+h/2; ++k) { // 因为折半定理，只需要计算枚举一半的长度即可 
                C u = y[k];
                C t = w*y[k+h/2];
                y[k] = u + t;
                y[k+h/2] = u - t;
                w = w * wn; // 更新旋转因子 
            }
        }
    }
    if (dir == 1) {
        for (int i = 0; i < L; ++i) {
            y[i] = y[i] * C(1.0/L, 0);
        }
    }
}

int main() {
    while (scanf("%s %s", num1, num2) != EOF) {
        memset(ret, 0, sizeof (ret));
        int len1 = strlen(num1), len2 = strlen(num2);
        int ML = len1+len2-1, L = 1;
        while (L < ML) L <<= 1;
        for (int i = len1-1, j = 0; i >= 0; --i, ++j) {
            a[j] = C(num1[i]-'0', 0);
        }
        for (int i = len2-1, j = 0; i >= 0; --i, ++j) {
            b[j] = C(num2[i]-'0', 0);
        }
        for (int i = len1; i < L; ++i) a[i] = C(0, 0);
        for (int i = len2; i < L; ++i) b[i] = C(0, 0);
        FFT(a, L, -1), FFT(b, L, -1);
        for (int i = 0; i < L; ++i) {
            a[i] = a[i] * b[i];
        }
        FFT(a, L, 1);
        for (int i = 0; i < L; ++i) {
            ret[i] = (LL)floor(a[i].r + 0.5);
        }
        for (int i = 0; i < L; ++i) {
            ret[i+1] += ret[i] / 10;
            ret[i] %= 10;
        }
        int p = L;
        while (!ret[p] && p) --p;
        while (p >= 0) printf("%d", (int)ret[p--]);
        puts("");
    }
    return 0;
} 
````


### `C++`编译

````shell

g++ -o my_program my_program.cpp

````


### 参考资料:

《算法导论》

《算法的乐趣》王晓华

《Principles and Practice Using C++》 Bjarne Stroustrup

[傅里叶变换：MP3、JPEG和Siri背后的数学](http://blog.jobbole.com/51301/)

[快速傅里叶变换](http://open.163.com/movie/2008/2/A/L/M7Q4BLENR_M7QDNTVAL.html)

[复数矩阵和快速傅里叶变换](http://open.163.com/movie/2010/11/7/7/M6V0BQC4M_M6V2B4U77.html)


[dft](http://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html#dft)

[OpenCV实现基于傅里叶变换的旋转文本校正](http://johnhany.net/2013/11/dft-based-text-rotation-correction/)

[The Discrete Fourier Transform](http://arachnoid.com/signal_processing/dft.html)

[快速傅里叶变换](https://zh.wikipedia.org/wiki/%E5%BF%AB%E9%80%9F%E5%82%85%E9%87%8C%E5%8F%B6%E5%8F%98%E6%8D%A2)

[快速傅里叶变换 易懂版](https://www.zybuluo.com/397915842/note/37965)

[Fast Fourier Transform ](http://picks.logdown.com/posts/177631-fast-fourier-transform)

[从多项式乘法到快速傅里叶变换](http://blog.miskcoo.com/2015/04/polynomial-multiplication-and-fast-fourier-transform)


[FFT-快速傅立叶变换](http://www.cnblogs.com/Lyush/p/3219605.html)

[A * B Problem Plus](http://acm.hdu.edu.cn/showproblem.php?pid=1402)

[不确定性原理的前世今生 · 数学篇（完）](http://songshuhui.net/archives/50550)

hid say: 简化。



