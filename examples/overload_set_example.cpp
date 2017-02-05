#include <vector>
#include <algorithm>
#include <iostream>

#include <wiertlo/overload_set.hpp>
#include <wiertlo/shitty_range.hpp>

template<typename T>
std::ostream& print(const T& x)
{
	return std::cout << x << "\n";
}

template<typename... F>
struct Functions;

template<typename Head>
struct Functions<Head> : Head
{
	using Head::operator();

	template<typename ArgsH>
	Functions(ArgsH&& argh) :
		Head(argh)
	{

	}
};

template<typename Head, typename... Tail>
struct Functions<Head, Tail...> : Head, Functions<Tail...>
{
	using Functions<Tail...>::operator();
	using Head::operator();

	template<typename ArgsH, typename... ArgsT>
	Functions(ArgsH&& argh, ArgsT&&... argt) :
		Head(argh),
		Functions<Tail...>(std::forward<ArgsT>(argt)...)
	{

	}
};

template<typename... Args>
Functions<typename std::remove_reference<Args>::type...> make_a_function(Args&&... args)
{
	return Functions<typename std::remove_reference<Args>::type...>(std::forward<Args>(args)...);
}

struct on_int
{
	void operator()(int wow)
	{
		std::cout << "int " << wow << "\n";
	}
};

struct on_long
{
	void operator()(long wow)
	{
		std::cout << "int " << wow << "\n";
	}
};

auto i = on_int();
auto l = on_long();

int main()
{
	std::vector<int> a = { 2, 3, -42 };
	//std::for_each(a.begin(), a.end(), print); // fails to compile
	std::for_each(WIERTLO_SHITTY_RANGE(a), WIERTLO_OVERLOAD_SET(print)); // standard algorithms taking functions
	WIERTLO_OVERLOAD_SET(print)("Hello") << "Hi there!\n"; // testing reference returning

	// it uses SFINAE properly

	auto f = make_a_function(i, l);
	// ICE's
	//auto g = make_a_function(WIERTLO_OVERLOAD_SET(on_long), WIERTLO_OVERLOAD_SET(on_int));
	auto g = make_a_function(WIERTLO_OVERLOAD_SET(i), WIERTLO_OVERLOAD_SET(l));
	f(42);
	//g(42);
}