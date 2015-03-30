---
layout: post
title:  JavaScript
category: 技术
tags: [JavaScript]
keywords: javascript
description: 
---

##### Monday,30 March 2015

###读《JavaScript核心概念和实践》(一)

1.JavaScript是一门动态的,弱类型的,基于原型的脚本语言.

弱类型,强类型,动态类型,静态类型语言区别:

强类型:偏向于不容忍隐式类型转换.譬如说haskell的int就不能编程double;
弱类型:偏向于容忍隐式类型转换.譬如说C语言的int可以编程double;
静态类型:编译的时候就知道每一个变量的类型,因为类型错误而不能做的事情是语法错误;
动态类型:编译的时候不知道每一个变量的类型,因为类型错误而不能做的事情是运行时错误.

静态类型指的是编译器在complie time执行类型检查,动态类型指的是解释器在runtime执行类型检查.
编程语言里所谓类型通常是用来对值分类的,动态类型和静态类型的本质区别是在那个阶段做类型检查.动态语言之所以看上去能改变变量的类型,是因为对值的类型检查在运行时.

动态类型特性的使用,动态的访问一个JavaScript对象的属性:

````javascript
var key = "property";
console.log(key); // "property"

var obj = {
  proterty: "my property"
}

console.log(obj[key]);  //"my property"
````

2.JavaScript的数据类型分为两种:基本类型和引用类型.
JavaScript又6种数据类型:字符串(string),数值(number),布尔值(boolean),undefined,null及引用类型.引用类型包括:对象(属性的集合,即键值的散列表),数组(有序列表),函数(包含可执行的代码).其中对象和数组的界限不明显,事实上他们属于同一种类型.故typeof运算的结果一样.

注意typeof的优先级高于*+等运算符.故:

````javascript
var a = 1;
var b = 2;
typeof a*b; //以为是number 2,其实返回NaN.因为"number*2"返回NaN
typeof a+b; //返回"number2".因为"number+2"返回"number2"
````

数据类型转换为布尔值的规则:

````javascript
number: 0 | -0 | NaN
string: ""
boolean: false
object: null
underfined: underfined
````

以上均会被转换为false.

#### 参考资料
[ 读过很多代码，却依然写不好的 JS ](https://cnodejs.org/topic/54d06d46ef1b48510c27e25e)
[抓些细节bug](http://book.douban.com/review/5960403/)
[强类型 JavaScript 的解决方案](http://www.ruanyifeng.com/blog/2015/02/strong-typing-javascript.html)
[弱类型、强类型、动态类型、静态类型语言的区别是什么？](http://www.zhihu.com/question/19918532)

hid say:读书还是欠思考的深度,或者说计算机理论有所欠缺,对书中一些不严谨的说法基本无感觉.这本书的一大好处就是作者不只是懂JavaScript,而且行文简洁,表意清楚,实属不易.


