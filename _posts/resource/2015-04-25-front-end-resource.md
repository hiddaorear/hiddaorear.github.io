---
layout: post
title:  Front End Tips 
category: 资源
tags: [JavaScript, CSS, HTML5, CSS3]
keywords: JavaScript
description: 
---

### Front End Tips

#### Saturday, 25 April 2015

![the_garden_of_world_38](/../../assets/img/resource/2015/the_garden_of_world_38.PNG)

## HTML

## CSS

### 1. 标签与SEO

- tite与h1的区别
- b与strong的区别
- i与em的区别

h1是在没有外界干扰的情况下，除了title以外，能强调页面主旨的标记，一个页面应该使用且只使用一次h1标记。对于搜索引擎来说，title的权重高于h1。

对于搜索引擎来说，em与strong要比i与b重视得多。因为em与strong是强调，而i与b只是告诉浏览器以何种格式显示文字。

em与strong是逻辑元素，而i与b是物理元素。物理元素强调一种物理行为，而逻辑元素告诉浏览器文字的重要程度。

## JavaScript
 
### setTimeout()作用域

`setTimeout()`调用的代码都是在全局作用域中执行的，因此函数中this的值在非严格模式下指向window对象，在严格模式下是undefined。

````javascript

var test = "in the window";
 
setTimeout(function() {alert('outer ' + test)}, 0); // 输出 outer in the window ，默认在window的全局作用域下
 
function fn() {
  var test = 'in the fn!';  // 局部变量，window作用域不可访问
  setTimeout('alert("inner " + test)', 0);  // 输出 outer in the window
  //虽然在fn方法的中调用，但执行代码(字符串形式的代码)默认在window全局作用域下，test也指向全局的test
}
 
fn();

````
添加一层闭包，即可变为函数内部的值。

````javascript

var test = "in the window";
 
setTimeout(function() {alert('outer' + test)}, 0); // outer in the window  ，没有问题，在全局下调用，访问全局中的test
 
function fn() {
  var test = 'in the fn!';
  setTimeout(function(){alert('inner '+ test)}, 0);  // inner in the fn! 
}
 
fn();

`````

### Single Thread 

JavaScript引擎是单线程运行的,浏览器无论在什么时候都只且只有一个线程在运行JavaScript程序。浏览器内核实现允许多个线程异步执行,这些线程在内核制控下相互配合以保持同步。假如某一浏览器内核的实现至少有三个常驻线程:javascript引擎线程,界面渲染线程,浏览器事件触发线程,除些以外,也有一些执行完就终止的线程,如Http请求线程,这些异步线程都会产生不同的异步事件。

1. GUI渲染线程
在JavaScript引擎运行脚本期间,浏览器渲染线程都是处于挂起状态的,也就是说被”冻结”了。

2. GUI事件触发线程
avaScript脚本的执行不影响html元素事件的触发。

3. 定时触发线程
注意这里的浏览器模型定时计数器并不是由JavaScript引擎计数的,因为JavaScript引擎是单线程的,如果处于阻塞线程状态就计不了时,它必须依赖外部来计时并触发定时,所以队列中的定时事件也是异步事件。
如果队列非空,引擎就从队列头取出一个任务,直到该任务处理完,即返回后引擎接着运行下一个任务,在任务没返回前队列中的其它任务是没法被执行的。

````javascript

setTimeout(function(){
   /* 代码块... */
   setTimeout(arguments.callee, 10);
}, 10);

setInterval(function(){
   /*代码块... */
 }, 10);
 
````

第一段中回调函数内的setTimeout是JavaScript引擎执行后再设置新的setTimeout定时, 假定上一个回调处理完到下一个回调开始处理为一个时间间隔,理论两个setTimeout回调执行时间间隔>=10ms 。第二段自setInterval设置定时后,定时触发线程就会源源不断的每隔十毫秒产生异步定时事件并放到任务队列尾,理论上两个setInterval回调执行时间间隔<=10。

setTimeout和setInterval设置的时间参数，意义在于在参数指定的时间后将执行方法放到执行队列中，如果队列中没有其他方法等待执行，则立即执行其指定的方法，故并非是立即执行的。

etTimeout()只是将事件插入了"任务队列"，必须等到当前代码（执行栈）执行完，主线程才会去执行它指定的回调函数。要是当前代码耗时很长，有可能要等很久，所以并没有办法保证，回调函数一定会在setTimeout()指定的时间执行。

setTimeout(fn,0)的含义是，指定某个任务在主线程最早可得的空闲时间执行，也就是说，尽可能早得执行。它在"任务队列"的尾部添加一个事件，因此要等到同步任务和"任务队列"现有的事件都处理完，才会得到执行。

### 参考资料：
[阿里一行之大神面对面 - 叶小钗](http://www.cnblogs.com/yexiaochai/p/3158443.html)
[B和strong以及i和em的区别](http://www.cnblogs.com/lpfuture/archive/2013/03/04/2942613.html)
[谈谈setTimeout的作用域以及this的指向问题](http://www.cnblogs.com/hutaoer/p/3423782.html)
[javascript线程解释（setTimeout,setInterval你不知道的事）](http://www.iamued.com/qianduan/1645.html)
[Javascript高性能动画与页面渲染](http://www.infoq.com/cn/articles/javascript-high-performance-animation-and-page-rendering)
[编写高性能JavaScript | Web前端 腾讯AlloyTeam Blog](http://www.alloyteam.com/2012/11/performance-writing-efficient-javascript/)
[JavaScript 运行机制详解：再谈Event Loop - 阮一峰的网络日志](http://www.ruanyifeng.com/blog/2014/10/event-loop.html)



hid say:人过了30岁，估计记忆力直降。好记性不如写博客，遇到有意思的知识，录之，不亦乐乎？
