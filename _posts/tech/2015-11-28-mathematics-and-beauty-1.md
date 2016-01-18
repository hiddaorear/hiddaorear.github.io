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



### 不确定性原理

### 离散傅立叶变换原理

### FFT算法实现关键

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

hid say: 简化。



