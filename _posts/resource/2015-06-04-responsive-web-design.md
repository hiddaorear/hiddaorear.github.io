---
layout: post
title:  Responsive web design(1)
category: 资源
tags: [seaJS jQuery Less git grunt project]
keywords: seaJS jQuery Less git grunt
description: 
---

### Responsive web design(1)

#### Thursday, 04 June 2015

![齐白石](/../../assets/img/resource/2015/qibaishi_10.jpg)

> 手机就像黑洞，在吸收一切。

### 响应式图片

### 1. 图片依赖宽度成比例缩放
利用CSS盒子模型的特性，在百分比为尺寸单位的情况下，`padding || margin`的值由`width`确定。而`padding`内可以显示背景，因此利用这两个特性，我们可以实现宽高比固定点的图片样式。

````css
//实现了宽高比为1:2
  .img-wrap {
    height: 0;
    width: 50%;
    padding-top: 50%; // 或者padding-bottom: 50%;
    background-image: url(hello.png);
    background-repeat： no-repeat;
  }
````

### 2. 使用CSS3特性

````html
<img src="image.jpg" data-src-600px="image-600px.jpg" data-src-800px="image-800px.jpg" alt="text">
````
````css
@media (min-width: 600px) {
  img[data-src-600px] {
    content: attr(data-src-600px, url);
  }
}

@media (min-width: 800px) {
  img[data-src-800px] {
    content: attr(data-src-800px, url);
  }
}

````

### 3. 利用JavaScript来切换图片的`src`

````javascript
  //判断是否手机
  window.op = window.op || {};
	op.isMobile = navigator.userAgent.toLowerCase().match(/Mobile/i)!==null;
	
	op.isIE8 = (!-[1,]);
	
	var $img = $('img');
	var srcPC = img.attr('src');
	if (op.isMobile && srcPC.length ) {
	  var srcString = srcPC.toString();
	  var _index = srcString.lastIndexOf('.');
	  var _src = srcString.substr(0, _index);
	  var imgFormat = srcString.substr(++_index);
	  var mobileSrc = _src + '_mobile.'+ imgFormat;
	  $img.attr('src', mobileSrc);
	}
````

### 响应式尺寸

如果使用像素作为尺寸的单位，会导致在不同屏幕上需要重写尺寸的CSS，以适应屏幕大小。这样有很多缺点，首先有冗余的样式，还有移动端需要加载其不需要的很多样式。可以考虑使用`rem`作为单位，调节根节点的尺寸即可。但如果PC要兼容到IE8，需要引入JavaScript支持该尺寸，会带来很大的性能损失。


````css
html,
body {
  width: 100%;
  font-family: "Helvetica Neue", Helveticam STHeiTi, sans-serif;
}
html {
  font-size: 62.5%;
  /*10/16=62.5%*/
}
/*===Mobile First Method==*/
/*Custom, iPhone Retina*/
@media only screen and (min-width: 320px) {
  html {
    font-size: 62.5%%;
  }
}
/*Extra small Device, Phones*/
@media only screen and (min-width: 480px) {
  html {
    font-size: 70%;
  }
}
/*Small Device, Tablets*/
@media only screen and (min-width: 768px) {
  html {
    font-size: 80%;
  }
}
/* Medium Devices, Desktops */
@media only screen and (min-width: 992px) {
  html {
    font-size: 90%;
  }
}
/* Large Devices, Wide Screens */
@media only screen and (min-width: 1200px) {
  html {
    font-size: 100%;
  }
}
/*iPhone < 5*/
@media screen and (device-aspect-ratio: 2/3) {
  html {
    font-size: 62.5%;
  }
}
/*iPhone 5*/
@media screen and (device-aspect-ratio: 40/71) {
  html {
    font-size: 75%;
  }
}

````


### 响应式DOM
有时候HTML结构需要根据不同屏幕调整，以实现其上面的理想的前端效果。如果由前端实现，则是在原有的基础之上，修改DOM结构，这种实现不优雅，但有时候很便捷，后续的维护不便。



### 参考资料：
[一次响应性开发实践 — Kejun's Blog](http://hikejun.com/blog/2012/08/30/%E4%B8%80%E6%AC%A1%E5%93%8D%E5%BA%94%E6%80%A7%E5%BC%80%E5%8F%91%E5%AE%9E%E8%B7%B5/)
[聊聊响应性设计和开发 — Kejun's Blog](http://hikejun.com/blog/2011/06/24/%E8%81%8A%E8%81%8A%E5%93%8D%E5%BA%94%E6%80%A7%E8%AE%BE%E8%AE%A1%E5%92%8C%E5%BC%80%E5%8F%91/)
[意识流 — Kejun's Blog](http://hikejun.com/blog/2012/07/23/%e6%84%8f%e8%af%86%e6%b5%81/)
[js和css的顺序关系 — Kejun's Blog](http://hikejun.com/blog/2012/02/02/js%e5%92%8ccss%e7%9a%84%e9%a1%ba%e5%ba%8f%e5%85%b3%e7%b3%bb/)
[你们觉得响应式好呢，还是手机和PC端分开来写？ - 知乎](http://www.zhihu.com/question/25836425)
[这种所有图片一直占据100%宽度的响应式是如何做的？ - 知乎](http://www.zhihu.com/question/20978898)
[两个宜于『统一Web』的方案：响应式与自适应 - 简书](http://www.jianshu.com/p/SkfFzt#)
[响应式设计应该会是今后的趋势，对前端的要求也将越来越高，你觉得呢？ - 知乎](http://www.zhihu.com/question/20155191)
[阿里巴巴（中国站）用户体验设计部博客 » 响应式导航的设计模式](http://www.aliued.cn/2015/01/05/%E5%93%8D%E5%BA%94%E5%BC%8F%E5%AF%BC%E8%88%AA%E7%9A%84%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F.html#nav)
[怎么还有那么多妹子搞不清镜头和脸的关系](http://www.douban.com/group/topic/75945912/)
[响应式网页设计-腾讯ISUX – 社交用户体验设计 – Better Experience Through Design](http://isux.tencent.com/responsive-web-design.html)

hid say: