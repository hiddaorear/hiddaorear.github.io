---
layout: post
title:  文本之shell
category: 技术
tags: [text]
keywords:  text shell
description:
---

##  文本之shell

#### Saturday, 16  2017 September

![ChengBi](/../../assets/img/tech/2017/ChengBi_2.jpg)

## git

git不会add空的目录，如果需要提交空目录，需要在其中新建一个`.keep`之类的文件。

### 本质

git的本质是有日志的文件系统。而其革命性的思想是存储Snapshot而非diff，这一设计思想，使得git的设计非常简洁高效。如果基于diff，每次根据版本管理系统获取代码，要从diff计算生成文件，速度不如Snapshot，同时导致分支管理策略不易设计。基于Snapshot，则记录修改的文件，未修改的文件直接引用即可，这是典型的以空间换时间，所以快，因为获取文件只需要根据Snapshot load即可，如果是diff则要merge。而branch基于这种设计，只不过是给Snapshot取了一个别名而已，故branch代价非常低，其他tag之类也是同理，只不过是别名而已。

Snapshot: In computer systems, a snapshot is the state of a system at a particular point in time.

Snapshot: Every time you commit, or save the state of your project in Git, it basically takes a picture of what all your files look like at that moment and stores a reference to that snapshot.

快照是一个摄影中的概念，比如早晨给桌子拍一张照片，就记录了桌子上所有物品以及其位置状态，晚上我们就可以根据这张照片恢复早晨这张桌子样子，而不需要存储早晨的桌子。

而对应生成快照的git操作是commit，对暂存区生成对应的commmit，`git commit filename`这一下。git底层的对象模型，分为三个部分：类型、大小和内容。而类型又分为四种：blob(文件数据)，tree(类似目录，管理blob与tree)，commit(管理tree)，tag(标记commit)。从git操作角度而言，最为根本的是其中的commit，很多操作都是基于commit。

从add操作角度看：保存一个文件的时候，blob记录文件的信息与文件内容，保存为一个文件，并对这个文件求sha1，作为文件名；保存一个目录，即把目录信息，以及以上求得的blob的sha1，保存一个文件，并对这个文件求sha1。当commit的时候，根据提交文件的sha1生成一个提交的sha1。所以可以通过commit的sha1来找回文件，而branch不过一个commit的一个指针，即一个别名。

git的好用之处，以及其快速，很大程度是因为Snapshot。长期我对git的理解是git记录diff，而并非如此。记录diff是很直观的一个想法，如果想节省版本管理的存储空间，第一个想法就是记录diff，这样只要处理修改之后的差异即可。而是记录Snapshot，本质上是利用指针，如果有变更，则生成sha1记录之，没有变更则直接用指针指向以前的记录即可。类似前端的不可变对象库immutable.js的思想。

Snapshot会生成sha1校验和，可以保证文件的文件的完整性。

### 第一原则

由于git的本质是一个存取Snapshot的文件系统，那么生成Snapshot这一步无疑是最为关键，即git的commit命令。只要commit的之后，就不用担心文件的丢失了。

### 知识结构

### branch

merge branch

`git pull master you_branch` 在本分支合并master分支
`git merge --abort` 取消合并
`git branch -r` 列出远端分支
`git branch -m old new` 重命名分支

### commit

commit message

前提，一个commit对应于一次单一功能的逻辑修改。  

`[修改类型] 主要涉及的组件： 修改内容`

`[Feature] tabs: 新建tabs组件`

`[Deleted] tabs: 删除tabs组件`

`[Update] tabs: 修改tabs组件`

`[Debug] tabs: 修复tabs的bug`

`[Optimization] tabs: 优化tabs的加载`

`[Releast] tabs: 发布tabs组件`

`[Merge] branch: 合并branch_name分支`

`[Refactoring] tabs: 重构tabs组件`

重写commit`git commit --amend`

checkout

`git checkout -- file` 取消对文件的修改，从暂存区覆盖worktree file

`git checkout -- .` 从暂存区取出文件覆盖工作区

`git checkout branch|tag|commit -- file_name` 从仓库取出file覆盖当前分支

revert、reset与checkout有两种操作，全局操作与对文件的操作(加上文件名即可)

stash

`git stash`

### search

log (在整个历史中搜索)

`git reflog` 所有的操作记录

`git blame filename` 查看每一行的修改的作者

`git log -p -1` 查看上一次提交修改的详细内容

`git log -S string --oneline` 查看string引入的提交



grep （在指定的提交中搜索）

`git grep --count string`  输出匹配的文件，以及有匹配个数

`git grep -p function_value *.js` 匹配的行是属于那一个方法或函数

`git grep --break --heading -n -e string` 输出易读的文本


diff

`git diff master --stat` 显示差异文件列表


## 端口占用

## search

## 文件上传




## 参考资料：

[Git的思想和基本工作原理](http://www.nowamagic.net/academy/detail/48160210)



Yvan say： 作为前端开发，在工程化极度依赖Node的情况下，以及React，Vue等框架普及的情况下，开发上班的第一件是打开IDE或文本编辑器，第二件事大概就是打开一个命令行终端，当然，IDE集成了终端的可以合二为一。但是正因为大家习惯用IDE，在终端中多少有点不习惯，比如很多鼠标功能的缺失。其实，终端本身有他的方便之处，特别是对于开发人员，因为当年这一套，就是开发人员为了自己的方便，所设计的。

