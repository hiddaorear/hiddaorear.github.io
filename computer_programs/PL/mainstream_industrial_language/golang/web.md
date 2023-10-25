# Golang Web 笔记

# gin

### `gin.H`

底层实现是：
```
type any = interface{}

// H is shortcut for map[string]any
type H map[string]any
```

### 接口测试

使用curl
- query 参数：`curl http://localhost:9999/users?name=Tom&role=student`
- post 参数：`curl http://localhost:9999/form  -X POST -d 'username=geektutu&password=1234' {"password":"1234","username":"geektutu"}`
- 字典参数：`curl -g "http://localhost:9999/post?ids[Jack]=001&ids[Tom]=002" -X POST -d 'names[a]=Sam&names[b]=David' {"ids":{"Jack":"001","Tom":"002"},"names":{"a":"Sam","b":"David"}}`


## 阅读资料

- [Go Gin 简明教程 ](https://geektutu.com/post/quick-go-gin.html)
- [7天用Go从零实现Web框架Gee教程](https://geektutu.com/post/gee.html)
