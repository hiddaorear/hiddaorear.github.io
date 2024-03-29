数组带单点及区间更新求区间和
描述信息
给定数组, 长度为n, 有下面如下操作:

1) update(i, num): 将第i个元素修改为num;

2) sum(i, j): 求区间i, j内元素总和

3) add(i, j, num): 将区间i, j内的所有元素都加上num;

参考答案
经典问题, 多种方式解决:

1) 分块

对该数组按sqrt(n)分块, 维护每块的总和;

对于update和sum的复杂度都为sqrt(n);

2) 线段树

直接用线段树维护该区间;

对于update和sum的复杂度都为logn;


数组带单点更新求区间和
描述信息
给定数组, 长度为n, 有下面如下操作:

1) update(i, num): 将第i个元素修改为num;

2) sum(i, j): 求区间i, j内元素总和

参考答案
经典问题, 多种方式解决:

1) 分块

对该数组按sqrt(n)分块, 维护每块的总和;

对于update和sum的复杂度都为sqrt(n);

2) 线段树

直接用线段树维护该区间;

对于update和sum的复杂度都为logn;




模拟排队购物
描述信息
某个商场提供了一项优惠活动, 导致陆续有人前去排队购买商品; 排队的人耐心有限, 一定时间后可能离开队伍; 由于商场的排队通道狭窄, 只有排在队尾的人, 才能离开队伍; 现在假设有n个人前去排队购买商品, 需要你打印出这些人所有的排队情况;

如, 假如n等于2, 那么排队情况大致有:

1-in, 1-out-head, 2-in, 2-out-head
1-in, 1-out-head, 2-in, 2-out-tail
1-in, 1-out-tail, 2-in, 2-out-head
1-in, 1-out-tail, 2-in, 2-out-tail
1-in, 2-in, 1-out-head, 2-out-head
1-in, 2-in, 2-out-tail, 1-out-head
...
x-in表示第x个人进入了队列; x-out-head, 表示x号人买到了商品, 从队头离开了队伍; x-out-tail, 表示队伍尾巴的x号人, 没有了耐心, 离开了队伍;

参考答案
该题目的模型类似于一个双端队列, 每次可以弹出头部或者尾部的一个元素, 也可以向尾部插入一个元素; 可以直接DFS所有情况进行打印; DFS时维护当前队列的状态, 然后枚举之后的情况发展, 有三种情况: 1: 队伍头的人离开; 2: 队伍尾的人离开; 3: 队伍尾巴进来了一个新的人;


给你一个先升序后降序的数组，输出去重后的升序排列
描述信息
给你一个先升序后降序的数组，输出去重后的升序排列
参考答案
双指针, 分别从头和从尾向中间扫描并不断输出即可;




数字字符串所有能被4整除的子串的个数
描述信息
求给定数字字符串所有能被4整除的子串的个数
参考答案
能被4整除的数, 最后两位是固定的某些数值; 求出最后两位的所有情况, 代入该字符串中去计算并累计;




判断二叉树是否是完全二叉树
描述信息
判断二叉树是否是完全二叉树

参考答案
O(n)算法即可



给定一组数字，任意组合，求比给定组合M大的最小值，例如给定 (1,3,4) 比 314 大的最小值是 341
描述信息
给定一组数字，任意组合，求比给定组合M大的最小值，例如给定 (1,3,4) 比 314 大的最小值是 341

参考答案
从低位向高位扫，找到第一个下降的断崖。 二分已经扫描的部分，将最小的比'断崖位'大的数与断崖位交换，然后重拍已经扫描的部分。 58721 -> 断崖位为5 -> 交换5与7， 7为已扫描部分，最小的比5大的数 -> 78521 -> 重排以扫描位 -> 71258




给定一个字符串，删除若干个字符使删除后的字符串字典序最大
描述信息
给定一个字符串，删除若干个字符使删除后的字符串字典序最大

参考答案
用数组maxOnRighti, 维护字符串第i位, 右边最大的字符; 然后从左到右的扫描, 如果stri < maxOnRighti, 则删除该字符, 否则保留;




找出最大的正方形
描述信息
给定一个包含0，1 的二维数组， 找出包含元素全部为 1 的最大正方形
参考答案
1) 暴力: O(n^3)以上; 2) DP1: 用dpi, j维护0, 0到i, j形成的矩形内, 1的个数; 然后枚举右下点, 和正方形长度, 利用dpi, j-dpi-k, j-k == k*k的方式进行验证; 复杂度为O(n^3); 3) DP2: 用dpi, j维护以i, j为右下点, 满足条件的最大正方形边长; 用upi, j维护以i, j为最下点, 向上最多延伸多少个1; 用lefti, j维护以i, j为最右点, 向左最多延伸多少个1; 于是转移方程大致为: dpi, j = min(dpi-1, j-1, upi, j, lefti, j) 复杂度为O(n^2);


