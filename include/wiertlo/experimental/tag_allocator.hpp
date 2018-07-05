#ifndef HEADER8f4e0e9a956e4889a9c7b1b26331172d
#define HEADER8f4e0e9a956e4889a9c7b1b26331172d

#include <memory>

namespace wiertlo
{
	namespace detail
	{
		template<typename T, typename... U>
		struct is_related : std::false_type {};

		template<typename T, typename U>
		struct is_related<T, U> : std::is_same<
			typename std::remove_cv<typename std::remove_reference<T>::type>::type,
			typename std::remove_cv<typename std::remove_reference<U>::type>::type
		>
		{

		};
	}

	// an allocator which does everything the same way the underlying allocator does,
	// but a provides a template parameter Tag, which can be used to 
	// make strict typedefs for arbitrary allocator aware container
	template<typename T, typename Tag, typename Allocator = std::allocator<T>>
	class tag_allocator : private Allocator
	{
		typedef std::allocator_traits<Allocator> UnderlyingTraits;

	public:
		typedef typename UnderlyingTraits::value_type value_type;
		typedef typename UnderlyingTraits::pointer pointer;
		typedef typename UnderlyingTraits::const_pointer const_pointer;
		typedef typename UnderlyingTraits::size_type size_type;
		typedef typename UnderlyingTraits::difference_type difference_type;
		typedef typename UnderlyingTraits::propagate_on_container_move_assignment propagate_on_container_move_assignment;
		typedef typename UnderlyingTraits::is_always_equal is_always_equal;

		template<typename U>
		struct rebind
		{
			// I spent 10 minutes on that `::template`
			typedef tag_allocator<U, Tag, typename UnderlyingTraits::template rebind_alloc<U>> other;
		};

		template<typename... Args, typename std::enable_if<!(
			detail::is_related<tag_allocator<T, Tag, Allocator>, Args...>::value
		)>::type* = nullptr>
		tag_allocator(Args&&... args) noexcept(std::is_nothrow_constructible<Allocator, Args...>::value) :
			Allocator(std::forward<Args>(args)...)
		{

		}

		#define WIERTLO_DETAIL_JUST_FUCKING_FORWARD_IT(name) \
		template<typename... Args> \
		auto name(Args&&... args) \
			noexcept(noexcept(UnderlyingTraits::name(std::declval<Allocator&>(), std::forward<Args>(args)...))) -> \
			decltype(UnderlyingTraits::name(std::declval<Allocator&>(), std::forward<Args>(args)...)) \
		{ \
			return UnderlyingTraits::name(*static_cast<Allocator*>(this), std::forward<Args>(args)...); \
		}

		WIERTLO_DETAIL_JUST_FUCKING_FORWARD_IT(allocate)
		WIERTLO_DETAIL_JUST_FUCKING_FORWARD_IT(deallocate)
		WIERTLO_DETAIL_JUST_FUCKING_FORWARD_IT(max_size)
		WIERTLO_DETAIL_JUST_FUCKING_FORWARD_IT(construct)
		WIERTLO_DETAIL_JUST_FUCKING_FORWARD_IT(destroy)

		#undef WIERTLO_DETAIL_JUST_FUCKING_FORWARD_IT

		friend bool operator==(const tag_allocator& lhs, const tag_allocator& rhs)
		{
			return *static_cast<const Allocator*>(std::addressof(lhs)) == *static_cast<const Allocator*>(std::addressof(rhs));
		}

		friend bool operator!=(const tag_allocator& lhs, const tag_allocator& rhs)
		{
			return !(lhs == rhs);
		}
	};
}
#endif