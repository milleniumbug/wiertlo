#include <algorithm>
#include <iterator>
#include <cassert>
#include <vector>
#include <wiertlo/make.hpp>
#include <wiertlo/overload_set.hpp>

int main()
{
	// wiertlo::make_array
	// will fail because of no explicit type
	// auto a = wiertlo::make_array(1, 2, 3);
	auto arr = wiertlo::make_array<int>(42, 2, 1, 5);
	static_assert(std::is_same<decltype(arr), std::array<int, 4>>::value, "");

	// wiertlo::make:
	// wiertlo::make<T>(...) is equivalent to T(...), but it's a function
	// so it has no issues with MVP or passing to standard algorithms
	std::vector<std::vector<int>> a_vector;
	std::transform(arr.begin(), arr.end(), std::back_inserter(a_vector), WIERTLO_OVERLOAD_SET(wiertlo::make<std::vector<int>>));
	for(std::size_t i = 0; i < arr.size(); ++i)
	{
		assert(arr[i] == static_cast<int>(a_vector[i].size()));
	}
	// triggers ICE in g++ 4.9.2
	// std::transform(arr.begin(), arr.end(), std::back_inserter(a_vector), WIERTLO_OVERLOAD_SET(std::vector<int>));

	// wiertlo::make_unique
	// C++14's std::make_unique backport to C++11
	// see http://en.cppreference.com/w/cpp/memory/unique_ptr/make_unique
	auto po = wiertlo::make_unique<int>(42);
	static_assert(std::is_same<decltype(po), std::unique_ptr<int>>::value, "");
	auto pua = wiertlo::make_unique<int[]>(42);
	static_assert(std::is_same<decltype(pua), std::unique_ptr<int[]>>::value, "");
	// will fail to compile, just like C++14's std::make_unique
	// auto pka = wiertlo::make_unique<int[5]>(42);

	// wiertlo::make_shared is declared for symmetry with wiertlo::make_unique
	// it just forwards the job to std::make_shared
	auto sp = wiertlo::make_shared<int>(42);
}