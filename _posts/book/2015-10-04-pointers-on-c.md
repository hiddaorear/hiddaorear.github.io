---
layout: post
title:  读《C和指针》
category: 读书
tags: [文化]
keywords:  读书
description: 
---

##### Sunday, 04 October 2015

### 读《Pointers on C》

![轻音](/../../assets/img/book/2015/wangxizhi_1.jpg)

> 高手往往都是有很强的系统的基础知识的，表面的东西永远是肤浅的。
--陈皓

又一次重回C语言，前段时间把Python过了一遍，没有留下什么，当然也没有用来做东西。过了这么这段时间，留下了，对其简洁的惊叹。用Python写的《集体智慧编程》，读着读着，就读不下去了。此外，本来想用Python来写一个完整的网站，或者爬虫，或者界面之类，也没有写成。至此，感觉跟没学差不多。

读C语言，只是想看看底层的原理。现在的技术多而杂，特别我所在的领域，真是一年一变，太快了。然而，刨根问底起来，其关键性的想法，都很多年前的旧东西。于是该回到C语言了。

C语言中，函数传值只有一种方式，那就传值，而数组这些数据结构，其表现是传址，实质还是传值，不过是指针变量罢了。函数作为计算过程的较为基本的封装，其传值如此，势必是C语言的内存管理的设计原则所决定。对内存的访问，直观而简便的办法，也就是通过地址了。所以作为左值的地址，其重要性不言而喻。

内存的管理，感觉是整个C语言的要义。之所以有指针，C是以面向一个flat内存模型为基础，指针系出自天然。各种基本的数据类型，其实给一块内存一个解释风格，比如int类型，解释为int。而函数只能传值，对于数组和结构体，这些数据结构，其作为参数传递，不过是作为指向数组和结构体的指针。而函数也是存在与内存中的代码，也有指针指向函数，所以可以用函数指针实现函数的传递。回调函数的实现，就是如此。

从抽象的层面上理解，其实指针不过是对内存中的数据或程序的一种抽象。数组和函数就具有一定的结构，而指针不用管具体的结构，只需要获取其地址即可，然后访问之。所以，回到底层，知道了这些基本的东西是怎么运作的，只完成了第一步，还应该知道怎么从这些基本的元件，搭建成一个有机的系统。而这其中抽象是极其重要的一个要素。

图灵机与lambda演算，分别从机器和从数学角度，对计算进行研究。而计算，不论何种形式的表达，其本性应该是不变的。数据结构和算法，以及离散数学，更能描述这些复杂多变的计算。

《Pointers on C》是一本很好的书籍。有很多事例代码的编写，相当用心。很多代码的思想也很经典，能看到很多设计模式的滥觞，其抽象计算的思想，如此一致。而C的好处在于，表达的计算，一是一，二是二，及其精确，这样精到的语言，其设计者Dennis Ritchie应该是在实践中千锤百炼，才能有如此简洁高效的形式。

摘录并分析一些优雅的代码：

校验大括号是否成对的C代码：

````c

/*
 * 检查花括号对
 * hiddaorear
 * study Pointers on C
 * 2015/11/05
 */

#include <stdio.h>
#include <stdlib.h>

int
main()
{
  int ch;
  int braces;
  int closing_braces;
  int opening_braces;

  braces = 1;
  closing_braces = 0;
  opening_braces = 0;

  while( (ch = getchar()) != EOF ) {
    if (ch == '{')
      ++opening_braces;
    
    if ( opening_braces > 0) {
      if (ch == '}')
        ++closing_braces;
    }
    else {
      braces = 0;
      printf("The order is wrong!\n");
      break;
    }

    if ( ch != '{' && ch != '}')
      break;
  }

  if ( closing_braces - opening_braces > 0 && braces == 1 ) {
    printf("%d unmatched opening brace(s)!\n", closing_braces - opening_braces );
  }
  else if ( closing_braces - opening_braces < 0 && braces == 1 ){
    printf("%d unmatched closing brace(s)!\n", closing_braces - opening_braces );
  }
  else if ( closing_braces - opening_braces == 0 && braces == 1 ) {
    printf("Success!\n");
  }

  return EXIT_SUCCESS;
}


````

可以看到，一个简单的功能用了四个变量，虽然实现功能，却有冗余逻辑，因为要求是校验，并没有要求要给出有几个括号没有配对。

我们来看看源码的方案：


````c

/*
 * Pointers on C
 */

#include <stdio.h>
#include <stdlib.h>

