# 深入浅出 Shor's Algorithm

## Shor's Algorithm 和量子计算机简介

秀尔算法（Shor's Algorithm）是数学家彼得·秀尔（Peter Williston Shor）在1994年发现的算法，又称量子质因数分解算法。这个算法在量子计算机领域很重要。1982年，诺贝尔物理学奖得主费曼在演讲《用计算机模拟物理》（Simulating Physics with Computers）提出经典计算机无法高效模拟量子系统。12年后，秀尔提出能在多项式时间内分解大整数（RSA加密的基础），远超传统计算机的能力，引发量子计算研究的热潮。秀尔因此获得了理论计算机科学成就的最高奖——内万林纳奖（Nevanlinna Prize）。秀尔算法的影响深远，时至今日，说起量子计算机的进展，常见到秀尔算法的实现，支持能把 15 分解为 $5 \times 3$ 之类的叙述（2001 年IBM的量子计算机）。

量子力学是科幻作品中的常客，刘慈欣先生的《球状闪电》中，很生动描述的量子力学的哥本哈根诠释。量子力学中还有名鼎鼎的物理学四大神兽之一，薛定谔的猫。其他三只是拉普拉斯兽，麦克斯韦妖，芝诺的乌龟。薛定谔的猫让人疑惑的问题是量子力学的量子态的叠加。

设死猫的量子态:
$$
|0\rangle
$$

活猫的量子态:
$$
|1\rangle
$$

箱子中的猫就是这两个量子态的叠加：

$$
\alpha|0\rangle + \beta|1\rangle
$$

其中 $\alpha$ 和 $\beta$ 是概率幅，可以是正数、负数、复数。Shor 算法中量子傅立叶变换就跟概率幅可以为负数相关，可以放大我们想要的量子态的概率幅，从而测量的时候有更高的概率获取到我们想要的结果。去测量猫是死还是活的时候，结果是死猫 $\|0\rangle$ 概率是 $\alpha^2$，同理活猫的概率是 $\beta^2$。薛定谔的猫不生不死，就是叠加态。在传统计算机中，1 比特要么是高电平 1，要么是低电平 0，一个比特的值是确定的。量子计算机中比特既可以是 0，也可以 1，二者叠加在一起。考察这个存储上的特点，在 L 个比特上，量子计算机可以同时表达 $2^L$ 个数，而传统计算机只能表达 1 个数，量子计算机是传统计算机的  $2^L$ 倍。

除了存储，还有计算操作上的不同。传统计算机中通过门电路计算。量子计算机是幺正变换，实现量子门。例如 Hadamard 变换实现单比特的 H 门，是一个幺正矩阵：

$$
\frac{1}{\sqrt{2}} \begin{bmatrix}1&1\\1&-1\\ \end{bmatrix}
$$

H 门的作用，把一个量子比特转换为 $\|0\rangle$ 和 $\|1\rangle$ 的叠加态。

$$
|0\rangle \to \frac{1}{\sqrt{2}} \left( |0\rangle + |1\rangle \right)
$$

$$
|1\rangle \to \frac{1}{\sqrt{2}} \left( |0\rangle - |1\rangle \right)
$$

H 变换的逆矩阵是他自身。即： $H*H = I$。那么在量子计算机里面，连续做两次变换，就相当于没有做变换，会把量子比特变会原来的样子，也就是量子计算是可逆的。这与传统计算机迥然不同。

当有 L个比特，表示的 $ 2^L $ 个数据，在量子门中一次就操作完成了。在传统计算机中分别对 $ 2^L $ 个数据处理，则需要  $ 2^L $ 次操作。忽略量子门和传统电路计算速度的差异，量子计算机相对传统计算机，相当于做了 $ 2^L $ 加速。效果很像传统计算机中的并行计算，并非严格意义上并行计算。

