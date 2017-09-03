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
		noisy& operator=(noisy&& other) noexcept { std::cout << "MOVE ASSIGNMENT<" << typeid(T).name() << ">(this = " << this << ", other = " << &other << ")\n"; return *this; }
		noisy& operator=(const noisy& other) { std::cout << "COPY ASSIGNMENT<" << typeid(T).name() << ">(this = " << this << ", other = " << &other << ")\n"; return *this; }
		noisy(const noisy& other) { std::cout << "COPY CONSTRUCTOR<" << typeid(T).name() << ">(this = " << this << ", other = " << &other << ")\n"; }
		noisy(noisy&& other) noexcept { std::cout << "MOVE CONSTRUCTOR<" << typeid(T).name() << ">(this = " << this << ", other = " << &other << ")\n"; }
		~noisy() { std::cout << "DESTRUCTOR<" << typeid(T).name() << ">(this = " << this << ")\n"; }
		noisy() { std::cout << "CONSTRUCTOR<" << typeid(T).name() << ">(this = " << this << ")\n"; }
	};
}

#endif