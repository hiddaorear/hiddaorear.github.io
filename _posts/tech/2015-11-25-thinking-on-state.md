---
layout: post
title:  Thinking on state
category: 技术
tags: [Programing Thinking]
keywords: thinking on programing
description:
---

##### Wednesday, 25 November 2015

### Thinking in state

![the gargen of world](/../../assets/img/tech/2015/the_garden_of_world_59.PNG)

> 所谓显然的事情通常并非真的那么显然，使用“显然”这个词往往意味着缺乏逻辑论证。 -- Errol Morris

> 再多的天赋也战胜不了对细节的偏执。  --俗语

## Curry

### 实现封装

JavaScript常见的DOM插入与删除。
普通写法：

````javascript

var append = function(parent, child) {
  parent.appendChild(child)
}

var remote = function(dom) {
  dom.remove()
}

append(parent, child)
remove(child)
````
变量都在函数外部，不能保证每个remove都正确。

curry办法：

````javascript

var append = function(parent, child) {
  parent.appendChild(child)
  return function() {
    child.remove()
  }
}

var remove = append(parent, child)
remove()

````


### 参考资料:
[JavaScript与有限状态机](http://www.ruanyifeng.com/blog/2013/09/finite-state_machine_for_javascript.html)
[基于有限状态机的交互组件设计与实现 ](http://ued.taobao.org/blog/2012/10/fsm/)
[有限状态自动机的javascript实现](http://yiminghe.iteye.com/blog/407443)
[jakesgordon/javascript-state-machine ](https://github.com/jakesgordon/javascript-state-machine)
[状态机——Javascript词法扫描示例 - 随机 - 博客园](http://www.html-js.com/article/1430)
[JavaScript 中的有限状态机，第 1 部分: 设计一个小部件](http://www.uml.org.cn/UMLApplication/200811172.asp)
[富交互性的动态用户界面 ](http://reactjs.cn/react/docs/interactivity-and-dynamic-uis.html)


hid say: 深思。



