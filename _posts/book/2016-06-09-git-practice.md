---
layout: post
title:  git practice
category: 读书
tags: [git]
keywords: git
description:
---

##### Thursday, 09 June 2016

## git实战

### git实战

![nice](/../../assets/img/book/2016/nice_13.jpg)

## 查看 git history

## git log 用法

### 过滤

#### 按范围

用法

`git log <since>..<until>`

作用

比如，显示两个分支的差异：`git log master..feature`，显示包含在feature分支，而不在master的所有提交。注意范围的顺序，如果是`git log feature..master`则是表示包含在master而不在feature分支所有提交。如果两个分支提交都输出了，表明提交历史已经交叉了。

#### 按内容

用法

`git log -S "<string>"`

`git log -G "<regex>"`

作用

搜索某字符串何时加到何文件中。类似于条是工具，定位到所有影响代码中特定的一行的提交。

### 按提交信息

用法

`git log --grep="<string>"`

作用

按提交信息来过滤。

用法(利用shell的grep功能)

`git shortlog --format='%H|%cn|%s' | grep '<string>'`

作用

找出某些commit内容包含某个特定的字符串。

### 查看特定历史

`git log file_name`，查看此文件的修改历史。

### git show

`git show commit_hash`，查看某次commit的修改。

`git show :/^string`，查看满足正则最后一条commit。`-a`标示，会在远程查找。



## git diff

`git diff master..branch_name`，找出master与branch_name之间的差异。

`git diff master...branch_name`，找出master与branch_name之间的共同点。

`git diff`，当前工作目录与上次提交的差异。

`git diff --cached`，下次提交时，所要提交的内容。

`git diff branch_name`，工作目录与另一个分支差异。

`git diff HEAD -- ./lib`，当前分支中`/lib`目录与上次提交之间的差别。

`git diff --stat`，查看统计信息。

### `git cherry`

`git cherry -v other_branch_name`，cherry检查分支的变化是否存在于其他分支，`+`表示不存在，`-`表示存在。

### `git branch`

`git branch --merged`，查看已经合并过当前分支。

`git branch --no-merged`，查看未合并过当前分支。

`git branch --merged | xargs git branch -d`，删除已经合并过的分支。

### `git blame`

blame显示一份文件每一行最近一次提交的hash值和提交者。

```shell

git blame -W <filename> # 忽略增删空白的改动
git blame -M <filename> # 忽略文本移动的改动
git blame -C <filename> # 忽略移动文本内容到其他文件的改动

```

### `git rev-list`

`git rev-list --all | xargs git grep -f "<string>"`，搜索字符串.



## 重写 git history

## modified 之后重写history

`git checkout -- file_name`

## add 之后重写history

`git reset HEAD file_name`


## commit 之后重写history

### `git commit --amend`

#### 场景

commit之后，发现漏掉了文件，或者提交信息写错了，需要重新编辑上一次提交之时。

#### 用法

```shell

//  修改注释
git commit --amend

//  文件处理
git commit -m 'initial commit'
git add forgotten_file
git commit --amend  --no-edit

```

#### 弊端

不要修改共享的提交。修复过的提交是全新的提交，之前的提交被移出项目的历史，其他开发看上去他们的工作从项目历史中消失了。


#### 本质

修改之前的commit并合并到一起，对原来的commit进行了一次替换。

![git](/../../assets/img/book/2016/git_commit_amend.svg)

### `git rebase`

#### 场景

保持项目的线性历史。

#### 用法

`git rebase <base>`

将当前分支rebase到`<base>`（可以是任何类型的提交引用，如ID，分支名，tag或者HEAD相对引用）。

#### 弊端

不能在公共仓库执行rebase，因为rebase会用新的提交替换就的提交，原有历史会消失。

#### 本质

![git](/../../assets/img/book/2016/git_rebase.svg)

####  容易出现的问题

误导的`forget to use 'git add'`提示

执行`git rebase --continue`之后，即使之前解决冲突之后，执行了`git add file_name`，`git status`仍然会提示`No Changes - Did You Forget to Use ‘Git Add’?`

此时执行`git rebase --skip`即可。

原因：

> Turns out that because there is no change from the patch git suspects something has gone wrong. Git expects a patch to have been applied, but the file has remained unchanged.

> The error message is not very intuitive, but it does contain the answer. We just need to tell rebase to skip this patch. It’s also not necessary to fix the conflict markers in the file. You will end up with the file version from the branch you are rebasing on.


#### `git add .`

