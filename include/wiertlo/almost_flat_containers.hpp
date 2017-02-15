#ifndef headerBB09D819199646B7BF083F0B0935C900
#define headerBB09D819199646B7BF083F0B0935C900

#include <initializer_list>
#include <memory>
#include <iterator>
#include <vector>
#include <algorithm>

namespace wiertlo
{
	template<typename T, typename Compare, typename Allocator, typename UniqueTag>
	class flat_base
	{
	public:
		typedef T value_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef Allocator allocator_type;
		typedef typename std::allocator_traits<Allocator>::pointer pointer;
		typedef typename std::allocator_traits<Allocator>::const_pointer const_pointer;
		typedef value_type* iterator;
		typedef const value_type* const_iterator;
		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
	private:
		typedef std::vector<T> underlying_container;
		underlying_container data;
		typename underlying_container::size_type divider;
	public:
		typedef typename underlying_container::size_type size_type;
		typedef typename underlying_container::difference_type difference_type;
		void reorganize()
		{
			std::inplace_merge(data.begin(), data.begin() + divider, data.end());
			divider = data.size();
		}
		
		explicit flat_base(
			const Compare& comp,
			const Allocator& alloc = Allocator())
		{
			
		}
		
		flat_base() : flat_base(Compare()) {}
		
		explicit flat_base(const Allocator& alloc)
		{
			
		}
		
		template<typename InputIterator>
		flat_base(
			InputIterator first,
			InputIterator last,
			const Compare& comp = Compare(),
			const Allocator& alloc = Allocator())
		{
			
		}
		
		template<typename InputIterator>
		flat_base(
			InputIterator first,
			InputIterator last,
			const Allocator& alloc)
		{
			
		}
		
		flat_base(const flat_base& other, const Allocator& alloc)
		{
			
		}
		
		flat_base(flat_base&& other, const Allocator& alloc)
		{
			
		}
		
		flat_base(
			std::initializer_list<value_type> init,
			const Compare& comp = Compare(),
			const Allocator& alloc = Allocator())
		{
			
		}
		
		flat_base(
			std::initializer_list<value_type> init,
			const Allocator& alloc)
		{
			
		}
		
		flat_base& operator=(const flat_base& other) = default;
		flat_base& operator=(flat_base&& other) = default;
		flat_base& operator=(std::initializer_list<value_type> ilist)
		{
			
			return *this;
		}
		
		allocator_type get_allocator() const
		{
			
		}
		
		bool empty() const
		{
			return data.size();
		}
		
		size_type size() const
		{
			return data.size();
		}
		
		size_type max_size() const
		{
			return data.max_size();
		}
		
		void clear()
		{
			data.clear();
			divider = 0;
		}
		
		void swap(flat_base& other)
		{
			return 
		}
	};
}
#endif