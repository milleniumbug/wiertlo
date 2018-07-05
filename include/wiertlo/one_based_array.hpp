#ifndef HEADER2499DC283D654FB086461D0FE8712029
#define HEADER2499DC283D654FB086461D0FE8712029

#include <cstddef>
#include <utility>
#include <wiertlo/defs.hpp>

namespace wiertlo
{

	template<typename T>
	class OneBasedArray
	{
		T underlying_array;
	public:
		auto operator[](std::size_t pos)
			-> decltype((wiertlo::extract_reference(underlying_array)[pos-1]))
		{
			return wiertlo::extract_reference(underlying_array)[pos-1];
		}

		auto operator[](std::size_t pos) const
			-> decltype((wiertlo::extract_reference(underlying_array)[pos-1]))
		{
			return wiertlo::extract_reference(underlying_array)[pos-1];
		}

		template<typename U>
		explicit OneBasedArray(U&& c) : underlying_array(std::forward<U>(c)) { }
	};

	template<typename T>
	OneBasedArray<T> make_one_based(T& a) { return OneBasedArray<T>(a); }

	template<typename T>
	OneBasedArray<const T> make_one_based(const T& a) { return OneBasedArray<const T>(a); }

}

#endif