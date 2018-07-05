#ifndef HEADER6a2f8a3f2a944076f96c21d3199b9b86
#define HEADER6a2f8a3f2a944076f96c21d3199b9b86

#include <memory>
#include <utility>

namespace wiertlo
{
	struct default_tag {};

	template<typename T, typename StrongTypedefTag = ::wiertlo::default_tag>
	class store_reference_wrapper
	{
		T* ptr;

	public:
		typedef T type;

		explicit store_reference_wrapper(T& arg) :
			ptr(::std::addressof(arg))
		{

		}

		explicit store_reference_wrapper(T&& arg) = delete;

		T& get()
		{
			return *ptr;
		}

		const T& get() const
		{
			return *ptr;
		}
	};

	template<typename T>
	store_reference_wrapper<T> store_ref(T& arg)
	{
		return store_reference_wrapper<T>(arg);
	}

	template<typename T>
	store_reference_wrapper<const T> store_cref(const T& arg)
	{
		return store_reference_wrapper<const T>(arg);
	}
}

#endif