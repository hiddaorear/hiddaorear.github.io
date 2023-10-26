# OOP

## 用 Struct 代替 Class 实现封装

用类型隐藏实现细节，数据仅能通过导出的方法来访访问和操作，即所谓的封装。Go中的Struct类型，有类似的抽象能力。

```
type Point struct {
	x, y float64
}

func (p Point) Length() float64 {
	return math.Sqrt(p.x * p.x + p.y * p.y)
}

```

所谓的方法，并没有放在struct内部，而是通过 receiver 参数和 struct 联系在一起。

## 用组合代替继承

```
type Animal struct {
	Name string
	mean bool
}

type Cat struct {
	Basics Animal
	MeowStrength int
}

type Dog struct {
	Animal
	BarkStrength int
}

```

结构体Animal具有其他结构体的共同属性。结构体Cat和Dog的声明基于Animal。变量、结构体、成员和函数的第一个字母大小写决定了访问权限。大写则公共，外部可以使用；小写则私有，外部不可用。故除了mean，其他成员都是公共的。

组合可匿名，如Dog结构体，也可以具名，如Cat中的Basics。

结构体对应的方法：

```


```

## 用Structural Typing 代替多态

## 阅读资料

- [为什么我不喜欢Go语言式的接口（即Structural Typing）](http://blog.zhaojie.me/2013/04/why-i-dont-like-go-style-interface-or-structural-typing.html)


