#include <algorithm>
#include <vector>
#include <wiertlo/not_fn.hpp>
#include <cassert>

int main()
{
	std::vector<int> x = { 2, 4, 6, 10, 14, 0, 16 };
	auto is_even = [](int i){ return i % 2 == 0; };
	assert(std::find_if(x.begin(), x.end(), wiertlo::not_fn(is_even)) == std::find_if_not(x.begin(), x.end(), is_even));
}