#ifndef HEADER46c671a6a8fa84336f9a3d49dde94a2f
#define HEADER46c671a6a8fa84336f9a3d49dde94a2f

#include <utility>
#include <type_traits>

namespace wiertlo
{
	namespace detail
	{
		template<typename T>
		struct Lazy
		{
			typedef T type;
		};

		template<typename... Args>
		struct VariadicConditional;

		template<>
		struct VariadicConditional<> {};

		template<typename Condition, typename Type, typename... Rest>
		struct VariadicConditional<Condition, Type, Rest...> : std::conditional<
				Condition::value,
				Lazy<Type>,
				VariadicConditional<Rest...>
			>::type
		{

		};

		template<typename T>
		struct is_nonown_ptr_obj : std::false_type
		{

		};

		template<typename Derived, typename T>
		struct nonown_ptr_common
		{
		protected:
			T* ptr;
		public:
			typedef T* pointer;
			typedef T element_type;

			void swap(Derived& other)
			{
				std::swap(this->ptr, other.ptr);
			}

			pointer get() const
			{
				return ptr;
			}

			explicit operator bool() const
			{
				return get() != nullptr;
			}
		};

		template<typename Derived, typename T>
		struct nonown_ptr_data : nonown_ptr_common<nonown_ptr_data<Derived, T>, T>
		{
			template<typename U,
			         typename std::enable_if<std::is_pointer<U>::value && std::is_convertible<U, T*>::value>::type* = nullptr>
			void reset(U p)
			{
				this->ptr = std::forward<U>(p);
			}

			template<typename U,
			         typename std::enable_if<std::is_pointer<U>::value && std::is_convertible<U, T*>::value>::type* = nullptr>
			nonown_ptr_data(U&& p)
			{
				reset(std::forward<U>(p));
			}

			template<typename U,
			         typename std::enable_if<detail::is_nonown_ptr_obj<U>::value && std::is_convertible<typename U::pointer, T*>::value && !std::is_same<typename U::pointer, T*>::value>::type* = nullptr>
			nonown_ptr_data(U other)
			{
				reset(other.get());
			}

			template<typename U,
			         typename std::enable_if<detail::is_nonown_ptr_obj<U>::value && std::is_convertible<typename U::pointer, T*>::value && !std::is_same<typename U::pointer, T*>::value>::type* = nullptr>
			Derived& operator=(U other)
			{
				reset(other.get());
				return static_cast<Derived&>(*this);
			}

			void reset(std::nullptr_t = nullptr)
			{
				this->ptr = nullptr;
			}

			nonown_ptr_data(std::nullptr_t = nullptr)
			{
				this->ptr = nullptr;
			}
		};

		template<typename Derived, typename T>
		struct nonown_ptr_object : nonown_ptr_data<nonown_ptr_object<Derived, T>, T>
		{
			using nonown_ptr_data<nonown_ptr_object<Derived, T>, T>::nonown_ptr_data;

			T& operator*() const
			{
				return *this->get();
			}

			T* operator->() const
			{
				return this->get();
			}
		};

		template<typename Derived, typename T>
		struct nonown_ptr_array : nonown_ptr_common<nonown_ptr_array<Derived, T>, T>
		{
			T& operator[](std::size_t index) const
			{
				return this->get()[index];
			}

			template<typename U,
			         typename std::enable_if<std::is_same<typename std::remove_cv<T>::type, std::nullptr_t>::value || std::is_same<U, T*>::value>::type* = nullptr>
			void reset(U p = nullptr)
			{
				this->ptr = p;
			}
			
			template<typename U,
			         typename std::enable_if<std::is_same<typename std::remove_cv<T>::type, std::nullptr_t>::value || std::is_same<U, T*>::value>::type* = nullptr>
			nonown_ptr_array(U p = nullptr)
			{
				reset(p);
			}

			friend Derived& operator+=(Derived& lhs, std::ptrdiff_t rhs)
			{
				lhs->ptr += rhs;
				return lhs;
			}

			friend Derived& operator-=(Derived& lhs, std::ptrdiff_t rhs)
			{
				lhs->ptr -= rhs;
				return lhs;
			}

			friend Derived operator+(Derived lhs, std::ptrdiff_t rhs)
			{
				return Derived(lhs->ptr + rhs);
			}

			friend Derived operator-(Derived lhs, std::ptrdiff_t rhs)
			{
				return Derived(lhs->ptr - rhs);
			}

