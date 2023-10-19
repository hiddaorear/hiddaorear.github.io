# emacs 基础

#### 2023/10/16

## emacs elisp 调试

### 调试相关的启动参数

- `Q`：不加载任何配置
- `--init-directory`：指定init文件路径
- `--debug-init`：在加载init文件时启动调试器

### debug调试器

触发调试器

- `M-x toggle-debug-on-error`：出现错误时，显示堆栈
- `(setq debug-on-message "message")`：当message匹配正则的时候触发
- `M-x debug-on-entry`：在指定函数入口启动调试器
- `(setq debug-on-quit t)`：当`C-g`时启动调试器，常用于调试无限循坏
- `(debug)`：插入到代码中，执行触发启动调试器

调试器操作

- d：单步执行
- q：退出
- c：退出当前debug中断，继续执行，直到遇到下一个error或者debug
- e：求值，并显示在minibuffer

## 文本编辑

#### 搜索

- 【查】consult搜索：`consult-ripgrep`，快捷键：`C-x s`

### 菜单  imenu

- 大纲视图，且支持跳转：`consult-imenu`，快捷键：`M-s i`

### 光标移动

- 向上向下移动一行 `C-n C-p`
- 移动到行首和行尾 `C-a C-b`
- 移动第n行：`M-g g n RET`
- 左右移动一个单词 `M-b M-f`
- 文章开始和结尾  `M-< M->`

### 复制粘贴

- 将光标移到需要复制区域的首字符
- `C-@`，设置标记
- 将光标移动到区域最后一个字符
- 键入`M-w`，复制这个区域内容到粘贴板（剪切是`C-w`）
- 光标移到需要粘贴的地方，键入`C-y`

### 代码搜索和重构

#### color-rg

- color-rg-search-input: Search user's input with current directory
- color-rg-search-symbol: Search current symbol with current direcory【搜索当前光标下单词】
- color-rg-search-input-in-project: Search user's input in project
- color-rg-search-symbol-in-project: Search current symbol in project
- color-rg-search-symbol-in-current-file: Search current symbol in current file
- color-rg-search-input-in-current-file: Search user's input in currfent file

Keymap for view mode

- `Tab`: Jump to next match keywork
- `r`: Replace all matches

## 文件编辑

### 阅读资料

- [How to open a file in Emacs](https://www.murilopereira.com/how-to-open-a-file-in-emacs/)

### 浏览目录

- 【查】使用内置的包：`speedbar`

其他sidebar包：treemacs、Dired-sidebar、NeoTree

见讨论：[Emacs 风格的文件操作和项目文件管理是啥样的？](https://emacs-china.org/t/emacs/22306/19)

### 文件搜索

- 【查】consult：`consult-ripgrep`，快捷键：`C-c p f`

### 进入Dired

- `C-x C-f`
- 直接进入：`C-x d`
- 新开一个window，并进入dird：`C-x 4 d`

### 在Dired操作文件

- 刷新：`g`
- 【增】子目录：`+`
- 【增】复制：`C`
- 【删】删除文件：`D`
- 【删】取消标记：`d`
- 【改】重命名：`R`

### 在Dired中使用书签

- 【增】新增书签：`C-x r m`
- 【删】删除书签：在Bookmark list中按`d`，为书签添加flag，然后按下`x`
- 【查】查看书签列表：`C-x r l`


## 阅读资料

- [Emacs之怒](http://blog.lujun9972.win/tags/emacs%E4%B9%8B%E6%80%92/)
