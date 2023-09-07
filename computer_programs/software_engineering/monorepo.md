# monorepo工作流

使用lerna和yarn workspace管理项目，用yarn处理依赖，lerna处理发布。

## 搭建环境
- 普通项目：clone以后，`yarn install`
- monorepo项目：各个包存在依赖，如A依赖B，需要将B link到A。手动管理成本高，使用yarn workpaces，按照拓扑排序，将各个依赖link

## 管理环境

### 清理

- 普通项目：直接删除node_modules，和编译产物
- monorepo项目：需要删除root中node_modules，还有package中各个包的

```shell
$ lerna cleas # 清理所有的node_modules
$ yarn workspaces run clean # 执行所有package的clean操作

```

### 安装和删除依赖

- 普通项目：通过`yarn add`和`yarn remove`即可
- monorepo项目：
  1. 给某一package安装依赖：B依赖A，`yarn workpace B add A`；删除：`yarn workpace B remove A`
  2. 给所有package安装依赖：`yarn workpace add lodash`；删除：`yarn workpace remove lodash`
  3. 给root安装依赖：公共开发工具放到root中，如TS等等，`yarn add -W -D typescript`；删除：`yarn remove -W -D typescript`

## 构建项目
- 普通项目：建立一个build的npm script，使用yarn build构建
- monorepo项目：各个package互相依赖。如B依赖A，B只能在A构建完成以后，才能构建。需要用拓扑排序规则进行构建：`lerna run --stream --sort build`


## 测试项目
- 普通项目：建立test的npm script即可
- monorepo项目：
  1. 使用统一的jest测试配置，全局跑jest接口，便于统计所有代码覆盖率；package有异构，配置不易处理
  2. 每个package支持test，使用`yarn workpace run test`。配置好写，不好统一收集代码测试覆盖率

## 升级版本和发包

### 验证

- 测试是否通过
- 是否存在未提交的代码
- 是否在主干分支进行发布操作

### 版本号

- 版本号遵循semVer语义。少量提交，可以手动处理，存在失误的可能。可以通过git的提交记录更新版本号。
- git commit message遵循Conventional commit规范。

### 生成git tag
 
 方便回滚操作
 
### 发布版本
 
 单独生成一个commit记录标识 milestone

### 发布npm包

发布git以后，发布包到npm，方便外部用户使用。lerna的publish和version支持版本升级和发布。

## 阅读资料

- [基于lerna和yarn workspace的monorepo工作流](https://zhuanlan.zhihu.com/p/71385053)
