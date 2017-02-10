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

### jQuery中的this

链式调用

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
scope 的this值。

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


### 为什么设计this？

### this指向的改变

### 利与弊

### 不同环境中的this值

### 拾遗

this可被重新赋值么？（不能，this是保留字）




