// 오... 근데 이거 디버깅은 못하나

#include <utility>


template <size_t>
struct Any
{
	template <class T>
	operator T() const;
};


template <class T, size_t N>
concept ConstructibleWithN = requires
{
	[]<size_t...Idxs>(std::index_sequence<Idxs...>) -> decltype(T{Any<Idxs>{}...})
	{
		return {};
	}(std::make_index_sequence<N>{});
};

template <class T, size_t N>
concept AggregateOfN = std::is_aggregate_v<T> && ConstructibleWithN<T, N> && !ConstructibleWithN<T, N + 1>;

template <class T>
constexpr auto NumAggregateMembers = []<size_t...Idxs>(std::index_sequence<Idxs...>)
{
	return ((AggregateOfN<T, Idxs> * Idxs) + ... + 0);
}(std::make_index_sequence<32>{});


struct Foo
{
	int    i;
	double j;
	int x = 3;
	int y;
};


int main()
{
	static_assert(NumAggregateMembers<Foo> == 2);
}
