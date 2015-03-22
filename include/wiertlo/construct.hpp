#ifndef HEADER33D6765669F0421B9D414D8F0D0830D4
#define HEADER33D6765669F0421B9D414D8F0D0830D4

namespace wiertlo
{
	template<typename T, typename U, typename... Args>
	T* construct(U ptr, Args&&... args)
	{
		static_assert(std::is_same<U, void*>::value or std::is_same<U, char*>::value, "must be void* or char*");
		return ::new(static_cast<void*>(ptr)) T(std::forward<Args>(args)...);
	}
}
#endif