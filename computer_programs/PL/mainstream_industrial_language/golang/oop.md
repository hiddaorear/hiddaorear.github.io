# OOP

![outline](./oop_outline.png)

## 用 Struct 实现封装行为

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

## 用组合实现继承的行为

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
func (dog *Dog) MakeNoise() {
	barkStrength := dog.BarkStrength
	if dog.mean == true {
		barkStrength = barkStrength * 5
	}
	for bark := 0; bark < barkStength; bark++ {
		fmt.Printf("BARK")
	}
	
	fmt.Println("")
}

func (cat *Cat) MakeNoise() {
	meowStrength := cat.MeowStrength
	if cat.mean == true {
		barkStrength = meowStrength * 5
	}
	for meow := 0; meow < meowStength; meow++ {
		fmt.Printf("MEOW")
	}
	
	fmt.Println("")
}

```

## 用Structural Typing 接口实现多态行为

任何实现接口类型的类型，都可以看做该接口的类型。

```
type AnimalSounder interface {
	MakeNoise()
}

func MakeSomeNoise(animalSounder AnimalSounder) {
	animalSounder.MakeNoise()
}

myDog := &Dog{
	Animal{
		"Rover",
		true,
	}
	2
}

MakeSomeNoise(myDog)

myCat := &Cat{
	Basice: Animal{
		Name: "Julius",
		mean: true,
	}
	MeowStrength: 3,
}

MakeSomeNoise(myCat)
```

Structural Typing 意味着具有接口声明的结构的类型，都符合此类型，也就是通过接口实现多态行为。

## Go的 Structural Typing 或 Duck Typing的问题

所谓Go语言接口，就是不用显示声明类型T，实现了接口I，只要类型T的公共方法满足接口I的要求，就可以把类型T用到接口I的地方，学名叫 Structural Typing，可以看做静态的Duck Typing。

所谓接口，通俗的说，就是一个协议，规定了一组成员或者行为。实际上，接口很有隐含的要求，不只是行为或者方法，还隐含规定了方法的复杂度要求，例如返回元素个数的接口，可能隐含了O(1)时间返回的要求，这样调用就不用担心性能问题。更进一步，接口可能需要保证行为特征。

Go的Duck Typing有一个问题，接口是人设计出来的，而不是自然发生的。Duck Typing只从表面（成员名，参数数量和类型等等）去理解接口，并不关心接口的规则和含义，也就是无法检查。例如：

```
interface IPainter {
	void Draw() // 画画
}

interface ICowBoy {
	void Draw() // 掏枪
}

```

英语中Draw具有画画和掏枪两种含义，所以画家Painter和牛仔CowBoy都可以有Draw的行为。但二者含义不同。如果是一个画家，让他去决斗，就是去送死。

### 避免命名碰撞

CowBoy的Draw应该改名，避免使用Draw。

在Go中，判断是否实现接口，会用到包名、函数签名，其中函数签名包含：函数名，参数、返回值。一般来说，这种碰撞概率不大。

### 谁的责任？

接口是程序所指定的。区别是实现者显式指定，还是调用者显式指定。这样就可以区分责任：接口调用者的责任，还是实现者的责任。

但是对一个类来说，实现者永远比调用者，更清楚类的细节。对于静态语言，是现在声明该类实现了接口，很合理。
而对应动态语言来说，调用者将类作为某个接口使用，可能合理，也可能不合理，因为调用不清楚类的细节。这也正常，类本身就是隐藏细节的设计。仅仅从名字猜测接口的使用，主要是因为语言本身，无法提供类似 身份标签 这样的强制限制。显式标注的接口，可以让设计者，通过良好的设计来避免使用者误用。

当然，鸭子类型舍弃严谨类获取灵活，在易变的逻辑中，很有用。

### dependency和coupling

Go是静态语言，避免了传统静态语言的dependency和coupling，通过也在编译期做类型检查。

举例来说，有个library中有 class A，B，C，而library的用户意识到ABC有common usage pattern，在Go里面，用户可以直接定一个interface，用户项目中就可以用interface变成。libaray不需要去定义这个interface。

而在其他语言中，可能处理common usage pattern，就需要在library中定义interface，然后让ABC显式继承。

## Java接口设计的失误

接口不仅仅规范了协议和成员，还规范了行为特征，具体来说是算法复杂度等要求。Java类库的LinkedList的设计就有问题。

在Java类库中，ArrayList和LinkedList都实现了List接口，都有get方法，传入一个下标，就能返回对应位置的元素，但二者的复杂度不一样。前者耗时O(1)，而后者O(N)，大相径庭。

当需要实现一个方法，获取从第一个元素开始，每隔P个位置的元素，是否可以面向List接口编程呢？

如果我们依赖下标访问，外部传入LinkedList的时候，算法的时间复杂度从期望的O(N/P)，变成了O(N^2/P)。退一步讲，ArrayList中，即使选择遍历，也可以得到O(N)的效率。

Java类库的List接口就是个笑话，连Stack类都实现了List。

因此，接口不能保证行为特性，具体来说，是复杂度等特征，面向接口编程就无意义。

也就是ArrayList和LinkList虽然都可以get，从List继承，但由于二者一些算法复杂度不同，不应该这样设计。虽然可以理解为，ArrayList和LinkList是因为特性不同，对get接口实现不一样。看起来似乎是子类型之间的差异。


## 阅读资料

- [为什么我不喜欢Go语言式的接口（即Structural Typing）](http://blog.zhaojie.me/2013/04/why-i-dont-like-go-style-interface-or-structural-typing.html)


