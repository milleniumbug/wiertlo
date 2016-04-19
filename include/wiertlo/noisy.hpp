#ifndef WIERTLO_NOISY_HPP_E9E22037161B4CEA869273970DA6FE93
#define WIERTLO_NOISY_HPP_E9E22037161B4CEA869273970DA6FE93

#include <typeinfo>
#include <iostream>

namespace wiertlo
{
	/// noisy
	///
	/// A class logs all of the calls to Big Five and the default constructor
	/// The name of the template parameter, received as if by call
	/// to `typeid(T).name()`, is displayed in the logs.
	template<typename T>
	struct noisy
	{
		noisy& operator=(noisy&&) noexcept { std::cout << "operator=(noisy<" << typeid(T).name() << ">&&)\n"; return *this; }
		noisy& operator=(const noisy&) { std::cout << "operator=(const noisy<" << typeid(T).name() << ">&)\n"; return *this; }
		noisy(const noisy&) { std::cout << "noisy(const noisy<" << typeid(T).name() << ">&)\n"; }
		noisy(noisy&&) noexcept { std::cout << "noisy(noisy<" << typeid(T).name() << ">&&)\n"; }
		~noisy() { std::cout << "~noisy<" << typeid(T).name() << ">()\n"; }
		noisy() { std::cout << "noisy<" << typeid(T).name() << ">()\n"; }
	};
}

#endif