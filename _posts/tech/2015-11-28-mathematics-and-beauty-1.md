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
函数在三角函数空间的投影。

### 不确定性原理

### 离散傅立叶变换原理

### FFT算法实现关键

### FFT具体实现

````c

#include<cmath>
#include<cstdio>
#include<cstring>

const int MAXN = 2e5 + 5;
const double PI = acos(-1.0);
#define max(a, b) (a) > (b) ? (a) : (b);

class Complex
{
public:
  double real, imag;

  Complex(double real = 0.0, double imag = 0.0)
  {
    this->real = real, this->imag = imag;
  }

  Complex operator - (const Complex &elem) const
  {
    return Complex(this->real - elem.real, this->imag - elem.imag);
  }

  Complex operator + (const Complex &elem) const
  {
    return Complex(this->real + elem.real, this->imag + elem.imag);
  }

  Complex operator * (const Complex &elem) const
  {
    return Complex(this->real * elem.real - this->imag * elem.imag, this->eal * elem.imag + this->imag * elem.real);
  }

  void setValue(double real=0.0, double imag = 0.0)
  {
    this->real = real, this->imag = imag;
  }
}

Complex A[MAXN], B[MAXN];
int res[MAXN], len, mlen, len1, len2;
char str1[MAXN >> 1], str2[MAXN >> 1];

void Swap(Complex &a, Complex &b)
{
  Complex tmp = a;
  a = b;
  b = tmp;
}

void Prepare()
{
  len1 = strlen(str1), len2 = strlen(str2);
  mlen = max(len1, len2);
  len = 1;

  while(len < (mlen << 1))
    len <<= 1;

  // 初始化多项式序数
  for(int i = 0; i < len1; ++ i)
    A[i].setValue(str1[str1[len1 - i - 1] - '0', 0]);

  for(int i = 0; i < len2; ++ i)
    B[i].setValue(str2[len2 - i - 1] - '0', 0);

  // 补0
  for (int i = len1; i < len; ++ i)
    A[i].setValue();

  for (int i = len2; i < len; ++ i)
    B[i].setValue();
}
````



### 参考资料:
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

hid say: 简化。