量子之间可以叠加，还可以纠缠。当2个电子纠缠在一起，一个电子自旋向上，另一个电子自旋向下。此时，测量一个电子自旋，若为向上，另一个电子必然会向下，反之亦然。即使两个电子之间隔着一个银河系也是如此。量子纠缠有大名鼎鼎的贝尔不等式实验证明。刘慈欣先生的《三体》中智子，与三体人的通信，设定上是通过量子纠缠实现。

综上所述，量子计算的计算是可逆的。量子态可以叠加，也可以纠缠在一起。利用量子的这些特性，可以实现相对于传统计算机的性能，有指数级的提升。

___

## Shor's Algorithm 例子

使用 Shor's Algorithm 算法来分解 N：15。步骤如下：

- 先选一个小于 15 的整数，如 a：2；
- 计算  $2^r \mod 15$ ;

  | 指数 $r$    | $2^r$         | $2^r \mod 15$   |
  |------------|---------------|------------------|
  | *0*        | 1             | *1*              |
  | 1          | 2             | 2                |
  | 2          | 4             | 4                |
  | 3          | 8             | 8                |
  | *4*        | 16            | *1*              |
  | 5          | 32            | 2                |
  | 6          | 64            | 4                |
  | 7          | 128           | 8                |
  | *8*        | 256           | *1*              |
  | 9          | 512           | 2                |
  | 10         | 1024          | 4                |
  | 11         | 2048          | 8                |

- 考察一下  $2^r \mod 15$ 的结果，以 4 为周期循环出现：$1 \to 2 \to 4 \to 8$，以此重复，周期 r 等于 4;
- 通过周期 r 来分解 15:

$$
2^r \equiv 1 (\mod 15) \\
2^r - 1 \equiv 0 (\mod 15) \\
(2^{r/2} + 1)(2^{r/2} - 1) \equiv 0 (\mod 15)
$$

$(2^{r/2} + 1)(2^{r/2} - 1)$中，$2^{r/2} + 1 $ 或者 $2^{r/2} - 1$ 是 15 的质因数。这里得到了 15 的分解结果： $5 \times 3$。

在这个例子中，$2^r \mod 15$ 是否一定就是周期性呢？答案是肯定的。数论中的欧拉定理：

> 若 n，a 为正整数，且n和a互素（$gcd(a,n) = 1$），则 $a^{\phi(n)} \equiv 1 (\mod p) $。

即 $a^{\phi(n)} $ 与 1 在模 n 下同余。$\phi(n)$ 为欧拉函数，是小于 n 的正整数中，与 n 互质的数的数目。当 n 是质数的时候，$phi(n)$ 的值为 $p - 1$，欧拉定理就变为费马小定理：$a^{n - 1} \equiv 1 (\mod n)$

所举的例子是简单的情况。遇到 r 是奇数，则需要重新计算。遇到 $a^{p - 1} \equiv 1 (\mod k \times n) $，其中 k 为正整数，则需要 $gcd(a^{r/2} + 1,k \times n)$ 或 $gcd(a^{r/2} - 1,k \times n)$。这样我们就把分解合数 N，转换化求周期 r。


## Shor's Algorithm 的实现

### 计算流程简述

#### 1. 制造等概率叠加态，操作寄存器1: register1
用 H 门制作正整数 N 的长度为 L 的处于叠加态的量子比特，存入寄存器 register1 中；

#### 2. 求模，制造纠缠态，操作寄存器2: register2
用 register1 中的值计算 $a^x \mod N$ ，并使二者纠缠，存入寄存器 register2 中；

