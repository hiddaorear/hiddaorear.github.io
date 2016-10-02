---
layout: post
title:  Project summary(1)
category: 资源
tags: [seaJS jQuery Less git grunt project]
keywords: seaJS jQuery Less git grunt
description: 
---

### Project summary

#### Wednesday, 27 May 2015

![吴昌硕](/../../assets/img/resource/2015/qibaishi_8.jpg)

> Nobody can go back and start a new begining, but anyone can start now and make a new ending.

### Project summary(1)

做完了项目的第一个版本，上线之后看到很多人在用，很是高兴。初到深圳做的第一个项目，虽在线上，但至今无人使用。这种心情，很是欣慰。

我是一个好高骛远的人，记录以下缺点，提醒自己，要有初心。

1. jQuery的使用
我是一个有原生JavaScript的人，以前甚至着手写了自己的框架。然而，破的前提是立，熟悉传统，才能改进传统。以前意味的原生情节，导致jQuery不熟悉，使用起来不顺手。这样，必然导致速度不快。

同时，一些常见的交互场景，缺乏经验，想出来的方案很拙劣。这个以后在github，自己封装相关的模块，时间充裕，原生的也实现一套。为以后移动端性能优化做准备。

对DOM的操作，须如做手术一样精确，笼统的方案，无论多么忙，一定要思考再三。DOM如不精确，会导致以后非常多的问题，调整起来很头痛。部分DOM结构的更改，如有必要须及时向后端提出。

与后端交互的部分，接口一定要定义好。对于Ajax，需要进一步研究。

对于一个读了jQuery源码的人，把jQuery用成这样，自打三十大板。

2. 响应式支持
响应式的支持，是从DOM结构开始的。尽量避免使用JavaScript，在响应式中调整DOM结构。做之前，就需要规划好。需要总结出一个响应式的方案，目前是针对不同屏幕，头痛医头，脚痛医脚，乱了手脚，也容易出现遗漏的部分。一定要细心。

3. fiddler
前端调试工具。用处很大，可以在线上环境中，使用本地的文件。这个工具的使用，在鹅场遇到了小贝和寿哥的提问，在这个点上完爆了，嗯，我记住你俩了。

4. grunt
前端工程化的工具。

5. git
git在多人协作的情况下，使用需要谨慎。虽然在github游荡了这么久，但都是一个人在玩。

6. 时间管理
一句话，以终为始。
胡适先生说：怎么收获，怎么栽种。

2015-05-30

### Project summary(2)

用AngularJS做完一个项目，体会了模块化与双向绑定的好处，对jQuery的灵活与便捷所带来的益处就有所顾虑。编写jQuery不容易写出好的模块化代码（当然是在功力较低的水准上而言），而AngularJS天然的让代码模块化，稍微体会了一点程序架构方面的重要性，如兵法中的将领，是五事七计中的五事之四。

同时，这次的代码美观整洁是以前没法比的，也体会到排版美观的重要，至少修改的时候一目了然，看了自己也赏心悦目。同时发现有时候，用Gvim加空格对齐时，有附带审查一下代码，也有益处。

然而bug生产量还是很多，有一部分是前期没有思考周到，后期补功能时产生的，所幸这次程序写得可读性较好，模块化与用面向对象组织函数，使得修改时不至于很困难。

总结一下：

### 1. KISS原则：
我们只是知道有这么一条原则，至于为什么如此，就需要有切身体会才能明了一二。曾有人问一个函数多大比较合适，答曰：头能装下。曰：这是多大？答曰：把你头放在屏幕上的投影，程序长度不能超过这投影。虽是幽默，但也有真谛。因为人的记忆力是有限的，短期程处理的变量个数也是有限的，大概也就6到7个变量而已。而程序是对这些变量的精确的操作，所以为了不至于复杂而出错，应当使得每一部分尽可能简洁，变量尽可能少，能使得人能记住，并能自如的在大脑里操作。

但不是所有的逻辑都能简化为6个左右的变量能处理，所以有了高级变量，即把变量与函数组织起来，看起来可以当作一个变量处理，这就有了面向对象之类的技术。

程序的本质在于对变量操作，好比一个水管，水是变量，管子是函数，有一个加热的函数对应于一个加热的管子，水流进管子，即函数处理变量。人大脑的记忆与能力的局限，使得KISS很有必要。

### 2. 模块化
从简陋的意义上理解，模块化相对于增加了命名空间而已。从形象上理解，就相当于把一类变量与函数装箱，一堆苹果散放在桌上，不方便搬动，但放在箱子里，就较易处理。命名空间就是这个箱子。但这样子有一个害处，如果不打开箱子，就不知道里面装的是苹果。所以顶层的命名很重要，相当于箱子上的商标，需要体现箱子里面内容。

装箱以后，我们处理的不再是一个一个的苹果，而是一个一个箱子，这样才能较为轻松的管理大型程序。

### 3. 错误类型
记录一下错误类型：

1. 名字拼错了。这类低级错误很常见，有时候又不容易发现，现在处理也只能用Gvim的`#`之类的功能来看看变量名是否一致。从本质上讲，其实是对变量使用的不重视，一个变量使用时应该记住，这样也可以促使自己使得变量尽可能少，写出简明的代码。

2. 初始条件。一个逻辑的初始条件与终止条件非常重要，而我往往注意中间的过程，而忽略了初始与终止条件，可能因为没有全局思维，只注重单方面功能的实现。从本质上讲，编写之前没有思考程序运行的过程，只好的办法是动手之前，程序在大脑里运行几遍，到呼之欲出的程度再写代码。

