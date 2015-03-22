#include <wiertlo/case_of.h>
#include <iostream>

using wiertlo::switch_on;
using wiertlo::case_of;

int main()
{
	int a = 42;
	switch_on(a,
		case_of(0, [&]{
			std::cout << "In the '0' branch"; 
		}),
		case_of(42, [&]{
			std::cout << "In the '42' branch";
		}),
		case_of(9000, [&]{
			std::cout << "In the '9000' branch";
		})
	);
}