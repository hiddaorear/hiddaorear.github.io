---
layout: post
title: CSS3 SVG Animation and DOM
category: 技术
tags: [CSS3 SVG]
keywords: CSS3 SVG
description:
---

##### Tuesday, 13 October 2015

### CSS3 SVG Animation and DOM

![王羲之](/../../assets/img/tech/2015/wangxizhi_3.jpg)

### CSS3 SVG Animation and DOM

### 图片的预加载与延迟加载

````javascript

var pre_load = function(images_src) {
if (images_src && images.length) return false

  var images_array = []
  , i = 0
  , l = images_src.length
  ;
  
  for (; i < l; i++) {
    images_array[i] = new Image()
    images_array[i].src = images_src[i]
  }
}

````

JavaScript对图片的处理，最基本的部分，就是如此了。即使用`Image()`对象，并获取`src`的值而已。

#### 图片缓存处理

以上只是基本的图片加载处理，如果图片有缓存，已经加载需要触发回调，得改进。

````javascript

var load_image(url, cb, error_cb) ｛
  var img = new Image()
  
  if (img.complete) {
    cb && cb(img)
    return;
  }
  
  img.onload = function() {
    img.onload = null
    cb && cb(img)
  }
  img.src = url
  
  img.onrror = function() {
    img.onerror = null
    error_cb && error_cb()
  }
}

````

代码很精简，只增加了监听图片的`onload`事件，但对闭包和图片加载兼容性的处理很精彩。

- `img.onload`绑定了匿名函数，并内部引用了图片，形成闭包，循环引用，容易导致内存泄漏。所以触发`onload`事件之后，立即就释放了`img.onload`。
- 同时，如果是gif图片，有可能多次触发onload，这么处理正好避免了这个问题。
- 为什么`src`的赋值是在`onload`之后呢？因为在IE，Opera下，对缓存图片的初始状态，与Firefox，Safari，Chrome是不一样的。IE与Opear对于缓存的图片，不会触发`onload`事件，而Firefox，Safari，Chrome会触发。根本原因是：`img`的`src`复制与`onload`事件的绑定，顺序不对。IE和Opear下，先赋值`src`，再触发`onload`，由于是缓存图片，`src`已存在，故错过`onload`。所以，为了绑定`onload`事件，后赋值`src`。


以下原来有问题的代码：

````javascript

var load_image(url, cb) {
  var img = new Image()
  img.src = url
  
  if (img.complete) { // 对缓存的处理
    cb && cb(img)
    return;
  }
  
  img.onload = function() {
    cb && cb(img)
  }
}

````





### 参考资料:

[jquery.appear](https://github.com/morr/jquery.appear)
[jquery-waypoints](https://github.com/imakewebthings/jquery-waypoints)
[waypoints](https://github.com/imakewebthings/waypoints)
[parallax](https://github.com/wagerfield/parallax)
[layzr](https://github.com/callmecavs/layzr.js)

### Image
[javascript预加载和延迟加载](http://www.cnblogs.com/youxin/p/3369666.html)

[Fex Notes](http://fexnotes.com/)
[xss零碎指南](http://segmentfault.com/a/1190000000497596)



hid say: 玩一玩新技术。




