# Objective-C

# 导读

**从语言设计角度看Objective-C**

# Objective-C安全的类型转换

## 代码

``` Objective-C

/**
* Category声明
*/
@interface NSObject (QNUtils)
+ (instancetype)qn_cast:(id)any warnOnFailure:(BOOL)warnOnFailure;
@end
/**
* Category实现
*/
@implementation NSObject (QNUtils)
+ (instancetype)qn_cast:(id)any warnOnFailure:(BOOL)warnOnFailure {
    if (any) {
        if ([any isKindOfClass:[self class]])
            return any;
        else if (warnOnFailure)
            NSLog(@"Can't cast %@ to type %@", any, NSStringFromClass([self class]));
    }

    return nil;
}
@end

/**
* 宏定义
*/
 //转换value类型到clz，如果类型不符，会输出错误日志，返回nil；
#define AS(clz, value) ([clz qn_cast:(value) warnOnFailure:YES])
 //强制转换value类型到clz，类型不符，返回nil；有限场合使用
#define CAST(clz, value) ([clz qn_cast:(value) warnOnFailure:NO])

/**
* 示例
*/
  for (UIView * subview in self.subviews) {
    AS(UIImageView, subview).image = image;
  }

/**
* 对比不安全的两种常见写法
*/
  for (UIView * subview in self.subviews) {
    ((UIImageView *)subview).image = image; //不安全类型转换
  }

  for (id subview in self.subviews) {
    [subview setImage:image]; //不安全使用语言动态性
  }

```

## 解析

使用Macro和instancetype的小技巧，实现其它语言里有的AS Pattern，相对安全且便捷。

Objective-C语言的动态性，让集合类操作，参数传递等场合容易无视对象类型，要么强制类型转换，或滥用id类型。
容易降低代码的维护性和稳定性。


## 涉及知识剖析

### Category 和 Extension

[OC 的类别和扩展（Category 和 Extension）](https://xiaovv.me/2017/06/03/Talk-about-Category-and-Extension-in-Objective-C/)

[OC 底层探索 - Category 和 Extension](https://juejin.im/post/6844904067987144711)

[深入理解Objective-C：Category](https://tech.meituan.com/2015/03/03/diveintocategory.html)

### 类型转换 AS Pattern

### 动态类型检测

- `- (BOOL)isKindOfClass:(Class)aClass` 判断类是否是类或其子类的实例
- `- (BOOL)isMemberOfClass:(Class)aClass` 判断是否类的实例
- `+ (BOOL)instancesRespondToSelector:(SEL)aSelector` 判断实例是否有以某名字命名的方法，只能用在类上
- `- (BOOL)respondsToSelector:(SEL)aSelector` 判断是否有以某名字命名的方法

### Macro

[ReactiveCocoa 中 奇妙无比的“宏”魔法](https://halfrost.com/reactivecocoa_macro/)

### `instancetype`

### `NSLog`

# 泛型

[Objective—C语言的新魅力——Nullability、泛型集合与类型延拓](https://my.oschina.net/u/2340880/blog/514804)

[oc 中的泛型与nullability](https://zhang759740844.github.io/2016/09/28/oc%E6%96%B0%E7%89%B9%E6%80%A7/)

[深入研究 Block 用 weakSelf、strongSelf、@weakify、@strongify 解决循环引用](https://halfrost.com/ios_block_retain_circle/)


# Collention 类

### `NSMutableArray`与`NSArray`剖析

可变数组`NSMutableArray` 不是线程安全的，不可变数组`NSArray`是线程安全的。为了满足多线程数组操作要求，需要对可变数字进行封装。

[线程安全的可变数组、可变字典](https://www.jianshu.com/p/9082d66fff3c)

[知识点：可变数组的属性使用copy修饰的后果](https://juejin.im/post/6844903714793193485)


# change log

- 2020/10/28 created document.
