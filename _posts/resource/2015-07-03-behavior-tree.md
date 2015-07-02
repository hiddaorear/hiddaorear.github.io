---
layout: post
title:  Behavior tree(1)
category: 资源
tags: [AI]
keywords: behavior tree 
description: 
---

### Behavior tree(1)

#### Friday, 03 July 2015

![齐白石](/../../assets/img/resource/2015/qibaishi_19.jpg)

深究了一下Promise的本质，发现其实其本质就是一个简单的有状态机（只有两个确定的状态，成功或者失败）。如果用行为树来分析，那么其组织形式应该是通过状态组织的，而非事件。因为事件可以有多种，而状态可以只有两种，要么成功要么失败。由于状态只有两种，也就避免了状态的优先级问题，在此情况下是较佳的实现。

web编程中事件是重中之重，那么是根据事件还是根据状态来组织行为树呢？将状态和事件组织为一张二维表格，事件为一列，状态一行，即可描述行为。前者可以竖向，后者为横向。

横向有缺点:
1. 状态有先后顺序，而有时候这是不必的;
2. 每个状态的事件是不定的，无法事先确定，需要通过查询的方式实现，不优雅;


### 参考资料
[有限状态机的编程思想 - 盛超電子的博客 - 与非博客 - 与非网](http://www.eefocus.com/lingaogang/blog/10-05/189950_24895.html)
[AI逻辑实现-用行为树取代状态机 - 移动开发之旅 - 博客频道 - CSDN.NET](http://blog.csdn.net/goodeveningbaby/article/details/42213149)
[有限状态机时代终结的10大理由 - 赖勇浩的编程私伙局 - 博客频道 - CSDN.NET](http://blog.csdn.net/gzlaiyonghao/article/details/2070675)
[共享节点型的行为树架构（1） | AI分享站](http://www.aisharing.com/archives/563)
[JavaScript异步编程原理 - Barret Lee - 博客园](JavaScript异步编程原理 - Barret Lee - 博客园)
[BehaviourTree AI 行为树AI 实现的一些总结思考 | 青的點滴](http://www.ispinel.com/2015/04/25/12466/)
[http://www.chenjunxyf.me/](风影博客)
[SHA1和MD5算法详解和源码 - fullsail - 博客园](http://www.cnblogs.com/fullsail/archive/2013/02/22/2921505.html)
[阅微堂 » 计算机科学](http://zhiqiang.org/blog/category/science/computer-science)


hid say: 计算逻辑的深入，到一定层次，会遇到其算法或数学。从来就没有新的技术，而是不同实现而已。
