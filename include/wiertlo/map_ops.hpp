#include <utility>
#include <type_traits>

namespace wiertlo
{
	template<
		typename SomeFunction,
		typename NoneFunction>
	auto make_at_function(SomeFunction s, NoneFunction n)
	{
		return [some = std::move(s), none = std::move(n)](auto&& map, auto&& key, auto&&... rest) -> decltype(auto)
		{
			auto it = map.find(std::forward<decltype(key)>(key));
			return (it != map.end()) ? 
				some(*it, std::forward<decltype(rest)>(rest)...) :
				none(std::forward<decltype(rest)>(rest)...);
		};
	}

	/*static const auto value_or = make_at_function(
		[](auto&& key, auto&& other){ return key.second; },
		[](auto&& other){ return other; });*/

	template<typename KeyValuePair>
	typename KeyValuePair::first_type& key(KeyValuePair& kvp)
	{
		return kvp.first;
	}

	template<typename KeyValuePair>
	const typename KeyValuePair::first_type& key(const KeyValuePair& kvp)
	{
		return kvp.first;
	}

	template<typename KeyValuePair>
	void key(const KeyValuePair&& kvp) = delete;

	template<typename KeyValuePair>
	typename KeyValuePair::second_type& value(KeyValuePair& kvp)
	{
		return kvp.second;
	}

	template<typename KeyValuePair>
	const typename KeyValuePair::second_type& value(const KeyValuePair& kvp)
	{
		return kvp.second;
	}

	template<typename KeyValuePair>
	void value(const KeyValuePair&& kvp) = delete;

	// pair_param_adapter
	// idea taken from http://stackoverflow.com/a/36552463/1012936
	// adapted to C++11, and renamed

	namespace detail
	{
		template<typename UnaryFunction>
		class pair_param_adapter
		{
		private:
			UnaryFunction f;
		public:
			template<typename Arg>
			auto operator()(Arg&& arg) -> decltype(f(arg.first, arg.second))
			{
				return f(arg.first, arg.second);
			}

			template<typename Arg>
			pair_param_adapter(Arg&& arg) :
				f(std::forward<Arg>(arg))
			{

			}
		};
	}

	template<typename T>
	detail::pair_param_adapter<T> pair_param_fn(const T& fun)
	{
		return detail::pair_param_adapter<T>(fun);
	}
}