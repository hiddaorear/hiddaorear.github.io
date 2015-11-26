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

从状态机的角度，每次执行curry化的函数之后，相当于重写了函数，可以作为状态转变的标记，而且没有用到标记变量。但用curry化来做状态转变，是一次性的，不可逆；另，只能处理简单的状态转变，复杂的状态转变也可以，但是returne不同的函数来说，得不偿失。

### 简单的状态模式
来自《JavaScript设计模式与开发实践》 的例子

````javascript

var State = function() {}
State.prototype.buttonWasPressed = function() {
  throw new Error('父类中的buttonWasPressed方法必需被重写')
}

var OffLightState = function(light) {
  this.light = light
}

OffLightState.prototype = new State()

OffLightState.prototype.buttonWasPressed = function() {
  console.info('弱光')
  this.light.setState(this.light.WeakLightState)
}

var WeakLightState = function(light) {
  this.light = light
}

WeakLightState.prototype = new State()

WeakLightState.prototype.buttonWasPressed = function() {
  console.info('强光')
  this.light.setState(this.light.StrongLightState)
}

var StrongLightState = function(light) {
  this.light = light
}

StrongLightState.prototype = new State()

StrongLightState.prototype.buttonWasPressed = function() {
  console.info('关灯')
  this.light.setState(this.light.OffLightState)
}


var Light = function() {
  this.OffLightState    = new OffLightState(this)
  this.WeakLightState   = new WeakLightState(this)
  this.StrongLightState = new StrongLightState(this)
  this.button = null
}

Light.prototype.setState = function(newState) {
  this.currState = newState;
}

Light.prototype.init = function() {
  var button = document.createElement('button')
    , self = this
    ;

  this.button = document.body.appendChild(button)
  this.button.innerHTML = '开关'

  this.currState = this.OffLightState;

  this.button.onclick = function() {
    self.currState.buttonWasPressed();
  }
}

var light = new Light()
  light.init()

````

核心思想是，调用同一个对象，其状态指针随状态的转变而变。通过改变指针的指向，实现了每次状态转变只调用同一个对象，而不是通过if判断来调用不同的对象。以不变应万变，而对象自身随变化而变。

以上代码中，有重复的地方，通过JavaScript的原型继承，将其抽象出来：

````javascript


var StateFactory = function(global) {
  var State = function(global) { this.gloabl = global }
  State.prototype.buttonWasPressed = function() {
    throw new Error('父类中的buttonWasPressed方法必需被重写')
  }

  return function(param) {
    var F = function(_default) {
      this._default = _default
    }
    F.prototype = new State()
    
    for (var i in param) {
      F.prototype[i] = param[i];
    }
    return F
  }
}

var Light = function() {}

Light.prototype.setState = function(newState) {
  this.currState = newState;
}

Light.prototype.init = function() {
  var button = document.createElement('button')
    , self = this
    ;

  this.button = document.body.appendChild(button)
  this.button.innerHTML = '开关'

  this.currState = this.OffLightState;

  this.button.onclick = function() {
    self.currState.buttonWasPressed();
  }
}

var light = new Light()

var OffLightState = StateFactory(light)({
  buttonWasPressed: function() {
    console.info('弱光')
    light.setState(light.WeakLightState)
  }
})

light.OffLightState    = new OffLightState(light)

var WeakLightState = StateFactory(light)({
  buttonWasPressed: function() {
    console.info('强光')
    light.setState(light.StrongLightState)
  }
})

light.WeakLightState   = new WeakLightState(light)

var StrongLightState = StateFactory(light)({
  buttonWasPressed: function() {
    console.info('关灯')
    light.setState(light.OffLightState)
  }
})

light.StrongLightState = new StrongLightState(light)

light.init()

````

使用工厂函数，将重复的代码抽象。curry的直接连续调用，看起来不错，虽然有点怪。`fn()()`这样的调用，不常见。

### 函数委托的使用`call | apply`
共用函数，我们直觉会想到面向对象的继承，很少能想到使用函数委托。实际上，函数委托是更为简洁的办法。

````javascript
function Delegate(context, delegate, to_delegate) {

  if (delegate.to_delegate) {
    throw new Error('to_delegate undefined')
    return false
  }
  
  var return_obj = {}
  return_obj[to_delegate] = function() {
      return delegate[to_delegate].apply(context, arguments)
  }
    
  return return_obj
}

var FSM = {
  off: {
    buttonWasPressed: function() {
      console.log('off')
      this.button.innerHTML = 'next on'
      this.currState = this.onState
    }
  }
  ,on: {
    buttonWasPressed: function() {
      console.log('on')
      this.button.innerHTML = 'next off'
      this.currState = this.offState
    }
  }
}

var Light = function() {
  this.offState = Delegate(this, FSM.off, 'buttonWasPressed')
  this.onState = Delegate(this, FSM.on, 'buttonWasPressed')
  this.currState = this.offState;
  this.button = null
}

Light.prototype.init = function() {
  var button = document.createElement('button')
  , self = this
  ;
  button.innerHTML = 'off'
  this.button = document.body.appendChild(button)
  this.button.onclick = function() {
    self.currState.buttonWasPressed()
  }
}

var light = new Light()
light.init()

````

需要要注意的是，被委托函数的this的使用。需要想到被委托对象的属性，这种预判的思维方式，估计是这个函数委托的思维挑战。
然而，这个办法的简明与高效，值得注意。

### 参考资料:
《JavaScript设计模式与开发实践》 曾探
[JavaScript与有限状态机](http://www.ruanyifeng.com/blog/2013/09/finite-state_machine_for_javascript.html)
[基于有限状态机的交互组件设计与实现 ](http://ued.taobao.org/blog/2012/10/fsm/)
[有限状态自动机的javascript实现](http://yiminghe.iteye.com/blog/407443)
[jakesgordon/javascript-state-machine ](https://github.com/jakesgordon/javascript-state-machine)
[状态机——Javascript词法扫描示例 - 随机 - 博客园](http://www.html-js.com/article/1430)
[JavaScript 中的有限状态机，第 1 部分: 设计一个小部件](http://www.uml.org.cn/UMLApplication/200811172.asp)
[富交互性的动态用户界面 ](http://reactjs.cn/react/docs/interactivity-and-dynamic-uis.html)

[JS设计模式笔记(状态模式)](http://blog.xinshangshangxin.com/2015/07/03/JS%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%E7%AC%94%E8%AE%B0-%E7%8A%B6%E6%80%81%E6%A8%A1%E5%BC%8F/)
[js状态机与setTimeout的特殊应用 ](http://pleasureswx123.github.io/2015/02/12/js%E7%8A%B6%E6%80%81%E6%9C%BA%E4%B8%8EsetTimeout%E7%9A%84%E7%89%B9%E6%AE%8A%E5%BA%94%E7%94%A8/)
[ 深入理解JavaScript系列（43）：设计模式之状态模式](http://www.cnblogs.com/tomxu/archive/2012/04/18/2437099.html)

hid say: 深思。



