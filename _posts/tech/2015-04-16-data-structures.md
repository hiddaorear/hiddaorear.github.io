---
layout: post
title:  Data Structures and Algorithm Analysis(4)
category: 技术
tags: [structures algorithm]
keywords: structures algorithm 
description: 
---

##### Thursday, 16 April 2015

### 读《数据结构与算法分析》(五)

#### ---带学术气息的C++

![伯克利大学](/../../assets/img/tech/2015/Berkeley.jpeg)

> 在精神世界经历既久，物质世界的豪华威严实在无足惊异，凡为物质世界的豪华威严所震慑者，必是精神世界的陌路人。
---木心·素履之往

> 对自然美抱有直接兴趣，永远是心地善良的标志。---康德
--木心·素履之往

> 艺术家凭其做平得以渐渐成熟其人。
在自己的做平中，艺术家才有望他本身趋于成熟。不仅人奇妙，不仅艺术奇妙，奇妙的是人与艺术竟有这一重严酷而亲昵的关系；别人的艺术无法是自己成熟，只有自己的，才行--重复三遍了，为什么要重复三遍。（赘注：通常的高明见解是：先做人，而后做艺术家；人成熟了，艺术随之成熟--且看持此格言者，一辈子吃夹生饭，动辄以夹生饭飨人）
--木心·素履之往

> C++ is a horrible language. It's made more horrible by the fact that a lot of substandard programmers use it, to the point where it's much much easier to generate total and utter crap with it. Quite frankly, even if the choice of C were to do nothing but keep C++ programmers out, that in itself would be a huge reasion to use C.
---Linus

读有关C和C++的书籍，简明的资料较少，很多也难以有自己的主干统领全书。细节在实践中很重要，而编程是一个实践的技艺，作为介绍编程语言的书籍，实践的细节必不可少，否则很多程序跑不起来，读者的兴趣大打折扣。而一门语言，若设计者有语言方面的深入研究，语言本身应该带有设计者思想的温度，设计哲学的主干，这背后是解决问题的想法。编程语言有两大源头，一是C，一是Lisp。后来设计语言的艺术，或多或少都是这两门语言的发展。因为计算机硬件的发展，高级语言慢慢带上了很多Lisp的特性，最为典型是垃圾回收机制。C++受C的影响更大，早期要兼容C，同时增加了高级抽象特性，而牺牲可以适度的运行效率。

因为兼容C，同时支持多范式，C++语言不得不有很多折中的实现。如此，语言本身的复杂度就大为增加，作为程序员本身又偏好奇技淫巧，C++就多出更多被发现的特性，而这特性在一个些开发中运用，后来者就不得不熟练这些技巧。C++的复杂度就成为每个学习这门语言必须过去门槛。C++书籍作者，自然在书籍会安排讲解这些诸多的细节，也是作者作为实践者功力的体现。但如果安排不当，就会使读者陷入细节的泥淖，而不能自拔。略读刘未鹏的有关C++学习的之路的感悟，大抵如上。其更重视如何运用语言来解决问题，甚于语言本身的繁文缛节。

Bjarne Stroustrup本人也是这样的观点。刘未鹏问Stroustrup学习C++的第一原则是什么？答曰：“关注基本的概念和技术，而非特定的语言特性，尤其不是C++中细枝末节的语言细节。”Stroustrup对C++的了解，无须多言。刘未鹏在大学期间，有三年多的C++学习时间。很多时候，当我们对细枝末节如数家珍之后，方能跳出细节的泥淖。无论语言本身如何，学习本身须努力，学习过程本身也是一种必要的学习，语言本身的所携带的细节和背后的思想，也是可以为初学者大快朵颐。这大概是Strousrup和刘未鹏作为过来人，所要表达的真意吧。

### 参考资料
《素履之往》
[[RFC] Convert builin-mailinfo.c to use The Better String Library](http://thread.gmane.org/gmane.comp.version-control.git/57643/focus=57918)

hid say: 反思一下元学习的想法。因刘未鹏本人对心理学和学习认知这些是兴趣之所在，故其想法不流于浅薄，时常触及根本。
