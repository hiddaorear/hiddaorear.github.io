# bRPC 核心设计

## RPC 和 HTTP 的对比

![RPC 和 HTTP 关系](./rpc_http_outline.png)

### 同

本质上来看HTTP 和 RPC ，从技术角度来看是同源的：
- 都是网络请求；
- 需要设计应用层协议（请求头，响应头，请求体，meta 数据等），而二者主要差异，主要是应用层协议。HTTP 是一种应用层协议；
- 需要设计编码和解码，序列化，选择通信协议，如：TCP,UDP

### 异
#### 协议
- 可以根据业务，设计的协议和编码解码方式。HTTP 不属于个人公司，不可能对协议改进，加入自己服务治理平台；
- HTTP 为了可读性，请求头部用的文本，占用了空间。RPC 相对 HTTP 接口而言，开销更小；
- HTTP 是一应一答传输协议，不能要求并发N个请求，然后乱序回包。HTTP 2 虽然解决此问题，但实现复杂，高性能后台偏向 RPC；


#### 服务治理

良好的 RPC 调用是面向服务的封装，针对服务的可用性和效率，做了优化，如：服务发现，负载均衡，熔断降级等。单纯调用 HTTP 容器缺少这些特性。如果把 HTTP 封装一层，服务发现和函数代理调用，就升级为一个 RPC 框架了。

- 可以自己做服务治理，如：负载均衡，限流
- RPC 在设计请求的时候，有设计接口和方法名，两端在使用服务治理平台的时候，使用接口和方法，就知道对方的 IP 和端口。而 HTTP 的请求路径，相当于接口和方法名，没有在服务治理体系，没有命名服务

服务间采用 RPC 更方便，而对外暴露采用采用 HTTP 接口更容易。


## 阅读资料

- [brpc 官网](https://brpc.apache.org/zh/)
- [Understanding RPC Vs REST For HTTP APIs](https://www.smashingmagazine.com/2016/09/understanding-rest-and-rpc-for-http-apis/)
- [ 现代 C++ 教程：高速上手 C++ 11/14/17/20](https://changkun.de/modern-cpp/zh-cn/01-intro/)
