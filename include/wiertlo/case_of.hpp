#ifndef HEADER7A125617CA5A44DCA71D25A7247AAC5B
#define HEADER7A125617CA5A44DCA71D25A7247AAC5B

#include <type_traits>
#include <functional>

namespace wiertlo
{
	namespace detail
	{
		template<typename V, typename P, typename F>
		struct case_of_impl
		{
			V value;
			P binary_predicate;
			F function;

			typedef std::false_type is_default_case;
		};

		template<typename F>
		struct default_case_impl
		{
			F function;

			typedef std::true_type is_default_case;
		};
	}

	template<typename V>
	bool switch_on(V&& value)
	{
		return false;
	}

	template<typename V1, typename P, typename V2, typename F, typename... Args>
	bool switch_on(V1&& value, const detail::case_of_impl<V2, P, F>& c, Args&&... args)
	{
		if(c.binary_predicate(value, c.value))
		{
			c.function();
			return true;
		}
		else
		{
			return switch_on(std::forward<V1>(value), std::forward<Args>(args)...);
		}
	}

	template<template <typename> class P, typename F, typename V>
	detail::case_of_impl<V, P<V>, F> case_of(V&& v, F&& f)
	{
		detail::case_of_impl<V, P<V>, F> ret = { std::forward<V>(v), P<V>(), std::forward<F>(f) };
		return ret;
	}

	template<typename P, typename F, typename V>
	detail::case_of_impl<V, P, F> case_of(V&& v, F&& f)
	{
		detail::case_of_impl<V, P, F> ret = { std::forward<V>(v), P(), std::forward<F>(f) };
		return ret;
	}

	template<typename F, typename V>
	detail::case_of_impl<V, std::equal_to<V>, F> case_of(V&& v, F&& f)
	{
		detail::case_of_impl<V, std::equal_to<V>, F> ret = { std::forward<V>(v), std::equal_to<V>(), std::forward<F>(f) };
		return ret;
	}

	template<typename F>
	detail::default_case_impl<F> on_default(F&& f)
	{
		detail::default_case_impl<F> ret = { std::forward<F>(f) };
		return ret;
	}
}

#endif