以 $2^r \mod 15$ 为例子，经过1和2，此时得到如下结果：

  | 指数 $r$   |register1：$2^r$|register2：$2^r \mod 15$|
  |------------|---------------|------------------|
  | *0*        | 1             | *1*              |
  | 1          | 2             | 2                |
  | 2          | 4             | 4                |
  | 3          | 8             | 8                |
  | *4*        | 16            | *1*              |
  | 5          | 32            | 2                |
  | 6          | 64            | 4                |
  | 7          | 128           | 8                |
  | *8*        | 256           | *1*              |
  | 9          | 512           | 2                |
  | 10         | 1024          | 4                |
  | 11         | 2048          | 8                |

  由数论中的欧拉定理，寄存器 register2 中的值，会以 r 为周期重复出现；为了简化问题的论述，假设 $r \mod L = 0$;若 r 不为偶数，则重新选择 a 计算；

#### 3. 量子傅立叶变换

周期 r 在 register2 中，我们需要设法获取周期 r 的值，利用 $(a^{r/2} + 1)(a^{r/2} - 1) \equiv 0 (\mod N)$，求得 N 的因数。我们的重心是周期 r， $a^x \mod N$ 的具体值并不重要，由于每次测量只能获取一个值，我们也无法通过直接测量值来计算周期。

为了获取周期，考虑使用量子傅立叶变换，获取频率ν，从而取得周期 $r = 1 / ν$。这里的量子傅立叶变换的效果，相当于光栅。光通过光栅以后，因光的干涉，会形成明暗相间的条纹，相长干涉产生明条纹，相消干涉产生暗条纹。含周期的量子态经过量子傅立叶变换，也会出现相长相消。

为了使量子傅立叶变换更好处理，我们可以只用保留周期 r 中的某一个值，把其他值变为0，这一操作不影响最终结果，却使得计算和测量更好处理。对 register2 进行一次测量以后，得到一个值 γ。因为 register1 与 register2 纠缠，register1 中的量子也坍缩，剩下与 γ 相关的量子态；

假设 register2 测量的所得值为 1，此时两个寄存器量子态如下：

  | 指数 $r$   |register1：$2^r$|register2：$2^r \mod 15$|
  |------------|---------------|------------------|
  | *0*        | 1             | *1*              |
  | 1          | 0             | 0                |
  | 2          | 0             | 0                |
  | 3          | 0             | 0                |
  | *4*        | 16            | *1*              |
  | 5          | 0             | 0                |
  | 6          | 0             | 0                |
  | 7          | 0             | 0                |
  | *8*        | 256           | *1*              |
  | 9          | 0             | 0                |
  | 10         | 0             | 0                |
  | 11         | 0             | 0                |

#### 4. 测量，并计算周期 r

周期 r 依然隐含在量子态中。此时进行量子傅立叶变换 QFT，与周期不相关的量子态的概率幅会相消，与周期相关的量子态概率幅会增加（概率幅的平方即概率）。

叠加态经过 QFT 后，只有在 $2^L/k$ 的整数倍的位置不为0，其他元素均为 0。对这一叠加的量子态采样（一次采样，即一次测量），得到值是 $2^L/k$ 倍数，设值为 γ 。下文" Shor 算法求周期 r"部分会给出详细的计算过程。

$$
  γ = k2^L/r
$$

周期 r 为：

$$
  r = k2^L/γ
$$

进一步处理即可求得周期。这里也有小概率会失败，就需要重新计算。下文会给出成功的概率 p，概率 p 与 L 正相关，L 越大，概率越高。

___

### Shor 算法求周期 r

#### 成功的概率

假设有 k 个互相独立的样本均匀分布：

$$
0,M/k,2M/k,...,(k-1)M/k
$$

则采用中获取到这些样本的最大公因数是 $M/k$ 的概率至少为 $1 - k/2^k$ 。

考虑最大公因数不是 $M/k$ 的情况。

所有的采样的值是 $jM/k$，其中 $j >= 2$，采样获取这一值的概率 p 最多是：$1/j$。

因 $j >= 2$，则这一概率 $p <= 1/2$。有最多有 k 种可能，计算乘积，即：$p^k <= (1/2)^k$。

以上考虑的是特定的数字 j。这种情况最多是对 j 取不同的值求和。j最多有 k 个值，则总概率：$kp^k <= k(1/2)^k$。

