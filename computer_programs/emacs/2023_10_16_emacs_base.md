# emacs 基础

#### 2023/10/16

## 文本编辑

### 查看

#### 菜单  imenu

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

## 文件编辑

### 浏览目录

- 【查】使用内置的包：`speedbar`

其他sidebar包：treemacs、Dired-sidebar、NeoTree

见讨论：[Emacs 风格的文件操作和项目文件管理是啥样的？](https://emacs-china.org/t/emacs/22306/19)

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
