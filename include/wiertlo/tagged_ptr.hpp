#ifndef HEADER79eadc0e32bf6af9915500e3b8b5fc03
#define HEADER79eadc0e32bf6af9915500e3b8b5fc03 

#include <cstdint>
#include <cstddef>
#include <cassert>
#include <utility>
#include <functional>
#include <type_traits>

namespace wiertlo
{
	template<typename T>
	class tagged_ptr
	{
	public:
		static const int max_tag_value = alignof(T)-1;
		static const int min_tag_value = 0;
		typedef T element_type;
		typedef element_type* pointer;
	private:
		std::uintptr_t ptr_;
		static const std::uintptr_t tag_mask = max_tag_value;
		static const std::uintptr_t ptr_mask = static_cast<std::uintptr_t>(~tag_mask);

		static void check_fundamental_class_assumptions(pointer p)
		{
			auto nullp = reinterpret_cast<std::uintptr_t>(static_cast<T*>(nullptr));
			auto a = reinterpret_cast<std::uintptr_t>(p);
			auto b = reinterpret_cast<std::uintptr_t>(p+1);
			std::size_t alignment = alignof(T);

			assert(a < b);
			assert(a % alignment == 0 && b % alignment == 0 && nullp % alignment == 0);
			auto not_overflowed_sum = [](std::uintptr_t a, std::uintptr_t b)
			{
				std::uintptr_t sum = a+b;
				return sum >= a || sum >= b;
			};
			assert(not_overflowed_sum(a, max_tag_value) && not_overflowed_sum(b, max_tag_value) && not_overflowed_sum(nullp, max_tag_value));
			auto do_tags_work = [](std::uintptr_t a)
			{
				auto ptr = a | static_cast<std::uintptr_t>(max_tag_value);
				return ((ptr & ptr_mask) == a) && ((ptr & tag_mask) == max_tag_value);
			};
			assert(do_tags_work(a) && do_tags_work(b) && do_tags_work(nullp));
		}

		bool is_valid_tag(int the_tag)
		{
			return the_tag >= min_tag_value && the_tag <= max_tag_value;
		}

		std::uintptr_t getint() const
		{
			return ptr_ & ptr_mask;
		}

	public:
		void reset(pointer ptr = pointer())
		{
			int t = tag();
			ptr_ = ptr;
			set_tag(t);
		}

		T* get() const
		{
			return reinterpret_cast<T*>(getint());
		}

		T& operator*() const
		{
			return *get();
		}

		T* operator->() const
		{
			return get();
		}

		void swap(tagged_ptr& other)
		{
			std::swap(this->ptr_, other.ptr_);
		}

		explicit operator bool() const
		{
			return get() != nullptr;
		}

		tagged_ptr(pointer p = nullptr, int new_tag = 0)
		{
			assert(is_valid_tag(new_tag));
			check_fundamental_class_assumptions(p);
			auto a = reinterpret_cast<std::uintptr_t>(p);
			ptr_ = a | static_cast<std::uintptr_t>(new_tag);
		}

		tagged_ptr(tagged_ptr p, int new_tag)
		{
			assert(is_valid_tag(new_tag));
			ptr_ = p.ptr_;
			set_tag(new_tag);
		}

		int tag() const
		{
			return ptr_ & tag_mask;
		}

		int set_tag(int new_tag)
		{
			assert(is_valid_tag(new_tag));
			auto t = static_cast<std::uintptr_t>(new_tag);
			ptr_ = getint() | t;
			return new_tag;
		}
	};

	template<typename T, typename U>
	bool operator==(tagged_ptr<T> lhs, tagged_ptr<U> rhs)
	{
		return lhs.get() == rhs.get();
	}

	template<typename T, typename U>
	bool operator!=(tagged_ptr<T> lhs, tagged_ptr<U> rhs)
	{
		return lhs.get() != rhs.get();
	}

	template<typename T, typename U>
	bool operator<(tagged_ptr<T> lhs, tagged_ptr<U> rhs)
	{
		typedef typename std::common_type<typename tagged_ptr<T>::pointer, typename tagged_ptr<U>::pointer>::type CT;
		return std::less<CT>()(lhs.get(), rhs.get());
	}

	template<typename T, typename U>
	bool operator>(tagged_ptr<T> lhs, tagged_ptr<U> rhs)
	{
		return rhs < lhs;
	}

	template<typename T, typename U>
	bool operator<=(tagged_ptr<T> lhs, tagged_ptr<U> rhs)
	{
		return !(rhs < lhs);
	}

	template<typename T, typename U>
	bool operator>=(tagged_ptr<T> lhs, tagged_ptr<U> rhs)
	{
		return !(lhs < rhs);
	}

	template<typename T>
	bool operator==(std::nullptr_t, tagged_ptr<T> rhs)
	{
		return !rhs;
	}

	template<typename T>
	bool operator==(tagged_ptr<T> lhs, std::nullptr_t)
	{
		return !lhs;
	}

	template<typename T>
	bool operator!=(std::nullptr_t, tagged_ptr<T> rhs)
	{
		return static_cast<bool>(rhs);
	}

	template<typename T>
	bool operator!=(tagged_ptr<T> lhs, std::nullptr_t)
	{
		return static_cast<bool>(lhs);
	}

	template<typename T>
	bool operator<(tagged_ptr<T> lhs, std::nullptr_t)
	{
		return std::less<typename tagged_ptr<T>::pointer>()(lhs.get(), nullptr);
	}

	template<typename T>
	bool operator<(std::nullptr_t, tagged_ptr<T> rhs)
	{
		return std::less<typename tagged_ptr<T>::pointer>()(nullptr, rhs.get());
	}

	template<typename T>
	bool operator>(tagged_ptr<T> lhs, std::nullptr_t)
	{
		return !(nullptr < lhs);
	}

	template<typename T>
	bool operator>(std::nullptr_t, tagged_ptr<T> rhs)
	{
		return !(rhs < nullptr);
	}
	template<typename T>
	bool operator<=(tagged_ptr<T> lhs, std::nullptr_t)
	{
		return nullptr < lhs;
	}

	template<typename T>
	bool operator<=(std::nullptr_t, tagged_ptr<T> rhs)
	{
		return rhs < nullptr;
	}

	template<typename T>
	bool operator>=(tagged_ptr<T> lhs, std::nullptr_t)
	{
		return !(lhs < nullptr);
	}

	template<typename T>
	bool operator>=(std::nullptr_t, tagged_ptr<T> rhs)
	{
		return !(nullptr < rhs);
	}
}

#endif