则采样的样本是最大公因数不是 $M/k$ 的概率是：$1 -  k(1/2)^k$。

k 为周期个数，数目越大，则测量获取最大公因数是 $M/k$ 的概率越大。

设量子比特的数目为 L，共可以表示 $2^L$ 个值。为了保证最后测量获取正确的值的概率够大，需要保证 $2^L$ 长度内有足够的周期数 k。设要分解的合数为 N，则需要满足：

$$
 N^2 \leq 2^L \leq 2N^2
$$

#### 制造量子态

利用 H 门制作等概率的量子叠加态 $\|x\rangle$ 存入寄存器 register1。

设函数 $f(x) = a^x(mod N)$ ，利用受控 U 门构造 $\|f(x)\rangle$，存入寄存器 register2，并使之与寄存器 register1 中量子态纠缠。两个寄存器中的量子态如下：

$$
\begin{cases}
\mathinner{|\Phi_1 \rangle}=\frac{1}{\sqrt{2^L}}\sum_{x=0}^{2^L-1} \mathinner{|x \rangle}&register1\\

\mathinner{|\Phi_2 \rangle}=\frac{1}{\sqrt{2^L}}\sum_{x=0}^{2^L-1} \mathinner{|x \rangle} \mathinner{|a^x(mod\;N) \rangle}&register1\oplus register2\\
\end{cases}\\
$$

通过欧拉定理可知，$f(x)$ 为周期函数，设周日为 r，A 为周期数，总长度为 $2^L$，则：

$$
  A = 2^L/r
$$

设 l 为第一个周期内（序号值小于周期 r）, 在第 b 个周期中的 $\|x\rangle$ 可表示为：

$$
 |x\rangle = | l +  br\rangle
$$

因此，寄存器 register1 的 量子态 $\|\Phi_1 \rangle$ 可表示为：

$$
|\Phi_1\rangle = |l\rangle + |l+r\rangle + |l+2r\rangle + ... + |l+(A - 1)r\rangle
$$

寄存器 register2的 量子态 $\|\Phi_2 \rangle$ 可表示为：

$$
|\Phi_2\rangle = |l\rangle|f(l)\rangle + |l+r\rangle|f(l + r)\rangle + |l+2r\rangle|f(l + 2r)\rangle + ... + |l+(A - 1)r\rangle|f(l + (A - 1)r)\rangle
$$

#### 第一次测量寄存器 register2

对寄存器 register2 进行计算基上的测量，则量子态坍缩为周期值的一个值，因寄存器 register1 中的量子态与之纠缠，其中的量子态变为：

$$
\begin{align}
  \mathinner{
    |\Phi_1 \rangle}&=\frac{1}{\sqrt{A}}\sum_{j=0}^{A-1} \mathinner{|l + jr \rangle}\tag{1}\\
                    &=\frac{1}{\sqrt{\frac{2^L}{r}}}\sum_{j=0}^{\frac{2^L}{r}-1} \mathinner{|l + jr\rangle
  }
\end{align}\\
$$

___

#### 量子傅立叶变换 QFT

对寄存器 register1 中的量子态进行QFT：

$$
QFT(\mathinner{|l + jr \rangle})=\frac{1}{\sqrt{2^L}}\sum_{\gamma=0}^{2^L-1}e^{2\pi i(l + jr)\gamma/2^L}\mathinner{|\gamma \rangle}
$$

因寄存器 register2 中的量子态与之纠缠，则量子态变为：
$$
QFT(\mathinner{|\Phi_{2} \rangle})=\frac{1}{\sqrt{A}}\sum_{j=0}^{A - 1}QFT(\mathinner{|jr+l \rangle})\\
$$

因对寄存器 register1 做过一次测量，求和从 $2^L-1$ 变为 $A - 1$，其中 A 为周期数。

将 $QFT(\mathinner{\|l + jr \rangle})$ 代入，并交换求和顺序：

