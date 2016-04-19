#ifndef WIERTLO_STRONG_TYPEDEF_HPP_7F0E6155B19442ADB4A13F8E9C63DEC3
#define WIERTLO_STRONG_TYPEDEF_HPP_7F0E6155B19442ADB4A13F8E9C63DEC3

#include <utility>
#include <type_traits>

namespace wiertlo
{
	namespace detail
	{
		// https://rmf.io/cxx11/is_related/
		// https://rmf.io/cxx11/type-traits-galore/
		template <typename T>
		using Bare = typename std::remove_cv<
			typename std::remove_reference<T>::type
		>::type;
		
		template <typename T, typename... U>
		struct is_related : std::false_type {};
		
		template <typename T, typename U>
		struct is_related<T, U> : std::is_same<Bare<T>, Bare<U>> {};
		
		template <bool B, typename...>
		struct dependent_bool_type : std::integral_constant<bool, B> {};
		
		template <bool B, typename... T>
		using Bool = typename dependent_bool_type<B, T...>::type;
		
		template <typename If, typename Then, typename Else>
		using Conditional = typename std::conditional<If::value, Then, Else>::type;
		
		template <typename... T>
		struct all : Bool<true> {};
		template <typename Head, typename... Tail>
		struct all<Head, Tail...> : Conditional<
			Head,
			all<Tail...>,
			Bool<false>>
		{};
	}
	
	template<typename T>
	struct null_precondition
	{
		void operator()(const T&)
		{
			
		}
	};
	
	template<typename Tag, typename T, typename Precondition = null_precondition<T>>
	class strong_typedef
	{
	private:
		T value;
	public:
		template<typename... Args, typename std::enable_if<
			!detail::is_related<strong_typedef<Tag, T>, Args...>::value
		>::type* = nullptr>
		strong_typedef(Args&&... args) :
			value(std::forward<Args>(args)...)	
		{
			Precondition()(value);
		}
		
		T get() const
		{
			return value;
		}
		
		explicit operator T() const
		{
			return get();
		}
	};
}

#define WIERTLO_STRONG_TYPEDEF(what, ...) struct what : wiertlo::strong_typedef<what, __VA_ARGS__> { using wiertlo::strong_typedef<what, __VA_ARGS__>::strong_typedef; }

#define WIERTLO_STRONG_TYPEDEF_WITH_PRECONDITION(what, precondition_functor, ...) struct what : wiertlo::strong_typedef<what, __VA_ARGS__, precondition_functor> { using wiertlo::strong_typedef<what, __VA_ARGS__, precondition_functor>::strong_typedef; }

#endif