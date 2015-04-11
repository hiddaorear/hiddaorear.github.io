---
layout: post
title:  Mastering Regular Expression(5)
category: 技术
tags: [Regular Expression]
keywords: Regulaer expression 
description: 
---

##### Staturday, 11 April 2015

### 读《精通正则表达式》(五)

#### ---JavaScript中的正则表达式

![秒速五厘米](/../../assets/img/tech/2015/one_more_time_one_more_chance.JPG)

> 必须静，才能产生深思力量，及会通能力。
---从文家书·1972年5月6日·张兆和

> 事情看得远，则不会为小小得失丧气，失去做人信心。
---从文家书·1972年8月7日·沈虎雏

> 作个“书呆子”比作个“混日子的人” 显然是不同的。前者或许会因对国家有个理想，受事实挫折而十分痛苦，但比一个“混日子的人”生命有分量，则极显明。
---从文家书·1972年8月7日·沈虎雏

> 我在学校二十五年，至少明白三事：一，仅照学校要求，学生成不了大气候。二，越学得杂而多越有用。三，书本学习还是不可缺少，因为千百种数学，物理，化学的进展，先都建设在一种理论上而从广泛实际证实。
---从文家书·1972年8月7日·沈虎雏

今天为正则表达式收尾。综合阅读了几本经典的书：
1.JavaScript: The Good Parts ---Douglas Crockford
2.Professional JavaScript for Web Developres ---Nicholas C.Zakas
3.Mastering Regular Expressions ---Jeffrrey E.F. Friedl
4.Regular Expression yet another introduction ---余晟
5.JavaScript核心概念及实践 ---邱俊涛

除了《精通正则表达式》没有JavaScript部分外，其余书籍与正则表达式相关的内容都较为简约。蝴蝶书中，正则表达式一章，以例子引入正则表达式，并就例子讲解相关的正则表达式的知识。讲解较为零碎，且不着要点。第8章讲正则表达式和字符串相关方式时，简明的列出了相关的API，就没有多的介绍了，整体来讲，这部分很鸡肋。《JavaScript高级编程》中只有4页纸，太简略了。《JavaScript核心概念及实践》用了一章讲解正则表达式，但还是较为简略。对于初学者，其中有一个较好的例子，匹配引号中的字符串。

````javascript

var str_0 = 'fair enough';
var str_1 = "hello, world";

var pattern = /['"][^'"]*['"]/; //该正则表达式有问题；

var str_2 = 'hello, world"; //两边的引号不对称也能匹配；

var pattern_0 = /['"][^'"]*\1/; // \1表示第一个分组

//单引号里面不能出现双引号，双引号亦然；故需要改进；

var pattren_1 = /['"][^\1]*\1/;
````

### `lastIndex`属性

`RegExp`变量有一组属性，其中最重要也是唯一的可写属性为`lastIndex`。如果使用`RegExp`的`exec()`和`test()`函数，并且设定了g参数，也就是在全局模式下，正则表达式的匹配会从`lastIndex`的位置开始，并且每次匹配成功之后会重新设定`lastIndex`。

这样是为了解决`g`参数带来偏移量记录问题。当我们没有使用`g`参数时，默认只匹配到第一个字符串。使用`g`参数时，需要找出整个字符串中匹配的字符串。当匹配了第一个字符串时，正则引擎需要寻找下一个可以匹配的字符串，应该接着匹配的地方继续往后寻找，因此在此种情况下，需要记录第一次匹配到的位置，接着寻找的时候无须重复查找第一次匹配的状态，直接使用`lastIndex`记录的偏移量接着寻找匹配。

那么，这样子的设计带来一个副作用。在不同的字符串调用同一个`RegExp`的`exec()`或`test()`方法，如果前面有匹配成功的字符串，那么`lastIndex`会记录其偏移量，当重新匹配新的字符串时，会从这个偏移量开始匹配，而不是我们所想的从字符串的开始匹配，就带来了意料之外的结果。所以在使用同一个正则表达式时，应该显式的将`RegExp`的`lastIndex`设定为0.

当然在使用`RegExp.test()`的很多情况下，更好的选择是`string.search(RegExp)`，判断返回值是否为0.

### String的方法与RegExp的方法区别

JavaScript中有一些正则操作是通过String的方法实现的。但与RegExp的方法有一些区别。
1.`string.match(RegExp)`，在指定了全局模式的情况下，返回各次成功的匹配文本；而`RegExp.exec()`总返回单次匹配的结果，不管是否指定了全局模式。但`string.match(RegExp)`不包含其他信息，也不包含捕获分组的信息。

2.`string.search(RegExp)`是用来寻找字符串中第一次匹配成功的位置，如果不成功则返回-1.因此，即使设定了全局模式，也只能匹配一次。
这个特性可以避免使用设定了全局模式的`RegExp.test(string)`，因为保存了`lastIndex`而带来意料之外的情况。

````javascript
var pattern = /^\d+$/g;
var pattern.test("1234"); // true
var pattern.test("6789"); // false

"1234".search(/^\d+$/g) == 0; // true
"6789".search(/^\d+$/g) == 0; //true
````

### 正则表达式有四大用处：

#### 1.验证

````javascript

var regexp = /^\d{4}-\d{2}-\d{2}$/;

"2015-04-11".search(regexp) == 0; //true

regexp.test("2015-04-11"); //true 不可以使用全局模式；
````

#### 2.提取

简单提取

````javascript
var pattern = /^\d{4}-\d{2}-\d{2}$/;
var str = "2015-04-10 2015-04-11";
var matchArray = str.match(pattern);
for (var i = 0, l = marchArray.length; i < l ; i++) {
  document.write(matchArray[i] + '<br/>');
}

//2015-04-10
//2015-04-11
````

#### 分组提取

要捕获分组匹配的文本，则必须使用RegExp.exec(str)，且需要设定全局g模式。

````javascript
var pattern = /^(\d{4})-(\d{2})-(\d{2})$/g;
var str = "2015-04-10 2015-04-11";
var matchArray = str.match(pattern);
while ((matchArray = pattern.exec(str)) != null)) {
  document.write(matchArray[i] + '<br/>');
}

//2015-04-10
//2015
//04
//10
//2015-04-11
//2015
//04
//11
````

#### 3.替换

````javascript

var regexp = /(\d{4})-(\d{2})-(\d{2})/;
var replacement = "$2/$3/$1";

document.write("2015-04-11".replace(regexp, replacement));

// 04/11/2015
````

#### 4.切分

````javascript

var regexp = /\s+/;
var matchArray = "one\ntwo\t three".split(regexp);

for (var i = 0, l = marchArray.length; i < l; i++) {
  document.write(matchArray[i] + '<br />');
}

// one two three
````

以上例子来自《正则指引》，因其简明的表达正则表达式的用处，故录之。

《正则指引》这本书虽然有缺点，但其内容安排的结构非常严谨，加上作者的很多实践经验，还是很值得一读。当然，最好是先读《精通正则表达式》，这样读其他的相关内容，就有底子在，读起来不至于吃力。

### 参考资料
[乱象，印迹](http://www.luanxiang.org/blog/)

hid say:学习须取法乎上。