$$
\begin{align}
  QFT(\mathinner{|\Phi_{2} \rangle}) &= \frac{1}{\sqrt{A}}\sum_{j=0}^{A-1}[\frac{1}{\sqrt{2^L}}\sum_{\gamma=0}^{2^L-1}e^{2\pi i(l + jr)\gamma/2^L}]\mathinner{|\gamma \rangle}\\
                                     &=\sum_{\gamma=0}^{2^L-1}[\frac{\sqrt{r}}{2^L}\sum_{j=0}^{A-1}e^{2\pi i(l + jr)\gamma/2^L}]\mathinner{|\gamma \rangle}
\end{align}\\

$$

因寄存器 register2 做过一次测量，量子态坍缩为 r 个值中的一个值，每一个值对应于寄存器 register1 中 A 个叠加态，设上式中括号里面的为：

$$
\begin{align}
 C_\gamma &=\frac{\sqrt{r}}{2^L}\sum_{j=0}^{A-1}e^{2\pi i(jr+l)\gamma/2^L}\\
          &=\frac{\sqrt{r}}{2^L}e^{2\pi il\gamma/2^L}[\sum_{j=0}^{A-1}e^{2\pi ijr\gamma/2^L}]\\
\end{align}\\
$$

 此时存在2中情况：

 1. $2^L \mod r = 0$，即 $2^L$ 能够整除周期 r 的情况。说明每一个波峰刚好在 $ γ = k2^L/r $；
 2.  $2^L \mod r \neq 0$，即 $2^L$ 不能够整除周期 r 的情况；说明值非常接近播放，此时需要加入微调参数；本文不分析这种情况；

 当 $2^L \mod r = 0$ 时，在(5)式中，$A = 2^L/r$，只有 γ 是 $ 2^L/r$ 整数倍时，出现相长干涉，其他的为相消干涉，值趋近为0，有：

$$
C_\gamma=\begin{cases}
  \frac{1}{\sqrt{r}}e^{2\pi il\gamma/2^L}&\gamma=k2^L/r\\
  0&\gamma\ne k2^L/r\\
\end{cases}\\
$$

计算 $C_\gamma$ 这个等比数列：

$$
\begin{align}
C_\gamma &=\frac{\sqrt{r}}{2^L}e^{2\pi il\gamma/2^L}[\sum_{j=0}^{A-1}e^{2\pi ijr\gamma/2^L}]\\
         &=\frac{\sqrt{r}}{2^L}e^{2\pi il\gamma/2^L}[\frac{e^{2\pi iAr\gamma/2^L}-1}{e^{2\pi ir\gamma/2^L}-1}]\\
\end{align}\\
$$

代入 $A = 2^L/r$ 得：

$$
C_\gamma=\frac{\sqrt{r}}{2^L}e^{2\pi il\gamma/2^L}[\frac{e^{2\pi i\gamma}-1}{e^{2\pi ir\gamma/2^L}-1}]\\
$$

由于 $e^{2\pi ir\gamma/2^L}-1 = 0$，也就是 $\gamma\ne k2^L/r$ 时，值为0.

将这一结果，代入可得：

$$
\mathinner{|\Phi_{n} \rangle}=\frac{1}{\sqrt{r}}\sum_{k=0}^{r-1}e^{2\pi ik/r}\mathinner{|\frac{k2^L}{r} \rangle}\\
\rho(\mathinner{|\Phi_{n} \rangle})=|\frac{1}{\sqrt{r}}|^2=\frac{1}{r}
$$

测量 $\gamma\rangle$ 值，会等概率 $1/r$ 的选择一个态，由 $\gamma=k2^L/r$ 可得：

$$
\frac{\gamma}{2^L}=\frac{k}{r}\\
$$

如果有 $gcd(k, r) = 1$，r 就可以从 $\frac{k}{r}$ 的不可约分数求得。


