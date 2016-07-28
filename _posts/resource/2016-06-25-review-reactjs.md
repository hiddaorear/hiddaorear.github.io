---
layout: post
title:  从Lisp到React.js
category: 资源
tags: [ReactJS] 
keywords: ReactJS
description:
---

### 从Lisp到React.js

#### 从Lisp到React.js

#### Saturday, 25 Juny 2016

![ChenBi](/../../assets/img/resource/2016/ChenBi_17.jpeg)

> 很多JavaScript程序员也盲目地鄙视Java，而其实JavaScript比Python和Ruby还要差。不但具有它们的几乎所有缺点，而且缺乏一些必要的设施。JavaScript的各种“WEB框架”，层出不穷，似乎一直在推陈出新，而其实呢，全都是在黑暗里瞎蒙乱撞。JavaScript的社区以幼稚和愚昧著称。你经常发现一些非常基本的常识，被JavaScript“专家”们当成了不起的发现似的，在大会上宣讲。我看不出来JavaScript社区开那些会议，到底有什么意义，仿佛只是为了拉关系找工作。
——王垠


### 函数式编程的三大特性

> immutable data 不可变数据：默认变量不可变，需要改变，把变量copy之后修改。减少程序中的状态，减少bug。

> first class functions：函数可以当作变量使用，可以被创建，修改，传递。

> tail call 尾递归优化：每次递归时重用stack。(无法提供准确的调用信息)

### 函数式编程典型技术

1. `map & reduce`，代码易读，无需中间变量;
2. `pipeline`，函数可组合;
3. `recursive`，把复杂的问题用简单的代码表述。其要义是描述问题，这是函数式编程的精髓;
4. `currying`，把函数的多个参数分解为多个函数，简化函数参数;
5. `higher order function`，高阶函数，把函数当作参数。所以闭包是必须的。

### 函数式编程优点

1. parallelization 并行：各线程之间不需要同步或着互斥；
2. lazy evaluation 惰性求值：被用的时候求值，而不是在绑定之后立即求值；
3. determinism 确定性：如数学表达式`f(x)=y`，相同的输入，相同的输出。

### 声明式编程

实现快速排序：

#### Haskell

````haskell

quicksort :: (Ord a) => [a] -> [a]
quicksort [] = []
quicksort (x: xs) =
  let smallerOrEqual = [a | a <- xs, a <= x]
      larger = [a | a <- xs, a > x]
  in quicksort smallerOrEqual ++ [x] ++ quicksort larger
  
````

### JavaScript

````javascript

    var quickSort = function(arr) {
    　　if (arr.length <= 1) { return arr; }
    　　
    　　var pivotIndex = Math.floor(arr.length / 2);
    　　var pivot = arr.splice(pivotIndex, 1)[0];
    　　var left = [];
    　　var right = [];
    　　for (var i = 0; i < arr.length; i++){
    　　　　if (arr[i] < pivot) {
    　　　　　　left.push(arr[i]);
    　　　　} else {
    　　　　　　right.push(arr[i]);
    　　　　}
    　　}
    　　return quickSort(left).concat([pivot], quickSort(right));
    };

````

描述性的实现优点显而易见。


### 如何编程

先为对应的问题建立一个模型，然后用代码设计出一套DSL(Domain-Specific Language：A computer programming language of limited expressiveness focused on a particular domain)，在将代码运行计算解决问题。


### MVC or `MV*`

即用户更新Model，Model更新到View。Angular1的实现是双向绑定, ViewModel跟Model的对应。


![ng](/../../assets/img/resource/2016/ng.png)

这是其模型。

### Flux

不再绑定，而是View更新会映射到Action,自己实现Action到Model的更新，不再受限制。

![react](/../../assets/img/resource/2016/react.png)

React的DOM是声明式的DSL，通过DOM diff生成更新。

MVVM通过将数据变成observable来变相实现Reactive Programming，数据按照数据流自动同步, JavaScript原生对象被hack掉，HTML也被hack掉，建立自己的DSL。
React，使用Immutable替换掉基础类型，JSX替换DOM，建立自己的DSL。

由于JavaScript自身的缺点，实现不过理想。无不可变数据，不易隔离副作用。

### React

`f(state, props) = veiw`，一个组件的渲染函数是基于state和props的纯函数，state是自身的，props是外来的，有变化则重新渲染。

问题：

1. 跨组件通信；

2. 多组建共享状态；

3. 大量嵌套组件的性能；


导致本来`callApi(res => data = res)`的事情,变成了`action => reducer => store => state => view`

### Redux

Redux三原则：

1. 单一数据源， 整个应用的state被存储在一棵object tree中，并且这个object tree只存在于一个唯一的store中。得益于单一state tree，实现撤销重做变得容易。

2. state只读，修改数据需要dispatch一个action，action是一个描述已发生事件的普通对象。视图与网络请求都不能直接修改state，只能表达修改的意图。所有修改被集中处理，严格的顺序执行，无race condition。

3. 使用纯函数来执行修改。为了描述action如何改变state tree，需要些reducers。


单一数据源，使得所有数据在同一个store中，全部作为React的props。让变化可以预测。



## 参考资料：

 编程珠矶

[快速排序（Quicksort）的Javascript实现](http://www.ruanyifeng.com/blog/2011/04/quicksort_in_javascript.html)

[API设计：用流畅接口构造内部DSL](http://coolshell.cn/articles/5709.html)

[尾调用优化](http://www.ruanyifeng.com/blog/2015/04/tail-call.html)

[理解Javascript的闭包](http://coolshell.cn/articles/6731.html)

[缓存更新的套路](http://coolshell.cn/articles/17416.html)

[给Java说句公道话](http://www.yinwang.org/blog-cn/2016/01/18/java)

[我们为什么需要React?](https://www.zhihu.com/question/47161776#answer-40022112)

[如何评价数据流管理架构 Redux?](https://www.zhihu.com/question/38591713)

[React.js 资料和教程](https://github.com/thoughtbit/it-note/issues/12)

[深入浅出 - Redux](http://www.w3ctech.com/topic/1561)

[精益 React 学习指南 （Lean React）](https://zhuanlan.zhihu.com/p/21107252)

[众成翻译](http://www.zcfy.cc/)

[Javascript作用域原理](http://www.laruence.com/2009/05/28/863.html)

[闭包--Closures](http://jscode.me/topic/146/%E9%97%AD%E5%8C%85-closures)

[子回技术博客](http://blog.leapoahead.com/)



hid say：重复是学习之道。
