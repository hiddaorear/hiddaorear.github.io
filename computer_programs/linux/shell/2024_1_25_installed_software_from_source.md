{:toc}
# Linux源码安装软件

## Tarball

源码一般是压缩后的文件，后缀为`.tar.gz`等等，源码安装的软件也称之为Tarball软件。

```shell
wget https://mirrors.cloud.tencent.com/gnu/emacs/emacs-26.2.tar.gz
tar xf emacs-26.2.tar.gz
cd emacs-26.2
./configure --without-x --with-modules  --with-tree-sitter
make && sudo make install
```
### wget


### tar


## configure

configure是可执行文件，用于检查环境，检查完毕以后会主动生成特定的makefile，用于下一步make操作。

configure检查项：
- 是否有合适的编译程序，如gcc
- 是否有软件所需的函数库
- 操作系统是否匹配
- 内核定义的头文件是否存在

## ln

## 检查文件

### 检查文件是否存在

`[ -e filename ];echo $?`
返回0说明文件存在。

### 检查文件是否软链

`[ -L filename ];echo $?`
返回0说明是软链。

## make

把源码编译为操作系统可执行的二进制过程。

相关的有make clean，会清除之前编译的文件

## make install

复制make生成的可执行文件，到指定目录。


## 阅读资料

- [configure、 make、 make install 背后的原理(翻译)](https://zhuanlan.zhihu.com/p/77813702)
- [How to Get Started with Tree-Sitter](https://www.masteringemacs.org/article/how-to-get-started-tree-sitter)