数学题
描述信息
给定区间 (a, b] , 其中 b > a > 0, 问：区间内的数的数字不包含 3，5，7 三个数字的数的个数， 例如 136 因为包含数字 3 不满足条件

参考答案
数位dp 或者单纯用容斥也可以



给你一个数组, 可以在该数组中任意取两个数来进行亦或, 求亦或后最大值
描述信息
给你一个数组, 可以在该数组中任意取两个数来进行亦或, 求亦或后最大值

参考答案
按位拆分, 用字典树维护并计算



求 K 个无序超长数组的中位数
描述信息
要求时间复杂度为O(n)
参考答案
将所有数组连起来 求中位数 快排的partition实现




求 K 个有序超长数组的中位数
描述信息
要求空间复杂度为O(1)
参考答案
先二分答案, 再验证该答案是否为整体中位数; 验证时去每个数组中二分; 复杂度为nlog(m); m为数字范围; 内存可解决；




判断一个二叉树是不是搜索二叉树
描述信息
如题
参考答案
直接中序遍历 看是否有序



简略版快排
描述信息
给定一个非负数组，使得所有的0 放在数组左边， 大于 0 的值位于数组右边, 要求空间为O(1), 时间为O(n);
参考答案
快速排序的子问题 扫描即可




杨氏矩阵
描述信息
二维数组

从左到右 依次增大

从上到下 依次增大

例如:

0 1 2
1 2 3
2 3 4
查找给定数的位置

参考答案
充分利用有序的属性 首先第一行从左到右找到最后一个比给定数小的数 然后到下一行 再往右找到最后一个比给定数小的数 依次找每一行 直到找到位置 时间复杂度O(n) 在第一步中可以使用二分搜索 使复杂度的常数变小




翻译单词
描述信息
"给一个黑盒，可批量输入单词，会返回其翻译，但不知道对应关系。 现有n个单词，问最少需要几次能确定它们的翻译"

参考答案
答案为 log(n)




容器取数
描述信息
给一些容器，每个容器里有一些数，按照容器顺序取数，空容器会自动跳过， 问第k次取到的为哪个容器的第几个数

参考答案
二分前缀和
评分标准
<div><i>缺省字段，这应该是2017年的老题目了~</i></div>



矩形相交
描述信息
给两个平行于坐标轴的矩形问是否相交（可询问不平行坐标轴时的做法）
参考答案
"判断点是否在另一个矩形中即可; 判断时可用基本的计算几何知识;"




吃水果
描述信息
"家里有n个水果，超市有m个水果，知道每个水果坏掉的时间，保证在不买水果的情况下有方案能吃完家里的水果。 1天最多吃k个水果，可以从超市买水果，要求家里的和超市买的水果都不能变坏, 问最多能吃到多少水果, 且输出需要买超市中的哪些水果;"

参考答案
家里的水果与超市的水果按坏掉的时间分别排序，从后往前安排家中的水果，对于剩下的位置从前往后插入超市的水果 O(nlog(n))




摘苹果
描述信息
"给一个圆上面有很多树，每棵树上有一些苹果，0是家， 现在有个人背个容量为k的筐去摘苹果，问将全部苹果摘完, 最少走的路;"

参考答案
预处理顺时针取完前 i 棵树的最少代价，以及逆时针取完后 i 棵树的最少代价，然后枚举中间点 x，在 x 之前的都顺时针取，x 之后的都逆时针取。复杂度 O(n)



神秘数字II
描述信息
给一列数，除1个数之外每个数都恰好出现k次(k>=2)，求那个数
参考答案
"开一个表示二进制位的数组，初始状态每位都为0。 对于每个数执行该操作：对于每个二进制为1的位，将上面提到的数组中对应的位+1并mod k。 最后将上面的数组中值为1的位组合起来即为要求的数。"

此题结合上题可改为：有n个数，除m个数外每个数都恰好出现k次(k>=2,1<=m<=k)，求那m个数。复杂度会变为 O(nm)




神秘数字
描述信息
给一列数，除两个数之外每个数都恰好出现2次，求那两个数
参考答案
"将所有数异或起来，得到的数就是那两个数的异或； 然后在这个值中任意挑一位不为0的位(二进制下)，再将所有该二进制位为1的数异或起来，得到的数即为两个数中的一个。 第一次的异或结果异或第二次的结果，得到另一个数。"




duplicate number
描述信息
给一列数，其中某个数出现次数超过一半，求这个数
参考答案
经典方法: 维护当前出现次数最多的数字和它的次数，遇到相同则+1，不同则-1



