---
layout: post
title:  文本之emacs
category: 技术
tags: [text]
keywords:  text emacs
description:
---

##  文本之emacs

#### Saturday, 16  2017 September

![ChengBi](/../../assets/img/tech/2017/ChengBi_4.jpg)

## 搜索优先

在编程或写作，大凡涉及文本的编辑，首要的一步，并非是编辑，而是找到需要编辑的文本，或者找到对应的目录并创建文本。而定位到对应的文本，有两种方式，一是UI界面显示目录结构，层层展开选择；二是搜索。IDE会显示对应的目录结构，用鼠标层层点开找到对应的文件，或是'Ctrl+p'，以关键字模糊搜索。

找到之后，编辑文件，亦须搜索到需要编辑的地方，小文件可以滚动浏览，大文件则依赖搜索。当然，如果有类似的大纲视图模式，也甚方便，比折叠功能强。

综上，大范围中搜索文件，是必然的，此时如果打开目录，一层一层的查找，效率极低，且易遗漏。

## 文件操作

### Helm

helm-find-files

是`Ctrl-x Ctrl-f`的优化，支持搜索。如果默认的行为没有被覆盖了，默认如果没有对应的文件，则创建新文件，这个操作是新建的文件很方便的方式。配合dired的`+`新建目录，可以完成一个闭环。还有替代的方案使用，`Ctrl-x Ctrl-v`，打开一个文件，替代当前缓冲区，也可以新建一个文件。

helm-find-files can fuzzy match candidates in the current directory.

To create a directory, enter a new name that does not exist in the current directory and append / at the end. After you create a directory, Helm continues in that directory.

To create a new file, enter a name and select the top row that has the symbol [?] next to it. By default, Helm always selects the first match in the directory.

helm-find

Normally, you use find command with arguments in terminal, then press RET and wait for a big list of result, and if the result is not as expected, repeat the whole thing. You can shorten this process by interactively get results from Unix find for every character you enter into Helm prompt.

By default, invoking `helm-find` only searches current directory.

`helm-find` can be invoked within `helm-find-files` session, by using `C-c /`.

只搜索当前目录的文件。这是局限，也是好处。我们编辑的时候，往往在同一个目录下。

helm-mini

helm-mini is comprised of multiple sources:

Current open buffers, under the header Buffers.
Recently opened files, under the header Recentf.
Allows you to create a new buffer by pressing RET, under the header Create Buffer.

`helm-mini`的相对于find的之类的优势在于，只搜索缓存以及最近打开过的文件。与计算机缓存的思想类似，刚才访问过的，继续访问的可能性很大。使用这个功能，可以每天下班编辑编辑器，无需为了明天工作而保持编辑器打开，避免需要重新搜索并打开需要编辑的文件。

dired

这是emacs自带的插件，如果编辑的文件在同一个目录下，不需要搜索，此时使用`Ctrl-x Ctrl-j`打开dirc，再操作文件或目录，甚是便捷。

`g`刷新缓冲区。如果目录有变更，则可以立即看到；
`s`列表默认是按照文件名排序，但按照时间排序更为有用。不用去会想昨天我编辑的文件是那一个的问题。按下s之后，会按照时间排序；
`v`以只读的模式查看文件；
`ESC=`diff;
`d x u`d标记需要删除的文件，u去掉标记，x删除；
`R`重命名文件；
`+`新增目录；

标记文件的操作

`m`标记文件， `ESC DEL`取消标记，`u`取消标记，`U`取消所有标记。
正则批量选取并删除，`%-m-d`。先输入`%`，再输入m，提示输入正则表达式，之后输入d，打上待删除的标记。

归并文件到目录

在整理目录下的文件，通常要会新建子目录，把相关文件移动到子目录下。其实R的操作，相当于shell的mv命令，所以此时我们先对文件进行标记，再按下R即可，emacs认为你将对标记文件进行操作。

查询与替换

