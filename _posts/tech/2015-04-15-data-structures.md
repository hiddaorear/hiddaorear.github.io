---
layout: post
title:  Data Structures and Algorithm Analysis(3)
category: 技术
tags: [structures algorithm]
keywords: structures algorithm 
description: 
---

##### Wedensday, 15 April 2015

### 读《数据结构与算法分析》(四)

#### ---带学术气息的C++

![风景](/../../assets/img/tech/2015/field.JPG)

> 深夜闲谈，列夫·托尔斯泰欲止又言：“我们到陌生城市，还不是凭几个建筑物的尖顶来识别的么，后日离开了，记得起的也就是只几个尖顶。”
---木心·素履之往·庖鱼及宾

> “书法”，只在古中国自成一大艺术，天才辈出，用功到了不近人情，所以造诣高深得超凡入圣神莫测。“书法”的黄金时代过去一个，又过去一个，终于过完了。日本的书法，婢作夫人，总不如真。中国当代的书法，婢婢交誉，不知有夫人。
--木心·素履之往·庖鱼及宾

读《C++ Primer》与读JavaScript类似的书籍的感觉迥然不同，JavaScript中介绍变量的要点就是要在变量之前使用`var`而已，外加动态弱类型。而C++讲了一堆变量和基本类型，各种类型的内存管理，防止溢出。以及各种类型之间的不同，const限定符以及变量的声明和定义之间的区别，作用域和头文件。我把《Professional JavaScript for Web Developer》(3rd Edition)中文版和《C++ Primer》（4rd Edition）中文版放在一起，发现两者居然一样厚。略比较内容，JavaScript书籍中有关其语言的核心并不多，大部分是在讲解有关浏览器的内容，DOM、事件、Ajax以及HTML5等等。而C++中单单语言本身而言，就慢慢的一本书，可能还有深入的内容没能深入讲解，像STL和OO应该有很多内容。不得不感叹C++的博大，而JavaScript的简便。

C++的基本类型以及泛型让我感觉类型系统很复杂，但强类型有一个很大的好处，在构架大型系统是能在类型检查中保证类型安全，以及带来的性能优势。相比之下，JavaScript的性能令人担忧，V8这一代JavaScript引擎应该把性能优化到了极致，剩下的提升的空间，只能是硬件层次的提升。所以在移动端使用JavaScript做APP之路还任重而道远。如果核心用原声语言实现，其他的界面渲染这些交给JavaScript做，这个思路应该可行。

阅读C++的基本类型，隐隐约约感到类型的背后其实内存的精准管理，而函数调用的背后是堆栈的精准控制。

### 参考资料
《C++ Primer》(4rd Edition)
[为什么移动Web应用程序很慢](http://www.cnblogs.com/rubylouvre/p/3213632.html)
[Why mobile web apps are slow | Sealed Abstract](http://sealedabstract.com/rants/why-mobile-web-apps-are-slow/)
[为什么Web App的运行速度慢-CSDN.NET](http://www.csdn.net/article/2013-09-16/2816957%A1%A3)

hid say: 越深入了解一件概念背后的内涵，越能理解超越的概念本身的思想,大概如古人取法乎上的原则。在理解JavaScript闭包过程中，知道了闭包的概念的提出是为了解决函数调用中变量存储的问题，就越过闭包概念的本身的所能表达的意义。也理解了语言设计中，对特性取舍，是一件值得思量的事情，因为一个特性的引入，会带来其他问题。