##  Shor's Algorithm 背后的数学物理

### 量子的叠加态和纠缠态

#### 叠加态 (Superposition State)
叠加态是指单个量子系统可以同时处于多个基态的线性组合状态。数学表示为：
$$ |\psi\rangle = \alpha|0\rangle + \beta|1\rangle $$
其中：
- $ \|0\rangle $ 和 $ \|1\rangle $ 是计算基态
- $\alpha$ 和 $\beta$ 是复数概率幅，满足 $ \|\alpha\|^2 + \|\beta\|^2 = 1 $

#### 纠缠态 (Entangled State)
纠缠态是指两个或多个量子系统之间存在非局域关联的状态，数学表示为：
$$ |\Psi\rangle = \frac{1}{\sqrt{2}}(|00\rangle + |11\rangle) $$

#### 叠加态例子
单个量子系统，如：电子自旋处于自旋向上和自旋向下的叠加态。

$$ |\psi\rangle = \frac{1}{\sqrt{2}}(|\uparrow\rangle + |\downarrow\rangle) $$

测量时有50%概率得到 $|↑\rangle$，50%概率得到 $|↓\rangle$
测量后状态坍缩到其中一个本征态。

#### 纠缠态例子（Bell不等式）

$$ |\Phi^+\rangle = \frac{1}{\sqrt{2}}(|00\rangle + |11\rangle) $$

特点：
1. 测量第一个量子比特为 $\|0\rangle$ 时，第二个必定为 $\|0\rangle$
2. 测量第一个为 $\|1\rangle$ 时，第二个必定为 $\|1\rangle$
3. 关联性不受空间距离限制

---

### 欧拉定理
#### 定理陈述
设 $ n $ 为正整数，$ a $ 为整数且满足 $ \gcd(a, n) = 1 $，则：
$$ a^{\phi(n)} \equiv 1 \pmod{n} $$
其中，$ \phi(n) $ 是欧拉函数，表示 $ 1 \leq k \leq n $ 中与 $ n $ 互质的整数 $ k $ 的个数。

#### 证明过程
##### Step 1：构造简化剩余系
设 $ r_1, r_2, \dots, r_{\phi(n)} $ 是所有小于 $ n $ 且与 $ n $ 互质的正整数。这些数构成模 $ n $ 的**简化剩余系**，即：
$$ \gcd(r_i, n) = 1, \quad 1 \leq r_i < n, \quad i = 1, 2, \dots, \phi(n). $$

##### Step 2：考察 $ a \cdot r_i $ 的性质
由于 $ \gcd(a, n) = 1 $，且 $ \gcd(r_i, n) = 1 $，故：
$$ \gcd(a \cdot r_i, n) = 1. $$
因此，$ a \cdot r_i \mod n $ 仍然与 $ n $ 互质，且落在 $ 1 $ 到 $ n-1 $ 之间。

##### Step 3：证明 $ \{a \cdot r_i \mod n\} $ 是 $ \{r_i\} $ 的排列
假设存在 $ i \neq j $ 使得：
$$ a \cdot r_i \equiv a \cdot r_j \pmod{n}. $$
由于 $ \gcd(a, n) = 1 $，可两边约去 $ a $ 得：
$$ r_i \equiv r_j \pmod{n}. $$
但 $ r_i $ 和 $ r_j $ 是简化剩余系中不同的元素，矛盾。因此：
$$ \{a \cdot r_1 \mod n, a \cdot r_2 \mod n, \dots, a \cdot r_{\phi(n)} \mod n\} = \{r_1, r_2, \dots, r_{\phi(n)}\}. $$

##### Step 4：乘积相等性
将两组数分别相乘：
$$ \prod_{i=1}^{\phi(n)} (a \cdot r_i) \equiv \prod_{i=1}^{\phi(n)} r_i \pmod{n}. $$
左边提取 $ a^{\phi(n)} $：
$$ a^{\phi(n)} \cdot \prod_{i=1}^{\phi(n)} r_i \equiv \prod_{i=1}^{\phi(n)} r_i \pmod{n}. $$