			friend Derived operator-(Derived lhs, Derived rhs)
			{
				return Derived(lhs->ptr - rhs->ptr);
			}
		};

		template<typename Derived, typename T>
		using nonown_ptr_conditional = typename VariadicConditional<
			std::integral_constant<bool, std::is_array<T>::value && std::extent<T>::value == 0>,
			detail::Lazy<
				nonown_ptr_array<
					Derived,
					typename std::remove_extent<T>::type>>,
			std::integral_constant<bool, std::is_object<T>::value>,
			detail::Lazy<
				nonown_ptr_object<
					Derived,
					T>>,
			std::integral_constant<bool, std::is_void<T>::value>,
			detail::Lazy<
				nonown_ptr_data<
					Derived,
					T>>>::type::type;
	}

	template<typename T>
	class nonown_ptr : public detail::nonown_ptr_conditional<nonown_ptr<T>, T>
	{
		using detail::nonown_ptr_conditional<nonown_ptr<T>, T>::nonown_ptr_conditional;
	};

	template<typename T, typename U>
	bool operator==(nonown_ptr<T> lhs, nonown_ptr<U> rhs)
	{
		return lhs.get() == rhs.get();
	}

	template<typename T, typename U>
	bool operator!=(nonown_ptr<T> lhs, nonown_ptr<U> rhs)
	{
		return lhs.get() != rhs.get();
	}

	template<typename T, typename U>
	bool operator<(nonown_ptr<T> lhs, nonown_ptr<U> rhs)
	{
		typedef typename std::common_type<typename nonown_ptr<T>::pointer, typename nonown_ptr<U>::pointer>::type CT;
		return std::less<CT>()(lhs.get(), rhs.get());
	}

	template<typename T, typename U>
	bool operator>(nonown_ptr<T> lhs, nonown_ptr<U> rhs)
	{
		return rhs < lhs;
	}

	template<typename T, typename U>
	bool operator<=(nonown_ptr<T> lhs, nonown_ptr<U> rhs)
	{
		return !(rhs < lhs);
	}

	template<typename T, typename U>
	bool operator>=(nonown_ptr<T> lhs, nonown_ptr<U> rhs)
	{
		return !(lhs < rhs);
	}

	template<typename T>
	bool operator==(std::nullptr_t, nonown_ptr<T> rhs)
	{
		return !rhs;
	}

	template<typename T>
	bool operator==(nonown_ptr<T> lhs, std::nullptr_t)
	{
		return !lhs;
	}

	template<typename T>
	bool operator!=(std::nullptr_t, nonown_ptr<T> rhs)
	{
		return static_cast<bool>(rhs);
	}

	template<typename T>
	bool operator!=(nonown_ptr<T> lhs, std::nullptr_t)
	{
		return static_cast<bool>(lhs);
	}

	template<typename T>
	bool operator<(nonown_ptr<T> lhs, std::nullptr_t)
	{
		return std::less<typename nonown_ptr<T>::pointer>()(lhs.get(), nullptr);
	}

	template<typename T>
	bool operator<(std::nullptr_t, nonown_ptr<T> rhs)
	{
		return std::less<typename nonown_ptr<T>::pointer>()(nullptr, rhs.get());
	}

	template<typename T>
	bool operator>(nonown_ptr<T> lhs, std::nullptr_t)
	{
		return !(nullptr < lhs);
	}

	template<typename T>
	bool operator>(std::nullptr_t, nonown_ptr<T> rhs)
	{
		return !(rhs < nullptr);
	}
	template<typename T>
	bool operator<=(nonown_ptr<T> lhs, std::nullptr_t)
	{
		return nullptr < lhs;
	}

	template<typename T>
	bool operator<=(std::nullptr_t, nonown_ptr<T> rhs)
	{
		return rhs < nullptr;
	}

	template<typename T>
	bool operator>=(nonown_ptr<T> lhs, std::nullptr_t)
	{
		return !(lhs < nullptr);
	}

	template<typename T>
	bool operator>=(std::nullptr_t, nonown_ptr<T> rhs)
	{
		return !(nullptr < rhs);
	}

	namespace detail
	{
		template<typename T>
		struct is_nonown_ptr_obj<::wiertlo::nonown_ptr<T[]>> : std::false_type
		{
			
		};

		template<typename T>
		struct is_nonown_ptr_obj<::wiertlo::nonown_ptr<T>> : std::true_type
		{
			
		};
	}
}

#endif