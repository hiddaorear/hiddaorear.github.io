template<bool C, typename Ta, typename Tb>
class IfThenElse;

template<typename Ta, typename Tb>
class IfThenElse<true, Ta, Tb> {
	public:
		typedef Ta ResultT;
}

template<typename Ta, typename Tb>
class IfThenElse<false, Ta, Tb> {
	public:
		typedef Tb ResultT;
}

// 计算平方根
// 基本模板
template<int N, int LO=0, int HI=N>
class Sqrt {
	public:
		enum { mid = (LO + HI + 1/2)};
		enum {
			result = (N < mid * mid) ? Sqrt<N, LO, mid-1>::result : Sqrt<N, mid, HI>::result;
		}
}

// 局部特化，当LO等于HI
// 不够严谨，有可能资源耗尽了也没到达LO=HI。最好是在一定范围就结束了
template<int N, int M>
class Sqrt<N, M, M> {
	public:
		enum { result = M };
}