#ifndef HEADERD3B40C1C72E4435D845C537D3A159DF2
#define HEADERD3B40C1C72E4435D845C537D3A159DF2

#include <type_traits>

namespace wiertlo
{
	namespace detail
	{
		template<typename T>
		struct identity { typedef T type; };
	}

	namespace type_traits
	{
		template<bool IsEnabled, typename Type = void>
		using EnableIf = typename std::enable_if<IsEnabled, Type>::type;

		template<typename... Args>
		using Void = void;

		template<typename T>
		using SuppressTemplateDeduction = wiertlo::detail::identity<T>::type

		template<typename T>
		using Lazy = wiertlo::detail::identity<T>;

		template<bool Cond, typename T, typename F>
		using Conditional = std::conditional<Cond, T, F>::type;

		template<bool Cond, typename T, typename F>
		using LazyConditional = std::conditional<Cond, T, F>::type::type;
	}
}

#endif