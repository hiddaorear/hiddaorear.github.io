### 前端调试

- console.trace() 来将 Stack trace 打印到控制台上来
- Error.captureStackTrace 函数的第一个参数是一个 object 对象，第二个参数是一个可选的 function。捕获堆栈跟踪所做的是要捕获当前堆栈的路径（这是显而易见的），并且在 object 对象上创建一个 stack 属性来存储它。如果提供了第二个 function 参数，那么这个被传递的函数将会被看成是本次堆栈调用的终点，本次堆栈跟踪只会展示到这个函数被调用之前




