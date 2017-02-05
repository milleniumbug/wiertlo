#ifndef HEADERab422750862a45b0a1bd99bc3d5d8dbc
#define HEADERab422750862a45b0a1bd99bc3d5d8dbc

#include <functional>
#include <utility>
#include <type_traits>

namespace wiertlo
{
	struct unit
	{
		friend bool operator==(unit, unit) { return true; }
		friend bool operator!=(unit, unit) { return false; }
	};
}

namespace std
{
	template<>
	struct hash<::wiertlo::unit>
	{
		std::size_t operator()(::wiertlo::unit) const
		{
			return 0;
		}
	};
}

namespace wiertlo
{
	template<typename T, typename Alternative = unit>
	struct unvoid
	{
		typedef T type;
	};

	template<typename Alternative>
	struct unvoid<void, Alternative>
	{
		typedef Alternative type;
	};

	template<typename Alternative>
	struct unvoid<const void, Alternative>
	{
		typedef typename std::add_const<Alternative>::type type;
	};

	template<typename Alternative>
	struct unvoid<volatile void, Alternative>
	{
		typedef typename std::add_volatile<Alternative>::type type;
	};

	template<typename Alternative>
	struct unvoid<const volatile void, Alternative>
	{
		typedef typename std::add_cv<Alternative>::type type;
	};

	template<
		typename Func,
		typename... Args>
	auto unvoid_apply(Func&& func, Args&&... args) ->
		typename std::enable_if<
			!std::is_void<decltype(std::forward<Func>(func)(std::forward<Args>(args)...))>::value,
			decltype(std::forward<Func>(func)(std::forward<Args>(args)...))>::type
	{
		return std::forward<Func>(func)(std::forward<Args>(args)...);
	}

	template<
		typename Func,
		typename... Args>
	auto unvoid_apply(Func&& func, Args&&... args) ->
		typename std::enable_if<
			std::is_void<decltype(std::forward<Func>(func)(std::forward<Args>(args)...))>::value,
			unit>::type
	{
		std::forward<Func>(func)(std::forward<Args>(args)...);
		return unit();
	}
}

#endif