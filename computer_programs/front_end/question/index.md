
一面：（主要考查基础知识和编程基础）
1. http1和http2的区别（多路复用，头部压缩的原理）
2. 实现求和sum，支持sum(1), sum(1,2,3,4), sum(1)(2)(3),  console.log(sum(1)(2,3)(4)) = 10
3. vue的生命周期及说明
4. 箭头函数题目
5. this题目
6. 闭包，闭包题目
7. chain = new Chain, chain.eat().sleep(5).eat().sleep(6).work()
8. xss和csrf
9. html meta
10. 浏览器缓存的原理
11. 什么是跨域，跨域的解决方式 （jsonp，服务端设置access-control-allow-origin：跨域资源共享，反向代理，postMessage）
12. 原型链

二面：（主要考查框架原理和业务场景提升性能的方法）
1. vue实现数据绑定的原理
2. vue data属性类型的数据响应（{},[]）
3. vue key对性能的影响
4. virtual dom的作用
5. computed的缓存以及根据data属性响应的原理 (发布订阅模式)
6. wap页面如何适配不同分辨率 （rem相关）
7. 如何实现图片懒加载，除了通过getBoundingClientRect，百度图库如何懒加载
8. 虚拟列表、无限列表的原理
9. 优化页面的指标：如何定义首屏渲染时间，观察占用内存
10. vue 3的变化
    

三面：
1. 判断数组的方式
2. instanceof
3. dns查询的过程（迭代/递归）
4. cookie在一级域名和二级域名的读取问题
5. 服务端是怎么设置浏览器cookie
6. domContentLoaded和window.onload的区别
7. 回到顶部的动画js实现
8. jsonp的原理和实现一个jsonp方法
9. 缓存问题
10. 小数精度问题
11. 数组A，数字N，A中找到a,b使a+b=N
12. 讲项目，虚拟列表的实现方法
13. wepack plugin的作用
14. 性能优化的方案
15. 字符串，得出最长的没有重复字符的子串长度
16. 跨站脚本注入和跨站请求伪造
17. computed是怎么随着data响应
18. 个人规划和发展方向

四面：
1.项目介绍
2.技术难点
3.有没有遇到过一些事故，怎么应急处理，后续怎么规避的
4.之前的团队的人员组成和分工是什么样的？
5. 团队管理，怎么带队的，项目的管理


算法题： 
- merge k sorted list，时间复杂度如何？ 
- HashMap 如果一直 put 元素会怎么样？hashcode 全都相同如何？equals 方法都相同如何？
- ApplicationContext 的初始化过程？初始化过程中发现循环依赖 Spring 是如何处理的？ 
- GC 用什么收集器？收集的过程如何？哪些部分可以作为 GC Root? 
- Volatile 关键字，指令重排序有什么意义？
- synchronied 怎么用？ 
- 并发包里的原子类有哪些，怎么实现？
- cas 在 CPU 级别用什么指令实现的？ 
- Redis 数据结构有哪些？
- 如何实现 sorted set？这种数据结构在极端情况下可能有什么问题？
- 二叉平衡树？ 
- 系统设计题：一个推送场景，50 条内容，定时推送，先推 5%用户，一段时间后再找出效果最好的几条，推给所有用户。设计相关库表，系统模块, 需要可以落地，有伪代码 
- MySql 索引是什么数据结构？B tree 有什么特点？优点是什么？ 慢查询怎么优化？ 


