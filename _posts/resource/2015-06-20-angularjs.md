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

###  `ng-repeat`

API:
`$index`当前索引
`$first`是否为头元素
`middle`是否为非头元素
`$last`是否为尾元素

````javascript
var TestCtrl = function($scope) {
  $scope.obj_list = [1, 2, 3, 4];
};

<div ng-controller="TestCtrl">
  <ul ng-repeat="member in obj_list">
    <li>{{member}}</li>
  </ul>
</div>
````
`ng-repeat`遍历对象时，并非是按照我们定义key的排序的。因为JavaScript Obejct本身就不保证key之间的排序。

> ECMAScript 3 An object is a member of the type Obejct, it is an unordered collection of which contains a primitive value, object of function.

但在`for in`中有一定的顺序：
1. 对于类型是number或者可以转换为整数的number的string类型的key，会按照number大小顺排序，类似数组。
2. 对于alphanumerical string类型的key，`for in`会按照定义object时的key排序。

故，对于`ng-repeat`,AngularJS可能有内部的排序，依靠object key排序是不可靠的，若有需要，最好用数组。

### scope of `ng-repeat`

实现单选框，可以从`$scope.SelectValue`中获取选中的value。

````javascript
blue:<input type="radio" value="1" ng-model="SelectValue">

red:<input type="radio" value="2" ng-model="SelectValue">

yellow:<input type="radio" value="3" ng-model="SelectValue">
````

`ng-repeat`的实现

````javascript
<ul ng-repeat="row in collections">
  <li>
    {{row.name}}:<input type="radio" value="{{row.value}}" ng-model="SelectValue"
  </li>
</ul>

````

点击对话框，`$scope.SelectValue`中值并没有保存对应单选框的值。
因为`ng-repeat`会创建自己的子scope，对全局的`$scope`是不可见的。所以如果要引用全局`$scope`里的成员，可以使用`$parent`来引用全局的`$scope`。

````javascript
<ul ng-repeat="row in collections">
  <li>
    {{row.name}}:<input type="radio" value="{{row.value}}" ng-model="$parent.SelectValue"
  </li>
</ul>

````

### AngularJS 视图模型的层次
如果有视图的包含关系，内层视图对应的作用域可以共享外层作用域的数据。

````javascript
var app = angular.module('test', [])
.controller('OuterCtrl', function($scope) {
    $scope.a = 1;
  })
.controller('InnerCtrl', function($scope) {
    $scope.b = 2;
  });
<body ng-app="test">
  <div ng-controller="OuterCtrl">
    <span ng-bing="a"></span>
    <div ng-controller="InnerCtrl">
      <span ng-bind="a"></span>
      <span ng-bind="b"></span>
    </div>
  </div>
</body>

````

因为在AngularJS内部，InnerCtrl的实例的原型会被设置为OuterCtrl的实例。所以内层改变外层变量的值，不会影响到外层。

### `ng-controller`

### `$scope`对象的职责是继承DOM中指令所共享的操作和模型。
1. 操作是指`$scope`上的标准的JavaScript方法；
2. 模型是指`$scope`上保存的包含瞬时状态数据的JavaScript对象。持久化状态的数据应该保存到服务中，服务的作用是处理模型的持久化；
3. 处于技术和架构方面的原因，绝对不要直接将控制器中的`$scope`赋值为值类型对象（字符串，布尔值或数字）。DOM中应该始终通过点操作符`.`来访问数据。以避免不可预期的麻烦；
4. 控制器应该尽可能简单。虽然可以用控制器来组织所有的功能，但是将业务逻辑移到服务和指令中是非常好的注意。

> 内置指令`ng-contoller`的作用是为嵌套在其中的指令创建一个子作用域，避免将所有操作和模型都定义在`$rootScope`上。用于在DOM放置控制器。

> 子`$scope`只是一个JavaScript对象，其中含有从父级`$scope`通过原型继承得到的方法和属性，包含`#rootScope`。
### 嵌套在`ng-controller`中的指令有访问子`$scope`的权限。由于原型继承的关系，修改父级对象中的值会修改子对像中的值，反之则不行。

