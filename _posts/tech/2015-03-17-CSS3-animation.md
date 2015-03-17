---
layout: post
title: CSS3 animation and JavaScript
category: 技术
tags: [JavaScipt, CSS3]
keywords: JavaScript
description: 
---


## CSS3动画配置初步方案

### 缘由

去年做了很多微信上的活动页面，每次做了很多重复的工作。总想找时间把代码整理一下，由于一直都忙着，不能如愿。移动端的滑动切换活动页面有很多成熟的方案，一些是高手的作品。我当时也想自己写一个轻量级的作品，不依赖其他的JavaScript库和框架，又苦于不能把DOM的结构处理我想要的形式，后来学习数据结构和算法，发现循环链表恰好可以满足我对DOM结构的要求。以此为突破点，加上看了jQuery和一些牛人的代码，慢慢沉淀下来了一些代码。到今天，我新增了CSS3动画写JavaScript中代码，实现CSS3动画的代码分离。把去年大半年的工作，做一个总结。过去一年了，记录一下自己的成长，任重而道远。


### 架构
完成了一个基础函数库c.js，提供基本的函数。每个函数基本独立，稍微改动就可以独立拿出来使用。

#### c.j函数库

- extend  与jQuery的extend代码一样，主要用来合并对象属性；
- tools   对象中目前主要有判断是否为函数、数组、对象的三个函数，还有一个前端调试的方便很DOM元素在浏览器中大小的调试辅助函数，其要点就是给原始设置不同颜色的outline；
- time    目前只有一个函数，debounce函数，参考了Underscore.js的代码；
- events  swipe函数是用来判断在手机屏幕上滑动的函数，实现对四个方向的监听，有参数设置，避免Hammer.js等手势库在一些情况不能使用的情况；
- dom     是一个与dom查询和图片加载的函数，图片加载函数很好用，手机图片达到2M时，也能很好的处理；
- css     只有两个函数，一个是判断浏览器前缀的函数，另一个是设置css的函数；
- circular_list 是循环列表的代码，这个数据结构的代码主要是我自己写就的，还有很多需要优化的地方；


#### animation.js中CSS3动画配置

- _default  是CSS3动画属性默认设置，还有我自己定义一些为了设置动画之间的衔接所设置的属性；
- _options  CSS3动画设置的主要内容，通过hook关联到DOM元素，然后设置动画属性，该属性的设置可以略去默认设置。因为通过extend方法合并了_default中属性；
- no_css    属性中非CSS3动画属性的部分，在设置CSS3属性时候，需要把这一部分忽略；


##### _options 参数设置详解

```javascript

    {
     'hook': '.site_text'
      ,'parent': _.dom.selector('.PageWrapper')[2]
      ,'superposition': false
      ,'asynchronization': false
      ,'name': [0, 'blurInDown', 'blurInLeft', 'blurInRight', 'blurInUp']
      ,'adjust': '0'
      ,'animation-delay': '1s'
      ,'animation-duration': '0.3s'
      ,'animation-fill-mode': 'both'
      ,'animation-timing-function': 'linear' 
    }
    
```

_options是一个数组，数组元素是对象。

- hook              是对应的选择器，支持类名（.前缀），ID（#前缀），标签名，目前只能支持单独的选择器，不能通过类似".a .b"之类的选择器来获取元素；
- parent            相应DOM元素的父元素；
- superpostion      是否需要在前一个CSS3属性的基础累加delay延迟时间。若为false，则不累加。为true则累加，累加会自动加上上一个元素的“animation-delay”和“animation-duration”属性的值。如果“animation-duration”值较大，可能不符合预期，故提供“adjust”属性，见下；
- adjust            支持调节“animation-delay”的值；
- animation-delay   设置动画的延迟；
- animation-duration设置动画的周期
- animation-fill-mode设置动画属性规定动画在播放之前或之后，其动画效果是否可见；
- animation-timing-function 设置动画时间函数；


还可以设置其他CSS3动画属性，不一一列出了。

在手机测试，在低端手机的浏览器上表现良好，在微信里面略有问题。

这是这个系列的第一篇，我会逐步把c.js中函数解析一下，以感谢那些分享知识的人，感谢ssb和我的同事们，感谢PAN，谢谢一年来你们陪伴我的时间。


### 代码（涉及公司权益，由于大部分代码是我平时所写，故开源，但里面内容是公司的）
[项目相关代码](https://github.com/hiddaorear/study/tree/master/2015_03_11_hr)
