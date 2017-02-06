#ifndef HEADER87bb365ec7e54dc98f646811e4ded3aa
#define HEADER87bb365ec7e54dc98f646811e4ded3aa

#include <limits>
#include <type_traits>

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
			// the rhs is signed so it will never be >= 0
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
}

#endif