> JavaScript对象要么是值复制要么是引用复制。字符串，数字，布尔值是值复制，而数组，对象和函数表达式则是引用复制。

> 如果将模型对象的中属性设置为字符串，他会通过引用进行共享，在子`$scope`修改也会修改`$scope`的属性。

````javascript

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
    <title>Angular Tab </title>
    <style type="text/css">
    </style>
    <script type="text/javascript" src="../bower_components/angular/angular.js"></script>
</head>
<body ng-app="ControllerApp">
  <div id="tabs" ng-controller="ParentCtrl">
   {{someModel.someValue}}
   <button ng-click="someAction()">parent</button>
   <div ng-controller="ChildrenCtrl">
    {{someModel.someValue}}
    <button ng-click="childAction()">chlid</button>
   </div>
  </div>

  <script type="text/javascript">
  angular.module('ControllerApp', [])
  .controller('ParentCtrl', ['$scope', function($scope) {
    $scope.someModel = {
      someValue: 'hello computer'
    };
    $scope.someAction = function() {
      $scope.someModel.someValue = 'hello human, from parent.';
    };
  }])
  .controller('ChildrenCtrl', ['$scope', function($scope) {
    $scope.childAction = function() {
      $scope.someModel.someValue = 'hello human, from child.';
    };
  }])
  </script>
 </body>
</html>

````



### 参考资料：

### ng-repeat
[AngularJS源码阅读之ngRepeat](http://loveky.github.io/2014/04/02/angularjsngrepeat/)
[AngularJS中如何去掉 ng-repeat的自动排序？](http://www.zhihu.com/question/28707241)
[Angular新手容易碰到的坑，随时更新，欢迎订阅 - AngularJS Nice Things](http://www.ngnice.com/posts/2c8208220edb94)
[angular controller as syntax vs scope - 破狼 - 博客园](http://www.cnblogs.com/whitewolf/p/3493362.html)
[AngularJS ng-repeat下使用ng-model 转 - 叶知秋红 - 博客园](http://www.cnblogs.com/zifeiyu/p/3765864.html)
[AngularJS沉思录（二） 视图模型的层次 - Div.IO](http://div.io/topic/583)
[AngularJS最佳实践: 请小心使用 ng-repeat 中的 $index - renfufei的专栏 - 博客频道 ](http://blog.csdn.net/renfufei/article/details/43061877)
[AngularJS最佳实践: 请小心使用 ng-repeat 中的 $index](https://github.com/cncounter/translation/blob/master/tiemao_2015/04_ng_repeat_%24index/ng_repeat_%24index.md)
[AngularJS性能优化心得 · Issue #5 · atian25/blog](https://github.com/atian25/blog/issues/5)
[使用超动感HTML & JS开发WEB应用! | AngularJS中文社区](http://angularjs.cn/A0lr)


### AnguarlarJS introduction
[AngularJS 应用身份认证的技巧 - Coding 博客](https://blog.coding.net/blog/techniques-for-authentication-in-angular-js-applications)
[七步从Angular.JS菜鸟到专家（2）：Scopes - 博客 - 伯乐在线](http://blog.jobbole.com/48593/)
[AngularJS学习笔记 - 进出自由,我的分享](http://www.zouyesheng.com/angular.html)
[How AngularJS implements dirty checking ](http://ryanclark.me/how-angularjs-implements-dirty-checking)
[彻底弄懂AngularJS中的transclusion - 用Angular开发web应用 - 前端乱炖](http://www.html-js.com/article/Using-Angular-to-develop-web-application-completely-understand-AngularJS-transclusion)
[AngularJS: 使用Scope时的6个陷阱 - 用Angular开发web应用 - 前端乱炖](http://www.html-js.com/article/2000)
[AngularJS 数据双向绑定揭秘 - 用Angular开发web应用 - 前端乱炖](http://www.html-js.com/article/2145)
[使用超动感HTML & JS开发WEB应用! | AngularJS中文社区](http://www.angularjs.cn/A00x)
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