3. 原理不熟悉。对于API不熟悉，会导致很多问题，首当其冲的是编程的速度很慢，其实是容易滋生bug。很多API还是有必要记住。框架的原理也要深入理解，不然使用起来就不得心应手。


最近用Node体会了一些后端编程，很有意思，想深入了解一下。

2015-07-30

### 参考资料：

### git
1. rebase
[git rebase小计(转) - 飞林沙](http://www.cnblogs.com/kym/archive/2010/08/12/1797937.html)

[使用 git rebase 避免無謂的 merge](https://ihower.tw/blog/archives/3843)

[关于git rebase和git merge - MinGKai的个人空间](http://my.oschina.net/MinGKai/blog/142517)

[Git Book 中文版 - rebase](http://gitbook.liuhui998.com/4_2.html)

[Git 少用 Pull 多用 Fetch 和 Merge - 技术翻译](http://www.oschina.net/translate/git-fetch-and-merge)

2. rerere
[你可能不知道的 git rerere » 社区 » Ruby China:](https://ruby-china.org/topics/15809)
[Git历险记（五）——Git里的分支＆合并](http://www.infoq.com/cn/news/2011/03/git-adventures-branch-merge)


3. trick 
[图解Git](https://marklodato.github.io/visual-git-guide/index-zh-cn.html#rebase)

[对于解决 Git 的 Merge Conflict 你有哪些经验和技巧？ - 知乎](http://www.zhihu.com/question/21215715)

[Git索引 | 猴子都能懂的GIT入门| 贝格乐](http://backlogtool.com/git-guide/cn/reference/)

[Git - 远程分支](http://git-scm.com/book/zh/v1/Git-%E5%88%86%E6%94%AF-%E8%BF%9C%E7%A8%8B%E5%88%86%E6%94%AF)

[解决冲突 - 廖雪峰的官方网站](http://www.liaoxuefeng.com/wiki/0013739516305929606dd18361248578c67b8067c8c017b000/001375840202368c74be33fbd884e71b570f2cc3c0d1dcf000)

### sublime
[sublime text 3解放鼠标的快捷键总结 – Dengo-淡高 - -关于计算机和互联网的那些事](http://dengo.org/archives/970)

### DOM
[document节点 -- JavaScript 标准参考教程（alpha）](http://javascript.ruanyifeng.com/dom/document.html)

[scrollTop | anjia](http://anjia.github.io/2014/11/08/jsScrollTop/)

[两个viewport的故事（第一部分）](http://weizhifeng.net/viewports.html)

[开发一个完整的JavaScript组件 - Div.IO](http://div.io/topic/831)


### Fiddler
[使用Fiddler| 微软WEB技术培训](http://te-webtraining.azurewebsites.net/cn/samples/using-fiddler.html)

[阿里巴巴（中国站）用户体验设计部博客 » 使用Fiddler提高前端工作效率 (实例篇)](http://www.aliued.cn/2010/04/25/use-fiddler-to-improve-efficiency-of-front-development-example.html)

[Web调试利器fiddler介绍-raochaoxun-ChinaUnix博客](http://blog.chinaunix.net/uid-27105712-id-3738821.html)

[使用fiddler提高前端开发效率 - lavachen.cn-一个程序猿的技术博客](http://www.lavachen.cn/?post=31)

[看懂 Fiddler 的瀑布图 | JerryQu 的小站](https://www.imququ.com/post/timeline-in-fiddler.html)

[谈谈Fiddler](http://zxhfighter.github.io/blog/javascript/2013/05/10/talk-about-fiddler.html)

[使用fiddler进行安卓手机抓包 - SegmentFault](http://segmentfault.com/a/1190000002597285)

[web debugger fiddler 使用小结 - for certain - 博客园](http://www.cnblogs.com/forcertain/archive/2012/11/29/2795139.html)

[使用fiddler模拟http请求 - 麒麟 - 博客园](http://www.cnblogs.com/zhuqil/archive/2011/10/11/2206918.html)

[网络抓包工具 - Fiddler使用方法 - 微软互联网开发支持 - 博客园](http://www.cnblogs.com/developersupport/archive/2013/03/24/fiddler.html)

[本文介绍Android及IPhone手机上如何进行网络数据抓包](http://www.trinea.cn/android/android-network-sniffer/)

[【HTTP】Fiddler（二） - 使用Fiddler做抓包分析](http://blog.csdn.net/ohmygirl/article/details/17849983)

[Fiddler高级进阶——使用自定义脚本 - 专栏 [] - 前端乱炖](http://www.html-js.com/article/The-frontend-tool-Fiddler-senior-advanced--using-a-custom-script-to-achieve-cross-domain-and-by-the-port-or-changing-directory-hosts)


### grunt
[Grunt: JavaScript世界的构建工具 -- Grunt中文网](http://www.gruntjs.net/)

[【grunt整合版】30分钟学会使用grunt打包前端代码 - 叶小钗 - 博客园](http://www.cnblogs.com/yexiaochai/p/3603389.html)

[Grunt打造前端自动化工作流-TGideas-腾讯游戏官方设计团队](http://tgideas.qq.com/webplat/info/news_version3/804/808/811/m579/201307/216460.shtml)

[Grunt教程——初涉Grunt | css3教程-css3实例-css3动画 | W3CPlus](http://www.w3cplus.com/tools/grunt-tutorial-start-grunt.html)



hid say:虽是光阴如梭，急了就织错了。不急。
