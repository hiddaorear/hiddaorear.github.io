// 计算3的N次方模板，实现一般的递归计算
template<int N>
class Pow3 {
	public:
		enum { result = 3 * Pow3<N-1>::result; };
}
// 特化：用于结束递归
template<>
class Pow3<0> {
	public:
		enum { result = 1 };
}