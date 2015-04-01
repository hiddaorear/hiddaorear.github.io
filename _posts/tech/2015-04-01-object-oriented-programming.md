---
layout: post
title:  JavaScript concept and practice (2)
category: 技术
tags: [JavaScript]
keywords: javascript
description: 
---

##### Monday, 01 April 2015

### 读《JavaScript核心概念和实践》(二)

![风景](/../../assets/img/tech/2015/object_oriented_programming.jpg)

> 面向对象编程语言的问题在于,他总是附带所有他需要的隐含环境.你想要一个香蕉,当得到的却是一个大猩猩拿着香蕉,而其还有整个丛林.
--Joe Armstrong(Erlang语言发明人)

> Software entities should be open for extension, but closed for modification.
--Bertrand Meyer (Object Oriented Software Construction)

开闭原则(OCP)是面向对象设计中"可复用设计"的基石,是面向对象设计中最重要的原则之一,其他很多的设计原则都是实现开闭原则的一种手段.

#### 软件实体应该对扩展开放,对修改关闭.

在JavaScript中,一切皆为对象,连函数也是对象.JavaScript的面向对象实现受Self影响,基于prototype实现继承.每一个对象都有一个prototye属性,而这个prototype自身也是一个对象,这样可以形成一个链式结构.

访问对象的一个属性的时候,解析器会遍历这个链式结构,访问到属性,则返回该属性,遍历到顶层的null对象,则返回undedined.因此,当A对象有一个属性proto,而B对象继承于A,则B对象也可以访问到proto,从而是实现了代码的复用.因此,原型链其实用来实现继承和共享属性的对象链.

JavaScript中为了灵活使用原型链,有三个典型实现:
1.prototype;
2.this指针;
3.call和apply;

对象的prototype属性可以指向另一个对象,从而实现了继承等面向对象的机制.

this指针表示当前上下文(cotext),即对调用者的引用.this指针的值并非由函数如何声明而确定,而是函数如何被调用而确定.

call的第二参数是若干个参数,而apply是一个数组.其中,call的性能要优于apply.

Backbone源码:

````javascript
// A difficult-to-believe, but optimized internal dispatch function for
// triggering events. Tries to keep the usual cases speedy (most internal
// Backbone events have 3 arguments).
var triggerEvents = function(events, args) {
    var ev, i = -1, l = events.length, a1 = args[0], a2 = args[1], a3 = args[2];
    switch (args.length) {
        case 0: while (++i < l) (ev = events[i]).callback.call(ev.ctx); return;
        case 1: while (++i < l) (ev = events[i]).callback.call(ev.ctx, a1); return;
        case 2: while (++i < l) (ev = events[i]).callback.call(ev.ctx, a1, a2); return;
        case 3: while (++i < l) (ev = events[i]).callback.call(ev.ctx, a1, a2, a3); return;
        default: while (++i < l) (ev = events[i]).callback.apply(ev.ctx, args); return;
    }
};
````

call和apply通常是用来修改函数的上下文,函数中的this指针被替换为call或者apply的第一个参数.在JavaScript中函数是一等公民,函数也是对象,而并非是对象的一个属性.函数的上下文是可以变化的,对应的是函数内的this指针是可以变化的,函数可以作为一个对象的方法,同时也可以作为另一个对象的方法.


````javascript
var jack = {
  name: "jack"
  ,age: 26
}

var abruzzi = {
  name: "abruzzi"
  ,age: 25
}

function printName() {
  return this.name;
}

console.log(printName.call(jack)); //jack
console.log(printName.call(abruzzi));  //abruzzi

````

#### 不只有对象的上下文有链式关系,函数的执行上下文也有继承关系.一个执行上下文可以抽象的表示为一个对象.每个执行上下文拥有一些属性,用来跟踪和他相关代码的执行过程.三个必要的属性有:
1.一个变量对象(ariable object);
2.一个this值;
3.一个作用域链(scope chain);

变量对象是执行上下文相关的数据作用域,他是与上下文相关的特殊对象,其中存储了上下文定义的变量和函数声明(函数表达式不在其中).
而在函数上下文中,变量对象是以活动对象(activation object)来表示的.活动对象除了变量和函数声明之外,还存储了形参和arugument对象(对形参的一个映射,但值是通过索引来获取的).

以执行上下文来理解作用域.JavaScript没有块作用域,变量作用域为函数体内有效.JavaScript为词法作用域,其作用域在词法分析的时候(定义时)就确定下来了,而并非执行时确定.

经典例子:

````javasript
var str = "global";
function scopeTest() {
  console.log(str);
  var str = "local";
  console.log(str);
}

scopeTest();
````

运行结果不是:
global
local

而是: 
undedined
local

原因在于,词法分析结束之后,构造作用域链的时候,会将函数内用var定义的变量放入作用域链,因此str在整个函数scopeTest内部都是可以访问的(从第一行到最后一行).由于开始时str变量是没有定义的,程序顺序执行,到第一行就会返回未定义,第二行返回str赋值.

从这里我们可以知道,作用域链带来上下文环境,而函数定义内部变量限制了变量在作用域上查找的优先顺序.遍历作用域链的时候,是由下而上的,最先遇到的属性值最先返回.以节点与连接来理解,执行上下文对象的三个必须属性:
1.变量对象,相当于节点本身具有的数据(变量)和执行过程(函数);
2.this指针,指向节点函数执行对应的对象,相当于自我引用;
3.作用域链,节点与其他节点的连接关系;

不只执行上下文如此,JavaScript中对象本身也具有类似的结构.JavaScript中的对象可以看作Hash链表,也可以形成节点与连接的结构.在这一个结构中抽象出来了前端与服务器数据交换的标准格式JSON.JSON可以表达除去自我引用的对象图之外的所有的数据形式.因为JSON的键值对中的值可以是除Function对象之外的所有对象和值.

自我引用举例:

````javasript
var obj = {
  self: null
  ,name: 'obj'
}

obj.self = obj;
````

因此Joe Armstrong说:你想要一个香蕉,当得到的却是一个大猩猩拿着香蕉,而其还有整个丛林.这番话也不无道理.在JavaScript中有时候要一个香蕉,而这个香蕉的prototype很有可能指向热带雨林.


#### 参考资料
[面向对象编程从骨子里就有问题——看看名人大家是如何吐槽面向对象的](http://www.vaikan.com/object-oriented-programming-is-inherently-harmful/)
[开闭原则](http://baike.baidu.com/view/866233.htm)
[程序基于精确的数学——STL之父Alex Stepanov访谈录](http://www.techcn.com.cn/index.php?doc-view-131345.html)
[	An Interview with A. Stepanov](http://www.stlport.org/resources/StepanovUSA.html)
[面向对象是个骗局？！](http://coolshell.cn/articles/3036.html)
[为什么说面向对象编程和函数式编程都有问题](http://www.vaikan.com/whats-wrong-with-oop-and-fp/)

hid say:世事无银弹,编程更是如此.当流行的观点一边倒的时候,我们需要清醒的认识到问题的本质.
这里面又很多我自己构造的东西,估计很有问题,等他日笑掉大牙.


