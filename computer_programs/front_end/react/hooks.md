# React

## hooks

### useEffect和useState


``` typescript
function Component() {
	const [a, setA] = useState(0);
	useEffect(()=>{
		const timer = setInterval(() => { setA(a + 1); }, 1000);
		return () => {
			clearInterval(timer);
		};
	}, []); // 第二个参数为[]空数组，后续react引发的渲染，都与此useEffect无关

}

```

组件挂载以后，并没有按照预期的执行`setA(a + 1)`，累加，而是只执行了一次。

react的警告：Either include it or remove the dependency array. You can also do a functional update 'setA(a =>...)' if you only need 'a' in the 'setA' call.

如果修改为：`cont timer = setInterval(() => { setA(a => a +1)}, 1000);`

就按照预期执行了。

#### 为什么？

useEffect传入空数组，则hooks只在组件挂载时候运行一次。而useEffect执行的时候，会创建一个闭包，将a保存到闭包中，且初始值为0。故每隔1s，就会执行`setCount(0 + 1)`，因此，a的值不会超过1.

注意：useEffect依赖不传值，则hook在组件每次render的时候都会执行。

### memo 系列

#### React.memo和useMemo区别

- React.memo 是HOC高阶组件，包装组件以后，只有props发生变化才会重新渲染
- useMemo是hooks，在组件中包装函数以后，只有依赖项发生变化了才重新计算；

#### useMemo和useCallback区别

- useMemo会调用函数并返回结果，而useCallback返回函数，而不调用

### ref 系列
ref在React中非常特殊，React是单向数据流，而ref通过和useImperativeHandle组合，实现子组件传递方法给父组件，实现父组件调用子组件的目的。

- ref的current属性，存储指定值和DOM元素。组件重新渲染，值也会维持不变。
- ref存储值修改，不会触发组件重新渲染
- ref是sealed属性：无法添加新属性，无法修改属性设定，但可以修改属性的值【与freeze区别，freeze的属性不可改变】
- 可以直接标记class component，无法标记function Component，因后者不是实例；无法像其他props一样传递到子组件，传递需要使用forwardRef

#### 妙用

Ref不仅仅能拿到组件的引用，还能创建一个mutable对象，配合useEffect，可以用来支持previousProps

```typescript
function usePrevious(value) {
  const ref = useRef();
  useEffect(() => {
    ref.current = value;
  });
  return ref.current;
}
```

#### useRef和forwardRef

- useRef可以勾住，本组件挂载完成以后的对象；
- forwardRef可以勾住，子组件挂载完成以后的对象;

#### useImperativeHandle

- 让父组件获取子组件定义的函数。本质是将子组件的函数，通过此hooks添加到父组件的useRef定义的对象中；
- 需要结合useRef和forwardRef一起使用；


```typescript
// 子组件

const someHandle = () => {
	// ...
}

useImperativeHandle(ref, () => ({
  someHandle
}));

```

1. useRef 创建引用变量
2. forwardRef将引用变量传递给子组件
3. useImperativeHandle将子组件函数，添加到父组件的ref对象上

### 经典文章

- [React Hooks 原理剖析](https://zhuanlan.zhihu.com/p/372790745)
- [React Hooks: 深入剖析 useMemo 和 useEffect](https://www.yuque.com/lxylona/note/tlc8hz)
- [useImperativeHandle基础用法](https://github.com/puxiao/react-hook-tutorial/blob/master/13%20useImperativeHandle%E5%9F%BA%E7%A1%80%E7%94%A8%E6%B3%95.md)


## 组件库设计

### 组件定义

```typescript
const MyComponent: React.FC<{text: string}> = ({text}) => {
    return React.useMemo(() => <div>{text}</div>, [text]);
}

MyComponent.defalutProps = {
    text: 'test'
}

```

- 用React.FC定义Props参数类型
- 用useMemo优化渲染性能
- 用defaultProps定义默认值

不用React.memo原因：无法做到按需渲染。在使用useContext情况下，memo会使组件重渲染。

### Function Component内部函数需要用useCallback包裹，保证性能

## 面试

- [reactjs-interview-questions](https://github.com/sudheerj/reactjs-interview-questions)


## 最佳实践

- [React Hooks 最佳实践](https://mp.weixin.qq.com/s/HwlnvAh18saKwXC_nZwSHw)

## 跨平台设计

- [taro](https://github.com/NervJS/awesome-taro)

## TODO

- [图解 React 源码系列](https://github.com/7kms/react-illustration-series)
- [React技术揭秘](https://react.iamkasong.com/)
