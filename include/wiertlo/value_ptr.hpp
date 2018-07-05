#ifndef HEADER1ade0fefcfa049d1b27597bcd5a355e2
#define HEADER1ade0fefcfa049d1b27597bcd5a355e2

#include <memory>

namespace wiertlo
{
template<typename T>
struct new_cloner
{
	T* operator()(T* p)
	{
		return new T(*p);
	}
};


template<typename T, typename Cloner = new_cloner<T>, typename Deleter = std::default_delete<T>>
class value_ptr : public std::unique_ptr<T, Deleter>
{
public:
	using std::unique_ptr<T, Deleter>::unique_ptr;

	value_ptr(const value_ptr& b) :
		std::unique_ptr<T, Deleter>(Cloner()(b.get()))
	{
		
	}

	value_ptr(value_ptr&& b) :
		std::unique_ptr<T, Deleter>(std::move(static_cast<std::unique_ptr<T, Deleter>&>(b)))
	{
		
	}

	value_ptr& operator=(const value_ptr& b)
	{
		static_cast<std::unique_ptr<T, Deleter>&>(*this).reset(Cloner()(b.get()));
		return *this;
	}

	value_ptr& operator=(value_ptr&& b)
	{
		static_cast<std::unique_ptr<T, Deleter>&>(*this) = std::move(static_cast<std::unique_ptr<T, Deleter>&>(b));
		return *this;
	}

	~value_ptr() = default;
};
}

#endif