#ifndef HEADER7A125617CA5A44DCA71D25A7247AAC5B
#define HEADER7A125617CA5A44DCA71D25A7247AAC5B

#include <functional>
#include <tuple>

namespace wiertlo
{
	template<typename V>
	bool switch_on(const V& value)
	{
		return false;
	}

	template<typename V, typename P, typename... Args>
	bool switch_on(const V& value, const P& p, Args... args)
	{
		if(std::get<0>(p)(value, std::get<1>(p)))
		{
			std::get<2>(p)();
			return true;
		}
		else
		{
			return switch_on(value, args...);
		}
	}

	template<template <typename> class P, typename F, typename V >
	auto case_of(const V& v, const F& p) -> decltype( std::make_tuple(P<V>(), v, p) )
	{
		return std::make_tuple(P<V>(), v, p);
	}

	template<typename P, typename F, typename V >
	auto case_of(const V& v, const F& p) -> decltype( std::make_tuple(P(), v, p) )
	{
		return std::make_tuple(P(), v, p);
	}

	template<typename F, typename V >
	auto case_of(const V& v, const F& p) -> decltype( std::make_tuple(std::equal_to<V>(), v, p) )
	{
		return std::make_tuple(std::equal_to<V>(), v, p);
	}
}

#endif