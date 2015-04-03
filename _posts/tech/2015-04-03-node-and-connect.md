---
layout: post
title:  JavaScript concept and practice (3)
category: 技术
tags: [JavaScript]
keywords: javascript
description: 
---

##### Monday, 03 April 2015

### 读《JavaScript核心概念和实践》(三)

#### 对闭包和this的自我理解

![夏达](/../../assets/img/tech/2015/xiada_0.jpg)

### JavaScript是动态的,弱类型,基于原型的脚本语言.

> A closure is a combination of a code block(in ECMAScript this is a function) and statically/lexically saved all parent scopes. Thus, via these saved scopes a function may easily refer free variables.

> 闭包是一个代码块(在ECMAScript是一个函数)和以静态方式/词法方式进行存储的所有父作用域的一个集合体.所以,通过这些存储的作用域,函数可以很容易的找到自由变量.

````javascript
function foo() {
  var x = 10;
  return function bar() {
    console.log(x);
  }
}

// "foo" returns also a function
// and this returned function uses
//free variable "x"

var returnedFunction = foo();

//global variable "x"
var x = 20;

//execution of the returned function

returnedFunction(); //10, but not 20

````


````javascript
//global "x"
var x = 10;

//global function
function foo() {
  console.log(x);
}

(function (funArg) {
  //local "x"
  var x = 20;
  
  funArg(); // 10, but not 20
  
  //there is no ambiguity,
  //because we use global "x",
  //which was statically saved in
  //[[Scope]] of the "foo" function,
  //but not the "x" of the caller's scope,
})(foo);

````


以上代码和文字引用自[ECMA-262 » JavaScript. The core](http://dmitrysoshnikov.com/ecmascript/javascript-the-core/#closures).

通过以上代码,我们可以看出在JavaScipt中,闭包的存在是为了解决两个问题.
第一个问题是:当一个函数从另一个函数向上返回(到外层)并且使用上面所提到的自由变量的时候,如何解决自由变量的存储?
第二个问题是:解析标识符的时候,标识符该使用那个作用域的值----以静态的方式存储在函数创建时刻的还是执行过程中以动态方式生成的(比如caller的作用域)?

两个问题可以归结一个问题,变量的存储问题.因为解析标识符的时候,使用的值是对应的存储的值.
为了在即使父函数上下文结束的情况下,也能访问其中的变量,内部函数在被创建的时候会在他的[[Scope]]属性中保存父函数的作用域链.这样就解决了第一个问题,自由变量存储被存储在闭包中.同样,解析标识符的时候,标识符的上下文决定了标识符的值,该上下文同样存储在闭包中.

因此,闭包的出现,归根到底是为了解决上下文存储的问题.

JavaScript中无处不在的上下文又是如何出现呢?
JavaScript一切皆可以看作对象.而所有的对象都可以通过原型链联系起来,原型链的出现使得实现继承和共享属性成为可能.不只有对象能通过有限的原型链联系起来,执行上下文同样也不是孤立的存在.

执行上下文可以抽象的表示为一个简单的对象,每一个执行上下文拥有一些属性来跟踪和他相关代码执行过程,一般来说有三个必要属性:
1.variable object,变量对象(变量,函数声明,在函数上下文还包括函数形参和arguments对象,此时变量对象成为活动对象(activation object))
2.this;
3.Scope chain,作用域链.

可见执行上下文同样也不是孤立的存在,通过作用域链(Scope chain)与其他上下文联系起来.

### 参考资料

[ECMA-262](http://dmitrysoshnikov.com/)
[JavaScript核心](http://weizhifeng.net/javascript-the-core.html#closures)
[「深入ECMA-262-3」第一章、执行上下文](http://weizhifeng.net/chapter-1-execution-contexts.html)
[「深入ECMA-262-3」第二章、变量对象](http://weizhifeng.net/chapter-2-variable-object.html)
[「深入ECMA-262-3」第三章、This](http://weizhifeng.net/chapter-3-this.html)

hid say:从语言的设计来理解语言的实现,应该是一件很有趣味的事情.奈何我计算机和数学功底太浅薄,只能做这么浅薄的理解.错误以后再修正,暂时贻笑大方也是权宜之计.


