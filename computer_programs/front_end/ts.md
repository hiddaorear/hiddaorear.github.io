# TypeScript

## 基础类型

### any和unknown

#### 共同点
any和unknow，都可以接收任意类型

#### 不同点
any可以赋值给任意类型，但unknown不行

因此，用来接收其他类型的情况，unknown比any要合适，更安全。

### 枚举值enum的问题

1. 数字类型的枚举值，则任意数字均可分配到此枚举，因此类型不安全；最初数据类型枚举，为了方便位运算
2. 字符串型枚举值，类型安全。但字符串枚举，不是结构化类型，而是名义类型类型（Nominally Typed），即使两个类型结构完全一致，也不相等；
3. const enum，会抹除所有enum运行时代码，直接用值替换。但这样有问题，使用枚举值映射的时候，会报错：
   ```TypeScript
   enum Enum {
	   A
   }
   let a = Enum.A;
   let nameOfA = Enum[a]; // 'A'
   
   ```
   如果替换为const enum，会报错；
   由于这个特性，const enum不能被用作发布npm包以后，导入的场景
4. 使用const enum+preserveConstEnums，本质相当于enum，一样有问题

因此，有人推荐用字面量类型的联合，类替代枚举，在大部分情况下，可以很好运作。


## 技巧

### 函数重载妙用

遇到函数返回值依赖参数，声明函数的时候，参数位置，无法推断返回值类型。可以利用函数重载，声明一个unknown类型的返回值，规避类型报错。实际调用的时候，参数类型能获取，也能推断出返回值类型。

面试题(来自：神说有光)：

1. 实现一个 zip 函数，对两个数组的元素按顺序两两合并，比如输入 [1,2,3], [4,5,6] 时，返回 [[1,4], [2,5],[3,6]]
2. 给zip函数定义TS类型（两种写法）
3. 用类型编程实现精确的类型提示，比如参数传入 [1,2,3], [4,5,6]，那返回值的类型要提示出 [[1,4], [2,5],[3,6]]

第1小题：

```TypeScript

function zip(target: any, source: any):any {
  if (!target.length  || !source.length) {
    return [];
  }
  const [one, ...targetRest] = target;
  const [other, ...sourceRest] = source;
  return [[one, other], ...zip(targetRest, sourceRest)];
}

```

第2小题：

```TypeScript
// 第一种
function zip(target: unknown[], source: unknown[]):unknown[] {
  if (!target.length  || !source.length) {
    return [];
  }
  const [one, ...targetRest] = target;
  const [other, ...sourceRest] = source;
  return [[one, other], ...zip(targetRest, sourceRest)];
}

// 第二种
interface Zip {
	(target: unknown[], source: unknown[]): unknown[]; 
}

const zip: Zip = (target: unknown[], source: unknown[]) => {
  if (!target.length  || !source.length) {
    return [];
  }
  const [one, ...targetRest] = target;
  const [other, ...sourceRest] = source;
  return [[one, other], ...zip(targetRest, sourceRest)];
}


```


第3小题：

```TypeScript

type Zip<One extends unknown[], Other extends unknown[]> = 
  One extends [infer OneFirst, ...infer Rest1]
    ? Other extends [infer OtherFirst, ...infer Rest2]
      ? [[OneFirst, OtherFirst], ...Zip<Rest1, Rest2>]
      : []
    : [];

type Mutable<T> = {
  -readonly [Key in keyof T]: T[Key];
}

function zip(target: unknown[], source: unknown[]): unknown[];
function zip<Target extends readonly unknown[], Source extends readonly unknown[]>(target: Target, source: Source): Zip<Mutable<Target>, Mutable<Source>>;
function zip(target: unknown[], source: unknown[]) {
  if (!target.length  || !source.length) {
    return [];
  }
  const [one, ...targetRest] = target;
  const [other, ...sourceRest] = source;
  return [[one, other], ...zip(targetRest, sourceRest)];
}

type res = Zip<[1, 2, 3] , [4, 5, 6]>

const arr1 = [1, 2, 3];
const arr2 = [4, '5', 6];
const reslut =  zip(arr1 , arr2);

```


### 类型状态机

```TypeScript
type RequestBuilder<Phase extends number = 0> = Phase extends 0
  ? {
      setId: (id: string | number) => RequestBuilder<1>;
    }
  : Phase extends 1
  ? {
      setBody: (body: string) => RequestBuilder<2>;
    }
  : Phase extends 2
  ? {
      send: (
        fn: (params: { id: string | number; body: string }) => void,
      ) => void;
    }
  : never;


  class HttpRequest implements RequestBuilder {
    public id: string | number | undefined;
    public body: string | undefined;
    constructor() {}
    setId(id: string | number) {
      this.id = id;
      return this;
    }
    setBody(body: string) {
      this.body = body;
      return this;
    }
    send(): RequestBuilder {
      const { id, body } = this;
      if (!id || !body || body?.length <= 0) {
        return this;
      }
      fetch(body);
      return this;
    }
  }

  new HttpRequest()
        .setId(1111)
        .setBody(JSON.stringify({body: 'test'}))
        .send();
```

调用的时候，只有按照顺序设置id和body，才能发起请求。把运行时存在的问题，在编译时暴露。
