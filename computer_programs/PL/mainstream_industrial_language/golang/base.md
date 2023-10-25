# 基础

## 项目规则

### 入口规则

- 入口 package 必须是 main
- 入口 func 也必须是 main

否则项目无法运行

### 依赖管理

Go Module 管理方案的设计原则：

- 兼容性
- 可重复性
- 合作性

### go.mod & go.sum 文件

go.mod 和 go.sum 成对出现在根目录中。go.mod 记录依赖关系和版本。go.sum 记录完全性和完整性校验的信息。

#### 兼容性（引入版本号到import语句中）

程序中的名称的含义，不应随时间而发生改变。如果有需要改变，则需要跟之前引入路径保持不同。

- 美学：对Go来说，良好的软件工程，比主观美学更加重要。如：使用首字母大小写替代是否可导出，够一眼看出哪些调用是可导出的，省去export关键字。导入路径有点长，但能更精细的表示导入模块，从而避免不必要的重复。

- 版本号放到路径中：版本号加入到导入路径中，保持语义的精确。当需要升级依赖包的时候，可以逐步，分阶段更新。随着时间推移，同一个项目代码，同一个依赖可能出现不同的版本。

#### 可重复性（最小版本选择）

构建可重复性很重要，这样保持程序的稳定性，这是基本要求。比使用最新版本更重要，虽然最新报备可能满足修复bug和性能提升。为了稳定性，Go modules 选择了最小版本选择（Minimal Version Selection）。

和当前常见的”最新最大（latest greatest）版本“不同。如果语义版本控制（sematic versioning），能被正确遵守，这样也可行。要求最新最大版本，与较早版本具有向后兼容性。

#### 合作性

Go Modules 引入语义化版本来标识依赖的版本，而且是强制的。

1. 第一位版本号：不兼容修改
2. 第二位版本号：新特性
3. 第三位版本号：bug修复

但规范没有约束力，由海勒姆 hyrums 定律，也叫做隐式接口定律：

> With a sufficient number of user of an API, it does not matter what you promise is the contract. All observable behaviors of your system will be depended on by somebody.

> 当 API 有足够多的用户时，你在文档中的承诺已不重要，你的系统所有可观察行为都被某些人所依赖。

例如，用户使用正则表示式匹配错误提示来判断API的错误类型，即使API文档中没有任何错误提示内容，而是指导用户使用错误码。这种情况下，修改API错误提示信息，实际会破坏 API 的使用。俗称：不按套路出牌。

关于语义版本的引入，Russ Cos说：

> A year ago， I believe that putting versions in import paths like this was ugly， undesirable， and probably avoidable. But over the past year, I've come to understand just how much clarity and simplicity they bring to the system. In this post I hope you a sense of why I changed my mind.

Russ Cos的想法也是随时间改变。没有一个东西开始就是完美的，谨慎引入，坚持原则，可以减少犯更大错误的概率。

## 阅读资料

- [Golang 版本管理系列 翻译 11 篇全](https://github.com/vikyd/note/tree/master/go_and_versioning)
- [Go modules：最小版本选择](https://tonybai.com/2019/12/21/go-modules-minimal-version-selection/)
- [studygolang 【简单的科普】](https://polarisxu.studygolang.com/page/2/)
