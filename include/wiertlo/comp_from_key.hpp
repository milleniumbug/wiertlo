#ifndef HEADER2029cab03db04a5eaeac0f9281b32f57
#define HEADER2029cab03db04a5eaeac0f9281b32f57

#include <functional>
#include <utility>

namespace wiertlo
{
	template<typename KeyFunction, typename CompFunction = std::less<>>
	auto comp_from_key(KeyFunction key, CompFunction comp = CompFunction())
	{
		return [key = std::move(key), comp = std::move(comp)](auto&& lhs, auto&& rhs)
		{
			return comp(key(std::forward<decltype(lhs)>(lhs)), key(std::forward<decltype(rhs)>(rhs)));
		};
	}
}

#endif