##### Step 5：约去 $ \prod r_i $
由于 $ \gcd\left(\prod r_i, n\right) = 1 $，存在逆元，故两边可约去 $ \prod r_i $：
$$ a^{\phi(n)} \equiv 1 \pmod{n}. $$

### 例子验证
**问题**：验证 $ n = 10 $, $ a = 3 $ 满足欧拉定理。
**解**：
1. $ \phi(10) = 4 $（因 $ 1, 3, 7, 9 $ 与 10 互质）。
2. 计算 $ 3^4 \mod 10 $:
   $$ 3^4 = 81 \equiv 1 \pmod{10}. $$
   结果与定理一致。


### 附录：欧拉函数计算公式
若 $ n $ 的质因数分解为 $ n = p_1^{k_1} p_2^{k_2} \cdots p_m^{k_m} $，则：
$$ \phi(n) = n \prod_{i=1}^m \left(1 - \frac{1}{p_i}\right). $$

**示例**：
- $ n = 12 = 2^2 \times 3 $，则：
  $$ \phi(12) = 12 \left(1 - \frac{1}{2}\right)\left(1 - \frac{1}{3}\right) = 4. $$

---

### 傅立叶变换
- 评价
- 多项式乘法
- 逆变换

---

### 酉空间

- 傅立叶变换的广泛性（薛定谔方程、热传导）
- 为什么可逆

