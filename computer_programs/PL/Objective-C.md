# Objective-C

# 面试题

- [iOS面试了20几家总结出来的面试题（一）](https://juejin.cn/post/6854573212165111822)

- [iOS Interviews DevNotes](https://github.com/DevDragonLi/iOSInterviewsAndDevNotes)

- [日常积累所看到的面试题集锦](https://github.com/iOShuyang/Book-Recommended-Interview)

- [阿里、字节 一套高效的iOS面试题解答（完结）](https://www.jianshu.com/p/c1765a6305ab)

- [2020年iOS面试题总结(一)](https://www.xuebaonline.com/2020%E5%B9%B4iOS%E9%9D%A2%E8%AF%95%E9%A2%98%E6%80%BB%E7%BB%93(%E4%B8%80)/)


# 基础

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

## 基础类

### BOOL的陷阱

1. `BOOL`定义为`signed char`，因此值具有除了`YES`和`NO`（1和0）之外的值。所以不要将BOOL与`YES`或`NO`比较
2. 由于原因1，所以将常规整型转换为`BOOL`，在没有使用`&&`,`||`,`!`的情况下，请使用三元运算符返回`YES`或`NO`



### NSString

### NSNumber

- int32_t类型，如果是后台下发，且有初始值。如果需要设置默认值，则需要考虑值是否存在为0的情况。此时，客户端应该无法处理。因为后台下发的值，可能恰好就是0，此时我们不能认为无值，而去用默认值。只有后台自身能处理。


## 基本容器

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

# 类型

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

# 开源项目

## AFNetwork





# change log

- 2020/10/28 created document.
- 2021/03/29 update.
