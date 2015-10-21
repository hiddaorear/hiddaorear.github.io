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
   
  img.onrror = function() {
    error_cb && error_cb()
    img = img.onload = img.onload = null
    return;
  }

  img.onload = function() {
    img.onload = null
    cb && cb(img)
  }
  img.src = url
  
}

````

代码很精简，只增加了监听图片的`onload`事件，但对闭包和图片加载兼容性的处理很精彩。

- `img.onload`绑定了匿名函数，并内部引用了图片，形成闭包，循环引用，容易导致内存泄漏。所以触发`onload`事件之后，立即就释放了`img.onload`。
- 同时，如果是gif图片，有可能多次触发onload，这么处理正好避免了这个问题。
- 为什么`src`的赋值是在`onload`之后呢？因为在IE，Opera下，对缓存图片的初始状态，与Firefox，Safari，Chrome是不一样的。IE与Opear对于缓存的图片，不会触发`onload`事件，而Firefox，Safari，Chrome会触发。根本原因是：`img`的`src`复制与`onload`事件的绑定，顺序不对。IE和Opear下，先赋值`src`，再触发`onload`，由于是缓存图片，`src`已存在，故错过`onload`。所以，为了绑定`onload`事件，后赋值`src`。


以下是原来有问题的代码：

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
由于浏览器能获取图片头部数据，如果获取图片的尺寸便可知图片就绪。

````javascript

// 更新：
// 05.27: 1、保证回调执行顺序：error > ready > load；2、回调函数this指向img本身
// 04-02: 1、增加图片完全加载后的回调 2、提高性能

/**
 * 图片头数据加载就绪事件 - 更快获取图片尺寸
 * @version    2011.05.27
 * @author    TangBin
 * @see        http://www.planeart.cn/?p=1121
 * @param    {String}    图片路径
 * @param    {Function}    尺寸就绪
 * @param    {Function}    加载完毕 (可选)
 * @param    {Function}    加载错误 (可选)
 * @example imgReady('http://www.google.com.hk/intl/zh-CN/images/logo_cn.png', function () {
        alert('size ready: width=' + this.width + '; height=' + this.height);
    });
 */
var imgReady = (function () {
    var list = [], intervalId = null,

    // 用来执行队列
    tick = function () {
        var i = 0;
        for (; i < list.length; i++) {
            list[i].end ? list.splice(i--, 1) : list[i]();
        };
        !list.length && stop();
    },

    // 停止所有定时器队列
    stop = function () {
        clearInterval(intervalId);
        intervalId = null;
    };

    return function (url, ready, load, error) {
        var onready, width, height, newWidth, newHeight,
            img = new Image();
        
        img.src = url;

        // 如果图片被缓存，则直接返回缓存数据
        if (img.complete) {
            ready.call(img);
            load && load.call(img);
            return;
        };
        
        width = img.width;
        height = img.height;
        
        // 加载错误后的事件
        img.onerror = function () {
            error && error.call(img);
            onready.end = true;
            img = img.onload = img.onerror = null;
        };
        
        // 图片尺寸就绪
        onready = function () {
            newWidth = img.width;
            newHeight = img.height;
            if (newWidth !== width || newHeight !== height ||
                // 如果图片已经在其他地方加载可使用面积检测
                newWidth * newHeight > 1024
            ) {
                ready.call(img);
                onready.end = true;
            };
        };
        onready();
        
        // 完全加载完毕的事件
        img.onload = function () {
            // onload在定时器时间差范围内可能比onready快
            // 这里进行检查并保证onready优先执行
            !onready.end && onready();
        
            load && load.call(img);
            
            // IE gif动画会循环执行onload，置空onload即可
            img = img.onload = img.onerror = null;
        };

        // 加入队列中定期执行
        if (!onready.end) {
            list.push(onready);
            // 无论何时只允许出现一个定时器，减少浏览器性能损耗
            if (intervalId === null) intervalId = setInterval(tick, 40);
        };
    };
})();

````

改进版：

````javascript

function ImageReady(error, url, ready, load) {

  var img = new Image()
    , onready = {end: false, setSrc: null, getSize: null}
    , width
    , height
    , new_width
    , new_height
    ;

  if (!url) return;

  if (img.complete) {
    ready && ready(img)
    load && load(img)
    return img;
  }
  
  img.onerror = function() {
    error && error(img)
    onready.end = true
    img = img.onload = img.onerror = null
    return false;
  }

  onready.setSrc = function() {
    img.src = url || ''
    width  = img.width
    height = img.height
    return true;
  }()
  
  onready.getSize = function() {
    if (!onread.setSrc) return false;

    new_width  = img.width
    new_height = img.height
    if (new_width != width || new_height != height || new_width*new_height > 0) {
      ready && ready(img)
      onready.end = true
    }
  }
  onready.getSize()


  img.onload = function() {
    !onready.end && onready.getSize()
    ready && ready(img)
    img = img.onload = img.onerror = null
  }
}

