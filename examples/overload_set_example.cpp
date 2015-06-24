#include <vector>
#include <algorithm>
#include <iostream>

#include <wiertlo/overload_set.hpp>
#include <wiertlo/range.hpp>

template<typename T>
std::ostream& print(const T& x)
{
	return std::cout << x << "\n";
}

int main()
{
	std::vector<int> a = { 2, 3, -42 };
	//std::for_each(a.begin(), a.end(), print); // fails to compile
	std::for_each(WIERTLO_RANGE(a), WIERTLO_OVERLOAD_SET(print)); // standard algorithms taking functions
	WIERTLO_OVERLOAD_SET(print)("Hello") << "Hi there!\n"; // testing reference returning
}