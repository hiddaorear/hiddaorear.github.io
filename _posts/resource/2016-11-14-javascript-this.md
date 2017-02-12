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

## 原理

### 错误的this指向

通常所说的：如果是全局环境中，this指向全局对象，如果是对象的方法，这this指向这个对象。

例子1：

````javascript

var foo = {
  bar: function() {
    console.log(this)
  }
}

foo.bar();
(foo.bar)();

(foo.bar = foo.bar)();
(false || foo.bar)();
(foo.bar, foo.bar)();

````

例子1前两者为foo，后面都是全局对象。后三者并没有指向foo。所以我们上面的通常说法不精确。

### 精确的this指向

在全局环境中，this指向全局对象。而在普通函数调用中，this是由激活上下文的调用者提供，即调用这个函数的父作用域，以及函数调用的语法形式，决定了this的值，这是一个动态可变的值。

例子2：

````javascript

var foo = {
  bar: function() {
    console.log(this)
    console.log(this === foo)
  }
}

foo.bar() // foo, true

var fn = foo.bar

console.log(fn === foo.bar) // true

fn() // global, false

````

例子2中，第一次调用指向foo，把`foo.bar`赋值给fn之后，this没有指向foo。是什么导致this指向的变化呢？

### this指向的内部原理

`this`是执行上下文的一个属性：

````javascript

activeExecutionContext = {
  VO: {...},
  this: thisValue
}

````

在普通函数调用中，this是由激活上下文的调用者提供，即调用这个函数的父作用域，函数调用的语法形式，决定了this的值，这是一个动态可变的值。

为什么会引起这个差异呢？
因为引用类型的不同处理，是否会获取真实的值，所导致的。

引用类型存在形式：

1 标识符（变量名，函数名，函数参数名，全局对象属性名）

2 属性访问器（`foo.bar(); foo['bar']()`, 点标记法；可以动态设置属性名的方括号`[]`）

为了从引用类型中获取真实的值，存在类似`getValue`的方法。而函数上下文的规则是，函数上下文中this由调用者提供，并由调用形式决定。如果调用的圆括号左侧是一个引用类型，this为这个引用类型，如果是非引用类型，这为null，但为null无意义，被隐式转化为全局对象。


### 为什么有this的特性？

this是一个指针，便于代码的更为简洁地复用。

````javascript

// 无this
function upper(context) {
  return context.name.toUpperCase()
}
function speak(context) {
  var greeting = "Hello, I'm " + upper(context)
  console.log(greeting)
}

var me = {
  name: 'm'
}

var you = {
  name: 'y'
}

speak(me)

// 利用this

function upper() {
  return this.name.toUpperCase()
}
function speak() {
  var greeting = "Hello, I'm " + upper.call(this)
  console.log(greeting)
}

speak.call(me)


````

这里this可以简化上下文对象的传递。其他OPP语言中this关键字和OPP密切相关，一般是引用刚创建的对象，但在ECMAScript中，this只限于引用创建过的对象，this的指向和函数调用形式有关，不一定引用类型调用就指向引用类型。

### this指向的改变

1 构造函数中的this

````javascript

function C() {
  console.log(this)
  this.x = 10
}

var a = new C()
console.log(a.x);

````

new操作符会调用函数的内部的Construct方法，创建对象，之后调用函数的Call方法，把新创建对象作为this值。

2 调用函数时call与apply设置this的值

````javascript

var b = 10
function a(c) {
  console.log(this.b)
  console.log(c)
}

a(20)
a.call({b: 20}, 30)
a.apply({b: 20}, [40])

````

### call, apply, bind以及箭头函数

call,apply,bind皆为动态的改变this指针的方法。其中call和apply是当Object没有某个方法，但是其它对象有，可以借助call和apply改变this的指向，调用其它对象的方法。bind为绑定this为某个对象。

典型的应用：

将类数组元素转化为数组：
`Array.prototype.slice.apply(document.getElementsByTagName('*'))`

检查类型：

````javascript

function isArray(obj) {
  return Object.prototpye.toString.call(obj) === '[object Array]'
}

````


箭头函数则与前三者不同。
If kind is Arrow, set the `[[ThisModel]]` internal slot of F to lexical.If the
value is "lexical", this is an ArrowFunction and does not have a local this
value. If thisModel is lexical, return NormalCompletion(undefined).

