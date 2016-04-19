#include <iostream>
#include <vector>
#include <wiertlo/noisy.hpp>

struct A
{
	int a = 5;
	int b = 10;
	// add for debugging
	wiertlo::noisy<A> n;
};

int main()
{
	// debug move constructor calls
	std::vector<A> vec;
	vec.push_back(A());
	vec.push_back(A());
	vec.push_back(A());
	vec.push_back(A());
	vec.push_back(A());
}