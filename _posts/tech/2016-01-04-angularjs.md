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

### module

module只能设置一次。

````javascript
// set module
angular.module('app', [])
````

````javascript
// get module
angular.module('app')
````

回调函数使用函数，而非匿名函数。为了易读，减少嵌套。

````javascript
// avoid
angular
  .modlue('app')
  .controller('Dashboard', function() {})
  .factory('logger', function() {});
````

````javascript
// recommended
angular
  .module('app')
  .factory('logger', logger)
  .controller('Dashboard', Dashboard);
  
  function logger() {}
  function Dashboard() {}
  ````
  
  ### controllerAs with vm
  
  使用`controllerAs`语法时把`this`赋值给一个可捕获的变量，选择一个有代表性的名字，例如`vm`代表ViewModel。避免`this`在不同地方有不同的语义。
  
  ````javascript
  // avoid
  function Customer() {
    this.name = {}
    this.sendMessage = function() {}
  }
  ````
  
  ````javascript
  // recommended
  function Customer() {
    var vm = this
    vm.name = {}
    vm.sendMessage = function() {}
  }
  ````
  
### 置顶绑定成员

> 把可绑定的成员放到controller的顶部，并按照字母顺序排序。提高代码的可读性。

1. 声明置顶，按照字母顺序排列；
2. 函数不用表达式，要用函数声明，因为函数声明会被置顶，无需担心声明顺序所导致的依赖问题；


````javascript
// avoid
function Session() {
  var vm = this;
  
  vm.gotoSession = function() {
    // ...
  }
  vm.refresh = function() {
    // ...
  }
  vm.searh = function() {
    // ...
  }
  vm.sessions = [];
  vm.title = 'Sesssion';
}
````

````javascript
// recommend

function Sessions() {
  var vm = this;
  
  vm.gotoSesssion = gotoSession;
  vm.refresh = refresh;
  vm.search = search;
  vm.sections = [];
  vm.title = 'Sessions';
  
  function gotoSession() {
  
  }
  function refresh() {
  
  }
  function search() {
  
  }
}
````

### Data Services

把进行数据操作和数据交互的逻辑放到factory中，数据服务服务XHR请求、本地存储、内存存储和其他的任何数据操作。

1. controller的作用是查看视图和收集视图信息，不应关心如何获取数据，专注对view的控制；
2. 把逻辑封装到单独的数据服务中，隐藏外部调用者如controller对数据的直接操作；

````javascript
// recommend

// dataservive factory

angular
  .module('app.core')
  .factory('dataservice', dataservice);
  
  dataservice.$inject = ['$http', 'logger'];
  
  function dataservice($http, logger) {
    return {
      getAvengers: getAvengers
    };
    
    function getAvengers() {
      return $http.get('/api/ma')
        .then(getAvengersComplete)
        .catch(getAvengersFailed);
        
        function getAvengersComplete(response) {
          return response.data.results;
        }
        
        function getAvengersFailed(error) {
          logger.error('XHR Failed for getAvengers.' + error.data);
        }
    }
  }
````

````javascript
 // controller calling the dataservice factory
 
 angular
  .module('app.avengers')
  .controller('Avengers', Avengers);
  
  Avengers.$inject = ['dataservice', 'logger']
  
  function Avengers(dataservice, logger) {
    var  vm = this;
    vm.avengers = [];
    
    activate();
    
    function activate() {
      return getAvengers().then(function() {
        logger.info('Activated Avengers View');
      })
    }
    
    function getAvengers() {
      return dataservice.getAvengers()
        .then(function(data) {
          vm.avengers = data;
          return vm.avengers;
        })
    }
  }
````

### 参考资料:
[后Angular时代二三事](https://github.com/xufei/blog/issues/21)
[Angular规范](https://github.com/johnpapa/angular-styleguide/blob/master/i18n/zh-CN.md#%E5%8D%95%E4%B8%80%E8%81%8C%E8%B4%A3)


hid say: 深化。