把需要查询与替换的文件标记，然后按`Q`(dired-do-query-replace)，相当于IDE中的全局替换，而且更为细腻，可以只替换标记的文件。

安装`dired+`插件，可以增强其功能。

## 文本操作

occur

与一般的搜索mode不同，会新建一个缓冲区，在其中可以编辑搜索显示的行。我喜欢其显示形式，是新开一个窗口显示搜索列表，点击列表中的行，可以跳转对应的原文件对应之处。在修改之前，使用ocur预览，或者查找某一函数在此文本中的使用。

helm-occur

Similar to occur, but using Helm interface. As you type, matching lines are updated immediately. This is convenient when you want to have a list of matches in the current buffer to jump back and forth. TAB to temporarily move the point to the location of the currently highlighted match. C-g cancels the current Helm session and returns to the original location where helm-occur was invoked. RET on a match jumps to that match.

相对与occur原生功能，`helm-occur`支持`Ctrl-n Ctrl-p`上下移动选择，而原生需要使用鼠标，当然原生也可以修改，就使用而言，原生的occur更好。

helm-semantic-or-imenu

The Imenu facility offers a way to find the major definitions, such as function definitions or variable definitions in a file by name. You can run imenu command individually.

相当于大纲视图，有了这个功能就无需折叠代码的功能。可以浏览代码中所定义的函数之类。

evil

使emacs支持vim的编辑模式，vim的编辑模式的快捷键很用。无需因为两个编辑器的差异与争论，而抹杀其优点。兼容并包，方能成其大。

我使用vim有三年多，切换到evil很自然。且因为是在emacs中，有额外的好处。其中vim的编辑模式是其强大之处，但有时常常需要切换，也不甚方便。比如编辑之后，需要移动光标，就需要切换，或者使用上下左右，但我喜欢。而在emacs，此时使用`Ctrl-f Ctrl-b`等即可。当然，也可以在vim设置，此处不争论，我需要的工具的好处，不在乎其差异，能更好的为我所用即可。

bookmark

`Ctrl-x r m` bookmark set;
`Ctrl-x r b` bookmark jump;
`Ctrl-x r l` bookmark menu list; 可以在此中进行编辑操作，操作与dired类似。

标签的优点在于，其全局性，不局限与本文件，可以直接跳转在其他文件的标记之处。在多个常用的文件进行切换，其速度当数第一。


## 全局操作

## `org-mode`

## 插件列表

helm

evil

dired+



# 参考资料：

[A Package in a league of its own: Helm](http://tuhdo.github.io/helm-intro.html#orgheadline1)

[Master Emacs in 21 Days](http://book.emacs-china.org/#orgheadline2)

Learinng GNU Emacs by Debra Cameron, Bill Rosenblatt, Eric Raymond

Yvan say：我是一个后知后觉的人，向来迟钝。当年喜欢编程，也是莫名其妙折腾Linux这些，用了好多年的Linux作为日常用系统，今年切换到Mac，也不过是因为他有Linux很多好处，还有具有一个美的外在。我用Vim有几年了，今年切换为emacs，也是不明缘由，喜好而已，也许回到初衷，刚玩起这些的时候，我最初学的是emacs。

有时候同事过来调试代码，发现自己很多IDE下的好用的技巧都不会，也是惭愧。然而，Vim和emacs的技巧，我用的得怎么样呢？大概是开发过程脱离了鼠标而已。我并没有领悟到其中的精要。

略整理一下我在emacs中常用操作，编辑未动，搜索先行，是一贯的思想，且重搜索。现在的项目越来越大，其目录，人脑能难以轻松记忆，故搜索是很重要的功能。但不要轻视大脑的记忆，能多记忆几个关键字，能快速的定位到对应的代码。这是编程的一个重要的习惯，IDE的提示固然好，但记忆几个自己定义的函数，或功能，能在全局把控。

相关插件配置，见github的emacs.init项目。此处略去不录，乃因配置多变，按键绑定多变，但其使用的流程，使用的情形，是不变，以不变应多变。

