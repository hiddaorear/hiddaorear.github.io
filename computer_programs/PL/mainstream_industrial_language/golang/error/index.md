# Go的错误

> 不管是Option还是Either还是Result之类的monad，又或者是throw Exception，他们的共同点就是错误和正常状态的关系是和类型，然后支持模式匹配（try catch也可以看成一种特殊的模式匹配）。而go的那个if err != nil最大的问题是他是一个积类型。
> 现在的主流语言满地都是用monad模式在处理错误，连java都有optional，go也有第三方fp库叫fpgo。我觉得不用纠结概念，haskell要参与这个讨论就肯定要提到functor semigroup monoid这些是haskell里很基础的类型类。这不是开发者要蹭范畴论，是人家标准库本来就这么实现的


## 阅读资料

- [Errors are values](https://go.dev/blog/errors-are-values)
- [Error Handling in Go](https://www.innoq.com/en/blog/2016/06/golang-errors-monads/)
- [为什么 Go 语言的 Error Handling 被某些人认为是一个败笔？](https://www.zhihu.com/question/330263279)
- [沅有芷兮：类型系统的数学之美](https://zhuanlan.zhihu.com/p/69223872)
