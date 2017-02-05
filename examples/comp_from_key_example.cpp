#include <wiertlo/comp_from_key.hpp>
#include <vector>
#include <algorithm>
#include <iostream>
#include <wiertlo/comp_from_key.hpp>

int main()
{
	std::vector<std::vector<int>> vecvec{ { 0 }, {}, { 0, 42, 23, 55 }, { 0, 0 } };
	std::sort(vecvec.begin(), vecvec.end(), wiertlo::comp_from_key([](auto&& vec){ return vec.size(); }));
	for(auto&& vec : vecvec)
	{
		std::cout << vec.size();
	}
}