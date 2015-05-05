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

### 1. HTML5新增标签

优势：
1. 语义性好，减少类名，有利于SEO；
2. 文档可读性增强，开发者易准确搜索信息，搜索引擎易理解页面内容。

新增标签：
1. article定义文章，代表文档、页面或者应用程序中独立、完整，可以独自被外部引用的内容；
2. aside定义文章的侧边栏；
3. audio定义音频；
4. canvas定义画布；
5. command表示命令按钮；
6. details表示用户要求得到并可以得到的详细信息；
7. embed插入各种多媒体；
8. mark定义需要突出显示或者高亮的文本；
9. figure一组媒体对象以及文字；
10. figcaption定义figure的标题；
11. fooder定义页脚；
12. header定义页面；
13. hgroup定义对网页标题的组合；
14. nav定义导航；
15. seciont定义文档中的区段；
16. time定义日期时间；
17. vidio定义视频；
18. wbr表示软换行；
19. progress显示JavaScript耗费的函数进程；

新增input元素类型

- email E-mail文本输入框；
- url 输入URL地址；
- number 输入数值的文本输入框；
- ranges 表示必须输入一定范围内的数字值的文本输入框；

### 2. 前端性能优化

### 性能优化是一个工程问题。

1. 请求数量，合并脚本和样式表，CSS Sprites，拆分初始化加载，划分主域；
2. 请求带宽，开启Gzip,精简JavaScript，移除重复脚本，图像优化；
3. 缓存利用，使用CDN，使用外部JavaScript和CSS，添加Expires头，减少DNS查找，配置ETag，使Ajax可缓存；
4. 页面结构，将样式表放在顶部，将脚本放在底部，尽早刷性文档输出；
5. 代码校验，避免CSS表达式，避免重定向；

### 3. 图片优化

1. 去掉无意义的修饰；
2. 不用图片，直接使用CSS替代；
3. 使用矢量图；
4. 使用恰当的图片格式；

### 4. DOCTYPE标签作用

1. 对文档的有效性验证。告诉用户代理和校验器文档的DTD类型。

2. 决定浏览器的渲染模式

- 标准模式
- 怪异模式
- 准标准模式

因为web标准的演进，浏览器在实现新的标准的时候需要兼容旧的标准，DOCTYPE就起到了一个兼容作用。而目前HTML5因为不再是SGML的语言，不需要在DTD中定义标签和属性，只起到一个激活模式的作用。

### 5. HTML5特性

1. Semantio (语义)
2. Offline & storage (本地存储：APP cache，Indexed DB)
3. device access (设备兼容特性：与浏览器内部数据相连，摄像头)
4. connectivity (连接特性：Server-Sent Eent & WebSockkets)
5. multimedia (网页多媒体：Audio,Video)
6. 3D, Graphics & Effects (三维、图形及特效：SVG,Canvas,WedGL,CSS3)
7. Performance & Integration (性能与集成特性：XMLHttpRequest2)
8. CSS3(更强的效果)

### 6. Web标准的理解

### 7. canvas

### 8. 浏览器输入url会发生什么

### 9. iframe标签的使用以及缺点


## CSS

### 1. 标签与SEO

- tite与h1的区别
- b与strong的区别
- i与em的区别

h1是在没有外界干扰的情况下，除了title以外，能强调页面主旨的标记，一个页面应该使用且只使用一次h1标记。对于搜索引擎来说，title的权重高于h1。

对于搜索引擎来说，em与strong要比i与b重视得多。因为em与strong是强调，而i与b只是告诉浏览器以何种格式显示文字。

em与strong是逻辑元素，而i与b是物理元素。物理元素强调一种物理行为，而逻辑元素告诉浏览器文字的重要程度。

### 2. CSS3新增属性：
1. border-colors;
2. border-images: stretch | repeat | round;
3. border-radius;
4. text-shadow;
5. box-shadow;
6. mask: url position repeat; (蒙板)
7. background-image: url, url;(多重背景)
8. background: linear-gradient() | gradient ;
9. box-reflect;
10. transform: rotate | scale | translate | skew;
11. backface-visibility: visible | hidden;
12. transition;
13. animation;

transition与ainmation区别：
1. aimation可以规定循环和动画的方式；
2. transition不能自行触发，而animation可以；
3. animation可以定义多个关键帧，而transition只能定义起始状态与结束状态（transition的本质作用是平滑改变CSS样式）；

### 3. CSS Box Model
1. 对于宽度为自动状态的静态（static）定位元素和相对定位元素（relatively positioned）元素，父元素的宽度减去外边距、边框、内边距、滚动条的宽度；
2. 浮动元素（float）与绝对定位元素（absolutely position），宽度会自动收缩为紧贴内容大小；
3. 浮动元素包含浮动元素，那么宽度会被自动延伸填充为父元素宽度；


### 4. 居中的实现

