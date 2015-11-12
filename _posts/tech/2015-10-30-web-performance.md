---
layout: post
title:  Web Performance
category: 技术
tags: [web]
keywords: web
description:
---

##### Friday, 30 October 2015

### Web Performance

![分形](/../../assets/img/tech/2015/riviera.jpg)


## timing

### Navigation timing API
用于缝隙页面整体性能指标，检测用户数据（RUM），例如带宽、延迟或主页的整体页面加载时间。个别资源，可以用Resource timing API

````javascript

var page = performance.timing
, plt = page.loadEventStart - page.navigationStart
;
console.log(plt)

````

###  High Resolution timing API

`var perf = performance.now()`
精确到微秒级别的当前时间，不受系统时间偏差或调整的影响。精确测量，性能分析的根本。

### Resource timing API

The Resource timing API allows you to collect complete timing information related to resources in a document.

The Resource timing API is exposed through the `performance` property of the `window` object. We can retrieve the information collected for each resource using the `getEntriesByType()` method. If this sounds familiar to you, this is because it's the same method used by the User Timing API. The difference is that to retrieve information about these resources we have to pass the sting `resource` to `getEntriesByType()`.

````javascript

if ( !('performance' in window) || !('getEntrieByType' in window.performace) || !(window.performance.getEntriesByType('resource') instanceof Array)) {
  // API not supported
}
else {
  window.addEventListener('load', function() {
    var resources = window.performance.getEntriedByType('resource')
    
    for (var obj in resources) {
      var list = ''
      for (var properties in resources[obj]) {
        console.info(resources[obj][properties])
      }
    }
  })
}


````

### 参考资料:

[7 天打造前端性能监控系统](http://fex.baidu.com/blog/2014/05/build-performance-monitor-in-7-days/)
[Web性能API——帮你分析Web前端性能](http://www.infoq.com/cn/news/2015/06/web-performance-api)
[前端性能优化指南](http://segmentfault.com/a/1190000003646305#articleHeader30)
[前端工程与性能优化](http://div.io/topic/371)
[How to lose weight in the browser](http://browserdiet.com/en/)
[浅谈移动前端性能优化](http://frontenddev.org/link/introduction-to-mobile-front-end-performance-optimization.html)
[前端性能优化](http://devconf.qiniudn.com/%E5%89%8D%E7%AB%AF%E6%80%A7%E8%83%BD%E4%BC%98%E5%8C%96.pdf)
[图片优化与合并](https://li-xinyang.gitbooks.io/frontend-notebook/content/chapter1/01_05_image_optimisation.html)
[web前端性能优化进阶路](http://www.aliued.cn/2013/01/20/web%E5%89%8D%E7%AB%AF%E6%80%A7%E8%83%BD%E4%BC%98%E5%8C%96%E8%BF%9B%E9%98%B6%E8%B7%AF.html)

[5173首页前端性能优化实践](http://stylechen.com/5173homepage-optimized.html)
[图片延迟加载的实现](http://stylechen.com/imglazyload2.html)
[ 淘宝前端：移动端端图片的优化流程 ](http://frontenddev.org/link/taobao-front-end-mobile-end-to-end-the-optimization-process-of-pictures.html#heading-1-0)
[js和jquery懒加载之可视区域加载](http://www.haorooms.com/post/js_jquery_lazyload_viewload)

[Introduction to the Resource Timing API](http://www.sitepoint.com/introduction-resource-timing-api/)
[Resource Timing](http://www.w3.org/TR/resource-timing/#resource-timing)
[Resource Timing api简介](http://www.html-js.com/article/Brief-introduction-of-JavaScript-Resource-Timing-API-to-learn-something-every-day)

hid say: 性能是一中度量，没有度量就没有性能，而度量是一种精细，凡事精细，则有味。




