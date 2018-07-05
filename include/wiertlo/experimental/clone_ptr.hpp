#pragma once

#include <tuple>

namespace wiertlo
{
	template<typename T>
	struct default_cloner
	{
		T* operator()(T* other)
		{

		}
	};

	namespace detail
	{
		template<typename Deleter>
		struct pointer
		{

		};
	}

	template<typename T, typename Cloner, typename Deleter>
	class clone_ptr
	{
	public:
		typedef T element_type;
		typedef typename detail::pointer<>::type pointer;
		typedef Deleter deleter_type;
		typedef Cloner cloner_type;
	private:

	public:
	};
}