### 5. 典型的CSS兼容性问题

### 6. 响应式的实现

### 7. 逐帧动画的实现

### 8. 使用CSS实现抛物线动画

### 9. 圆周运动

### 10. 典型的动画实现方案

### 11. 重绘



## JavaScript
 
### 1. setTimeout()作用域

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

### 2. Single Thread 

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

### 3. Ajax优缺点

优点：
1. 最大优点，页面无刷新即可与服务器通信，用户体验好；
2. 使用异步的方式与服务器通信，具有更加迅速的响应能力；
3. 减轻服务器负担，按需取数据，减少冗余的请求；

缺点：
1. 不支持浏览器back按钮；
2. 安全问题，暴露了与服务器交互的细节；
3. 对搜索引擎不友好；


XMLHttpRequest对象常用方法与属性：
1. open('get | post', 'url');建立对服务器的调用；
2. send() ,发送请求；
3. abort()，停止当前请求；
4. readyState，请求状态：0=未初始化， 1=正在加载， 2=已加载， 3=交互中， 4=完成； 
5. responseText
6. responseXML
7. status

### 4. JavaScript变量解析过程

### 5. get请求与服务器握手次数与过程

### 6. JavaScript性能优化

### 7. 前端安全问题

### 8. 跨域请求的实现

### 9. http3.0

### 10. Ajax的API，原生以及jQuary实现

### 11. 事件

### 12. DOM操作API

- 创建新元素

````javascript

var node = document.createElement('div');
var text = document.createTextNode('hi');

````

- 添加新元素

````javascript

var node = document.createElement('div');
node.innerHTML = 'new';
document.body.appendChild('node');  //追加在尾部

var list = document.getElementById('list');
var item1 = document.getElementById('item1');
list.insertBefore(node, item1); // 添加第二个参数之前，若无此参数，默认添加在最后。

````

其他API
1. `innerHTML()`;
2. `outerHTML()`;
3. `textContent()`;
4. `innerText()`;
5. `outerText()`;
6. `insertAdjacentHTML()`;

- 移动元素

使用添加元素的API完成

````javascript

var item1 = document.getElementById('item1');
var item2 = document.getElementById('item2');
list.insertBefore(item2, item1);

````


- 复制元素

````javascript

var node = document.getElementById('node');
var clone = node.cloneNode(true);

````


- 删除元素

````javascript

var list = document.getElementById('list');
var item1 = document.getElementById('item1');
list.removeChild(item1);

````


- 查找元素

````javascript

// 属性

parentNode;
childNode;
previousSibling;
nextSibling;
firstChild;
lastChild;

````


### 13. cookie

### 14. cookie与section的区别

二者都是为了克服HTTP无状态的方案。

1. cookie数据存放在浏览器，而session存放在服务器；
2. cookie不安全，session相对安全；
3. session消耗服务器性能，cookie不会；
4. 单个cookie数据不能超过4k，一般浏览器cookie不超过20个；

PS： session id机制：
1. cookie保存；
2. URL重写；
3. 表单隐藏字段；

### 15. 改变元素的位置方法

### 16. 插入兄弟节点方法

### 17. DOM操作

1. jQuery

- 创建元素
`$('<span>new</span>');`

- 插入元素
1. `insertBefore`&`before`,指定元素外部，前面；
2. `insertAfter`&`after`,指定元素外部，后面；
3. `prependTo`&`prepend`,指定元素内部，前面；
4. `appendTo`&`append`,指定元素内部，后面；

````javascript

$('<span>new</span>').prependTo('div');

$('div').prepend('<span>new</span>');

````

- 移动元素
使用插入的API即可。

````javascript

// <div><span>new</span>>wrapper</div>

$('span').insertAfter('div');

//<div>wrapper</div><span>new</span>

````

- 包裹元素

1.` wrap`;
2. `wrapAll`;

- 克隆元素

`clone() | clone(ture)`

- 删除元素
1. `remove()`;
2. `empty()`;

- 替换节点

1. `replaceAll()`;
2. `replaceWith()`;

- 设置DOM
1. `html()`;
2. `text()`;
 
18. 浮点数精度问题

````javascript

var a = 0.1;
var b = 0.2;
var c = 0.3;

[b - a == 0, c - b == a ]; // => false, false;

````

JavaScript中的小数采用双精度(64位)表示，由三部分组成：符号+阶码+尾数。因为浮点数只有52位，从53位开始就舍入，造成了浮点数精度损失。

解决方案：

1. 设定精度范围：

````javascript

var a = 0.2;
var b = 0.3;
var equal = (Math.abs(b -a) < 0.00001);

````

2. `toPrecision()` | `toFixed()`，注意两方法返回的是字符串，故其目的在于显示。

````javascript

(0.1 + 0.2).toPrecision(10) == 0.3; // => true

(0.1 + 0.2).toFixed(10); // => true

````

