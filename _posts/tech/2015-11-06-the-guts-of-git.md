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
即新增加的文件不能通过`git commit -a`命令添加到暂存区域，需要使用`git add| git stage`命令。

`git add`不是将文件置于版本控制之下，而是将文件添加到stage。而新增的文件必须通过`git add`才能commit。commit不理会工作区的文件，而是根据stage为每个目录生成tree对象，然后再创建commit对象指向他。

### Git 实现过程

With Git, I think it was a lot about coming at a problem width fresh eyes(not having ever really bought into the traditional SCM mindset), and really trying to think about the issues, and spending a fair amout of time thinking about what the real problems were and what I wanted the design to be. And then the inital self-hosting code took about a day to write(OK, that was "self-hosting" in only the weakest sense, but still).

真正编写Git最初版本才一天而已，但真正重要的是思考和设计过程。也就是Git在大脑中编程时间远远大于在编辑器上编程时间，而前者可以大大压缩后者的时间。

### Git高速的原因

记录snapshoot而非具体差异。

Git只关系文件数据的整体的改变，而很多版本控制系统只关系文件内容的具体差异。Git并不直接记录这些差异的数据，而是把变化的数据snapshoot，记录在一个文件系统各种。每次提交更新是，会比较文件的指纹信息，并对文件做sanpshoot，并保存sanpshoot的索引。

在保存到Git之前，所有数据都要进行内容的checksum计算（SHA-1做Hash计算），并以此作为结果，为数据的唯一表示索引。所以文件一有变动，Git立即就能察觉。

文件的三种状态

modified | staged | committed
---------|--------|----------
working directory  |  staging area  |  git directory(repository)

基本的Git工作流程：

- 在Working directory中修改文件
- 修改之后，sanpshoot，并保存到stage中
- commit更新，把stage中的snapshoot转存到Git的directory中

实现这一切的关键是checksum计算，而checksum有赖于diff。由此，试设想一下Git的设计灵感来源：

Linux这样的大型项目，由Linus等维护。而且是开源的项目，更新来自世界，更新的内容更是纷至迭来，所以不可能每次都检查并更新整个项目文件，只能处理diff。Linus只需要把diff加入到对应的文件即可。diff如果是要一个文件一个diff，那么文件较多的情况下，也不可行。因此，diff只能做整体修改的diff，因此也就有了整体的diff，而非针对单个的文件。

如何实现能达到速度的极致？从旧式的版本管理系统来看，其对文件的变化逐一跟踪，在文件较多的情况下，这样要逐一检查文件，速度不可能快，这种实现也最直接的实现，相当于把版本管理当作编辑器中hisotry类似的处理之。然而，我们每次改变文件，并非关注于单个文件的改变，而显然是更关心此次的整体的改变。

思路至此，也就是直接处理整体的改变即可。如何得到整体的改变？我们在Linux下最常用的对比文件是否改变的办法，就是用md5sum来对比文件的指纹。因此，判断文件是否改变，对比指纹即可，由此可以得到设计commit id的思路。

文件的改变，本质还是在于文件。文件系统无疑是最好的参照，而Ext4、Btrfx、ReiserFS，其对文件index的处理非常高效。引用Archlinxu的文档：

> Btrfs - 也被称作"Better FS", 是一种具备与Sun/Oracle的ZFS相近特性的新文件系统。特性包括快照，多磁盘条带化，多盘镜像（不需要mdadm即可组成软RAID），数据校验，增量备份，以及能同时提升性能并节省空间的透明压缩功能（目前支持zlib和LZO）。截止2014年4月，Btrfs虽然已经合并到主干内核中，但仍被标记为实验性质。Btrfs被认为是 GNU/Linux 文件系统的未来，并被所有主流发行版的安装程序设置为root分区文件系统选项。

可见snapshoot，在文件处理已有相应的技术。而这些文件系统，对文件恢复都有高效办法。从版本管理的角度，文件系统本身就是一个版本管理系统。由此，就自然有了Git的snapshoot的实现。

所以称Git是一个特殊的文件系统，比称其为版本管理工具更确切。

由此可知，计算机中，有关计算系统的原理与实现，具有永久的价值与意义，对此领悟越深，越能迁移至其他地方。因为，系统所追求的稳定与高效，远胜于其他软件开发的情况。

所以Git，是由Linux一两天开发出来，并不为怪。同时，应该也只能诞生于Linux社区。因为只有这里有才Git特性之树，所需的肥沃的土壤。


### 参考资料:

[Linus Torvalds Answers Your Question](http://linux.slashdot.org/story/15/06/30/0058243/interviews-linus-torvalds-answers-your-question?sdsrc=rel)
[The guts of git](http://lwn.net/Articles/131657/)
[为什么要先 git add 才能 git commit ？](http://www.zhihu.com/question/19946553)
[写出好的 commit message](https://ruby-china.org/topics/15737)
[Git的思想和基本工作原理](http://www.nowamagic.net/academy/detail/48160210)
[File systems ](https://wiki.archlinux.org/index.php/File_systems_(%E7%AE%80%E4%BD%93%E4%B8%AD%E6%96%87))

hid say: 如果没有熟悉事物的结构与缘由，那么即使你对事物的每个细节都非常熟悉了，也不能把握事物的实质。

幻想了一个Git的设计，权当勉励自己一下，贻笑大方。


