#ifndef HEADERbcff4ce395e0d2912672be5dd8bf2dc0
#define HEADERbcff4ce395e0d2912672be5dd8bf2dc0

#include <utility>
#include <memory>
#include <array>
#include <type_traits>

namespace wiertlo
{
	namespace detail
	{
		template<typename T>
		struct SuppressTemplateDeduction
		{
			typedef T type;
		};

		template<typename T>
		struct DependentFalse
		{
			static const bool value = false;
		};
	}

	template<typename T, typename... Args>
	T make(Args&&... args)
	{
		return T(std::forward<Args>(args)...);
	}

	template<typename T, typename... Args>
	std::array<T, sizeof...(Args)> make_array(Args&&... args)
	{
		std::array<T, sizeof...(Args)> arr = { std::forward<T>(args)... };
		return arr;
	}

	template<typename T, typename... Args, typename std::enable_if<!std::is_array<T>::value>::type* = nullptr>
	std::unique_ptr<T> make_unique(Args&&... args)
	{
		return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
	}

	template<typename T, typename std::enable_if<std::is_array<T>::value && std::extent<T>::value == 0>::type* = nullptr>
	std::unique_ptr<typename std::remove_extent<T>::type[]> make_unique(std::size_t size)
	{
		return std::unique_ptr<typename std::remove_extent<T>::type[]>(new typename std::remove_extent<T>::type[size]());
	}

	template<typename T, typename std::enable_if<std::is_array<T>::value && std::extent<T>::value != 0>::type* = nullptr>
	void make_unique(std::size_t size)
	{
		static_assert(detail::DependentFalse<T>::value, "wiertlo::make_unique of array with a known bound is disallowed");
	}

	// make_shared is declared for symmetry with make_unique
	template<typename T, typename... Args>
	std::shared_ptr<T> make_shared(Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
	
}

#endif