19. var赋值问题

````javascript

(function(){
    var a = b = 3;
})();

console.log(typeof a);//"undefined"
console.log(b);//3

````

> The issue here is that most developers understand the statement var a = b = 3; to be shorthand for:

````javascript
var b = 3;
var a = b;
````

> But in fact, var a = b = 3; is actually shorthand for:

````javascript
b = 3;
var a = b;
````

> Therefore, b ends up being a global variable (since it is not preceded by the var keyword) and is still in scope even outside of the enclosing function.

> The reason a is undefined is that a is a local variable to that self-executing anonymous function

````javascript
(function(){
    var a = b = 3;
})();
````


## 参考资料：
[阿里一行之大神面对面 - 叶小钗](http://www.cnblogs.com/yexiaochai/p/3158443.html)
[B和strong以及i和em的区别](http://www.cnblogs.com/lpfuture/archive/2013/03/04/2942613.html)
[谈谈setTimeout的作用域以及this的指向问题](http://www.cnblogs.com/hutaoer/p/3423782.html)
[javascript线程解释（setTimeout,setInterval你不知道的事）](http://www.iamued.com/qianduan/1645.html)
[Javascript高性能动画与页面渲染](http://www.infoq.com/cn/articles/javascript-high-performance-animation-and-page-rendering)
[编写高性能JavaScript | Web前端 腾讯AlloyTeam Blog](http://www.alloyteam.com/2012/11/performance-writing-efficient-javascript/)
[JavaScript 运行机制详解：再谈Event Loop - 阮一峰的网络日志](http://www.ruanyifeng.com/blog/2014/10/event-loop.html)
[CSS3 主要知识点复习总结+HTML5 新增标签 | 英特尔® 开发人员专区](https://software.intel.com/zh-cn/blogs/2014/05/23/css3-html5#)
[AJAX笔试面试题汇总_Web开发笔试面试题](http://mianshiti.diandian.com/post/2013-05-01/40050873257)
[深入理解CSS盒子模型](http://www.cnblogs.com/hh54188/archive/2010/12/28/1919078.html)
[前端工程与性能优化 - Div.IO](http://div.io/topic/371)
[前端开发中，对图片的优化技巧有哪些？ - 知乎](http://www.zhihu.com/question/21815101)
[移动H5前端性能优化指南-腾讯ISUX](http://isux.tencent.com/h5-performance.html)
[前端工作面试HTML相关问题](http://www.html-js.com/article/Problems-related-to-frontend-development-interview-questions-a-large-set-ofAvi-front-end-job-interview-HTML)
[编码规范 by @mdo](http://codeguide.bootcss.com/)
[Witcher42 - doctype（文档类型）的作用是什么](http://witcher42.github.io/2014/05/28/doctype/)
[html的DOCTYPE标签的作用 | FEX Notes](http://www.fexnotes.com/2014/01/09/2014-01-09-html-doctype.html)
[DOCTYPE的作用及说明 ](http://bbs.blueidea.com/home.php?mod=space&uid=590876&do=blog&id=27461)
[HTML <!DOCTYPE> 标签](http://www.w3school.com.cn/tags/tag_doctype.asp)
[HTML5 到底是什么？ - 知乎](http://www.zhihu.com/question/19812140)
[移动平台上的HTML5技术是否华而不实](http://www.infoq.com/cn/news/2013/03/mobile-html5)
[javascript操作DOM元素 - 吕大豹](http://www.cnblogs.com/lvdabao/p/3493356.html)
[cookie 和session 的区别详解](http://www.cnblogs.com/shiyangxt/articles/1305506.html)
[build-web-application-with-golang/06.1.md at master · astaxie/build-web-application-with-golang](https://github.com/astaxie/build-web-application-with-golang/blob/master/zh/06.1.md)
[JavaScript的设计缺陷?浮点运算](http://ourjs.com/detail/54695381bc3f9b154e000046)
[每一个JavaScript开发者应该了解的浮点知识](http://yanhaijing.com/javascript/2014/03/14/what-every-javascript-developer-should-know-about-floating-points/)
[What Every Computer Scientist Should Know About Floating-Point Arithmetic](http://docs.oracle.com/cd/E19957-01/806-3568/ncg_goldberg.html)
[Python 的浮点数损失精度问题](http://my.oschina.net/lionets/blog/186575)
[代码之谜（五）- 浮点数（谁偷了你的精度？）](http://my.oschina.net/justjavac/blog/88823)
[js浮点类型计算偏差原因](http://bbs.csdn.net/topics/380247520)
[javascript - Why a is undefined while b is 3 in var a=b=3? - Stack Overflow](http://stackoverflow.com/questions/27329444/why-a-is-undefined-while-b-is-3-in-var-a-b-3)


hid say:人过了30岁，估计记忆力直降。好记性不如写博客，遇到有意思的知识，录之，不亦乐乎？
