#ifndef HEADER9b283805941d4d9f9689accdaac6b80f
#define HEADER9b283805941d4d9f9689accdaac6b80f

#include <type_traits>

namespace wiertlo
{
	namespace cpp_style_declarations
	{
		template<typename T>
		using ref = T&;

		template<typename T>
		using rvalue_ref = T&&;

		template<typename T>
		using universal_ref = T&&;

		template<typename T/*, typename = typename std::enable_if<!std::is_function<T>::value>::type */>
		using ptr = T*;

		template<typename T, typename = typename std::enable_if<std::is_function<T>::value>::type>
		using function_ptr = T*;

		template<typename T, std::size_t N>
		using c_array = T[N];

		template<typename T>
		using c_array_infer_size = T[];
	}

	template<typename T>
	T& extract_reference(T& v)
	{
		return v;
	}

	template<typename T>
	const T& extract_reference(const T& v)
	{
		return v;
	}

	template<typename T>
	T& extract_reference(std::reference_wrapper<T> v)
	{
		return v.get();
	}

	template<typename T>
	const T& extract_reference(std::reference_wrapper<const T> v)
	{
		return v.get();
	}
}

#endif