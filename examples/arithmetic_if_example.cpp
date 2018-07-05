#include <iostream>
#include <cmath>
#include <wiertlo/arithmetic_if.hpp>

using wiertlo::arif;

int main()
{
	double a,b,c;
	std::cout << "Give values of a, b, c\n";
	std::cin >> a >> b >> c;
	double delta = b*b+4*a*c;
	arif(delta,
		[&](){ std::cout << "Discriminant is negative"; },
		[&](){ std::cout << -b/2*a; },
		[&](){ std::cout << (-b+sqrt(delta))/(2*a) << " " << (-b-sqrt(delta))/(2*a); }
	);
}