- [如果把傅里叶变换突然一键删除，世界上会发生什么变化？](https://www.zhihu.com/question/13671804165/answer/1888868718425134475)

---

## golang的errors

学数学是学思想。TODO

对于一门编程语言，多关注编程语言的特性。不同编程语言的语法不同，但不同的语法可能都需要表达一种编程所需的特性。

考察一下golang中很有争议的errors，典型代码如下：

```go
if err != nil {
        return err
}
```

更具体的例子，当具有多个 error 的情况下：

```go
fd, err := os.OpenFile(filePath, os.O_RDWR|os.O_CREATE, 0644)
if err != nil {
  fmt.Printf("无法打开文件: %v\n", err)
  return
}
defer func() {
  // 确保在函数结束时关闭文件
  if err := fd.Close(); err != nil {
    fmt.Printf("关闭文件时出错: %v\n", err)
  }
}()

_, err = fd.Write(p0[a:b])
if err != nil {
    return err
}
_, err = fd.Write(p1[c:d])
if err != nil {
    return err
}
_, err = fd.Write(p2[e:f])
if err != nil {
    return err
}
// and so on
```

上述代码中，有重复的 err 赋值，重复的 `err != nil ` 检查。把重复的 err 放到 struct 中，并提供`err != nil `检测方法， 代码可以优化成：

```go
type errWriter struct {
    w   io.Writer
    err error
}

func (ew *errWriter) write(buf []byte) {
    if ew.err != nil {
        return
    }
    _, ew.err = ew.w.Write(buf)
}

fd, err := os.OpenFile(filePath, os.O_RDWR|os.O_CREATE, 0644)
if err != nil {
  fmt.Printf("无法打开文件: %v\n", err)
  return
}
defer func() {
  // 确保在函数结束时关闭文件
  if err := fd.Close(); err != nil {
    fmt.Printf("关闭文件时出错: %v\n", err)
  }
}()

ew := &errWriter{w: fd}
ew.write(p0[a:b])
ew.write(p1[c:d])
ew.write(p2[e:f])
// and so on
if ew.err != nil {
    return ew.err
}
```
考察优化后的代码。多个 `fd.Write` 返回值的 `err` ，共用了 `errWriter` 中 `err`。多个 `err != nil ` 检查，共用了 `write` 方法处理。

### 错误相关的特性

综上，编程中错误的处理，至少需要考虑 3 个特性：

1. 错误的返回；

2. 错误的处理；

3. 发生错误以后，支持必要的收尾；

### 错误状态的返回

调用方要通过返回的错误，判断所调用者是否出错。编程中调用者一般为函数或方法。函数有多个入参，通常只有一个返回值，也有直接支持多返回值的语言，例如golang。如何处理错误和正常的返回值，是所有编程语言需要处理的问题。解决办法有：

  - 使用 `try-catch-finally` 的 `try` 捕获错误，无需额外的返回值；
  - 支持多个返回值，例如golang，约定最后一个返回值是 err；
  - 增加错误状态的全局变量；
  - 返回一个集合类型，如：array 或 map，把正常返回值和错误存储在一个变量中；

### 错误的处理

调用过程中，可能存在多个错误，例如上文中的多个 `fd.Write` 调用的 err。处理办法有：

- 统一处理，如 `try-catch-finally` 的 `catch`；
- 逐一处理，如 golang 的 `if err != nil`；

### 必要的收尾

调用以后，如打开了文件，即使发生错误了，还需关闭文件。处理办法有：

- 随着错误一起处理，如：`try-catch-finally` 的 `finally`
- 在其他地方处理，如 golang 中的 `defer`

### Nil 不是 Nil

```go
func do() error {
    return nil
}

func main(){
    if do() != nil {
        return err
    }
}

```

> These constructs are idiomatic to Golang, as it encourages developers to explicitly return errors as values and handle them as usual variable. But this post is not about errors, its about nil values.

``` go
var p *int              // (type=*int,value=nil)
var i interface{}       // (type=nil,value=nil)

if i != p {             // (type=*int,value=nil) != (type=nil,value=nil)
// to successfully compare these values, both type and value must match
    fmt.Println("not a nil")
}

//the code outputs "not a nil"
```



```go
// example #1
type myerr string

func (err myerr) Error() string {
    return "an error ocurred: " + err
}

func do() error {
    var err *myerr
    //do logic...
    return err // might return nil pointer
}

func main() {
    err := do()
    print(err == nil) // prints `false` because it is nil pointer
}

// example #2
type myerr string

func (err myerr) Error() string {
    return "an error ocurred"
}

func do() *myerr {
    return nil // returns nil pointer
}

func wrap() error {
    return do() // the information about nil pointer is dissolved
}

func main() {
    err := wrap()
    print(err == nil) //prints `false` because underneath is nil pointer not empty interface
}


```

> The solution is simple - always use error interface when returning an error from function and never initialize an empty error variable that might be return from function (as `nil`).This makes the code more readable and generic but also avoid the situations above.

### errors.As

```go


// example #2
type myerr string

func (err myerr) Error() string {
    return "an error ocurred"
}

func do() *myerr {
    return nil // returns nil pointer
}

func wrap() error {
    return do() // the information about nil pointer is dissolved
}

func main() {
    err := wrap()
    print(err == nil, "\n") //prints `false` because underneath is nil pointer not empty interface

    var myerr1 *myerr
	  if errors.As(err, &myerr1) {
		  print("== err \n")
	  }
}


```


### Errors are values

Rob Pike, 12 January 2015:

> all the time, something must be wrong, and the obvious target is Go itself.

> This is unfortunate, misleading, and easily corrected. Perhaps what is happening is that programmers new to Go ask, “How does one handle errors?”, learn this pattern, and stop there. In other languages, one might use a try-catch block or other such mechanism to handle errors. Therefore, the programmer thinks, when I would have used a try-catch in my old language, I will just type if err != nil in Go. Over time the Go code collects many such snippets, and the result feels clumsy.

> Regardless of whether this explanation fits, it is clear that these Go programmers miss a fundamental point about errors: Errors are values.

> Values can be programmed, and since errors are values, errors can be programmed.

- [Golang 有什么致命的问题吗？](https://www.zhihu.com/question/311207855)
