---
layout: post
title:  AngularJS UI
category: 资源
tags: [JavaScript AngularJS]
keywords: JavaScript AngularJS
description: 
---

### AngularJS UI

#### AngularJS UI

#### Thursday, 08 October 2015

![书法](/../../assets/img/resource/2015/wangxizhi_6.jpg)

### ng-options


````javascript

app.controller('ExampleCtrl', function($scope) {
    $scope.items = [
        {id: 1, name: 'Foo'}
        ,{id: 2, name: 'Bar'}
    ]
    
    $scope.selectItem = null
})

````


````html

<div ng-controller="ExampleCtrl">
    <select ng-model="selectedItem" ng-init="selectedItem=1"  ng-options="item.id as item.name for item in items"></select>
    {{selectedItme | json}}
</div>

````

ng-options: [value] as [text] for [item] in [items]
ng-init: selectItme=value

这样，select的`value`,`label`都有值。初始化，设置`value`的值即可。

AngularJS文档描述：
- select as label for value in array

ng-options=person.lastName as getPersonFullName(person) for person in peopleArray

this means "user peopleArray as data source, for each item put its value in the person variable, user the result of the getPersonFullName function(with the person parameter) as label in the options of the drop-down list, but set the value of the lastName property of person in the model variable whenever an item is selected in the drop-down list"

