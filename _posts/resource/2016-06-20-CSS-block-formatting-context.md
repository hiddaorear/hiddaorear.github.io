---
layout: post
title:  CSS Block Formatting Context
category: 资源
tags: [CSS]
keywords: CSS
description:
---

### CSS Block Formatting Context

#### CSS Block Formatting Context

#### Monday, 20 Juny 2016

![ChenBi](/../../assets/img/resource/2016/ChenBi_20.jpeg)

### 引子：分栏高度相等布局

在有分栏的情况下，如不同的栏有背景颜色或者边框，在不能设置死高度的情况下，需要保持每个分栏的高度相等。

```html

<div class="content">
  <div class="left">left</div>
  <div class="right">right</div>
  <div class="center">center</div>
</div>

```

```css

.content {
  overflow: hidden;
}

.left,
.right {
  width: 200px;
  margin-bottom: -30000px;
  padding-bottom: 30000px;
}

.left {
  float: left;
  background-color: red;
}

.right {
  float: right;
  background-color: green;
}

.center {
  margin-left: 210px;
  margin-right: 210px;
  height: 600px;
  background-color: #ccc;
}

```

核心代码是，`padding-bottom & margin-bottom`的设置，父元素的`overflow: hidden;`。


### Block Formatting Context

用于决定块盒子的布局及浮动相互影响的一个区域。


下列情况将创建一个块格式化上下文：

1. 根元素或其他包含他的元素；
2. float不为none的元素；
3. 元素的position为absolute或fixed；
4. `inline-block`元素；
5. `display: table-cell`元素；
6. `display: table-caption`元素；
7. overflow的值不为visible的元素；
8. `display: flex | inline-flex`元素；

块格式化包括了创建该上下文的元素的所有子元素，但不包含创建了新的块格式化上下文的子元素。

块格式化上下文对定位与清除浮动很重要。块格式化上下文规定其影响的边界，定位和清除浮动的样式规则只适用于同一块格式化上下文内的元素。浮动不会影响其他格式化上下文中元素的布局，并且清除浮动只清除同一块格式化上下文中在他前面的原元素的浮动。

### Block formatting context 作用

1. 阻止边距折叠(margin collapsing);
2. 包含内部元素的浮动（闭合浮动）；
3. 阻止元素被浮动元素覆盖。



### 补充：去除`inline-block` 元素间距

其出现的原因为标签之间的空格。

消除办法：

```css

.space {
  font-size: 0;

  -webkit-text-size-adjust: none; // Chrome最小字体限制
}

```

## 参考资料：

[Block formatting context(块级格式化上下文)](http://www.cnblogs.com/MockingBirdHome/p/3365346.html)

[块格式化上下文](https://developer.mozilla.org/zh-CN/docs/Web/Guide/CSS/Block_formatting_context)

[CSS深入理解流体特性和BFC特性下多栏自适应布局](http://www.zhangxinxu.com/wordpress/2015/02/css-deep-understand-flow-bfc-column-two-auto-layout/)

[纯CSS实现侧边栏/分栏高度自动相等](http://www.zhangxinxu.com/wordpress/2010/03/%E7%BA%AFcss%E5%AE%9E%E7%8E%B0%E4%BE%A7%E8%BE%B9%E6%A0%8F%E5%88%86%E6%A0%8F%E9%AB%98%E5%BA%A6%E8%87%AA%E5%8A%A8%E7%9B%B8%E7%AD%89/)

[我熟知的三种三栏网页宽度自适应布局方法](http://www.zhangxinxu.com/wordpress/2009/11/%E6%88%91%E7%86%9F%E7%9F%A5%E7%9A%84%E4%B8%89%E7%A7%8D%E4%B8%89%E6%A0%8F%E7%BD%91%E9%A1%B5%E5%AE%BD%E5%BA%A6%E8%87%AA%E9%80%82%E5%BA%94%E5%B8%83%E5%B1%80%E6%96%B9%E6%B3%95/)

[去除inline-block元素间间距的N种方法](http://www.zhangxinxu.com/wordpress/2012/04/inline-block-space-remove-%E5%8E%BB%E9%99%A4%E9%97%B4%E8%B7%9D/)

[我是如何对网站CSS进行架构的](http://www.zhangxinxu.com/wordpress/2010/07/%E6%88%91%E6%98%AF%E5%A6%82%E4%BD%95%E5%AF%B9%E7%BD%91%E7%AB%99css%E8%BF%9B%E8%A1%8C%E6%9E%B6%E6%9E%84%E7%9A%84/)

hid say：笃思。
