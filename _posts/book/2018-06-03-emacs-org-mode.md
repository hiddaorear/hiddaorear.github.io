---
layout: post
title:  org mode的简介
category: emacs
tags: [emacs]
keywords: org mode
description:
---

##### Sunday, 3 June 2018

## org mode的简介

![image](/../../assets/img/book/2018/Brother_typewriter_by_awdean1.jpg)

### 简介

Org mode 是 Emacs 的一个插件，能为 Emacs 用户提供一个强大的纯文本编辑环境。org是一种轻量级的标记语言，与Markdown类似。

### 基本使用

#### 以\*开头并空一个空格，创建一个headline

#### Tab键是折叠的开关

#### Shift-Tab是全局的折叠开关

#### Control-Enter生成一个同级的headline

### 导出文件

#### C-c C-e导出文件，可以导出HTML、Markdown和PDF等

#### 设置

-   \#+TITLE: 设置标题
-   \#+OPTIONS: toc:nil 去掉目录

### Markup

#### 加粗：使用\*包裹

#### 斜体：使用/包裹

#### 下划线：使用<sub>包裹</sub>

#### 删除线：使用+包裹

#### 引用块：输入"<q"，然后按Tab键，自动插入一个引用块

#### 事例块：输入"<e"，然后按Tab，插入一个事例块

#### 代码块: 输入"<s"，然后按Tab，并输入代码的语言类型，可以根据对应的语言高亮，需要设置

```` elisp
    (setq org-src-fontify-natively t)

````

```` js
    function demo() {
      console.log("Hi!");
    }

````

### Todo

#### C-c C-t可以循环切换状态

#### C-c C-d可以插入结束时间

#### 设置DONE状态插入完成时间 `(setq org-log-done 'time)`

#### 标签

##### 设置标签

```` elisp
    (setq org-tag-alist '(("紧急重要" . ?a) ("紧急不重要" . ?s) ("不紧急重要" . ?d) ("不紧急不重要" . ?f)))

````

##### 在headline上C-c C-c，然后选择对应的标签，按空格清空标签

### List

#### 在列表开头使用[]即可

#### 可以在headline之后添加[]，可以自动同级这样下面的item项

```` org
    ** todolist [1/2]
    - [X] 1
    - [ ] 2
    
````

#### 在对应的项上，按C-c C-c就可以修改状态