````

去掉多余的逻辑，只做好一件事情，就是做好单张的图片加载，多张的逻辑交由其他逻辑处理。

### debounce

如果一个函数频繁的触发，消耗浏览器的性能，并有可能导致浏览器崩溃。解决这种难过情形的方案有两种：

- debounce 防抖，一个callback执行完了，过了一定时间才再次执行callback；
- throttle 每隔一段时间执行callback；

举例：

````javascript

var $win = $(window);

function setSize() {
  var win_width = $win.width()
  var win_height = $win.height()
  
  $('#wrapper').css({
    width: win_width
    ,height: win_height
  }) 
}

$win.on('resize', function(event) {
  setTimeout(setSzie, 1000)
})


````
通过使用`setTimout`，来避免过于频繁触发回调。但是这里的实现有一个问题，`setTimeout`计数器并没有清除，而且每遇到这种情形，都要重复写相同的逻辑。我们试着把这个逻辑抽象出来。

````javascript

// for timestamp
var now = Date.now || function() {
  return new Data.getTime()
}

function debounce(fn, wait, immediate) {
  var timeout = null
    , args = arguments
    , result = null
    , later = null
    , timestamp = 0
    , context = this
    ;
    
  later = function() {
    var last = now() - timestamp

    if (!immediate) {
      result = fn.call(context, args)
      timeout = timestamp =args = context = null
    }
    return result
  }
  
  
  return function() {

    timestamp && (timestamp = now())
    var lock = false
      , start = null
      ;
    
    lock = immediate && !timeout
    if (lock) {
      result = fn.call(this, args)
      args = lock = context = null
    }
    
    !timeout && (timeout = setTimeout(later, wait))
    return result
  }
}

````

这是看了underscore的debounce函数之后，自己写的。相对原来的函数，有改进的地方。

````javascript

 // Returns a function, that, as long as it continues to be invoked, will not
  // be triggered. The function will be called after it stops being called for
  // N milliseconds. If `immediate` is passed, trigger the function on the
  // leading edge, instead of the trailing.
  _.debounce = function(func, wait, immediate) {
    var timeout, args, context, timestamp, result;

    var later = function() {
      var last = _.now() - timestamp;

      if (last < wait && last >= 0) {
        timeout = setTimeout(later, wait - last);
      } else {
        timeout = null;
        if (!immediate) {
          result = func.apply(context, args);
          if (!timeout) context = args = null;
        }
      }
    };

    return function() {
      context = this;
      args = arguments;
      timestamp = _.now();
      // 每次执行回调函数都会更新这个时间戳的值，导致有可能wait的时间到了
      //  var last = _.now() - timestamp;这个表达式的值小于wait的值
      var callNow = immediate && !timeout;
      if (!timeout) timeout = setTimeout(later, wait);
      if (callNow) {
        result = func.apply(context, args);
        context = args = null;
      }

      return result;
    };
  };


````
不得不说这个函数写得很巧妙。`later`函数用递归调用来实现时间差没有达到预定的时间的情况。
然而，对于`setTimeout`函数的特性来说，这种时间差小于`wait`的情况是不可能的，所以原函数实现上有缺陷，`timestamp = _.now();`这个语句应该检查`timestamp`的是否有值，并且在执行回调之后设置为`null`，以预备下一个回调。

改正之后的版本：

````javascript
_.debounce = function(func, wait, immediate) {
    var timeout, args, context, timestamp, result;

    var later = function() {
      var last = _.now() - timestamp;

        timeout = null;
        if (!immediate) {
          result = func.apply(context, args);
          if (!timeout) context = args = null;
        }
      
    };

    return function() {
      context = this;
      args = arguments;
      !timestamp && (timestamp = _.now());
      var callNow = immediate && !timeout;
      if (!timeout) timeout = setTimeout(later, wait);
      if (callNow) {
        result = func.apply(context, args);
        context = args = null;
      }
      return result;
    };
  };

````

没想到看这么一个广泛使用的函数库的代码，居然发现一个实现上的缺陷。以前也照这个函数实现了debounce函数，由于没有用自己想法去实现，没有发现这个问题，这次自己直接动手写，对比之下，发现问题。

也算不上问题，只不过原本的实现会导致有些情况回调不会按期执行，会有延迟。不过，发现这个问题，依然值得高兴。

后来读Underscore相关文章发现，其实`debounce`的实现，本应如此。是我理解有误。`debounce`的策略本就是，如果新的回调触发了，重新计时，重新过了`wait`才执行回调。以上修改也留着，不失为一种理解的思路。

重新实现一下自己写的`debounct`。

````javascript

