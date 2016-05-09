---
layout: post
title:  CSS瀑布流列布局
category: 资源
tags: [CSS 瀑布流列 布局]
keywords:  CSS瀑布流列布局
description: 
---

###  CSS瀑布流列布局

####  CSS瀑布流列布局

#### Sunday, 08 May 2016

![陈璧](/../../assets/img/tech/2016/ChenBi_8.jpg)

## `float`列布局
通过float使块元素水平排列，超过一行自动折行。此时有一个问题，里面排布的子元素间距的处理。考虑响应式布局，每行数目不固定，不能通过CSS3的选择器给最右边的单独设置间距。

### 负margin

```html
<ul class="list-wrap">
  <li>1</li>
  <li>1</li>
  <li>1</li>
  <li>1</li>
  <li>1</li>
</ul>

```

```css
.list-wrap {
  padding-top: 28px;
  padding-bottom: 20px;
  margin-left: -8px;
}

// 清除浮动
.list-wrap:before, .list-wrap:after {
  content: " ";
  display: table;
}
.list-wrap:after {
  height: 0;
  line-height: 0;
  visibility: hidden;
  clear: both;
}


.list-wrap li {
  float: left;
  margin-top: 28px;
  margin-left: 8px;
  width: 222px;
  height: 302px;
  overflow: hidden;
  position: relative;
}

```

要点： `margin`负值刚好与间距相等，这样刚好抵消多次来的间距。注意整体宽度的处理。


### 父元素padding

思路来自淘宝首页

```html
<ul class="list-wrap">
  <li>1</li>
  <li>1</li>
  <li>1</li>
  <li>1</li>
  <li>1</li>
</ul>

```

```css
.list-wrap {
  padding-left: 20px;
  padding-top: 28px;
  padding-bottom: 20px;
  /* margin-right: -20px; */ // 作者带上这个负margin的实现，实际在这里并没有用处
}

// 清除浮动
.list-wrap:before, .list-wrap:after {
  content: " ";
  display: table;
}
.list-wrap:after {
  height: 0;
  line-height: 0;
  visibility: hidden;
  clear: both;
}

.list-wrap li {
  float: left;
  margin-top: 28px;
  margin-right: 8px;
  width: 222px;
  height: 302px;
  overflow: hidden;
  position: relative;
}

```

要点：父元素提供统一的左间距，而子元素统一拥有右间距，故每列最后一个元素此时不会被换行。

## `display:inline-block`列布局

利用`inline, inline-block`的两端对齐。注意最后一行的处理。

```html
<ul class="list-wrap wrap">
  <li>1</li>
  <li>1</li>
  <li>1</li>
  <li>1</li>
  <li>1</li>
</ul>

```

```css

.list-wrap {
  text-align: justify;
}

.list-wrap li {
  display: inline-block;
  width: 210px;
}

.wrap {
      text-align:justify;
      text-justify:distribute-all-lines;/*ie6-8*/
      text-align-last:justify;/* ie9*/
      -moz-text-align-last:justify;/*ff*/
      -webkit-text-align-last:justify;/*chrome 20+*/
  }
  @media screen and (-webkit-min-device-pixel-ratio:0){/* chrome*/
      .wrap:after{
          content:".";
          display: inline-block;
          width:100%;
          overflow:hidden;
          height:0;
      }
  }


```

要点：子元素必须是`inline-block`，父元素设置`text-align: justify;`。缺点，间距要通过宽度来控制，其子元素宽度占据空间剩下的宽度均分的距离。


## `column-width`列布局

使用CSS3属性，`column-width`设置资子元素宽度，`colmun-gap`设置子元素间距。兼容`IE9-`，即IE9以及其以下不支持。

```html
<ul class="list-wrap">
  <li>1</li>
  <li>1</li>
  <li>1</li>
  <li>1</li>
  <li>1</li>
</ul>

```

```css

.list-wrap {
  column-width: 320px;
  column-gap: 15px;
  width: 90%;
  max-width: 1100px;
  margin-left: auto;
  margin-right: auto;
}

.list-wrap li {

}

```

所谓瀑布流，在列布局的基础上，在各列加上多行即可。



## 参考资料：

[折腾:瀑布流布局（基于多栏列表流体布局实现）](http://www.zhangxinxu.com/wordpress/2012/03/%E5%A4%9A%E6%A0%8F%E5%88%97%E8%A1%A8%E5%8E%9F%E7%90%86%E4%B8%8B%E5%AE%9E%E7%8E%B0%E7%9A%84%E7%80%91%E5%B8%83%E6%B5%81%E5%B8%83%E5%B1%80-waterfall-layout/)

[display:inline-block/text-align:justify下列表的两端对齐布局](http://www.zhangxinxu.com/wordpress/2011/03/displayinline-blocktext-alignjustify%E4%B8%8B%E5%88%97%E8%A1%A8%E7%9A%84%E4%B8%A4%E7%AB%AF%E5%AF%B9%E9%BD%90%E5%B8%83%E5%B1%80/)

[CSS兼容性检测](http://caniuse.com/#tables)

[使用纯CSS制作Pinterest样式的瀑布流图片列布局 ](http://www.htmleaf.com/ziliaoku/qianduanjiaocheng/201503091492.html)

[ 瀑布流布局浅析 ](http://ued.taobao.org/blog/2011/09/waterfall/)

[ jQuery 瀑布流布局插件 jQuery Masonry 参数介绍](http://www.lrxin.com/archives-693.html)

[css 文本两端对齐](http://www.cnblogs.com/rubylouvre/archive/2012/11/28/2792504.html)

[css实现两端对齐的3种方法](http://www.cnblogs.com/PeunZhang/p/3289493.html)



Hid say：文字属性的妙用。
