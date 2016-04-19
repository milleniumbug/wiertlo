#ifndef WIERTLO_STRING_HPP_BE11054B57F4424B9B2CDA913290906C
#define WIERTLO_STRING_HPP_BE11054B57F4424B9B2CDA913290906C

#include <type_traits>

namespace wiertlo
{
	namespace detail
	{
		template<typename StringLike>
		typename StringLike::size_type to_index(
			StringLike in,
			typename std::make_signed<typename StringLike::size_type>::type i)
		{
			return i >= 0 ?
				i :
				in.size() - static_cast<typename StringLike::size_type>(-i);
		}
		
		template<typename StringLike>
		typename StringLike::size_type to_index(
			StringLike in,
			typename StringLike::size_type i)
		{
			static_cast<void>(in);
			return i;
		}
		
		template<
			typename StringLike,
			typename T,
			typename std::enable_if<(
				std::is_integral<T>::value &&
				std::is_signed<T>::value &&
				!std::is_same<T, typename std::make_signed<typename StringLike::size_type>::type>::value
			)>::type* = nullptr>
		typename StringLike::size_type to_index(
			StringLike in,
			T i)
		{
			return to_index(in, typename std::make_signed<typename StringLike::size_type>::type(i));
		}
		
		template<
			typename StringLike,
			typename T,
			typename std::enable_if<(
				std::is_integral<T>::value &&
				std::is_unsigned<T>::value &&
				!std::is_same<T, typename StringLike::size_type>::value
			)>::type* = nullptr>
		typename StringLike::size_type to_index(
			StringLike in,
			T i)
		{
			return to_index(in, typename StringLike::size_type(i));
		}
		
		template<typename StringLike>
		StringLike slice_impl(
			StringLike in,
			typename StringLike::size_type b,
			typename StringLike::size_type e)
		{
			return b < in.size() ? in.substr(b, e-b) : in.substr(0,0);
		}
	}
	
	template<typename StringLike, typename Int1, typename Int2>
	StringLike slice(
		StringLike in,
		Int1 b,
		Int2 e)
	{
		return detail::slice_impl(in, detail::to_index(in, b), detail::to_index(in, e));
	}
	
	template<typename StringLike, typename Int1>
	auto slice(
		StringLike in,
		Int1 b) -> decltype(slice(in, b, in.size()))
	{
		return slice(in, b, in.size());
	}
	
	template<typename StringLike>
	StringLike trim_left(StringLike in, StringLike whitespace = " \r\n\t")
	{
		return slice(in, in.find_first_not_of(whitespace));
	}
	
	template<typename StringLike>
	StringLike trim_right(StringLike in, StringLike whitespace = " \r\n\t")
	{
		return slice(in, 0, in.find_last_not_of(whitespace)+1);
	}
	
	template<typename StringLike>
	StringLike trim(StringLike in, StringLike whitespace = " \r\n\t")
	{
		return trim_left(trim_right(in, whitespace), whitespace);
	}
}

#endif