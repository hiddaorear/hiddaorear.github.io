# 耦合与编程范式

#### 2023/08/07 摘录pongba的TopLanguage

## 为什么GP更自然？

### 面向对象和GP

实现ADT，如stack。完成了一个stack类，用数组实现。函数foo要用到这个stack：`void foo(stack)`;

面向对象：

按照面向对象的思路，要使得foo可以复用，所有的stack，比如，因为效率原因，要替换stack为一个链表实现，就需要抽象出一个IStack接口。此时，具体类尚未实现，或者刚刚写出来，就需要考虑抽象，可能过早抽象了。

`void foo(IStack);`

GP：

GP的方式，把形参给虚化掉，当成无类型语言使用。

`void foo<Stack>(Stack s);`

foo不依赖任何具体的interface，天生就依赖stack这个概念本身的抽象语义。


lijie的看法：GP的Stack，用concept来处理，和面向对象差别不大。不同的是面向对象是二进制复用，GP是源码级别复用。面向对象可以动态化绑定，GP只能静态绑定。

Jian Wang和longshanksmo对lijie的反驳：

- OOP和GP差别很大，OOP的二进制复用，会引入更多细节，interface难以稳定。如果IStack接口会依赖Stack中的元素类型，而元素类型和Stack没什么关系，foo也未必会关心元素类型，这正是GP的大显身手的地方。
- 并不是所有stack都实现了IStack，有些不是stack，但行为又是stack的东西，是实现IStack好还是不实现好？如果这个东西敲好有具备list的行为，是否应该还实现IList？

### GP和OOP的差异

> GP倾向于产生不同类型，OO倾向于提取出同一个类型

首先，OO对性能的降低再少，还是有降低，有时候一点降低也是不可接受的；
其次，OO的主要问题不是性能降低，而是OO容易造成系统的耦合。一个系统中，有无数的类，每个类不知道在干什么？而且互相有关联，就像一张蜘蛛网，造成严重的系统功能拓展和维护问题。

耦合是最大的问题。设计得好，加上抽象体系固有的稳定性（如GUI），OO固然能搭建出好的框架。然而，如云风所说，在实际中的一个典型系统，你敢保证两年以后，这个抽象体系还适用吗？到那个时候类已经叠床架屋了，怎么办？








- [耦合的三重境界](https://groups.google.com/g/pongba/c/dnRCUVOMQ-Q)
- [《敏捷软件开发：原则、模式与实践》重读笔记（一）：寻找属于你的依赖](https://groups.google.com/g/pongba/c/1WzHqjFUaaY)
- [为什么GP更自然](https://groups.google.com/g/pongba/c/5VOiFHa6Lr0)
- [聊聊 API 设计](https://groups.google.com/g/pongba/c/Ss4wZ4035gY)
- [高阶特性与低阶语言的尴尬](https://groups.google.com/g/pongba/c/bVzIWvjTPFM)
