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

hid say: 深思。



