#ifndef WIERTLO_ENUM_INCLUDED
#define WIERTLO_ENUM_INCLUDED

#include <vector>
#include <functional>
#include <initializer_list>
#include <map>
#include <cstddef>
#include <iterator>
#include <cassert>
#if __cpp_lib_experimental_string_view > 201411 && defined(WIERTLO_ENUM_USE_EXPERIMENTAL_STRING_VIEW)
#include <experimental/string_view>
#endif
#include <string>

namespace wiertlo
{
	namespace detail
	{
		namespace enumeration
		{
			template<typename T>
			constexpr T sum(T value)
			{
				return value;
			}

			template<typename T, typename... U>
			constexpr T sum(T head, U... tail)
			{
				return head + sum(tail...);
			}

			struct indirect_less
			{
				template<typename T, typename U>
				bool operator()(const T& lhs, const U& rhs) const
				{
					return *lhs < *rhs;
				}
			};

			template<typename T>
			struct self_referring_handle
			{
				const void* handle;

				friend bool operator==(const self_referring_handle& lhs, const self_referring_handle& rhs)
				{
					return lhs.handle == rhs.handle;
				}

				friend bool operator!=(const self_referring_handle& lhs, const self_referring_handle& rhs)
				{
					return !(lhs == rhs);
				}

				friend bool operator<(const self_referring_handle& lhs, const self_referring_handle& rhs)
				{
					return std::less<const void*>()(lhs.handle, rhs.handle);
				}

				friend bool operator>(const self_referring_handle& lhs, const self_referring_handle& rhs)
				{
					return rhs < lhs;
				}

				friend bool operator<=(const self_referring_handle& lhs, const self_referring_handle& rhs)
				{
					return !(rhs < lhs);
				}

				friend bool operator>=(const self_referring_handle& lhs, const self_referring_handle& rhs)
				{
					return !(lhs < rhs);
				}

				self_referring_handle()
				{
					handle = this;
				}
			};

			template<typename T>
			class indirect_iterator : public std::iterator<std::forward_iterator_tag, typename T::value_type, std::ptrdiff_t, const T*, const T&>
			{
			private:
				typename T::const_iterator impl_it;
			public:
				auto operator*() const -> decltype(**impl_it) { return **impl_it; }
				auto operator->() const -> decltype(*impl_it) { return *impl_it; }
				indirect_iterator& operator++() { ++impl_it; return *this; }
				indirect_iterator operator++(int) { indirect_iterator it(impl_it); ++impl_it; return it; }

				friend bool operator==(const indirect_iterator& lhs, const indirect_iterator<T>& rhs)
				{
					return lhs.impl_it == rhs.impl_it;
				}

				friend bool operator!=(const indirect_iterator& lhs, const indirect_iterator<T>& rhs)
				{
					return !(lhs == rhs);
				}

				indirect_iterator(typename T::const_iterator it) : impl_it(it) {}
			};

			template<typename T>
			class indirect_range
			{
			private:
				const T* cont;
			public:
				indirect_range(const T* cont) : cont(cont) {}

				indirect_iterator<T> begin()
				{
					return indirect_iterator<T>(cont->begin());
				}

				indirect_iterator<T> end()
				{
					return indirect_iterator<T>(cont->end());
				}				
			};

			#if __cpp_lib_experimental_string_view > 201411 && defined(WIERTLO_ENUM_USE_EXPERIMENTAL_STRING_VIEW)
			using string_type = std::experimental::string_view;
			#else
			using string_type = std::string;
			#endif
		}
	}
}

#endif