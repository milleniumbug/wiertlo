#include <vector>
#include <iostream>
#include <wiertlo/baretype.hpp>

void whatever(const std::vector<int>& input)
{
	//decltype(input)::iterator // fails to compile because `input` is not a class type or enumeration type
	WIERTLO_BARETYPE(input)::const_iterator
		b = input.begin(), e = input.end();
	for(; b != e; ++b)
		std::cout << *b << "\n";
}

int main()
{
	whatever(std::vector<int>{1,2,3});
}