[angularjshub-select](http://www.angularjshub.com/examples/forms/select/)

### ui-router

````javascript

var myapp = angular.module('myapp', ["ui.router"])

myapp.config(function($stateProvider, $urlRouterProvider) {
    $urlRouterProvider.when('', '/contacts/list')
    $urlRouterProvider.when('/', '/contacts/list')
    
    $urlRouterProvider.otherwise('/contacts/list')
    
    $stataProvider
        .state('contacts', {
            absolute: true
            ,url: '/contacts'
            ,templateUrl: 'contacts.html'
            ,controller: function($scope) {
                $scope.contacts = [{id: 0, anme: 'Alice'}, {id: 1, name: 'Bod'}]
            }
            ,onEnter: function() {
                console.log('enter contacts')
            }
        })
        .state('contacts.list', {
            url: '/list'
            ,templateUrl: 'contacts.list.html'
            ,onEnter: function() {
                console.log('enter contacts.list')
            }
        })
        .state('contacts.detail', {
            url: '/:id'
            ,templaterUrl: 'contacts.detail.html'
            ,controller: function($scope, $stateparams) {
                $scope.person = $scope.contacts[$sateParams.id]
            }
            ,onEnter: function() {
                console.log('enter contacts.detail')
            }
        })
})


````

[完整例子](http://plnkr.co/edit/gmtcE2?p=preview)

###  ui-routes要义

$stateProvider是通过“状态”（state）来管理路由。
- 状态对应页面的ui-view；
- 状态通过controller,template,view等属性，描述对页面的视图展示和行为；
- 状体之间的层级结构，最好的模式是用状态继承，有名状态嵌套（父/子状态）。


### ui-router template

````html

<body ng-controller="MainCrtl">
    <select ui-view>Some content will be load here!</select>
</body>

````

````javascript

$stateProvider.state('contacts', {
    template: '<h1>Contacts</h1>'
})

````
- 当一个状态激活，其模版会自动填充到父状态的模版的ui-view元素。如果ui-view有原始内容，子状态激活之后，其会被替换掉；
- 并非所有的状态都可以激活，顶层状态是不能被激活的，因为其父状态模版是整个html；
- 如果一个状态是abstract，即抽象状态，其拥有自己的子状态，但本能激活自身，只能当子状态激活时，隐式激活。因为，如果子状态被激活其父状态必被激活，对于abstract状态也如此。


#### 激活状态的三种办法：

- Call `$state.go()`. High-level convenience method.
- Click a link containing the `ui-self` directive.
- Navigate to the `url` associated with the state.

#### $state.go()
`$state.go(to, [, toParams][, options])`

Returns a Promise represening the state of the transition.

- `to` , String Absolute State Name or Relative Statte Path
The name of the state that will be transitioned to or relative state path. If the path starts with `^` or `.`then it is relative, otherwise it is absolute.

Some example:
- $state.go('contact.detail') will go to the 'contact.detail' state;
- $state.go('^') will go to a parent state;
- $state.go('^.sibling') will go to a sibling state;
- $state.go('.child.grandchild') will go to a grandchild state.


- `toParams`, Object, A map of the parameters that will be sent to the state, will populate `$stateParams`;
- `options`, Object, if Object is passed, object is an options hash. The following options are supported:
   `location`,`inherit`,`relative`,`reload`.

### 状态嵌套的4种方法：

- 使用`.state()`，比如`.state('parent', {}).state('child', {})`;
- 使用`ui-route.stateHelper`来创建状态嵌套树，这种方式需要另外引入依赖，所以很少使用；
- 定义状态的`parent`属性，可以为一个字符串或者一个对象；


````html

<div>
    <a href="contacts">look view</a>
    <a href="contacts/list">look child view</a>
    <ui-view>There will load contact!</ui-view>
</div>

````

````javascript

var app = angular.module('app', ['ui.router'])

app.config(function($stateProvider) {
    $stateProvider.state('contacts', {
        url: '/contacts'
        ,templateUrl: 'contacts.html'
    }).state('contacts.list', {
        url: '/list'
        ,templateUrl: 'contacts.list.html'
    })
})

// 注意state之后的状态的写法，需要写上父级状态


app.config(function($stateProvider) {
    $stateProvider.state('contacts', {
        url: '/contacts'
        ,templateUrl: 'contacts.html'
    }).state('list', {
        url: '/list'
        ,templateUrl: 'contacts.list.html'
        ,parent: 'contacts'
    })
})

// state不需要带上父级的状态

var contacts = {
    name: 'parent'
    ,url: '/contacts'
    ,templateUrl: 'contacts.html'
}

var list = {
    name: 'parent.child'
    ,url: '/list'
    ,templateUrl: 'contacts.list.html'
    ,parent: contacts
}

app.config(function($locationProvider, $stateProvider) {
    $stateProvider.state(contacts).state(list)
})

````

### 状态规则
- 状态无顺序，子状态可以在父状态之前
- 父状态必须存在
- 状态不能重，即使是不同的父状态下



#### Abstract States使用

- 为所有的子状态提供一个基url
- 必须设置`templateUrl`属性，子状态对应的模板将插入到父模版中的`ui-view`中
- `resolve`属性，可以为所有子状态解决依赖项
- `data`属性，为所有的子状态或者事件提供自动一数据
- `onEnter onExit`函数，页面加载或退出是执行

#### $stateparams
`$stateparams`服务，其作用是解析url中带的参数，可以直接当作对象，访问属性。
要通过url来传递参数，`state`需要把如此写：`you_ulr/:params_1/:params_2`；
而页面上，`ui-sref = myapp.you_state({params_1: value_1, paramse_2: value_2})`
`$stateparms.params_1`即可以获取对应的值。


### ui-router resolve

`resolve`为控制器提供依赖注入项。
`resolve`为Object

- `key-{string}`:注入控制器依赖项名称；
- `factory-{String | function}`：
-- string：服务的别名；
-- function：函数的返回值将作为依赖注入项。如果函数是一个耗时操作，那么控制器也必须等待函数执行完成才会被实力化。

````javascript

$stateProvider.state('mystate', {
    resolve: {
    
    // Example using function with simple return value.
    // Since it's ont a promise, it resolves immediately
        simpleObj: function() {
            return {value: 'simple'}
        }
        
    // Example using function with returned promise.
        ,promiseObj: function($http) {
            return $http({method: 'GET', url: '/someUrl'})
        }
        ,promiseObj2: function($http) {
            return $http({method: 'GET', url: '/someUrl'})
                .then(function(data) {
                    return doSomeStuffFirst(date)
                })
        }
        ,translations: 'translations'
        ,translations2: function(translations, $stateParams) {
            translations.getlang($stateParams.lang)
        }
        ,greeting: function($q, $timeout) {
            var deferred = $q.defer()
            $timeout(function() {
                deferred.resolve('Hello')
            }, 1000)
            return deferred.promise
        }
    }
    ,controller: function($scope, simpleObj, simpleObj2, promiseObj, promiseObj2, translations, translations2, greeting) {
        $scope.simple = simpleObj.value
        $scope.items = PromiseObj.items
        $scope.itmes = PromiseObj2.items
        
        $scope.title = translations.getLang('english').title
        $scope.title = translations.title
        
        $scope.greeting = greeting
        
    }
})

````

需要改变页面的状态，且需要获取数据的时候，这种保证在状态之前执行的程序，很有用处。

甚至是jQuery的页面做的难以做到的事。例如：如果提交表单成功之后，跳转到对应的页面。看起来很简单的功能，其实不容易实现。因为浏览器的安全策略，JavaScript是不能自己触发跳转，但有用户的点击事件之后，是可以的。在这个场景里面，有用户点击事件，但是点击之后不能立即跳转，Chrome等浏览器，能容易在一定时间之后跳转，但IE等就不能支持，即使有这个功能，这个时间很短暂，而数据从服务器返回的时间是不定的，有可能很耗时，所以这样不能实现此功能。

唯一的办法是，点击之后就跳转到一个空页面，给与提示信息，等数据返回之后重新渲染。

而这个功能在AngularJS中，很容易实现，因为其为单页面的缘故。而且，利用state的嵌套功能，可以实现局部刷新。

然而，`resolve`虽然有在状态改变之前，实现数据注入的能力，但细想一下，这个功能不容易利用。因为去服务器请求数据，一般要用到页面中数据，如何在`resolve`中使用其他状态中的数据，要么是把数据放在顶层的$scope中，要么使用服务。这也不失为一种好的方案。

服务作为全局的单例对象，不止可以用来作为函数，封装业务逻辑，而且可以用来作为全局变量使用。

### $state data
可以给`$state`提供定义数据，建议使用`data`属性，防止冲突。

````javascript

var contacts = {
    name: 'contacts'
    ,templateUrl: 'contacts.html'
    ,data: {
        customData1: 5
        ,customData2: 'blue'
    }
}
var list = {
    name: 'contacts.list'
    ,templaterUrl: 'contacts.list.html'
    ,data: {
        customData1: 44,
        ,customData2: 'red'
    }
}

$stateProvider.state(contacts).state(list)


function Ctrl($state) {
    $state.current.data.customData1 // 5
    $state.current.data.customData2 // 'blue'
    
}

````

路由中的自定义数据，较好的用处，是作为权限管理。

### Interceptor

The `$httpProvider` provider contains an array of interceptors. An interceptor is simply a regular service factory that is registered to that array. 

````javascript

module.factory('intercepor', ['$log', function($log) {
    $log.debug('$log is here to show you that this is a regular factory with injection')
    
    var myInterceptor = {
        ...
    }
    return myInterceptor
}])


````

And then add it by it's name to `$httpProvider.interceptors` array:

````javascript

module.config(['$httpProvider', function($httpProvider) {
    $httpProvider.interceptors.push('myIntercepror')
}])

````

### Difference between Service, Factory and Provider in AngularJS
服务本身是一个任意单例的对象，AngularJS通过依赖注入机制提供服务。而准入机制调用一个`provider`的`$get()`方法，把得到的东西作为参数进行相关调用。所以，对于使用服务而言，服务仅指`$get`方法返回的东西。而作为提供服务的依赖注入机制，服务又要提供了`$get()`方法的整个对象。

[AngularJS深入(5)——provider](http://div.io/topic/1169)
[angularjs-providers服务详解](http://www.boiajs.com/2015/07/02/angularjs-providers-explained)
[AngularJS系列(4) 那伤不起的provider们啊](http://hellobug.github.io/blog/angularjs-providers/)
[ 自定义模块和服务](https://checkcheckzz.gitbooks.io/angularjs-learning-notes/content/chapter14/chapter14.html)

````javascript
angular.module('app', [])
    .service('myService', function() {
        this.name = 'Service man'
    })
    .factory('myFactory', function() {
        return {
            name: 'Factory man'
        }
    })
    .provider('configurableProvider', function() {
        var privateName = 'Default man'
        return {
            setName: function(name) {
                privateName = name
            }
            ,$get: function() {
                return {
                    name: privateName
                }
            }
        }
    })
        .config(function (configurableProvider) {
            configurableProvider.setName('New man')
        })
            .controller('Ctrl', function($scope, myServie, myFactory, configurable) {
                $scope.serviceNaem = myService.name
                $scope.factoryName = myFactory.name
                $scope.providerName = configurable.name
            })


````




### 参考资料：

[前端工程——基础篇](https://github.com/fouber/blog/blob/master/201508/01.md)

[AngularJS Routing Using UI-Router](https://scotch.io/tutorials/angular-routing-using-ui-router)
[AngularJS Multi-Step Form Using UI Router](https://scotch.io/tutorials/angularjs-multi-step-form-using-ui-router)

[流浪猫の窝之AngularJS](http://www.cnblogs.com/liulangmao/tag/angular/)
[ui.router源码解析](http://www.html-js.com/article/Front-end-source-code-analysis-original-uirouter-source-code-analysis)
[学习 ui-router - 状态嵌套和视图嵌套](http://bubkoo.com/2014/01/01/angular/ui-router/guide/nested-states%20&%20nested-views/)
[AngularJS 使用 UI Router 实现表单向导](http://www.oschina.net/translate/angularjs-multi-step-form-using-ui-router)

[Interceptors in AngularJS and Useful Examples](http://www.webdeveasy.com/interceptors-in-angularjs-and-useful-examples/)
[AngularJS 拦截器和好棒例子](http://my.oschina.net/ilivebox/blog/290881)
[Winning with HTTP Interceptors in AngularJS](http://onehungrymind.com/winning-http-interceptors-angularjs/)
[Techniques for authentication in AngularJS applications](https://medium.com/opinionated-angularjs/techniques-for-authentication-in-angularjs-applications-7bbf0346acec)
[Cookies vs Tokens. Getting auth right with Angular.JS](https://auth0.com/blog/2014/01/07/angularjs-authentication-with-cookies-vs-token/)

[Injecting $state (ui-router) into $http interceptor causes circular dependency](http://stackoverflow.com/questions/20230691/injecting-state-ui-router-into-http-interceptor-causes-circular-dependency)
[AngularJS 应用身份认证的技巧](https://blog.coding.net/blog/techniques-for-authentication-in-angular-js-applications)
[Difference between Service, Factory and Provider in AngularJS](https://gist.github.com/Mithrandir0x/3639232)
[Testing Angular Services](http://jsbin.com/xolom/2/edit?html,js,output)


hid say：知识的运用，不在于其寻根问底，而在于其实用。知识的融汇才在于知根知底。学于难处学，用于易处用。

对于框架的使用，稍微用心看一下文档，要远胜于到处找资料。文档简明精确，是其他资料不能达到的效果，其缺点在于过于简明，失之枯燥无味。
