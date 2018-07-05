#ifndef HEADER33D6765669F0421B9D414D8F0D0830D4
#define HEADER33D6765669F0421B9D414D8F0D0830D4

#include <cassert>
#include <cstdint>
#include <utility>
#include <type_traits>

namespace wiertlo
{
	namespace detail
	{
		// http://stackoverflow.com/a/1898487/1012936
		template<typename T>
		bool is_aligned(T* ptr, std::size_t alignment)
		{
			auto intp = reinterpret_cast<uintptr_t>(reinterpret_cast<void*>(ptr));
			return intp % alignment == 0;
		}
	}

	template<typename T, typename U, typename... Args>
	T* construct(U ptr, Args&&... args)
	{
		assert(detail::is_aligned(ptr, alignof(T)));
		// avoid issues mentioned in http://www.reddit.com/r/cpp/comments/1tedni/notsocommon_pitfalls_of_c_xpost_rcplusplus/ce7bqnu
		return ::new(static_cast<void*>(ptr)) T(std::forward<Args>(args)...);
	}
}
#endif