#include <iostream>
#include <string>
#include <variant>
#include <vector>

using namespace std::string_literals;

using var_t = std::variant<int, double, std::string>;

template <class... Ts>
struct overloaded : Ts...
{
	using Ts::operator()...;
};

template <class... Ts>
overloaded(Ts ...)->overloaded<Ts...>;

int main()
{
	std::vector<var_t> varvec = { 10, 3.5, "abc"s };
	for (auto& i : varvec)
	{
		std::visit([](auto&& args)
			{
				std::cout << args << std::endl;
			}, i);
		//void visitor, 부작용만 일으킴

		var_t vs = std::visit([](auto&& arg) -> var_t
			{
				return arg + arg;
			}, i);
		// 값 반환 방문자, 받는 인자를 통해 새로운 타입으로 반환함

		std::visit([](auto&& args)
			{
				using T = std::decay_t<decltype(args)>;
				if constexpr (std::is_same_v<T, int>)
					std::cout << "타입 : int" << std::endl;
				else if constexpr (std::is_same_v<T, double>)
					std::cout << "타입 : double" << std::endl;
				else if constexpr (std::is_same_v<T, std::string>)
					std::cout << "타입 : std::string" << std::endl;
			}, vs);
		// 타입 매칭 방문자, 각 타입을 다르게 처리함
	}

	std::cout << "new varvec" << std::endl;

	for (auto& i : varvec)
	{
		std::visit(overloaded{
						[](int                arg) { std::cout << "타입 : int" << std::endl; },
						[](double             arg) { std::cout << "타입 : double" << std::endl; },
						[](const std::string& arg) { std::cout << "타입 : std::string" << std::endl; }
			}, i);
		// 다른 타입 매칭 방문자, operator() 를 호출함
		// 다중 람다를 할 수 있는 이유는 overloaded가 가변인자 템플릿이기 때문
	}
}

