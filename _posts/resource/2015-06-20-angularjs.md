---
layout: post
title:  AngularJS(1)
category: 资源
tags: [JavaScript AngularJS]
keywords: AngularJS 
description: 
---

### AngularJS(1) 

#### Saturday, 20 June 2015

![齐白石](/../../assets/img/resource/2015/qibaishi_16.jpg)

AngularJS学习笔记，所参考的原程序有误，均已修正。

### Hello Wrold

````html

<!DOCTYPE html>
<!--[if lt IE 7]>
<html class="no-js lt-ie9 lt-ie8 lt-ie7"> <![endif]-->
<!--[if IE 7]>
<html class="no-js lt-ie9 lt-ie8"> <![endif]-->
<!--[if IE 8]>
<html class="no-js lt-ie9"> <![endif]-->
<!--[if gt IE 8]><!-->
<html class="no-js"> <!--<![endif]-->
<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1">
    <title>Angular Hello World</title>
    <script type="text/javascript" src="../bower_components/angular/angular.js"></script>
    <script type="text/javascript" src="./demo-app.js"></script>
    <script type="text/javascript" src="./demo-controller.js"></script>
</head>
<body data-ng-app="myApp">
  <div ng-controller="MyCtrl">
      {{hellos}} 
  </div>
</body>
</html>

````

````javascript
'use strict';

var myApp = angular.module('myApp', []);

myApp.service('helloWorldService', function() {
  this.sayHello = function() {
    return "Hello, World! service";
  };
});

myApp.factory('helloWorldFactory', function() {
  return {
    sayHello: function() {
      return "Hello, World! factory";
    }
  };
});

myApp.provider('helloWorldProvider', function() {

  this.$get = function() {
    var name = this.name;
    return {
      sayHello: function() {
        return 'Hello, ' + name + '! provider';
      }
    }
  };

  this.setName = function(name) {
    this.name = name;
  };
});


myApp.config(function(helloWorldProviderProvider) {
  helloWorldProviderProvider.setName('World');
});


myApp.controller('MyCtrl', function ($scope,  helloWorldFactory, helloWorldService, helloWorldProvider) {
 $scope.hellos = [
    helloWorldService.sayHello(),
    helloWorldFactory.sayHello(),
    helloWorldProvider.sayHello()
   ]; 
});


````

### AngularJS implements dirty checking

````javascript

var Scope = function() {
  this.$$watchers = [];
};

Scope.prototype.$watch = function(watchExp, listener) {
  this.$$watchers.push({
    watchExp: watchExp
    ,listener: listener || function() {}
  });
};

Scope.prototype.$digest = function() {
  var dirty;

  do {
    dirty = false;

    for (var i = 0; i < this.$$watchers.length; i++) {
      var newValue = this.$$watchers[i].watchExp();
      var oldValue = this.$$watchers[i].last;

      if (oldValue !== newValue) {
        this.$$watchers[i].listener(newValue, oldValue); 

        dirty = true;

        this.$$watchers[i].last = newValue;
      }
    }
  } while(dirty);
};

//test 

var $scope = new Scope();
$scope.name = 'Ryan';
$scope.$watch(function() {
  return $scope.name;
}, function(newValue, oldValue) {
  console.warn(newValue, oldValue); 
});

$scope.$digest();

````


### 参考资料：
[How AngularJS implements dirty checking and how to replicate it ourselves](http://ryanclark.me/how-angularjs-implements-dirty-checking/)
[彻底弄懂AngularJS中的transclusion - 用Angular开发web应用 - 前端乱炖](http://www.html-js.com/article/Using-Angular-to-develop-web-application-completely-understand-AngularJS-transclusion)
[AngularJS: 使用Scope时的6个陷阱 - 用Angular开发web应用 - 前端乱炖](http://www.html-js.com/article/2000)
[AngularJS 数据双向绑定揭秘 - 用Angular开发web应用 - 前端乱炖](http://www.html-js.com/article/2145)
[使用超动感HTML & JS开发WEB应用! | AngularJS中文社区](http://www.angularjs.cn/A00x)
[]()
[[AngularJS] 仿照Angular Bootstrap TimePicker创建一个分钟数-秒数的输入控件](http://blog.csdn.net/dm_vincent/article/details/42612189)
[有jQuery背景，该如何用AngularJS编程思想？ - 博客 - 伯乐在线](http://blog.jobbole.com/46589/)
[七步从Angular.JS菜鸟到专家（1）：如何开始 - 博客 - 伯乐在线](http://blog.jobbole.com/46779/)
[表单控件 | AngularJS学习笔记](http://checkcheckzz.gitbooks.io/angularjs-learning-notes/content/chapter7/7-5.html)
[如何在AngularJS指令中创建controller与ngModel进行交互 - 用Angular开发web应用 - 前端乱炖](http://www.html-js.com/article/Using-Angular-to-develop-web-application-to-AngularJS-instruction-to-create-controller-interacts-with-ngModel)

hid say: 后端的思维。

Tips:

````javascript

var IsMobile = navigator.userAgent.toLowerCase().match(/Mobile/i)!==null;

if ( !-[1,] ) { 
    alert("IE6-8"); 
} else { 
    alert("Not IE"); 
}


````