int
main()
{
  int ch;
  int braces;

  braces = 0;

  while( (ch = getchar()) != EOF ) {
    if (ch == '{')
      braces += 1;
    
    if ( ch == '{') {
      if (braces == 0)
        printf("Extra closing brace!\n");
      ele
        braces -= 1;
    }
  }

  if ( braces > 0 )
    printf("%d unmatched opening brace(s)!\n", braces);

  return EXIT_SUCCESS;
}


````

只需要两个变量，而且处理反括号出现在前的情况，其方案非常巧妙，简洁而明快。这种单一if语句不写括号的习惯，也值得借鉴。虽然改动时可能会出错，但此时应该都注意到，此种情况可以避免。不写括号使得程序非常简短，明了。

这段程序虽然简单，但为了得不能匹配的括号个数，这段简单的程序花了我很多时间。出现了几个典型的错误：

- 单词拼写错误，根本原因是英语不熟悉，和对程序变量没有形成在大脑映射的习惯；
- 不写分号，这是写习惯了JavaScript造成的，看来编程习惯有强大的迁移能力，一门语言真能影响一个人的思维习惯；
- 修改程序需要反复调试，这是写学要学习的新程序的老毛病，病在不思考，不检查程序，因为没有能力去这么做，然而更根本的是，没有这习惯；

雄关漫道真如铁，如今迈步从头越。底层实践，从此开始，望汝耐得烦，慢慢来。

摘录《笑傲江湖》风清扬教令狐冲的话：

> 岳不群课徒极严，众弟子练拳使剑，举手提足间只要稍离了尺寸法度，他便立加纠正，每一个招式总要练得十全十美，没半点错误。

> 那老者道：“唉，蠢才，蠢才！无怪你是岳不群的弟子，拘泥不化，不知变通。剑术之道，讲究如行云流水，任意所至。你使完那招‘白虹贯日’，剑尖向上，难道不会顺势拖下来吗？剑招中虽没这等姿式，难道你不会别出心裁，随手配合么？”

> 忽听那老者道：“蠢才！手指便是剑。那招‘金玉满堂’，定要用剑才能使吗？”令狐冲脑海中如电光一闪，右手五指疾刺，正是一招“金玉满堂”……令狐冲没想到自己随手这么一戳，竟将一个名动江湖的“万里独行”田伯光轻轻易易的便点倒在地。

> 风清扬又道：“单以武学而论，这些魔教长老们也不能说真正已窥上乘武学之门。他们不懂得，招数是死的，发招之人却是活的。死招数破得再妙，遇上了活招数，免不了缚手缚脚，只有任人屠戮。这个‘活’字，你要牢牢记住了。学招时要活学，使招时要活使。倘若拘泥不化，便练熟了几千万手绝招，遇上了真正高手，终究还是给人家破得干干净净。”令狐冲大喜，他生性飞扬跳脱，风清扬这几句话当真说到了他心坎里去，连称：“是，是！须得活学活使。”风清扬道：“五岳剑派中各有无数蠢才，以为将师父传下来的剑招学得精熟，自然而然便成高手，哼哼，熟读唐诗三百首，不会作诗也会吟！熟读了人家诗句，做几首打油诗是可以的，但若不能自出机杼，能成大诗人么？活学活使，只是第一步。要做到出手无招，那才真是踏入了高手的境界。你说‘各招浑成，敌人便无法可破’，这句话还只说对了一小半。不是‘浑成’，而是根本无招。你的剑招使得再浑成，只要有迹可寻，敌人便有隙可乘。但如你根本并无招式，敌人如何来破你的招式？”

--《笑傲江湖》

### 参考资料
《Pointers on C》
[如何学好C语言](http://coolshell.cn/articles/4102.html)
[Cuckoo Filter：设计与实现](http://coolshell.cn/articles/17225.html)
[Linus：利用二级指针删除单向链表](http://coolshell.cn/articles/8990.html)
[深入理解C语言](http://coolshell.cn/articles/5761.html)
[C语言的谜题](http://coolshell.cn/articles/945.html)
[How do I strengthen my knowledge of data structures and algorithms?](https://www.quora.com/How-do-I-strengthen-my-knowledge-of-data-structures-and-algorithms/answer/Robert-Love-1)
[C 语言的前世今生](http://blog.codingnow.com/2010/06/c_programming_language.html)

hid say: 编程中的《独孤九剑》。

2015年10月6日，微软发布了Surface Book，真让人惊艳，感觉世界上有了一款理想的电脑。发布会还演示了虚拟现实，让人惊讶，虽然能预想到这样的情形，没想这么快就到来了。

技术的发展，所能呈现的远景，有时候超乎想象。作为其中微小的一份子，何去何从？
