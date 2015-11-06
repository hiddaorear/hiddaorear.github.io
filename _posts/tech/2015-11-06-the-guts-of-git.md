---
layout: post
title:  The guts of git
category: 技术
tags: [git]
keywords: git
description:
---

##### Friday, 06 November 2015

### The guts of git

![起风了](/../../assets/img/tech/2015/Hayao_Miyazaki_2.jpg)

> Git is not source code management(SCM) system. It is, install, a set of low-level utilities(Linus compares it to a special-purpose filesystem) which can be used to construct an SCM system.

### Git为什么在`commit`之前要`stage|add`？

 `git add`与`git stage`是同一个指令不同的名字，而stage更切合命令的功能。

从设计理念来看：

> Every Git commit represents a single, atomic changeset width respect to the previous state.

Git中的所有commit，均是原子性commit，每一个commit都是由多个文件的修改组成，修改的commit要么全部成功，要么全部失败，保持原子性。而stage的存在，可以使得我们随意精确挑选所需的修改，然后一次性全部（即原子性）提交到版本库。

从实现来看：
Git对象，其用Git用blob对象来存储文件，用tree对象存储目录里的文件名，用commit对象存储提交。
`git add`将文件存入blob对象，并更新index；
`git commit`根据index生成tree对象，然后生成commit对象指向这个tree对象。

从使用上来看：
`git commit -a`
> Tell the command to automatically stage files  that hava been modified and deleted, but new files you have not told git about are not affected.
即新增加的文件不能通过`git commit -a`命令添加到暂存区域，需要使用`git add`/命令。

`git add`不是将文件置于版本控制之下，而是将文件添加到stage。而新增的文件必须通过`git add`才能commit。commit不理会工作区的文件，而是根据stage为每个目录生成tree对象，然后再创建commit对象指向他。

### Git 实现过程

With Git, I think it was a lot about coming at a problem width fresh eyes(not having ever really bought into the traditional SCM mindset), and really trying to think about the issues, and spending a fair amout of time thinking about what the real problems were and what I wanted the design to be. And then the inital self-hosting code took about a day to write(OK, that was "self-hosting" in only the weakest sense, but still).

真正编写Git最初版本才一天而已，但真正重要的是思考和设计过程。也就是Git在大脑中编程时间远远大于在编辑器上编程时间，而前者可以大大压缩后者的时间。

### 参考资料:

[Linus Torvalds Answers Your Question](http://linux.slashdot.org/story/15/06/30/0058243/interviews-linus-torvalds-answers-your-question?sdsrc=rel)
[The guts of git](http://lwn.net/Articles/131657/)
[为什么要先 git add 才能 git commit ？](http://www.zhihu.com/question/19946553)
[写出好的 commit message](https://ruby-china.org/topics/15737)

hid say: 如果没有熟悉事物的结构与缘由，那么即使你对事物的每个细节都非常熟悉了，也不能把握事物的实质。




