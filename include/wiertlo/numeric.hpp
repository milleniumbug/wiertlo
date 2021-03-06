#ifndef HEADER87bb365ec7e54dc98f646811e4ded3aa
#define HEADER87bb365ec7e54dc98f646811e4ded3aa

#include <limits>
#include <type_traits>
#include <array>
#include <cmath>

namespace wiertlo
{
	namespace detail
	{
		// same sign, same size
		// like: signed char and char
		// or unsigned char and char
		// depending on your implemenetation
		template<
			typename Integral1,
			typename Integral2,
			typename std::enable_if<
				std::is_signed<Integral1>::value == std::is_signed<Integral2>::value &&
				std::is_same<
					typename std::make_signed<Integral1>::type,
					typename std::make_signed<Integral2>::type>::value
		>::type* = nullptr>
		int integral_compare(Integral1 lhs, Integral2 rhs)
		{
			if(lhs < rhs)
				return -1;
			else if(lhs > rhs)
				return 1;
			else
				return 0;
		}

		// same sign, different sizes
		template<
			typename Integral1,
			typename Integral2,
			typename std::enable_if<
				std::is_signed<Integral1>::value == std::is_signed<Integral2>::value &&
				!std::is_same<
					typename std::make_signed<Integral1>::type,
					typename std::make_signed<Integral2>::type>::value
		>::type* = nullptr>
		int integral_compare(Integral1 lhs, Integral2 rhs)
		{
			// same-sign promotions are sane, so we can rely on them
			typedef typename std::common_type<Integral1, Integral2>::type Common;
			return integral_compare(static_cast<Common>(lhs), static_cast<Common>(rhs));
		}

		// different signs, same sizes
		template<
			typename Integral1,
			typename Integral2,
			typename std::enable_if<
				std::is_signed<Integral1>::value &&
				std::is_unsigned<Integral2>::value &&
				std::is_same<
					typename std::make_signed<Integral1>::type,
					typename std::make_signed<Integral2>::type>::value
		>::type* = nullptr>
		int integral_compare(Integral1 lhs, Integral2 rhs)
		{
			// the rhs is unsigned so it will always be >= 0
			if(lhs < 0)
				return -1;
			const auto ulhs = static_cast<typename std::make_unsigned<Integral1>::type>(lhs);
			const auto urhs = static_cast<typename std::make_unsigned<Integral2>::type>(rhs);
			return integral_compare(ulhs, urhs);
		}

		template<
			typename Integral1,
			typename Integral2,
			typename std::enable_if<
				std::is_unsigned<Integral1>::value &&
				std::is_signed<Integral2>::value &&
				std::is_same<
					typename std::make_signed<Integral1>::type,
					typename std::make_signed<Integral2>::type>::value
		>::type* = nullptr>
		int integral_compare(Integral1 lhs, Integral2 rhs)
		{
			return -integral_compare(rhs, lhs);
		}

		// different signs, different sizes
		template<
			typename Integral1,
			typename Integral2,
			typename std::enable_if<
				std::is_signed<Integral1>::value != std::is_signed<Integral2>::value &&
				!std::is_same<
					typename std::make_signed<Integral1>::type,
					typename std::make_signed<Integral2>::type>::value
		>::type* = nullptr>
		int integral_compare(Integral1 lhs, Integral2 rhs)
		{
			// promote to the integrals of their specific sign, but with common size
			typedef typename std::common_type<Integral1, Integral2>::type Common;
			typedef typename std::conditional<
				std::is_signed<Integral1>::value,
				typename std::make_signed<Common>::type,
				typename std::make_unsigned<Common>::type>::type NewIntegral1;
			typedef typename std::conditional<
				std::is_signed<Integral2>::value,
				typename std::make_signed<Common>::type,
				typename std::make_unsigned<Common>::type>::type NewIntegral2;
			return integral_compare(static_cast<NewIntegral1>(lhs), static_cast<NewIntegral2>(rhs));
		}
	}

	// warningless comparison of two numbers with potentially
	// different signedness and sizes
	// returns negative value when lhs < rhs
	// returns 0 when lhs == rhs
	// returns positive value when lhs > rhs
	// IOW strcmp-style
	template<typename Integral1, typename Integral2>
	int integral_compare(Integral1 lhs, Integral2 rhs)
	{
		return detail::integral_compare(lhs, rhs);
	}

	template<typename InputNumber, typename InputContainer>
	std::array<InputNumber, std::tuple_size<InputContainer>::value+1> decompose(
		const InputContainer& components,
		InputNumber number)
	{
		std::array<InputNumber, std::tuple_size<InputContainer>::value+1> decomposed;
		for(std::size_t i = 0; i < components.size(); ++i)
		{
			decomposed[i] = number % components[i];
			number /= components[i];
		}
		decomposed.back() = number;
		return decomposed;
	}

	template<typename Integral>
	constexpr Integral wrap(Integral x, Integral wrapValue)
	{
		// thanks https://stackoverflow.com/a/44184152/1012936
		return ((x % wrapValue) + wrapValue) % wrapValue;
	}

	// provides a strict weak order for floating point values
	// even for when one of the values is a NaN
	// NaNs are considered to be bigger than any other value
	template<typename T = void, typename = void>
	struct float_less;

	template<>
	struct float_less<void>
	{
		typedef std::true_type is_transparent;

		template<typename Float1, typename Float2>
		bool operator()(Float1 a, Float2 b) const
		{
			static_assert(
				std::is_floating_point<Float1>::value &&
				std::is_floating_point<Float2>::value,
				"must be a floating point type");
			if(std::isnan(a))
				return false;
			if(std::isnan(b))
				return true;
			return a < b;
		}
	};
	
	template<typename T>
	struct float_less<T, typename std::enable_if<std::is_floating_point<T>::value>::type>
	{
		static_assert(std::is_floating_point<T>::value, "must be a floating point type");

		bool operator()(T a, T b) const
		{
			float_less<void> comp;
			return comp(a, b);
		}
	};
}

#endif