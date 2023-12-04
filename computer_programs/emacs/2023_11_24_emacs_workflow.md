# Emacs 工作流

## 基本按键

- 向前移动一个单词： Alt + f
- 向后移动一个单词： Alt + b
- 向前删除： Ctrl + d
- 重复最后一次执行的命令: `C-x z`（repeat），按了一次以后，后面只需要按`z`。或者`C-x M-z`（repeat-complex-command）

## 智能补全

lsp-bridge

## 括号插件

## 代码编辑

move-text：把当前行上移或下移。

open-newline：不用移光标，在上面或下面新开一行。相当于三个操作的结合：移动到行尾，按回车，按缩进。

## 位置导航

写代码经常需要移动光标到其他地方看一下，再切回来。可用Emacs的register临时保存代码的位置，使用懒猫的小函数：remember-init和remember-jump，先用remember-init保存位置，切走以后，调用remember-jump即可回到之前的位置。

## 微操作

- bury-buffer/unbury-buffer: 快速切换里斯记录中的前后两个buffers。如果buffer可以通过sort-tab或者bury/unbury操作切换，更直观，更高效，不用弹搜索框。

## 窗口管理

遇到分屏，快速切换状态。可以使用Emacs内置的current-window-configuration 记住当前窗口布局，delete-other-windows命令清理其他窗口，用set-window-configuration恢复之前的窗口布局。

## 代码重构

正则式的代码重构，使用color-rg。常用的有color-rg-search-input和color-rg-search-symbol。

## 阅读资料

- [我平常是怎么使用 Emacs 的？](https://manateelazycat.github.io/2022/11/07/how-i-use-emacs/)

- [面向产品经理的Emacs教程](https://remacs.cc/posts/)