此时不能使用此命令，根本就没有把解决冲突之后的文件add，后续运行`git rebase --continue`之后会再次提示冲突，并且冲突的地方增加一处。

同时，执行`git add file`之后，不需要执行commit，直接`git rebase --continue`即可。

#### 两次冲突

在2以下的版本，ubuntu环境。需要两次解决冲突，第一次冲突是`<base>`与空的冲突，第二次才是本分支更新之后部分与`<base>`的冲突，表现很诡异。


### `git rebase -i`

#### 场景

需要更细腻的reabse。想修改单个提交，而不是一次性把所有的提交都rebase。就像需要多次`git commit --amend`.

#### 用法

`git rebase -i <base>`

此后在编辑器处理即可。

#### 弊端

将不重要的提交合并，删除不需要的，使在正式项目中的历史整齐。也不能在公共版本上执行。



#### 本质

控制项目的历史。

#### 容易出现的问题

在编辑中完成之后，不能保存，如下：

I simply want to edit some commits with git rebase -i HEAD~2 inside the current branch. I use Ubuntu 10.10 and had to install gvim first to make the command work. Afterwards, the command opens a gvim window with the normal rebase content. But when I want to save the file gvim says `".git/rebase-merge/git-rebase-todo" E212`


ths solution was:

run `git config --global core.editor "gvim -f"`.


### 清除 git history

`git checkout --orphan new_branch_name`，新建一个分支，并清除历史信息。


## 恢复 git history

`git branch branch_name commit_hash`，基于commit新建分支。

## 冲突的处理

当我们`git pull/push/merge`时，有可能产生冲突，有些文件可能要我们手来解决，还有些可以确定时保留`local`还是`remote/other_branch`分支的修改。

`git checkout --ours path/file`

`git checkout --theirs path/file`

`git -lr '<<<<<<<' . | xargs git checkout --ours`

`git -lr '>>>>>>>' . | xargs git checkout --theirs`


## 发布 git history

### `git archive`

场景

打增量包。

用法

`git archive -o ../updated.zip HEAD $(git diff --name-only HEAD^)`,把最近commit过的修改的文件，导出到一个zip文件。也就git打增量包。

`git archive -o ../latest.zip new_commit_id_head $(git diff --name-only old_commit_id_head new_commit_id_head)`，导出两次提交之间修改过的文件。


## 常用技巧

0.
发布版本之前，一定要去master分支看看是否有新的提交，避免覆盖代码。

1.
`git checkout branch_name -- path_to_file_in_branch`，在不切换分支的情况下，从其他分支获取文件。

2.
`git update-index --assume-unchanged path_to_file`，忽略特定的文件的更改。

3.
`git checkout -`，切换到上次的分支。



### 参考资料

[No Changes - Did You Forget to Use ‘Git Add’?](http://wholemeal.co.nz/blog/2010/06/11/no-changes-did-you-forget-to-use-git-add/)

[How to remove/delete a large file from commit history in Git repository?](http://stackoverflow.com/questions/2100907/how-to-remove-delete-a-large-file-from-commit-history-in-git-repository)

[9.7 Git 内部原理 - 维护及数据恢复](https://git-scm.com/book/zh/v1/Git-%E5%86%85%E9%83%A8%E5%8E%9F%E7%90%86-%E7%BB%B4%E6%8A%A4%E5%8F%8A%E6%95%B0%E6%8D%AE%E6%81%A2%E5%A4%8D)

[如何修改 git 记录？](https://segmentfault.com/a/1190000003947100)

[6.4 Git 工具 - 重写历史](https://git-scm.com/book/zh/v1/Git-%E5%B7%A5%E5%85%B7-%E9%87%8D%E5%86%99%E5%8E%86%E5%8F%B2)

[初次使用 git 的“核弹级选项”：filter-branch](http://lilydjwg.is-programmer.com/2011/4/22/tried-the-nuclear-option-filter-branch-of-git-the-first-time.26331.html)

[5.3 Git log高级用法](https://github.com/geeeeeeeeek/git-recipes/wiki/5.3-Git-log%E9%AB%98%E7%BA%A7%E7%94%A8%E6%B3%95)

[每一行代码都有记录—如何用git一步步探索项目的历史](http://www.cnblogs.com/lanxuezaipiao/p/3552805.html)

[你所不知道的git技巧](http://ilucas.me/2015/12/17/git-tips/)

[高富帅们的Git技巧](http://mux.alimama.com/posts/711)

[你不一定知道的几个很有用的 Git 命令](http://www.cnblogs.com/lhb25/p/10-useful-advanced-git-commands.html)


hid say: 温故。
