---
layout: post
title:  this拾遗
category: 资源
tags: [review]
keywords: review
description:
---

### this拾遗

#### this拾遗

###  Monday, 14 November 2016

![cassini](/../../assets/img/resource/2016/cassini_21.jpg)

### ES7中的`::`

````javascript

  this.x = 0
  let module = {
    x: 1,
    getX: function() {
      console.log(this.x)
    }
  }
  module.getX()
  let get = module.getX
  get() // 0
  let boundGetX = get.bind(module)
  boundGetX() // 1
  let ES7boundGetx = module::get
  ES7boundGetx() // 1

````

### jQuery中的end()

### call, apply, bind

### 箭头函数

### super

### 为什么设计this？

### this指向的改变

### 利与弊

### 不同环境中的this值

### 拾遗

this可被重新赋值么？（不能，this是保留字）


