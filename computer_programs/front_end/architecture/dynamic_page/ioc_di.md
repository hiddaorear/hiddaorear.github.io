# IoC （控制反转）

#### 2023/8/18

## 产品需求中的控制反转

用户通过所见即所得的编辑页面，生成一份数据。多个后台加工这份数据并添加其他相关数据，发送给前端。前端解析后台所给数据，通过多样化的组件和组件运行的上下文等，支持不同的渲染架构（如webview，React native等），渲染页面，支持交互。不妨称之为LEGO项目，因为通过多个组件拼成一个页面，和LEGO积木类似。

![多后台多引擎](./thinking_in_design/multiple_backends.png)

## 使用多态实现控制反转

![control flow](./IoC/control_flow.png)

![IoC](./IoC/IoC.png)

## OOP（面向对象）和FP（函数式编程） 


## log

- 2023/8/18 初稿