箭头函数没有自己的this绑定，同时在函数执行时绑定this会被直接忽略。其中this总是指向定义时所在的对象，而不是运行时所在的对象。即箭头函数的this值是lexical
scope 的this值。这一特性使得箭头函数在React中的render函数中使用起来很方便。

````javascript

function foo() {
  setTimeout(() => {
    console.log('id: ', this.id)
  }, 100)
}

var id = 0

foo.call({id: 42})

// 容易误解的地方
// {id: 42}
// 是箭头函数定义所在的对象还是运行时所在的对象。由于箭头函数位于foo函数内部，只有foo函数运行之后他才会生成，所以foo运行时所在的对象，即箭头函数定义所在的对象。

````

````javascript

var f = () => 5;
// 近似等价于
var f = function() {return 5;}.bind(this);

````

综上，call,apply,bind使得JavaScript具有动态改变this的特性，而箭头函数使得JavaScript具有固定this的指向的特性。一动一静，相得益彰。

## 在编程中的运用

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

### super

````javascript

class P {
  foo() {
    console.log('P.foo')
  }
}

class C extends P {
  foo() {
    super.foo()
  }
}

var c1 = new C()
c1.foo() // P.foo

var D = {
  foo: function() {
    console.log('D.foo')
  }
}

var E = {
  foo: C.prototype.foo
}

Object.setPrototypeOf(E, D)
E.foo() // P.foo


````

可见super的绑定是静态绑定，创建时即完成绑定。所以E委托了D，但并不能调用到`D.foo()`，类似于箭头的函数的this绑定。


### jQuery中的this

链式调用的实现；

````javascript

function Constructor() {
  this.art = 0
}

Constructor.prototype.fn_0 = function() {
  console.log('0')
  return this;
}

Constructor.prototype.fn_1 = function() {
  console.log('1')
  return this;
}

new Constructor().fn_0().fn_1()

````

调用的方法返回this即可。

`end()`的实现

````javascript

function end() {
  return this.prevObject || this.constructor(null)
}

// 设置preObject的函数
function pushStack( ele ) {
  // Build a new jQuery macthed element set
  var ret = jQuery.merge( this.constructor(), elems);
  ret.prevObject = this // ret.pervObject 设置为当前jQuery对象引用
  ret.context = this.context
  return ret;
}

````

pushStack函数在很多涉及DOM操作的函数都有调用，用于缓存了当前的this。由于只存储当前，所以这里只需要一个preObject即可，无需放在一个数组里。

### 利与弊

this是JavaScript特性之一，具有脚本语言的动态特性，带来很多便捷，同时由于super和箭头函数的特性，使得this具有了静态的特性，在这两种情况下，this是固定且无法改变的。其利与弊都是this的灵活，双刃剑。所以才有了ES2015中super和箭头函数的固定this的特性。


### 拾遗

this可被重新赋值么？（不能，this是保留字）

### 问题

1 call参数为null时，this的指向

````javascript

function a() {
  console.log(this)
}
a.call(null)

````

2 调用形式对this的影响

````javascript

var foo = {
  bar: function() {
    console.log(this)
  }
}

foo.bar();
(foo.bar)();

(foo.bar = foo.bar)();
(false || foo.bar)();
(foo.bar, foo.bar)();

````



### 参考资料：

《你所不知道的JavaScript（上卷）》

[关于JavaScript的执行域,标识符解析,闭包的研究 ](http://www.laruence.com/2008/07/28/210.html)

[深入ECMA-262-3 第三章、This](http://weizhifeng.net/chapter-3-this.html)

[JavaScript内部原理实践——真的懂JavaScript吗？](https://github.com/goddyZhao/GPosts/blob/master/javascript/JavaScript%E5%86%85%E9%83%A8%E5%8E%9F%E7%90%86%E5%AE%9E%E8%B7%B5%E2%80%94%E2%80%94%E7%9C%9F%E7%9A%84%E6%87%82JavaScript%E5%90%97%EF%BC%9F.md)


### 答案

1 全局对象（window）,由于null没有意义，此处变为全局对象。

2 前两者为foo，后面都是全局对象。前两者没有没有调用GetValue，都是引用类型的。后面的赋值(3)，逗号(4)，逻辑表达式(5)失去了引用类型的值，而是得到函数类型的值，this的值被设置为全局对象。




