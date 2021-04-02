# Objective-C

# 面试题

- [iOS面试了20几家总结出来的面试题（一）](https://juejin.cn/post/6854573212165111822)

- [iOS Interviews DevNotes](https://github.com/DevDragonLi/iOSInterviewsAndDevNotes)

- [日常积累所看到的面试题集锦](https://github.com/iOShuyang/Book-Recommended-Interview)

- [阿里、字节 一套高效的iOS面试题解答（完结）](https://www.jianshu.com/p/c1765a6305ab)

- [2020年iOS面试题总结(一)](https://www.xuebaonline.com/2020%E5%B9%B4iOS%E9%9D%A2%E8%AF%95%E9%A2%98%E6%80%BB%E7%BB%93(%E4%B8%80)/)

# 技术博客

- [上善若水，人淡如菊](https://onevcat.com/)

- [一缕殇流化隐半边冰霜](https://halfrost.com/)

- [唐巧的博客](https://blog.devtang.com/)

- [ObjC中国](https://objccn.io/issues/)


# 基础

## nil

OC独特的消息传递机制，允许对nil发消息。在其他语言中，需要多一层if判nil的情况，在OC可以省略，代码可以更简洁。

举例：

``` objc
if (self.handers) {
	for(id<EventHandler> handler in self.handlers){
		if (handler && [handler respondsToSelector:@selector(onVideoStart:)]) {
			[handler onVideoStart:adItem];
		}
	}
}
```

有冗余的if判断，可以简化为：

``` objc
for(id<EventHandler> handler in self.handlers){
	if ([handler respondsToSelector:@selector(onVideoStart:)]) {
		[handler onVideoStart:adItem];
	}
}
```

以上例子虽然很简单，但在实际项目中非常常见。去掉多余的if语句以后，代码看起来会更清爽。

## 常量

新规范要求以g开头，而非以k开头。k开头为《Effective Objective-C 2.0》第4条中常量命名的推荐写法。

### static

- **修改作用域**：被static修饰的全局变量，只能在当前文件下可见。对多数const的处理，多数利用此特点。因不加static，编译器会为变量创建“外部符号”(external symbol)，若另一个编译单元中声明了同名变量，则编译会报错。因此，static const定义的常量不应定义在头文件中。
- **延长生命周期**：static修饰的变量，存储在全局数据区，而不是栈区，生命周期与应用程序等同，直到程序结束。static修饰的局部变量，只会分配一次内存。

点评：一般会认为static是用来延长生命周期的，而不是修改作用域。以至于定义常量的时候，看到static修饰的常量会疑惑。这个特性大概跟JS低版本一样，用函数的作用域来强行处理私有变量。从PL角度看，这个OC的这个设计，不是一个好的设计，一个语法有两种意义。

### const

const在常量定义的位置很重要，语义应该从右到左解读。`NSString * const gQADConversionInfoDefaultTextColor = @"#ffffff"`，语义为：gQADConversionInfoDefaultTextColor是一个常量，而这个常量是指针，指向NSString对象。

应用举例：

``` objc

static const CGFloat gQADConversionInfoTextRightPadding = 12.f;
static NSString * const gQADConversionInfoDefaultTextColor = @"#ffffff";

```
#### 修饰基本变量

即修饰int,double,float等类型

``` objc

const int a = 1; // a不可变
int const b = 2; // b不可变
a = 3; // error

```
const放在类型左边或者右边，是一个习惯问题。从主工程代码来看，`const int`与`int const`的比例为：986/18，即大家习惯用前者。

#### 修饰指针变量

C++中const修饰指针变量，有3种情况：

以指针为界：

1. const在`*`左边，则指针指向的内容不可变，简称*左定值*，举例：`const int *p = 8;`
2. const在`*`右边，则指针指向的内存地址不可变，简称*右定向*，举例：`int a = 8; int* const p = &a;`
3. 合并1和2，出现两个const，即地址和内容都不可变，举例：`int a = 8; const int * const p = &a;`

公司的C++规范：

>const 的位置：

>有人喜欢` int const *foo `形式，不喜欢` const int* foo`，他们认为前者可读性更好因为更一致：遵循了` const `总位于其描述的对象之后的一致性原则。但是大多数` const `表达式只有一个` const`，因此这个一致性原则不适用于几乎没有深度嵌套的指针表达式的代码库。将` const `放在首位更具可读性，因为在自然语言中形容词（`const`）是在名词（`int`）之前.

>这是说, 我们提倡但不强制` const `在前。但要保持代码的一致性

C++规范中提倡的写法，如果放到OC里面，在相同的语义下（即不是const位置不同，表达的意思不同的场景），应该是放前面。但《Effective Objective-C 2.0》推荐写法，以及一般的`NSString`的定义来看，多数是`NSString * const str=@“xxx”`。所以const位置，莫衷一是，还是以项目习惯写法为准。

我们你探讨一下，OC的数据对象都有`mutable`和`immutable`两种。故，想定义不可变对象，用`immutable`即可，用const修饰，意义不大。

举例如下：

``` objc
// const修饰可变字符串 1
const NSMutableString *str1 = [NSMutableString stringWithFormat:@"a"];
[str1 appendString:@"b"]; // 值可变
// const修饰可变字符串 2
NSMutableString * const str2 = [NSMutableString stringWithFormat:@"c"];
[str2 appendString:@"e"]; // 值可变

str2 = [NSMutableString stringWithFormat:@"f"] // 不合法，st2指向的对象不可变

```

综上，我们常用写法`NSString * const value1 = @"test"`，定义的是“指针常量”，即不能改变指针的指向，但允许指针所指向的值被修改。限制值的修改，需要用其他手段。如字符串用`NSString`。

点评：PL理论中，特别是函数式编程中，不可变变量是非常重要的内容。变量可变，就导致有状态，有状态就导致多线程问题，为了解决多线程问题，就回引入各种锁，就有死锁问题。当然，变量不可变也有他自己的问题，性能以及理解的成本，monad能理解清楚的人，怕是比例不多吧。实际上，变量还有其他语义，如变量的持有等等，这些可以在Rust语义，看到严格的处理。const这种写法，看来是一种习惯约定。

### 命名规则

TODO

## 基础类

### BOOL

#### BOOL的陷阱

1. `BOOL`定义为`signed char`(此说法不准确)，因此值具有除了`YES`和`NO`（1和0）之外的值。所以不要将BOOL与`YES`或`NO`比较
2. 由于原因1，所以将常规整型转换为`BOOL`，在没有使用`&&`,`||`,`!`，if的括号，以上情况下，请使用三元运算符返回`YES`或`NO`。直接赋值`BOOL hasButton = self.button;`，`BOOL hasButton = (BOOL)self.button`，这些可能在32-bit和64-bit下出现不同的结果，不安全

补充一下历史原因：

BOOL在32-bit和64-bit环境下，具有不同的定义。在iPhone 4s(32-bit)，BOOL的本质是signed char。在内存占一个字节。当把超过2位的值赋值给BOOL的时候，高位会被截断。而在64-bit环境下，BOOL的本质是`_Bool`，即C语言定义的boolean的真布尔类型，只有0和1。只有0是0，非0都会变为1.

### NSString

### NSNumber

- int32_t类型，如果是后台下发，且有初始值。如果需要设置默认值，则需要考虑值是否存在为0的情况。此时，客户端应该无法处理。因为后台下发的值，可能恰好就是0，此时我们不能认为无值，而去用默认值。只有后台自身能处理。

### 枚举

#### 枚举与枚举之间的映射

通常使用switch处理两个枚举之间的映射。如果是特殊情况，原来的枚举值修改以后有风险，需要拓展原来的枚举值，也就是旧枚举是新枚举的子集。可以考虑使用类型强转，就不用写冗长的switch语句。


``` C
typedef EnumA{
    a_dog = 0,
    a_cat = 1
} EnumA;

typedef EnumB{
	b_dog = 0,
	b_cat = 1
} EnumB;

EnumA a = a_dog;
EnumB b;

b = (EnumB)a;
// or
b = (int)a;
```

强转的办法非常简洁，但前提条件是枚举值不被修改。一旦枚举值被修改了，一一对应被破坏，后面的处理就有问题。例如，旧枚举新增一个枚举值表示失败，值为5，恰好对应新枚举中一个值，但这个值是原有，表示的不是失败。这就错位了。而switch是手动用代码控制的对应关系，不会有这个问题。

考虑代码修改的情况，一般有两种处理方式：assert和单测。单测相对assert有一个好处，单测在集成流水里面，每次集成都会跑。而assert可能走不到。

用单测来保证两个枚举的一一对应关系，考虑枚举可能修改新增，就涉及一个问题。我们只有遍历枚举值了，才能检查这种修改，否则我们维护一个静态的对应关系就好了，用字典之类都可以。而遍历枚举，就需要两个条件，循环的起始条件和终止条件。一般而言，如果原枚举有枚举值可以使用，就可以直接用，如果没有需要手动修改枚举值，加入开始和结束枚举值，我们就可以写循环遍历了。

这里有一个非常麻烦问题，新枚举值的时候，对应int值可能比我们选的结束的枚举值还要大，我们写遍历的是不可能遍历到的。这就失去是检查的意义。所以一旦有这种两个枚举的对应关系，考虑到修改时遗漏的程序化检测，对枚举值而言，不好处理。这是受限制于枚举这种类型。我认为这里最后的方式，就是避免出现问题。但实际开发中有时候难以避免，比如两个一个枚举值来源与外部sdk的定义，我们在其他地方用的枚举，与外部的不同，就需要转化。

综上，修改枚举值的时候，最好全局搜索一下，梳理一下逻辑，然后再做修改，特别要注意这种有关联关系的枚举。

点评：维护枚举对应关系的问题，从PL角度看，还是语言类型系统不够强。比如，如果用模式匹配处理枚举，那么新增的枚举没有在模式匹配中，无法通过编译。我们想办法处理的修改枚举的问题，在类型系统中就自然保证了。而OC的中这种枚举拓展，复制原有的枚举，然后加新的枚举值，这个方式也是问题的根源。如果支持了sum类型，就可以轻易的实现类型拓展了，这样旧枚举值一定是原来的值，也不存在维护枚举对应关系问题。不得不感叹，语言虽然是工具，其实影响超越了工具。

C++中实现举例：

``` objc

enum Foo {
  One,
  Two,
  Three,
  Last
};

for ( int fooInt = One; fooInt != Last; fooInt++ )
{
   Foo foo = static_cast<Foo>(fooInt);
   // ...
}

```

#### 枚举值与字符串之间的映射

通常使用switch处理。但有其他更优雅一点的方案，避免一旦枚举较多，会导致swtich的圈复杂度较高的情况。使用数组和字典，都需要注意一个问题，当枚举更新的时候，需要更新数组和字典。

1. 使用数组

``` objc


// 例子1

typedef enum {
  JSON,
  XML,
  Atom,
  RSS
} FormatType;

+ (NSArray *)names {
    static NSMutableArray * _names = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _names = [NSMutableArray arrayWithCapacity:4];
        [_names insertObject:@"JSON" atIndex:JSON];
        [_names insertObject:@"XML" atIndex:XML];
        [_names insertObject:@"Atom" atIndex:Atom];
        [_names insertObject:@"RSS" atIndex:RSS];
    });

    return _names;
}

+ (NSString *)nameForType:(FormatType)type {
    return [[self names] objectAtIndex:type];
}


// 例子2

// In a header file
typedef enum FormatType {
    JSON,
    XML,
    Atom,
    RSS
} FormatType;

extern NSString * const FormatType_toString[];

// In a source file
// initialize arrays with explicit indices to make sure 
// the string match the enums properly
NSString * const FormatType_toString[] = {
    [JSON] = @"JSON",
    [XML] = @"XML",
    [Atom] = @"Atom",
    [RSS] = @"RSS"
};
...
// To convert enum to string:
NSString *str = FormatType_toString[theEnumValue];

```

2. 使用字典

``` objc

typedef NS_ENUM(NSUInteger, UserType) {
    UserTypeParent = 0,
    UserTypeStudent = 1,
    UserTypeTutor = 2,
    UserTypeUnknown = NSUIntegerMax
};  

@property (nonatomic) UserType type;

+ (NSDictionary *)typeDisplayNames {
    return @{@(UserTypeParent) : @"Parent",
             @(UserTypeStudent) : @"Student",
             @(UserTypeTutor) : @"Tutor",
             @(UserTypeUnknown) : @"Unknown"};
}

- (NSString *)typeDisplayName {
    return [[self class] typeDisplayNames][@(self.type)];
}

NSLog(@"%@", [self typeDisplayName]);

```
## 基本容器

### 命名

容器类的命名，以苹果UIKit为例，使用复数即可。切忌带上多余的类型，如：`handerArray`，直接`handers`即可。

``` objc

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) @interface UITabBar : UIView

@property(nullable, nonatomic, weak) id<UITabBarDelegate> delegate;     // weak reference. default is nil
@property(nullable, nonatomic, copy) NSArray<UITabBarItem *> *items;        // get/set visible UITabBarItems. default is nil. changes not animated. shown in order
@property(nullable, nonatomic, weak) UITabBarItem *selectedItem; // will show feedback based on mode. default is nil

- (void)setItems:(nullable NSArray<UITabBarItem *> *)items animated:(BOOL)animated;   // will fade in or out or reorder and adjust spacing

// Reorder items. This will display a sheet with all the items listed, allow the user to change/reorder items and shows a 'Done' button at the top

- (void)beginCustomizingItems:(NSArray<UITabBarItem *> *)items API_UNAVAILABLE(tvos);   // list all items that can be reordered. always animates a sheet up. visible items not listed are fixed in place
- (BOOL)endCustomizingAnimated:(BOOL)animated API_UNAVAILABLE(tvos);    // hide customization sheet. normally you should let the user do it. check list of items to see new layout. returns YES if layout changed

@property(nonatomic, readonly, getter=isCustomizing) BOOL customizing API_UNAVAILABLE(tvos);

```

如UIkit中的`items`。

### 集合的遍历

从集合中遍历找到对应的元素，然后删除。需要注意以下2点：

1. 以数组为例，如果直接正序遍历，并移除元素，所移除的元素以后的元素会前移，即index减1，会导致下标不一致，导致结果与预期不一样。所以如果用for，则需要逆序遍历
2. `for in`遍历时删除元素，会抛异常。且`for in`无法获取index

为了规避删除元素，index错乱问题。有几种方案：

1. 逆序删除，以`enumerateObjectsWithOptions:usingBlock`为例，也可以使用for循环实现

``` objc

NSMutableArray *array = @[@"1", @"2", [NSNull null]].mutableCopy;
__weak typeof(array) weakArray = array;  // retain cycle
[array enumerateObjectsWithOptions:NSEnumerationReverse usingBlock:^(id _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
	if ([obj isKindOfClass:[NSString class]]) {
		[weakArray removeObject:obj];
	}
}]

```

还可以通过NSEnumerationConcurrent枚举值开启并发迭代功能。

2. 使用额外的变量缓存（缓存全部数组，或者缓存要删除的元素）

``` objc

NSMutableArray *array = @[@"1", @"2", [NSNull null]].mutableCopy;

NSMutableArray *removedArray = [NSMutableArray array];

for (id element in array) {
	if ([element isKindOfClass:[NSString class]]) {
		[removedArray addObject:element];
	}
}

[array removeObjectsInArray:removeArray];

```

**其他遍历方式**

1. 使用GCD中的dispatch_apply函数

优点：开启多线程并发处理
缺点：对字典和集合需要借助数组，无法反向遍历

``` objc

NSArray *array = @[@"1", @"2", @"3"];
dispatch_queue_t queue = dispatch_get_global_queue(0, 0);

dispatch_apply(array.count, queue, ^(size_t index) {
	NSLog(@"%@--%@", array[index], [NSThread currentThread]);
});

```

### 字面量的优点和局限

优点：

1. 字面量语法，从语法层面看，更为安全，因为遇到nil，在NSArray和NSDicionary中，都会抛异常，导致crash。

2. 但在实际项目中，一旦忘记判nil，会到crash。属于严重的线上问题。因此，考虑使用字面量，需要谨慎处理，要处处判空。

局限：

1. 除字符串以外，创建的对象，必须属于Foundation框架。即使是其子类也不行。

2. 字面量创建的对象，都是不可变的。若想可变，需要复制。

`NSMutableArray *mutable = [@[@1, @2, @3] mutableCopy];`

3. 使用NSMutableDictionary代替NSDictionary，可以避免字面量遇到nil导致crash的缺点。当给一个NSMutableDictionary设置nil，和remove操作是一样

### 容器对象的初始化

``` objc
// 方法1
NSMutableDictionary *dic1 = [[NSMutableDictionary alloc] init];

// 方法2
NSMutableDictionary *dic2 = [NSMutableDictionary new];

// 方法3
NSMutableDictionary *dic3 = [NSMutableDictionary dictionary];

// 方法4
NSMutableDictionary *dic4 = [NSMutableDictionary dictionaryWithCapacity:10];

// 方法5

NSMutableDictionary *dic5 = @{}.mutableCopy;

```

- 方法1：常见的NSObject对象初始化的写法。
- 方法2：new相当于alloc和init的组合，与方法1等价
- 方法3：在ARC下与方法1等价。在MRC下，相当于`[[[NSMutableDictionary alloc] init] autorelease]`，即不用调用release去释放
- 方法4：创建一个可变字典，并分配内存以存储长度为10个内容对象。当长度超过10，会自动分配新内存。如果可以确定字典的大致存储个数，推荐此方法
- 方法5：通过字面量创建空的不可变Dictionary对象，然后调用NSObject的mutableCopy，赋值为新的可变对象

### 对象相关的补充知识

**alloc**

- alloc会返回一个未被初始化的对象实例。在OC中，消息机制决定了，每一个方法调用都会被转化为一条`objc_msgSend()`函数，从这个意义上讲，alloc提供了`objc_msgSend()`函数的发送目标。通常来说，alloc创建未被初始化对象的过程有：分配内存，写入isa指针，初始化引用计数，重置所有实例变量。
- 给nil发送消息，不会引起crash，会在`objc_msgSend()`直接返回0

*因此关于nil检查的代码规范：*

nil检查只用在逻辑流程中，避免在对象发送消息前，逐行进行nil检查。因为对nil发送任何消息都是可以的。

``` objc
[dataSource moveItemAtIndex:1 toIndex:0]; // Good.

// Avoid
if (dataSource) {
	[dataSource moveItemAtIndex:1 toIndex0];
}

```

**init**

init用于初始化对象，即此时对象处于可用状态，实例变量可以被赋值。当我们重写一个对象的init方法的时候，常用格式：

``` objc
- (instancetype)init {
	if (self = [super init]) {
      // todo
   }
   return self;
}
```

为什么要写`[super init]`？因为init方法可以通过返回`nil`来告诉开发者，初始化失败了。如果超类初始化失败，那当前类处于不稳定状态，初始化也可能失败。此时不应该继续初始化，而也要返回nil。避免接下来会操作一个不可用对象，导致crash。重写init，调用`self = [super init]`，保证创建过程的容错。

*关于类初始化方法的代码规范*

- 必须重写制定的初始化方法：写子类的时候，如果需要init方法，需要重载父类指定的构造函数。如果没有重载，子类的构造函数可能不会被调用，会导致非常隐秘的bug
- 必须明确指定初始化方法：基于上一条，此类如果需要被继承，需要明确指出初始化方法，子类只需要重写一个初始化方法。有助于调试和理解
- 提供“全能初始化方法”：当底层数据存储机制改变时，只需修改此方法的代码，无须修改其他初始化方法。子类也可以调用，维护全能初始化方法的调用链。【来自《Effective Objective-C 2.0》第16条】

评论与补充：

现代编程语言，创建对象很难看到需要两步，一般直接new即可。而在OC中需要两步，先alloc，后init。这样设计，有历史原因。

1. OC诞生较早，需要手动管理内存。alloc的主要功能是从虚拟地址空间为对象分配内存
2. 将新对象的Retain Count设置为1
3. 将isa成员变量指向类对象
4. 将新对象所有其他成员的值设置为nil或Nil或0

而init类方法会做真正的初始化工作，让成员变量初始化。

后面苹果引入类方法new来创建对象。但new不能指定init参数。原因无他，init是实例方法，而new是类方法。

所以历史上，alloc和init做了2件不同的事情，放在2个方法中，职责分明。

但有了ARC以后，这个设计就显得冗余了。

### NSDictionary

**减少函数参数个数**

1. 使用`NSDictionary`

把参数放在`NSDictionary`中。优点是简便，缺点是并不能保证类型安全。使用类，避免这个缺点。

``` objc

// key 定义
NSString * const KEY_A_PARAM = @"key_a_param";
NSString * const KEY_B_PARAM = @"key_b_param";
NSString * const KEY_C_PARAM = @"key_c_param";

// 函数实现
(NSDictionary *)collectionParam: (BOOL)aParam
                 bParam: (SomeEnumerateTYPE)bParam
                 cParam: (NSString*)cParam {
    return @{
            KEY_A_PARAM: @(aParam),
            KEY_B_PARAM: @(bParam),
            KEY_C_PARAM: @(cParam)
    };
}

// 调用的地方
NSDictionary *params = [self collectionParam:YES bParam:1 cParam:@"ccccc"];
[self someFunctionWithParams: params];

```

2. 使用类

如果是涉及多个地方共用的参数，典型的例子：上报的公共参数。推荐使用类型来实现，后续可以使用继承或者泛型的特性拓展。

``` objc
// ------------------- CommonContext begin -------------------
// CommonContext.h
@interface CommonContext: NSObject
@end
// CommonContext.m
@implementation CommonContext

@end
// ------------------- CommonContext end -------------------

// ------------------- CommonCollector begin -------------------
// CommonCollector.h
#import "CommonContext.h"

// __covariant表示允许将子类转为父类
@interface CommonCollector<__covariant T: CommonContext *> : NSObject
@property (nonatomic, strong, readonly) T commonContext;
- (instancetype)initWithContext:(T)commonContext;
- (NSDictionary *)getCommonParams;
@end

// CommonCollector.m
#import "CommonCollector.h"

@implementation CommonCollector

- (instancettype)initWithContext:(id)commonContext {
    if (self = [super init]) {
            _commonContext = commonContext;
    }
    return self;
}

- (NSDictionary *)getCommonParams {
    return @{
            kCommonParamA: @"pamam a" // kCommonParamA为常量字符串，定义技巧见常量条目
    };
}

@end
// ------------------- CommonCollector end -------------------


// 还可以实现BContext BCollector等等
// ------------------- AContext begin -------------------
// AContext.h
#import "CommonContext.h"
@interface AContext : CommonContext
@property (nonatomic, assign) BOOL isAAA;
@end

// AContext
#import "AContext.h"
@implementation AContext

@end
// ------------------- AContext end -------------------


// ------------------- ACollector begin -------------------
// ACollector.h
#import "CommonContext.h"
#import "CommonCollector.h"

@interface ACollector : CommonCollector<AContext *>

@end

// ACollector.m
#import "AContext.h"
@implementation AContext

- (NSDictionary *)getCommonParams {
    NSMutableDictionary *params = self.getCommonParams.mutableCopy;
    BOOL success = self.commonContext.isAAA;
    if (success) {
            params[kSuccess] = YES; // kSuccess为常量
    } else {
            params[kSuccess] = NO;
    }
    return params.copy;
}

- (BOOL)isAAA {
    return self.commonContext.isAAA;
}
@end
// ------------------- ACollector end -------------------

```

### NSArray

#### 使用NSSet处理数组包含关系

数组包含、去重，用set处理，非常简便。

`BOOL isSubset = [[NSSet setWithArray: array1] isSubsetOfSet: [NSSet setWithArray: mainArray]];`

## 对象隐藏信息的技巧

### class-continuation

**property**

《Effective Objective-C 2.0》第27条

**通过协议提供匿名对象**

《Effective Objective-C 2.0》第28条

property声明为只读，但支持内部修改。

``` objc
// .h
#import <Foundation/Foundation.h>

@interface EOCPerson : NSObject
@property (nonatomic, copy, readonly) NSString *name
@end

// .m
@interface EOCPerson()
@property (nonatomic, copy, readwrite) NSString *name
@end
```

# block

点评：block是一项常见的PL特性，即支持高阶函数，而高阶函数会遇到一个问题，就是高阶函数中的自由变量的问题。例如，函数执行结束，返回一个函数，此函数引用上层函数中变量，此时上层函数已执行结束，此变量常规情况下应该被释放了，那返回的函数就无法使用此变量了，怎么解决在这个问题呢？PL中有两种方案，其一，定义的时候从外部捕获，即常见的词法或静态作用域；其二，使用的时候从外部捕获，当前已不常见了，部分函数式编程语言使用。OC使用的是前者，就涉及一个变量捕获的问题。通常来说，需要维护一下外在环境，保存这些被捕获的变量。在手动管理内存的语言里面，这就容易导致循环引用问题。虽然会导致问题，但这是一项非常有表现力的语言特性，比如：早期JS会用这个特性模拟私有变量；函数式编程语言用闭包模拟面向对象。

## block与delegate

block和deleage，都可以把逻辑委托给其他地方处理，在具体场景，选择从二者中选择，需要考量。

1. 需要处理多种情况的传值，不适合使用block。这种情况下，block的参数会有多个，block包含的逻辑不再单一，代码可读性降低

例如：

`void (^matchBlock)(GKMatchEventeventType, Player *player, NSData *data, NSError *err);`

2. 单例只有一个delegate的情况下，若对应多个对象，需要改变delegate的引用，此时delegate不适合。

3. 在期望获取返回值或对象状态的情况下，不适用block。例如想获取对象某个状态，用block有两种方式，其一，通过block获取对象状态，此时对象用属性表示这个状态更好，外部直接获取；其二，获取对象，既然都获取对象了，就可以省略block，直接获取对象即可。也就是我们需要对象额外的信息，此时使用delegate更好

点评：这一条值得商榷。这里的理由，并非泾渭分明。实际上这些理由也适用于delegate。我觉得需要返回值的情况下，在OC中，由于语法等习惯问题，block似乎不太友好。实际上block作为高阶函数的特性，有返回值是很常见的。而且我本人比较讨厌delegate，因为delegate在实际项目中，可能会有很长的链路，实际我遇到过5层，这种设计有问题。而且对IDE不友好，不方便直接找到实际执行的地方。

4. delegate偏向向过程化的，而block偏向结果。典型的如请求返回成功和失败的block。

原文中推荐成功和失败放在一个block中处理，理由是成功和失败可能有共同的逻辑：

``` objc

[fetcher makeRequest:^(id result) {
    [progressBar stopAnimating];
    /* do something with result*/
} error:^(NSError *err) {
    /*为什么你这里要写两句一模一样的代码!*/
    [progressBar stopAnimating];
    /* Do something with error */
}];

```

列举的例子有重复逻辑。我觉得举例虽然非常正当。但不能说可能有重复逻辑，就一定要合并二者，按照这个看法，我们设计接口的时候，考虑可能有重叠情况，就把接口合并为一个？分开处理失败和成功，职责分明。前端中Promise也是这么设计的。

参考资料：[When Should I Use Blocks and Closures or Delegates for Callbacks?](https://stablekernel.com/article/use-blocks-closures-delegates-callbacks/)

点评：二者虽各有优缺点。但block是一项函数式编程的设计，但OC又缺乏其他函数式特性。导致使用的时候，多有商榷。

## block变量的捕获

OC中有5种变量类型：

1. 自动变量
2. 函数参数
3. 静态变量
4. 全局静态变量
5. 全局变量

从Block特性来说，以上5中变量类型中，需要捕获只有自动变量和静态变量，其余可以看作在“环境”中，无需捕获，即不会增加retainCount的值。

自动变量的值，会被copy，只能访问，不能改变外部的值。相当于参值。

带`__block`的自动变量和静态变量，可以改变外部的值。相当于传引用。

变量类型一分为二，非对象类型的变量和对象类型的变量。对象无论是声明为`__block`还是没有声明，block都会retain。这是为了保证block能安全使用外部对象。正是因为这个特性，容易导致循环引用。

## 循环引用

所有权修饰符共4种：

1. `__strong`
2. `__weak`：底层维护了weak_table_t的hash表，key为对象地址，value是weak指针的地址数组。达到不用持有对象，但能访问对象的目的。weak_table_t使得retainCount不用加1.
3. `__unsafe_unretained`
4. `__autoreleasing`

如果不写，默认是`__strong`。

**循环引用举例（来自一缕殇流化隐半边冰霜博客）**

``` objc
#import "ViewController.h"
#import "Student.h"

@interface ViewController ()
@end

@implementation ViewController 

- (void)viewDidLoad {
	[super viewDidLoad];

	Student *student = [[Student alloc] init];

	__block Student *stu = student;
	student.name = @"Hello World";
	student.study = ^{
		NSLog(@"my name is =%@", stu.name);
		stu = nil;
	};
}

@end

```

其中block没有执行，student持有block，block持有`__block`变量，`__block`变量持有student。3者形成了环。如果打破其中一个引用，就可以破坏环。

执行block即可。

``` objc
#import "ViewController.h"
#import "Student.h"

@interface ViewController ()
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    Student *student = [[Student alloc]init];
    student.name = @"Hello World";
    __block Student *stu = student;

    student.study = ^{
        NSLog(@"my name is = %@",stu.name);
        stu = nil;
    };

    student.study();
}

@end
```


**weak和strong使用举例（来自一缕殇流化隐半边冰霜博客）**

``` objc
#import "ViewController.h"
#import "Student.h"

@interface ViewController ()
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    Student *student = [[Student alloc]init];
    student.name = @"Hello World";
    __weak typeof(student) weakSelf = student;
    
    student.study = ^{
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(2.0 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
            NSLog(@"my name is = %@",weakSelf.name);
        });
    };

    student.study();
}

```

输出：`my name is = (null)`

为什么是null呢？问题在dispatch_after里面，study的block结束以后，student是weak，被自动释放了。`__weak`对象会变为null，防止野指针。

怎么做到既要被`__weak`修饰，又能在逻辑执行完了，才释放呢？

此时把weak变量变为`__strong`修复即可。由于weak的实现是中层weak_table_t的hash表维护的，用`__strong`，也不会导致循环引用。

``` objc

#import "ViewController.h"
#import "Student.h"

@interface ViewController ()
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    Student *student = [[Student alloc]init];
    
    student.name = @"Hello World";
    __weak typeof(student) weakSelf = student;
    
    student.study = ^{
        __strong typeof(student) strongSelf = weakSelf;
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(2.0 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
            NSLog(@"my name is = %@",strongSelf.name);
        });
        
    };

    student.study();
}

```

这个举例中的一步场景，weakSelf和strongSelf使用较为常见。但具体情况需要具体分析，不能无论是否需要，都加上二者。

# 类型

TODO

## 泛型

### 协议+泛型

规定对象可以响应特定的方法和属性，可以使用协议结合泛型，达成这个约束。

``` objc
// protocol
@protocol SomeProtocol <NSObject>
@property (nonatomic, copy) NSString *name;
@end

// .h
@interface ViewController ()
@property (nonatomic, copy) NSString *name;
@property (nonatomic, copy) NSArray <UIViewController <SomeProtocol> *> *array;

// .m
// 调用
- (void)useGenericProtocol {
    NSString *name = self.array.firstObject.name;
}

@end
```

# 多线程

## 两个线程，其中一个优先级高，且二者一起有超时的处理

使用两个线程，其中一个优先级高，且二者有超时的处理。

其中：线程2的优先级比线程1高

``` objc
dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0), ^{
	dispatch_semaphore_t semaphore = dispatch_semaphore_create(0);
	dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0), ^{
		// 线程1
		[NSThread sleepForTimeInterval:100];
		NSLog(@"线程1完成 %@", [NSThread currentThread]);
		dispatch_semaphore_wait(semaphore, waitTimeout);  // 信号量减1
	});

	dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0), ^{
		// 线程2
		for (NSInteger i = 0, l = 2; i < l; i++) {
			NSLog(@"线程2 %@", [NSThread currentThread]);
			[NSThread sleepForTimeInterval:0.1];
			if (i % 2 == 0) { // 模拟失败和成功的场景
				dispatch_semaphore_signal(semaphore);  // 信号量加1
			}
			dispatch_semaphore_signal(semaphore);  // 信号量加1
		}
	});

	dispatch_time_t waitTimeout = dispatch_time(DISPATCH_TIME_NOW, 8000 / 1000.f * NSEC_PER_SEC);
	dispatch_semaphore_wait(semaphore, waitTimeout);  // 使用两次dispatch_semaphore_wait
	dispatch_semaphore_wait(semaphore, waitTimeout);

	NSLog(@"--------------end %@", [NSThread currentThread]);
});

```

注意：这个方案应该只适合这个特殊的场景：两个线程，其中一个优先级高，且对性能要求高。如果这里有三个线程，这个方案就非常不直观，难以维护。

使用1次dispatch_semaphore_wait的问题:

``` objc

dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0), ^{
	dispatch_semaphore_t semaphore = dispatch_semaphore_create(0);
	dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0), ^{
		// 线程1
		[NSThread sleepForTimeInterval:100];
		NSLog(@"线程1完成 %@", [NSThread currentThread]);
	});

	dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0), ^{
		// 线程2
		for (NSInteger i = 0, l = 2; i < l; i++) {
			NSLog(@"线程2 %@", [NSThread currentThread]);
			[NSThread sleepForTimeInterval:0.1];
			if (i % 2 == 0) { // 模拟失败和成功的场景
				dispatch_semaphore_signal(semaphore);  // 成功的时候，信号量加1
			}
		}
	});


	dispatch_time_t waitTimeout = dispatch_time(DISPATCH_TIME_NOW, 8000 / 1000.f * NSEC_PER_SEC);
	dispatch_semaphore_wait(semaphore, waitTimeout);  // 使用1次dispatch_semaphore_wait

	NSLog(@"--------------end %@", [NSThread currentThread]);
});

```


问题：当线程2失败的时候，不执行dispatch_semaphore_signal，如果此时线程1已经完成了，仍然要等到超时。性能不佳。

# 代码组织

## 静态库与动态库

- 静态库：链接时，完整的复制到可执行文件中，被多少次使用就有多份复制，浪费空间
- 动态库：链接时不复制，程序运行时由系统动态加载到内存，只加载一次，多个程序共用，节省空间

一般一种常以.a为后缀，为静态库；另一种以.so为后缀，为动态。

### 静态库优缺点：

命名由来：在链接阶段，会将汇编生成的目标文件.o文件，与引用到的库一起打包到可执行文件中，故名静态链接

- 对函数库的链接在编译期完成
- 程序运行时与函数库在于瓜葛，移植方便
- 浪费空间和资源，因所有相关的目标文件与牵涉的函数库，被链接合成一个可执行文件

### 动态库：

为什么需要动态库？

- 静态库的空间浪费
- 静态库的程序更新部署很麻烦，需要重新编译发布，只能全量更新

命名由来：编译时并不会被链接到目标代码中，而是程序运行时才加载。故可以支持增量更新。

优点：

- 库函数的加载推迟到运行时
- 实现进程之间的资源共享（动态库也成为共享库）
- 程序升级更简单
- 甚至可以做到，链接载入完成由程序控制（显式调用）

缺点：

- 会带来DLL Hell问题
- 动态载入，会带来性能损失

### OC中的静态库和动态库

- 静态库：.a和.framework
- 动态库：.bylib和.framework

framework为什么既是动态也是静态？

系统的framework是动态库，自定义的framework是静态库

### .a和.framework区别

- .a + .h + sourceFile = .framework

- .a是纯二进制文件，.framework除了二进制文件还有资源文件

- .a是不能直接使用，至少需要.h文件配合，.framework文件可以直接使用

### 实践中的斟酌

静态库优点：直接链接到目标文件，不要动态加载，性能好，缺点：目标程序增大
动态库优点：不需要复制到目标文件，不影响体积，可以动态更新，缺点：动态载入会损失性能

虽然静态库和动态库各有优缺点，但苹果鼓励使用静态库。在项目实践中，将动态改为静态，会减少包大小。静态库虽然单个库大，但链接到可执行文件会小很多，并且会加快启动速度，减少启动时间。有时候，处于性能考虑，也会优先使用静态库。

参考资料：[iOS 静态库和动态库对ipa包大小的影响](https://www.jianshu.com/p/2dd7fe0c4333)

# 调试

## log

注意NSLog是一个C函数：

> Logs an error message to the Apple System Log facility.

对性能有影响。所以只能在demo或者调试阶段使用。

### 在Log中使用宏

- `__func__`：C99标准，输出函数名

- `__FUNCTION__`：同`__func__`

- `__PRETTY_FUNCTION__`：同`__func__`，非标准宏，但功能更强。前者只输出类的方法名，而后者会方法的详细信息

- `__LINE__`：源码的行号

- `__FILE__`：源文件名

### Core Fundation从CFString层级获取有用字符串，如selector，class，protocol

- `NSLog(@"Current selector: %@", NSStringFromSelector(_cmd))`，`_cmd`在OC中表示当前方法的selector

- `NSLog(@"Object class:%@", NSStringFromClass([self class]))`，`[self class]`获取当前方法调用类，同理`[self superclass]`当前方法调用的父类

- `NSLog(@"Filename:%@", [[NSString stringWithUTF8String:__FILE__] lastPathComponent])`


# OC和Swift混编

[如何在模块化/组件化项目中实现 ObjC-Swift 混编？](https://juejin.cn/post/6844904182873325581)


# 开源项目

值得花时间看的库：

1. MessageKit
2. Parchment
3. SDWebImage
4. Alamofire
5. Alpha
6. analytics-swift
7. AFNetwork


# change log

- 2020/10/28 created document.
- 2021/03/29 update.