duplicate number 复杂度计算
描述信息
给一列数，其中某个数出现次数超过一半，求这个数

对于上题, 给出下述解法, 请求出他的复杂度:

随机从数列中选一个数;
扫描数列验证该数是否出现了一半以上;
如果出现了一半以上, 输出该数, 结束算法;
否则继续执行1);
参考答案
令P(k)为选取k次后结束算法的概率;

于是P(1) = 1/2; P(2) = 1/4; P(3) = 1/8...

设F(k)为选取k次结束的计算基础, 则F(k) = k * n; (需要检验k次

则总体复杂度为O = P(1)F(1)+P(2)F(2)+P(3)*F(3) ...; (该公式的意义为将每个局面的概率乘上该局面的计算次数, 做累加, 则得到总复杂度;

将上面公式展开O = n (1/2 1 + 1/2^2 2 ... + 1/2^k k ...);

(1/2 1 + 1/2^2 2 ... + 1/2^k * k ...) = 2;

因此整体复杂度为O(n);


带TTL的N-kv cache
描述信息
"实现一个带过期的KV cache, 所有KV过期间隔相同, 满足如下性质: 1. 最多存储n对KV; 2. 如果大于n个, 则随意剔除一个已经过期的KV; 3. 如果没有过期的KV, 则将最老的那一对KV给剔除; 4. 查询时如果已经过期, 则返回空; 5. 所有操作复杂度都为O(1)"

参考答案
"最老的那个, 肯定最先过期; 如果都没有过期, 也只能剔除最老的那个; 因此在解决剔除与过期时, 完全同上;

为了解决过期返回空, 有比较简单的办法是在每次查询前先过期一次;"



树的染色
描述信息
给一棵树，要给节点染色，每个点及其相邻节点颜色都不同，问最少需要多少颜色, 输出任意染色方案
参考答案
"颜色数量是所有节点的最大度+1 染色随便染就行了"



极大点
描述信息
给一列数，首尾都是负无穷，求找到任意一个极大点
参考答案
使用三分法, 复杂度大致为logn级别；或二分然后判断与左右两点的关系



满二叉树节点数
描述信息
求一棵满二叉树节点个数
参考答案
"不断的向左边递归, 得到深度h; 节点总数为2^h-1;"




LRU cache
描述信息
实现一个LRU过期算法的KV cache, 所有KV过期间隔相同, 满足如下性质: 1. 最多存储n对KV; 2. 如果大于n个, 则随意剔除一个已经过期的KV; 3. 如果没有过期的KV, 则按照LRU的规则剔除一个KV; 4. 查询时如果已经过期, 则返回空;

参考答案
用一个map来维护K->V索引; 用一个双向链表list来维护K, 保证越靠前的K时间越早; 用一个map来维护K->list.node, 该map用于删除时使用 剔除时, 从list取出最老的K, 从map中剔除即可;

最老的那个, 肯定最先过期; 如果都没有过期, 也只能剔除最老的那个; 因此在解决剔除与过期时, 完全同上;

为了解决过期返回空, 有比较简单的办法是在每次查询前先过期一次;

解法大致同上; 为了实现LRU, 可在每次get后, 将该K从cache中删除并重新插入一遍;



带TTL的N-kv cache
描述信息
实现一个带过期的KV cache, 所有KV过期时间相同, 满足如下性质: 1. 最多存储n对KV; 2. 如果大于n个, 则随意剔除一个已经过期的KV; 3. 如果没有过期的KV, 则将最老的那一对KV给剔除; 4. 查询时如果已经过期, 则返回空;

参考答案
用一个map来维护K->V索引; 用一个双向链表list来维护K, 保证越靠前的K时间越早; 用一个map来维护K->list.node, 该map用于删除时使用 剔除时, 从list取出最老的K, 从map中剔除即可;

最老的那个, 肯定最先过期; 如果都没有过期, 也只能剔除最老的那个; 因此在解决剔除与过期时, 完全同上;

为了解决过期返回空, 有比较简单的办法是在每次查询前先过期一次;



N-kv cache
描述信息
实现一个KV cache, 满足如下性质: 1. 最多存储n对KV; 2. 如果大于n个, 则将最老的那一对KV给剔除;

参考答案
用一个map来维护K->V索引; 用一个双向链表list来维护K, 保证越靠前的K时间越早; 用一个map来维护K->list.node, 该map用于删除时使用 剔除时, 从list取出最老的K, 从map中剔除即可;



模拟子弹
描述信息
给你一副类似于如下的地图:

0000000000
0010001011
000010E001
00S0000000
0000001000
1000000000
初始时你在S的位置, 你可以向上下左右四个方向发射一枚子弹;

子弹碰到1时, 会顺时针变向90度, 然后继续前进;

问你在S向哪个方向射击, 能够最快将子弹打入E内;

假设一定有一个方向可以成功, 如上图中向上射击;

参考答案
模拟题; 同时模拟四个方向; 哪个方向先成功, 则选那个方向;

也可以单独计算每个方向到达终点的步数, 然后进行比较; 不过此种方法需要注意子弹在途中形成死循环;




砍竹竿
描述信息
"你有n根竹竿, 每根竹竿有各自的高度, 范围为1~1e9米; 现在需要选择一个高度一刀切下去; 如果竹竿高于此高度, 则高于的部分便被切下; 要你选择一个最高的高度, 使得所有竹竿被切下的长度之和大于m;"

参考答案
二分最后答案后验证; O(nlogn)




日志提取
描述信息
你有一份非常大的日志文件; 日志的格式为: timestamp: content; 如 2017-01-01 20:00:00: hello hello hello; 需要你提取日志中指定时间内的内容; 如提取2017-01-01 20:00:00 ~ 2017-01-01 22:30:00的日志数据

参考答案
由于时间是递增的, 可以先二分到指定时间, 然后再进行读取;



开k次方根
描述信息
"写出函数f(n, k), n, k为正整, 返回数字x, 使得x^k == n; 不能使用系统函数, 如pow;"

参考答案
不断的二分逼近答案即可;



字符串翻转
描述信息
有n个字符串, 你可以选择对其中一些字符串进行左右翻转;选择需要你翻转最少的字符串, 使得这n个字符串整体为升序;
参考答案
简单DP题; dp[i]表示将前i个字符串保持整体升序, 最少需要多少次操作;



青蛙跳石子
描述信息
在长度为m的地面格子上，每个格子里面有一些石子；有一只青蛙, 从格子开始处起跳，每次可以跳3到5个格子，求青蛙跳出格子最少需要踩几个石子；
参考答案
简单DP dpi表示调到第i的位置最少需要踩几个石子; 于是dpi可由dpi-3, dpi-4, dpi-5得来;





给定两个链表，求它们交叉节点
描述信息
已知两个链表, 从某个节点开始就交叉了
已知这两个链表的头节点, 求出交叉的节点
参考答案
依次遍历两个链表分别得到链表的长度M和N
然后让长的那个一个从头开始走|M-N|的步数;
两个指针同时走, 直到碰头



找出其中最大的一块全为1的面积;
描述信息
你有一副位图, 如下

00000000000
00011110100
0000010000
11111111000
1000000000
规定上下左右为相邻; 找出其中最大的一块全为1的面积;

参考答案
简单题, BFS/Floodfill



给一个数组, 求出其中的逆序对个数; 只需要个数, 不需要输出全部的逆序对; 数组中的数字小于100000;
描述信息
给一个数组, 求出其中的逆序对个数; 只需要个数, 不需要输出全部的逆序对; 数组中的数字小于100000;

参考答案
经典问题, 多种解法; 归并排序/线段树/树状数组, O(nlogn), 3.5;



是学校老师, 有n个学生; 某次考试后, 你让n个学生排成一排, 按照他们的分数来给予奖励; 奖励为发送糖果, 每个孩子至少会得到一个糖果; 另外如果某个孩子发现他的分数比相邻同学分数高, 但是糖果
描述信息
你是学校老师, 有n个学生; 某次考试后, 你让n个学生排成一排, 按照他们的分数来给予奖励; 奖励为发送糖果, 每个孩子至少会得到一个糖果; 另外如果某个孩子发现他的分数比相邻同学分数高, 但是糖果却不比他们多, 便会不开心; 你需要用最少的糖果来让所有孩子都开心; example: 分数为 80 90 99 80 70: 那糖果最少给1+2+3+2+1 = 9

参考答案
定义极小点: 某点的分数比左右两边的人都低;

将每个极小点的糖果数设置为1, 然后向左右两边扩散; for i := 0; i < n; i++ { if childi.score > childi-1.score { childi.socre = max(childi.sugar, childi-1.sugar+1) } }

然后再从后往前的扩散一次;




数列（顺序为: 一堆负数 + 一堆 0 + 一堆正数），求最后一个出现的负数和第一个出现的正数
描述信息
数列（顺序为: 一堆负数 + 一堆 0 + 一堆正数），求最后一个出现的负数和第一个出现的正数的位置，从 1 开始计数。例如： -2，-1，0，0，0，0，4，5 最后一个负数出现的位置为：2，第一个正数出现的位置为7。

参考答案
二分查找 0 的位置;
注意边界位置 0 的处理，在二分条件上需要做一些处理，如果只是找到 0 的位置然后遍历找到第一个和最后一个 0 的话， 复杂度为恶化;
整体复杂度为 O(lg(n));




蓄水问题, 2维
描述信息
给定一个二维数组用于描述海拔，计算下雨后能留下多少雨水
参考答案
将原2维数组上下左右相连，再将最外围一圈点与一个特殊点(边缘)相连，特殊点(边缘)的实际高度与水位高度为0。 从该特殊点开始做bfs，

每次取出队列中水位高度最低的点，更新与其相连的未被更新的点的水位高度：max(更新到该点的水位高度，当前点的实际高度)，并把该点加入队列

另：有别的做法，如用并查集维护每个点的蓄水块及其高度，在此不再做详细描述了





蓄水问题, 1维
描述信息
给定一个一维数组用于描述一个海拔，相邻的海拔高度不同，则下雨后低洼海拔的洼地会有积水，假设雨水足够，能够填满所有低洼地段，计算下雨后所有低洼地段总蓄水量。

例如给定数组为：

5, 2, 1, 4, 3

则：所有低洼地段蓄水为量为 5

参考答案
定义左极高点: 该点左边最高的那个点;

定义右极高点: 该点右边最高的那个点;

于是每个点的蓄水高度为: min(左极高点高度, 右极高点高度) - 该点高度，累加每个点的高度即可;所有点的左右极点可以分别通过一次向右和向左的扫描得到;

算法复杂度为 O(n)



给定单链表，求离终点距离为 k 的节点
描述信息
给定单链表，求离终点距离为 k 的节点，要求只扫一次且空间复杂度为O(1)
参考答案
两个指针, 第一个先向后走k步;

然后两个一起走;

当第一个指针到达链表尾部时另一个指针指向的就是距离终点距离为 k 的节点。





给定无向图和它一个顶点，求无向图中到该顶点距离为K的所有点
描述信息
给定无向图和它一个顶点，求无向图中到该顶点距离为K的所有点，各个相邻顶点间距离为1
参考答案
方案：对图进行K步的BFS, 注意处理被重复走过的点;




给定链表，将其中的某一部分翻转
描述信息
给定链表，将其中的某一部分翻转, 要求空间复杂度为O(1);
参考答案
指针a与d指向要翻转部分的第一个节点，指针b指向a的上一个节点；

指针c指向a，并将a指向下一个节点，再将c插入到b的后面，重复执行该操作直到a走出要翻转的区间；

最后将a接在d后面，完成翻转。




给定无向图和它一个顶点，求无向图中到该顶点距离为K的所有点
描述信息
给定无向图和它一个顶点，求无向图中到该顶点距离为K的所有点，各个相邻顶点间距离为1
参考答案
方案：对图进行K步的BFS, 注意处理被重复走过的点;

评分标准
主要考察BFS的实现，比较简单，适用于各个岗位，不适用于ACM同学，代码思路正确得3分；




数字字典序输出
描述信息
将 1 到 n 的数字, 按照字典序输出，要求时间复杂度 O(n) Example: n = 11, Output: 1, 10, 11, 2, 3, 4, ..., 9

参考答案
把所有数字构造成一个10叉树, 10个儿子分别表示0, 1, 2...9; 按顺序DFS;




二维矩阵动态求和
描述信息
二维矩阵，每次修改/查询子矩阵的和; 矩阵的长和宽都在n/2, n的范围; 总共的询问次数为m, 可假设多种情况, 比如修改远大于查询; 查询远大于修改; 修改和查询差不多时; 要求给出各种情况下的算法和复杂度;

参考答案
1 (修改 >> 查询) 直接维护矩阵，每次 O(1) 修改，O(n^2) 求和 2 (查询 >> 修改) 维护每个点到左上角的和，每次 O(n^2) 修改，O(1) 求和 3 (4分) 二位树状数组/线段树，O(log^2n)修改/求和




动态中位数查询
描述信息
给定你一个集合, 要求你求出其中的中位数; 并且支持, 不断的向该集合内加入数字; 能实时的得到当前的中位数;

参考答案
维护两个大顶堆, 每个堆维护一半的数据量; 且两个堆的满足性质: 堆A的所有数据 > 堆B的所有数据;

加入数据时根据先随意加到某一个堆; 然后将两个堆的数据量调整到一半一半;

时间复杂度: 建堆: O(n), 之后每次维护: O(logn)





二叉树最近公共祖先
描述信息
给定一个二叉树的两个叶子节点，每个节点给出指向父节点的指针，返回它们的最近公共父亲节点。 要求空间复杂度为O(1);

参考答案
可把问题的模型转化为: 给定两个链表指针, 俩链表在某一点相交, 求该交点;

先让两个指针分别走到头, 记录下两个链表的长度, 假设为: n和m, 且n>=m; 先让第一个指针向后走n-m步; 接着两个指针同时开始走; 当两个指针第一次指向同一个节点时, 该节点既为交点;




平行矩阵求交
描述信息
给两个平行于坐标轴的矩形问是否相交或者包含 (可询问不平行坐标轴时的做法)

参考答案
直接判断所有举证的点, 是否在另一个矩阵中;

平行坐标轴可直接使用解析几何强行判断; 非平行坐标轴可利用基本的计算几何知识;



树染色
描述信息
给一棵树，要给节点染色， 要求每个点及其相邻节点颜色都不同， 问最少需要多少颜色, 并输出任意染色方案

参考答案
颜色数量是所有节点的最大度+1; 节点的度定义为与之相邻的节点数目;

染色时从根节点开始, 进行DFS, 每次随便挑选一个不冲突的颜色就行了;




数列极大点
描述信息
给一列数，首尾都是负无穷，求找到任意一个极大点; 假设一共有n个数, 给出计算复杂度;

参考答案
对于找极点这类问题, 直接使用三分法, 复杂度为log3(n)级别；



子集打印
描述信息
给一个集合S, 且Size(S) <20; 需要打印出S的所有子集, 且这些子集的元素个数在a, b内; 要求给出复杂度;

参考答案
"直接枚举即可; 实现时可直接用DFS;

下面是复杂度计算; 令n = Size(S); 我们用C(n, k)表示组合数, 则复杂度为: C(n, a) + C(n, a+1) ... + C(n, b)"





数组0值筛选
描述信息
给定一个非负数组，要求你对它进行操作, 使得所有的0 放在数组左边， 大于 0 的值位于数组右边,

要求空间为O(1), 时间为O(n);

参考答案
从右往左扫描，同时维护另一个指针指向出现在最右侧的 0，每次扫描到非 0 数字则和它交换
评分标准
该题最多给3分，属于基础编码题，适用于仅考察编码部分，工作年限较长候选人，不适用于应届生；
代码正确，时间和空间复杂度符合题目要求，得3分；
对于客户端同学，如果代码质量较高，可以适当加0.5分；



文本编辑器实现
描述信息
你需要实现一个文本编辑器, 支持下面几种操作: 1. Insert(k, S): 在第k个字符后, 插入字符串S; 2. Delete(k, n): 删除第k个字符开始的n个字符; 3. Get(k, n): 取出第k个字符开始的n个字符;

保证字符串的总体长度不会超过1e6; 描述实现思路;

参考答案
方案一： 比较经典的解决办法为分块维护; 取m = sqrt(1e6), 并设定块大小的区间为[m, 2m); 于是将整个编辑器内的字符串按照m的大小划分为多个块; 块和块之间用链表串联起来, 块内部用数组进行维护; 对于Insert, Delete, Get操作分别在块内和块间维护相应的操作; 当块的大小大于等于2m时, 将其分裂为2个块;

于是块的总数不会超过m个, 每个块内维护的字符个数不会超过2m个; 总体的复杂度为O(m), 即O(sqrt(1e6));

方案二： 平衡树亦可;



拼凑最多个VK对
描述信息
给一个由'V'和'K'组成的string; 你可以修改其中一个字母; 问最多能够凑出几个""VK""对; 要求给出计算复杂度

参考答案
"可以事先处理处lefti, righti, 分别表示在不做任何修改的情况下, 第i位左边和右边, 最多能有多少VK对; 事先处理的复杂度为O(n);

直接模拟修改每个字符, 并同时计算解, 取一个最大值; 可做到O(n)的复杂度;"





K个有序超长数组求中位数;
描述信息
求 K 个有序超长数组的中位数; 超长的含义为, 你无法将任意一个数组, 直接全部载入内存中; 需要给出复杂度;

参考答案
"先不考虑内存问题, 思路为: 先二分答案, 再验证该答案是否为整体中位数; 验证时去每个数组中二分; 复杂度为nlog(m); m为数字范围;

现在来解决内存问题: 设置一种可解释的文件格式, 去存放每个数组; 如直接将每个数组存到不同的文件; 每份文件按照8byte划分, 第k个8byte则表示该数组中的第k个数字; 然后需要某个数字时, 直接计算偏移量, 去读取该数字即可;"





1-n数字字典序第k大
描述信息
给你一个数字n(n < 1e9), 再给你一个数字k(k < n), 要求你找到1, 2, 3, ... n按照字典序排序后, 第k大的数字;

如, n = 15, k = 7;

那1 ~ 15按照字典序排序为: 1, 10, 11, 12, 13, 14, 15, 2, 3, 4, 5, 6, 7, 8, 9;

则答案为15;

参考答案
利用字典树的思想; 我们假设有这么一棵树, 每个节点都要10个儿子, 10条到儿子的边分别对应数据0~9; 那么我们在这棵树上, 对边按照0~9的顺序进行DFS, 当走到第k个节点时, 该节点对应的数字既为我们的第k大字典序数字;





两升序数组中查找特定和的数对
描述信息
"给定两个升序数组, 长度都为n; 且保证, 两个数组中, 各自都不会有重复的元素; 再给定一个值m: 你需要在两个数组中, 分别选出一个数, 构成值对(a, b); 使得a + b == m; 输出所有满足条件的值对; 并给出计算复杂度;"

参考答案
"使用双指针; 第一个数组从头开始维护指针; 第二个数组从尾开始维护指针;"





字符串升序翻转
描述信息
"有n个字符串, 你可以选择对其中一些字符串进行左右翻转; 如""abc"" => ""cba""; 选择需要你翻转最少的字符串; 使得这n个字符串整体为升序; 最后可能为无解; 同时需要你给出时间复杂度;"

参考答案
"简单DP题; 维护一个二维数组: dpn; dpi表示第i个字符串不翻转的情况下, 使得前i个字符串成升序需要几次操作; dpi表示第i个字符串进行翻转的情况下, 使得前i个字符串成升序需要几次操作; 最后结果为 min(dpn, dpn)"





数组循环向右移动k位
描述信息
"将一个长为n的数组循环右移 k 位，要求时间复杂度O(n)，空间复杂度O(1)。 Example: 1, 2, 3, 4, 5, k = 2; Output: 4, 5, 1, 2, 3"

参考答案
"进行三次镜像翻转： 1. reverse(0, n) 2. reverse(0, n - k) 3. reverse(n - k, n) reverse 实现上保持原地交换就可以了。"





模拟最大堆操作
描述信息
实现最大堆的 up 和 down 两个操作，即把一个元素向上调整和向下调整。
参考答案
"function up(x): if (x is root) then return if (value(x) <= value(father(x))) then return swap(value(x), value(father(x))) up(father(x))

function down(x): if (x is leaf) then return y = value(left(x)) > value(right(x)) ? left(x) : right(x) if (value(y) < value(x)) then return swap(value(x), value(y)) down(y)

这里注意 y 的边界情况，left(x) 和 right(x) 可能不同时存在，需要特殊判断一下。"





二叉树特定权志路径计数
描述信息
给定一棵二叉树，每条边带一个权值。 给定一个整数 x，然后从任意一个点出发，只能向下走，求所有的路径当中权值之和等于 x 的路径条数。

参考答案
"在题目限制下，对于两个节点 u 和 v（u 是 v 的祖先），他们的距离为 depth(v) - depth(u)，其中 depth(u) 表示从根节点到 u 的路径权值之和，显然 depth(u) = depth(father(u)) + value(father(u), u)。 DFS，同时维护一个map，每遍历到一个点 v，则将 depth(v) 插入到 map 当中。插入之前先检索一下 map 中等于 depth(v) - x 的元素个数即可。"





二叉树镜像判断
描述信息
"给定两棵二叉树，判断它们是否镜像对称。 例如，下列两棵树是镜像对称的： 1 -> (2, 3 ->(4, 5)) 以及 1 -> (2 -> (3, 4), 5)"

参考答案
维护两个指针，在两棵树上同时递归（顺序相反，a 向左移动时 b 向右移动），维护它们当前在两棵树中的位置。如果其中一个指针为空而另一个非空则说明不是镜像对称的。



pow函数实现
描述信息
"实现一个函数 f(int n, int k), 其中 n, k > 0，函数返回整数 x 使得 x^k == n。 不能使用系统函数（如 pow）。"

参考答案
二分 x，判断 x^k 和 n 的大小关系并逼近答案。




日志文件查找指定时间段日志
描述信息
"给定一份 100M 级别的日志文件，日志的格式为: timestamp: content（如 2017-01-01 20:00:00: helloworld）。 请在日志中提取指定时间内的内容（如提取 2017-01-01 20:00:00 ~ 2017-01-01 22:30:00 的所有日志数据）"

参考答案
日志文件中时间是递增的，因此先二分到指定的开始时间（移动文件指针到某一行并读取当前时间戳进行比较），找到开始时间之后顺序读取即可。（注意不需要两次二分）



行列单调矩阵数字查找
描述信息
给定 n * n 的二维数组，保证任意一行和任意一列都是单调递增的。 给定数字 x，求它在数组中的位置。

参考答案
从右上角开始和 x 比较，如果 x 比当前数字 x 小则往左走，否则往下走。最坏情况下会遍历 2n 个数，复杂度是 O(n) 的。



用户时长前100筛选
描述信息
给定头条所有用户的每日使用时长（约 80M），尽可能快地找到当中使用频率最高的 100 个人。
参考答案
维护一个大小为 100 的最小堆来储存频率最高的人。每次读入新数据，则和堆顶（第 100 大的人）进行比较，如果比它大则弹出堆顶并插入新数据。需要考察建立和维护堆的过程。





散列表hash实现
描述信息
实现一个 Hashmap，不允许使用语言自带的 map，只允许使用数组，链表等结构进行实现。
参考答案
用数组维护链表的表头，每次插入时使用哈希函数找到其表头的位置（例如 hash(x) = x mod n），然后将当前元素插入到这条链表中即可。



用数组模拟队列
描述信息
使用定长数组实现一个队列，要求可以实现满足队列性质（FIFO，先进先出）的插入，删除操作。
参考答案
"维护一个数组，并维护 head 和 tail 指针。每次插入新节点则 tail 向后移，删除节点则 head 向后移。注意当 tail 大于数组长度时应重新指向数组头部，即 tail = (tail + 1) mod n。

在队列长度大于 n 时代码需要指出错误。"





单向链表求最后第k个节点
描述信息
给定一个单链表（每个节点都连向其后边的节点，但没有反向边），求离末尾点距离为 k 的节点。要求只允许一次遍历。
参考答案
维护两个指针，第一个先向后走 k 步，然后两个一起走。当第一个节点到达终点时，第二个指针就是答案。




搜索二叉树判断
描述信息
判断一颗二叉树是否是搜索二叉树。 搜索二叉树的定义是，对于树上的任意一个节点，其左侧的所有后代的权值都小于它， 右侧所有后代节点的权值都大于它。

参考答案
递归时只需判断每个节点和它的左右两个孩子的大小关系即可，不需要额外的检索。




链表奇偶翻转
描述信息
链表奇偶反转，例如对于链表 1->2->3->4->5->6, 将其翻转为 2->1->4->3->6->5
参考答案
模拟题，维护链表当前的尾部节点，然后每次两步跳，逆序插入新链表的尾部。




字符串前后缀翻转
描述信息
"输入字符串 str 和一个整数 m，将 str 的前 m 位与后面的部分前后翻转。 Example: str = ""abcde"", m = 2; Output: ""cdeab"""

参考答案
先整体镜像翻转 str，再分别镜像翻转[0, m) 和 [m, n)。




有向图判环
描述信息
给定一个有向图，判断其中是否存在环。 注意这样的两条边 (1 -> 2), (2 -> 1) 也成为了一个环。

参考答案
DFS / BFS，维护一个 bool 数组表示每个节点是否被遍历过，如果下一个即将遍历的点已经之前被标记过则出现环。




数组全排列
描述信息
给定一个数组（数组内的元素不可比较且不重复但可打印），输出实现全排列函数
参考答案
直接递归实现，在每一层枚举当前数字取或不取




升序转换
描述信息
给定一个先升序后降序的数组，输出去重后的升序排列;
参考答案
维护两个指针，分别从头部和尾部往中间移动，每次取出较小的数字插入新数组。复杂度 O(n)。




完全二叉树判断
描述信息
给定一棵二叉树，判断其是否是完全二叉树。 完全二叉树的定义是，除了最后一层之外，其他层的节点都是满的；最后一层的节点都在最左侧

参考答案
"先序遍历树，每次到达叶子节点时，判定当前节点的深度 d(now) 和前一个叶子的深度 d(prev) 的关系。

is_deepest = true if (it's the first leave) then continue if d(now) == d(prev) then continue else if is_deepest and d(now) == d(prev) - 1 then is_deepest = false else return false"



二叉树路径打印
描述信息
给定一棵二叉树，打印出所有从根到叶子的路径。
参考答案
递归遍历，维护一个栈保存当前依次经过的所有节点。如果当前节点是叶子节点，就将栈里所有元素输出出来。时间和空间复杂度最坏情况下（一条链）都是 O(n)。




URL转换
描述信息
给定形如 www.toutiao.com 的 URL，将其转换成 com.toutiao.www 的形式。
参考答案
先整体翻转，各部分再分别翻转。注意 URL 可能不只三个部分; 也可以考虑按照"."划分数组，前后对调即可。





URL反转
描述信息
给定形如 `www.toutiao.com` 的 URL，将其转换成 `com.toutiao.www` 的形式，要求必须原地操作
参考答案
原地全部翻转一遍；
遍历遇到"."，继续翻转该部分字符串； 该题目重点考察编码，需要保证代码简洁，要不不允许使用字符串库函数
















