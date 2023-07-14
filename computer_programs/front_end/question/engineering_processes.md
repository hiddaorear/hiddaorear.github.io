# 从工程流程看前端知识结构

## 新建工程

## 模块划分和包管理

## 项目架构

### 设计

8. 虚拟列表、无限列表的原理
12. 讲项目，虚拟列表的实现方法
    
### JS
1. 实现求和sum，支持sum(1), sum(1,2,3,4), sum(1)(2)(3),  console.log(sum(1)(2,3)(4)) = 10

2. 箭头函数题目
3. this题目
4. 闭包，闭包题目
5. chain = new Chain, chain.eat().sleep(5).eat().sleep(6).work()

6.  原型链

7. 判断数组的方式
8. instanceof

9.  数组A，数字N，A中找到a,b使a+b=N

15. 字符串，得出最长的没有重复字符的子串长度
   
### TS

### vue

3. vue的生命周期及说明

1. vue实现数据绑定的原理
2. vue data属性类型的数据响应（{},[]）
3. vue key对性能的影响
4. virtual dom的作用
5. computed的缓存以及根据data属性响应的原理 (发布订阅模式)
10. vue 3的变化
17. computed是怎么随着data响应

## 打包发布

13. wepack plugin的作用

## 浏览器获取资源和渲染

### http

1. http1和http2的区别（多路复用，头部压缩的原理）
   
10. 浏览器缓存的原理

11. 什么是跨域，跨域的解决方式 （jsonp，服务端设置access-control-allow-origin：跨域资源共享，反向代理，postMessage）

3. dns查询的过程（迭代/递归）
4. cookie在一级域名和二级域名的读取问题
5. 服务端是怎么设置浏览器cookie
   
8. jsonp的原理和实现一个jsonp方法
   
### 安全

1. xss和csrf
16. 跨站脚本注入和跨站请求伪造


### html

9. html meta

#### dom

6. domContentLoaded和window.onload的区别

7. 回到顶部的动画js实现

### css

6. wap页面如何适配不同分辨率 （rem相关）

### 性能优化

7. 如何实现图片懒加载，除了通过getBoundingClientRect，百度图库如何懒加载

9. 优化页面的指标：如何定义首屏渲染时间，观察占用内存

14. 性能优化的方案