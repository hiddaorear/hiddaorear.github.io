namespace NSVarTypeDict
{
    // 实现循环逻辑，N：还需要构造的元素数量；TCont：容器类型，用于存储最终结果（值是类型的数组）；T是已生成的类型序列
    template <size_t N, template<typename...> class TCont, typename...T>
    struct Create_ {
        using type = typename Create_<N - 1, TCont, NullParameter, T...>::type; // 将N-1，进行下一个迭代
    };
    template <template<typename...> class TCont, typename...T>
    struct Create_<0, TCont, T...> { // 特化：N为0，循环终止，返回TCont<T...>类型数组
        using type = TCont<T...>;
    };
}

// TParameters表示键
template <typename...TParameters>
struct VarTypeDict
{
    // TTypes表示值类型
    template <typename...TTypes>
    struct Values {
        Values() = default;
        Values(std::shared<void>(&&input)[sizeof...(TTypes)])
        {
            for (size_t i = 0; i < sizeof...(TTypes); ++i) {
                m_tuple[i] = std::move(input[i]);  // 复制给 m_tuple，供Set使用
            }
        }
    public:
        template <typename TTag, typename TVal>
        auto Set(TVal&& val) &&  // 函数结尾加&&，表明此函数只能用于右值
        {
            using namespace NSMultiTypeDict;
            constexpr static size_t TagPos = Tag2ID<TTag, TParameters...>;  // 获取TTag在TParameters的位置

            using rewVal = std::decay_t<TVal>;
            rawVal* tmp = new rawVal(std::forward<TVal>(val));
            m_tuple[TagPos] = std::shared_ptr<void>(tmp, [](void* ptr) {
                rawVal* nptr = static_cast<rawVal*>(ptr);
                delete nptr;
            });

            using new_type = NewTupleType<rawVal, TagPos, Values<>, TTypes...>;
            return new_type(std::move(m_tuple));
        }

        template <typename TTag>
        const auto& Get() const;
    };
private:
    std::shared_ptr<void> m_tuple[sizeof...<TTypes>];  // 智能指针数组，每一个元素都是void的智能指针
public:
    static auto Create() {
        using namespace NSVarTypeDict;
        using type = typename Create_<sizeof...(TParameters), Values>::type; // Values保存类型计算结果；只提供两个模板参数，T...对应的是一个空的类型系列
        return type{};
    }
};



struct FParams : public VarTypeDict<A, B, C> {};

template <typename TIn>
float fun(const TIn& in) {
    auto a = in.template Get<A>();
    auto b = in.template Get<B>();
    auto c = in.template Get<C>();
    return a ? b : c;
}

int main() {
    std::cerr << fun(FParams::Create()
                        .Set<A>(true)
                        .Set<B>(2.4f)
                        .Set<C>(0.1f))
}