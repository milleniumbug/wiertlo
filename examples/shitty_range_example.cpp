#include <wiertlo/shitty_range.hpp>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>

int main()
{
	std::vector<int> a = { 1, 2, 3 };
	std::copy(WIERTLO_SHITTY_RANGE(a), std::ostream_iterator<int>(std::cout));
	int b[] = { 4, 5, 6 };
	std::copy(WIERTLO_SHITTY_RANGE(b), std::ostream_iterator<int>(std::cout));
	// std::sort(WIERTLO_SHITTY_RANGE(std::vector<int>{1,2,3})); // fails to compile
}