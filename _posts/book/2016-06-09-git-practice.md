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

## 查看git history

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

### 参考资料

[No Changes - Did You Forget to Use ‘Git Add’?](http://wholemeal.co.nz/blog/2010/06/11/no-changes-did-you-forget-to-use-git-add/)

[How to remove/delete a large file from commit history in Git repository?](http://stackoverflow.com/questions/2100907/how-to-remove-delete-a-large-file-from-commit-history-in-git-repository)

[9.7 Git 内部原理 - 维护及数据恢复](https://git-scm.com/book/zh/v1/Git-%E5%86%85%E9%83%A8%E5%8E%9F%E7%90%86-%E7%BB%B4%E6%8A%A4%E5%8F%8A%E6%95%B0%E6%8D%AE%E6%81%A2%E5%A4%8D)

[如何修改 git 记录？](https://segmentfault.com/a/1190000003947100)

[6.4 Git 工具 - 重写历史](https://git-scm.com/book/zh/v1/Git-%E5%B7%A5%E5%85%B7-%E9%87%8D%E5%86%99%E5%8E%86%E5%8F%B2)

[初次使用 git 的“核弹级选项”：filter-branch](http://lilydjwg.is-programmer.com/2011/4/22/tried-the-nuclear-option-filter-branch-of-git-the-first-time.26331.html)

[5.3 Git log高级用法](https://github.com/geeeeeeeeek/git-recipes/wiki/5.3-Git-log%E9%AB%98%E7%BA%A7%E7%94%A8%E6%B3%95)

[每一行代码都有记录—如何用git一步步探索项目的历史](http://www.cnblogs.com/lanxuezaipiao/p/3552805.html)

[ 发新帖 Git中级用户的25个提示](http://www.guokr.com/post/696433/)

[如何优雅地使用 Git？](https://www.zhihu.com/question/20866683)

[25个Git用法技巧](http://www.techug.com/25-git-tips)

[够用一年的Git 技巧 ](http://www.imooc.com/article/1426)

[你所不知道的git技巧](http://ilucas.me/2015/12/17/git-tips/)

[高富帅们的Git技巧](http://mux.alimama.com/posts/711)

[ Git命令10个很有用的使用技巧](http://www.linuxde.net/2013/08/15141.html)

[Git 有什么奇技淫巧？](https://www.zhihu.com/question/27462267)

[19个Git日常实用技巧(上)](http://www.jointforce.com/jfperiodical/article/1522)

[开发指南之Git命令的最佳实践技巧 ](http://www.freebuf.com/sectool/98396.html)

[Git显示漂亮日志的小技巧](http://coolshell.cn/articles/7755.html)

[git使用技巧汇总](http://www.jianshu.com/p/b0e072c5470c)

[少有人知的 GitHub 使用技巧](https://segmentfault.com/a/1190000000475547)

[MrZheng Git版本控制器的基本使用 ](http://div.io/topic/897)



id say: 温故。
