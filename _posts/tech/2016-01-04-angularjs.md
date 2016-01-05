---
layout: post
title:  AngularJS笔记
category: 技术
tags: [AngularJS]
keywords: AngularJS
description:
---

##### Monday, 04 Jan 2016

### AngularJS笔记

![Jobs](/../../assets/img/tech/2016/jobs_4.jpg)

#### 一下均为笔记，原文地址见参考资料。

### Controller

两种controller写法：

1. 带`$scope`

````javascript

function TestCtrl($scope) {
  $scope.counter = 0
  
  $scope.inc = function() {
    $scope.counter++
  }
}

````

````html
<div ng-controller="TestCtrl">
  {{counter}}
  <button ng-click="inc()">+1</button>
</div>
````

2. 不带`$scope`的写法

````javascript

function TestCtrl() {
  this.counter = 0
  
  this.inc = function() {
    this.counter++
  }
}

````

````html
<div ng-controller="TestCtrl as test">
  {{test.counter}}
  <button ng-click="test.inc()">+</button>
</div>
````

虽然区别只是里面没有了`$scope`，但是这意味着controller以及不再是独立的cuntroller，而是view model，controller代码对应一个界面片段，使得其更加纯净。

从形式上讲，如此使用`this`的写法，更具有JavaScript原原本本的形式。有了`this`面向对象与函数是更发挥的空间。



### 参考资料:
[后Angular时代二三事](https://github.com/xufei/blog/issues/21)

hid say: 深化。



