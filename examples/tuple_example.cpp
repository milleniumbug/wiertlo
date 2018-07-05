#include <string>
#include <iostream>
#include <iomanip>
#include <tuple>
#include <type_traits>
#include <wiertlo/tuple.hpp>


int main()
{
	int i = 0;
	std::tuple<int, char, std::string> tup(42, 'x', "the quick brown fox jumps over the lazy dog");
	// for each element in tuple, no index
	wiertlo::tuple::foreach(tup, [](auto& x){ std::cout << x << "\n"; });
	// for each element in tuple, with index
	wiertlo::tuple::foreach_with_index(tup, [](auto& x, std::size_t i){ std::cout << i+1 << " " << x << "\n"; });
	// map function
	std::tuple<int, double, float> other(5, 4.0, 3.0f);
	auto a = wiertlo::tuple::map(other, [](auto& x){ return std::remove_reference_t<decltype(x)>(0.1); });

	std::cout << std::setprecision(18) << std::fixed;
	wiertlo::tuple::foreach(a, [](auto& x){ std::cout << x << "\n"; });
}