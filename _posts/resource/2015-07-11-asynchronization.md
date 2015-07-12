---
layout: post
title:  Monad(1)
category: 资源
tags: [monad, group]
keywords: monad 
description: 
---

###  Monad(1)

#### Saturday, 11 July 2015

![齐白石](/../../assets/img/resource/2015/qibaishi_21.jpg)

> Monad不就是自函子范畴上的幺半群，这有什么难理解的。
  --Phillip Wadler

> ### Group
G为非空集合，如果在G上定义了二元运算*,满足
1. Closure(封闭性):对于任意a，b∈G，有a*b∈G
2. Associativity(结合律)任意a，b，c∈G，有（a*b）*c=a*（b*c）
3. Identity(幺元):存在幺元e，使得对于任意a∈G，e*a=a*e=a
4. 逆元:对于任意a∈G，存在逆元a^-1，使得a^-1*a=a*a^-1=e
则称(G, *)是群，简称G是群。

如果仅满足Closure和Associativity，则称G是一个半群(Semigroup);
如果Semigroup有Identity，则称G是一个Monoid(幺半群);

### 异步
异步函数调用与普通函数调用的本质区别是，异步函数调用将函数的执行分为两个阶段：
1. 未执行完；
2. 执行完；
因此，只要能实现这两种状态转换时的函数调用，本质上等价于异步函数调用。

异步实现的五种形式:
1. Callback;
2. Event;
3. Observer Pattern;
4. Promise;
5. Generator;

Callback以函数栈，实现当前函数执行完毕，立即执行回调函数；
事件与观察者模式，以信号传递区分了事件发生前与事件发生后，两个状态，并监听事件执行下一个状态的函数；
Promise,通过简单的状态机（两种状态，成功与失败），将横向的回调形式，变换为竖向的形式；
Generator将函数的状态增加，函数原只有两个状态，调用与执行完毕。而Generator的yiel可以暂停函数的执行，并转移控制权；
由于Generator的迭代器可以返回值与传值，非常方便错误的处理与函数间的传值，天生就适合来处理异步。

### 参考资料

### `yield & generators`
[协程的好处是什么？ - 知乎](http://www.zhihu.com/question/20511233)
[提高你的Python: 解释‘yield’和‘Generators（生成器）’ - 技术翻译 - 开源中国社区](http://www.oschina.net/translate/improve-your-python-yield-and-generators-explained)
[Harmony Generator, yield, ES6, co框架学习](http://bg.biedalian.com/2013/12/21/harmony-generator.html)
[用ES6 Generator替代回调函数 - 每天学点javascript - 前端乱炖](http://www.html-js.com/article/A-day-to-learn-JavaScript-to-replace-the-callback-function-with-ES6-Generator)
[异步流程控制：7 行代码学会 co 模块 - SegmentFault](http://segmentfault.com/a/1190000002732081)
[ES6 Generator介绍 | Web前端 腾讯AlloyTeam Blog | 愿景: 成为地球卓越的Web团队！](http://www.alloyteam.com/2015/03/es6-generator-introduction/)

### CPS
[怎样理解 Continuation-passing style? - 知乎](http://www.zhihu.com/question/20259086)

### `monad` 
[我所理解的monad(0) | 写点什么](http://hongjiang.info/understand-monad-0/)
[我所理解的monad(1)：半群(semigroup)与幺半群(monoid) | 写点什么](http://hongjiang.info/semigroup-and-monoid/)
[我所理解的monad(2)：fold与monoid | 写点什么](http://hongjiang.info/fold-and-monoid/)
[我所理解的monad(3)：半群(semigroup)与并行运算 | 写点什么](http://hongjiang.info/semigroup-and-parallel/)
[我所理解的monad(4)：函子(functor)是什么 | 写点什么](http://hongjiang.info/understand-monad-4-what-is-functor/)
[我所理解的monad(5)：自函子(Endofunctor)是什么 | 写点什么](http://hongjiang.info/understand-monad-5-what-is-endofunctor/)
[我所理解的monad(6)：从组合子(combinator)说起 | 写点什么](http://hongjiang.info/understand-monad-6-combinator/)
[我所理解的monad(7)：把monad看做行为的组合子 | 写点什么](http://hongjiang.info/understand-monad-7-action-combinator/)
[论面向组合子程序设计方法 之一 创世纪 - ajoo - BlogJava](http://www.blogjava.net/ajoo/articles/27838.html)
[翻译 monads-are-elephants 第三部分 | 写点什么](http://hongjiang.info/monads-are-elephants-part3-chinese/)

[Functors, Applicatives, And Monads In Pictures - adit.io](https://www.evernote.com/shard/s279/sh/a3b59986-0488-4914-bbbd-633161565c92/f69ab4eda37ab94ba71528a102ce5472)
[Haskell与范畴论](http://yi-programmer.com/2010-04-06_haskell_and_category_translate.html)

### Continuation
[尾递归与Continuation - 老赵点滴 - 追求编程之美](http://blog.zhaojie.me/2009/03/tail-recursion-and-continuation.html)
[Continuation与CPS（Continuation Passing Style）的理解 - 大尾巴龙](http://daweibalong.iteye.com/blog/1882795)

### Coroutine
[协程的好处是什么？ - 知乎](http://www.zhihu.com/question/20511233)


### Generator
[Generator与异步编程](http://www.infoq.com/cn/articles/generator-and-asynchronous-programming)
[Generator 函数的含义与用法 - 阮一峰的网络日志](http://www.ruanyifeng.com/blog/2015/04/generator.html)
[Thunk 函数的含义和用法 - 阮一峰的网络日志](http://www.ruanyifeng.com/blog/2015/05/thunk.html)
[Functional JavaScript Mini Book](http://blog.oyanglul.us/javascript/functional-javascript.html#sec-2-2)
[Iterator和for...of循环 - ECMAScript 6入门](http://es6.ruanyifeng.com/#docs/iterator)
[异步编程之Generator（1）：领略魅力 - FED社区](http://frontenddev.org/link/asynchronous-programming-of-the-generator-1-enjoy-charm.html)
[异步编程之Generator（2）：剖析特性 - FED社区](http://frontenddev.org/link/the-generator-of-asynchronous-programming-2-analyze-the-characteristics.html)
[异步编程之co：源码分析 - FED社区](http://frontenddev.org/link/co-of-asynchronous-programming-source-code-analysis.html)
[Javascript Generator - 函数式编程 - Javascript核心 - SegmentFault](http://segmentfault.com/a/1190000000515173)


hid say: 寻本溯源
