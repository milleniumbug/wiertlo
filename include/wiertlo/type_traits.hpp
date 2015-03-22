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
	}
}

#endif