function debounce(fn, wait, immediate) {
  var timeout = null
    , args = arguments
    , result = null
    , later = null
    , timestamp = null
    , context = this
    ;
    
  later = function() {
    var last = now() - timestamp

    if (last > 0 && last < wait) {
    	timeout = setTimeout(later, wait - last)
    } else {
    	if(!immediate) {
    	  result = fn.call(context, args)
    	  clearTimeout(timeout)
    	  timeout = timestamp =args = context = null
    	}
    }
    
    return result
  }
  
  
  return function() {
    timestamp = now()
    var lock = false
      , start = null
      ;
    
    lock = immediate && !timeout
    if (lock) {
      result = fn.call(this, args)
      args = lock = context = null
    }
    
    !timeout && (timeout = setTimeout(later, wait))
    return result
  }
}

````

这个实现与Underscore一样，用自己的习惯重新实现一遍而已。这么已折腾，发现Underscore这函数的实现，真精练，实在也找不出大的优化的地方，只想到用`clearTimeout`来释放一下`setTimeout`，原实现只把其`id` `timeout`变为空，失去原本`id`的意义。以前的误解，回想一下，其实恰好是`throttle`的实现，因为不让重新设置时间戳，导致回调函数会在wait时间之后执行。

这函数的实现，对闭包的功能使用，很典型，对内存的管理也很典型。JavaScript一般不用去操心内存管理，但在这样的情况，对内存的管理影响到功能的实现，是要谨慎考虑的。包括前面的图片加载的实现，对内存的处理都是很谨慎，也很有必要。


### 参考资料:

[jquery.appear](https://github.com/morr/jquery.appear)
[jquery-waypoints](https://github.com/imakewebthings/jquery-waypoints)
[waypoints](https://github.com/imakewebthings/waypoints)
[parallax](https://github.com/wagerfield/parallax)
[layzr](https://github.com/callmecavs/layzr.js)

### Image
[javascript预加载和延迟加载](http://www.cnblogs.com/youxin/p/3369666.html)
[Javascript图片预加载详解](http://www.cnblogs.com/v10258/p/3376455.html)

[Fex Notes](http://fexnotes.com/)
[xss零碎指南](http://segmentfault.com/a/1190000000497596)

### Time function
[浅谈 Underscore.js 中 _.throttle 和 _.debounce 的差异](https://blog.coding.net/blog/the-difference-between-throttle-and-debounce-in-underscorejs)
[谈谈Javascript中的throttle and debounce](http://www.zuojj.com/archives/1036.html)

### SVG
[Mozilla SVG教程](https://developer.mozilla.org/zh-TW/docs/Web/SVG/Tutorial)
[SVG应用指南](https://svgontheweb.com/zh/)
[Web 设计新趋势: 使用 SVG 代替 Web Icon Font](http://io-meter.com/2014/07/20/replace-icon-fonts-with-svg/)
[W3School SVG 教程](http://www.w3school.com.cn/svg/)

### requestAnimationFrame
[Javascript高性能动画与页面渲染](http://www.infoq.com/cn/articles/javascript-high-performance-animation-and-page-rendering)
[CSS3动画那么强，requestAnimationFrame还有毛线用？](http://www.zhangxinxu.com/wordpress/2013/09/css3-animation-requestanimationframe-tween-%E5%8A%A8%E7%94%BB%E7%AE%97%E6%B3%95/)
[使用requestAnimationFrame更好的实现javascript动画(转)](http://www.cnblogs.com/rubylouvre/archive/2011/08/22/2148793.html)
[Leaner, Meaner, Faster Animations with requestAnimationFrame](http://www.html5rocks.com/en/tutorials/speed/animations/)
[Learning from Twitter](http://ejohn.org/blog/learning-from-twitter/)

### DOM API
[CSSOM视图模式(CSSOM View Module)相关整理](http://www.zhangxinxu.com/wordpress/2011/09/cssom%E8%A7%86%E5%9B%BE%E6%A8%A1%E5%BC%8Fcssom-view-module%E7%9B%B8%E5%85%B3%E6%95%B4%E7%90%86%E4%B8%8E%E4%BB%8B%E7%BB%8D/)
[Element.getBoundingClientRect()](https://developer.mozilla.org/zh-CN/docs/Web/API/Element/getBoundingClientRect)
[浏览器 窗口 scrollTop 的兼容性问题](http://www.cnblogs.com/----1/archive/2011/12/16/2290193.html)

### CSS
[纯CSS实现易拉罐3D滚动效果](http://www.zhangxinxu.com/wordpress/2010/03/%E7%BA%AFcss%E5%AE%9E%E7%8E%B0%E6%98%93%E6%8B%89%E7%BD%903d%E6%BB%9A%E5%8A%A8%E6%95%88%E6%9E%9C/)

hid say: 玩一玩新技术。




