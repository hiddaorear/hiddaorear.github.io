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

### branch

merge branch

`git pull master you_branch`

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


stash

`git stash`

### search

log

`git reflog`

`git log -p -1` 查看上一次提交修改的详细内容

diff

`git diff master --stat` 显示差异文件列表

grep

`git grep --count string`  输出匹配的文件，以及有匹配个数

`git grep -p function_value *.js` 匹配的行是属于那一个方法或函数

`git grep --break --heading -n -e string` 输出易读的文本

## 端口占用

## search

## 文件上传




## 参考资料：


Yvan say： 作为前端开发，在工程化极度依赖Node的情况下，以及React，Vue等框架普及的情况下，开发上班的第一件是打开IDE或文本编辑器，第二件事大概就是打开一个命令行终端，当然，IDE集成了终端的可以合二为一。但是正因为大家习惯用IDE，在终端中多少有点不习惯，比如很多鼠标功能的缺失。其实，终端本身有他的方便之处，特别是对于开发人员，因为当年这一套，就是开发人员为了自己的方便，所设计的。

