#include <wiertlo/case_of.hpp>
#include <iostream>

using wiertlo::switch_on;
using wiertlo::case_of;
using wiertlo::on_default;

int main() {
    int a = 42;
	switch_on(a,
		case_of(0, [&]{
			std::cout << "In the '0' branch\n"; 
		}),
		case_of(42, [&]{
			std::cout << "In the '42' branch\n";
		}),
		case_of(9000, [&]{
			std::cout << "In the '9000' branch\n";
		}),
		on_default([&]{
		    std::cout << "In the default branch\n";
		})
	);
	
	// This is a compiler error because on_default comes before case_of
	// int b = 0;
	// switch_on(b,
	//     on_default([&]{
	//         std::cout << "In the default branch\n";
	//     }),
	//     case_of(0, [&]{
	//         std::cout << "In the '0' branch\n";
	//     })
	// );
}
