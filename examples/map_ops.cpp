#include <iostream>
#include <map>
#include <type_traits>
#include <boost/optional.hpp>
#include <experimental/optional>
#include <wiertlo/map_ops.hpp>

// use boost::optional
static const auto at = wiertlo::make_at_function(
	[](auto&& key){ return boost::optional<decltype(key)>(std::forward<decltype(key)>(key)); },
	[](){ return boost::none; });

// use std::experimental::optional
static const auto atexp = wiertlo::make_at_function(
	[](auto&& key){ return std::experimental::make_optional(std::forward<decltype(key)>(key)); },
	[](){ return std::experimental::nullopt; });

int main()
{
	std::map<int, int> m;
	m.emplace(4,5);
	m.emplace(35,10);

	// boost::optional
	// needs Boost, can handle references
	if(auto kv = at(m, 4))
	{
		using wiertlo::key;
		using wiertlo::value;
		std::cout << key(*kv) << " " << value(*kv) << "\n";
		value(*kv) = 42;
		std::cout << key(*kv) << " " << value(*at(m, 4)) << "\n";
	}
	if(!at(m, 5))
	{
		std::cout << "Not found\n";
	}

	// std::experimental::optional
	// doesn't support references
	if(auto kv = atexp(m, 4))
	{
		using wiertlo::key;
		using wiertlo::value;
		std::cout << key(*kv) << " " << value(*kv) << "\n";
	}
	if(!atexp(m, 5))
	{
		std::cout << "Not found\n";
	}
}