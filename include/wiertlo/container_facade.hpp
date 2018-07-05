#ifndef headerBB09D819199646B7BF083F0B0935C900
#define headerBB09D819199646B7BF083F0B0935C900

#include <initializer_list>
#include <memory>
#include <iterator>
#include <vector>
#include <type_traits>
#include <stdexcept>
#include <algorithm>
#include <limits>

namespace wiertlo
{
	// reversible trait for facades
	// Requires:
	// - Types::iterator must be Bidirectional
	// - const overloaded begin() and end() member functions
	template<typename Derived, typename Types>
	struct reversible
	{
		typedef std::reverse_iterator<typename Types::iterator> reverse_iterator;
		typedef std::reverse_iterator<typename Types::const_iterator> const_reverse_iterator;
		
		reverse_iterator rbegin()
		{
			auto self = static_cast<const Derived*>(this);
			return reverse_iterator(self->end());
		}
		
		const_reverse_iterator rbegin() const
		{
			auto self = static_cast<const Derived*>(this);
			return reverse_iterator(self->end());
		}
		
		const_reverse_iterator crbegin() const
		{
			auto self = static_cast<const Derived*>(this);
			return reverse_iterator(self->end());
		}
		
		reverse_iterator rend()
		{
			auto self = static_cast<Derived*>(this);
			return reverse_iterator(self->begin());
		}
		
		const_reverse_iterator rend() const
		{
			auto self = static_cast<const Derived*>(this);
			return reverse_iterator(self->begin());
		}
		
		const_reverse_iterator crend() const
		{
			auto self = static_cast<const Derived*>(this);
			return reverse_iterator(self->begin());
		}
	};
	
	// allocator support trait for facades
	// Requires:
	template<typename Derived, typename Types>
	struct allocator_aware
	{
		
	};
	
	// equality comparison support trait for facades
	template<typename Derived, typename Types>
	struct equality_comparable
	{
		friend bool operator==(
			const equality_comparable& lhs,
			const equality_comparable& rhs)
		{
			auto left = static_cast<const Derived*>(&lhs);
			auto right = static_cast<const Derived*>(&rhs);
			auto first1 = left->cbegin();
			auto first2 = right->cbegin();
			auto last1 = left->cend();
			auto last2 = right->cend();
			for(; bool(first1 != last1) && bool(first2 != last2); ++first1, void(), ++first2)
			{
				if(!(*first1 == *first2))
					return false;
			}
			return true;
		}
		
		friend bool operator!=(
			const equality_comparable& lhs,
			const equality_comparable& rhs)
		{
			return !(lhs == rhs);
		}
	};
	
	// comparable trait for facades
	template<typename Derived, typename Types>
	struct comparable
	{
		friend bool operator<(
			const comparable& lhs,
			const comparable& rhs)
		{
			auto&& left = static_cast<const Derived&>(lhs);
			auto&& right = static_cast<const Derived&>(rhs);
			return std::lexicographical_compare(
				left.begin(),
				left.end(),
				right.begin(),
				right.end());
		}
		
		friend bool operator>(
			const comparable& lhs,
			const comparable& rhs)
		{
			auto&& left = static_cast<const Derived&>(lhs);
			auto&& right = static_cast<const Derived&>(rhs);
			return right < left;
		}
		
		friend bool operator<=(
			const comparable& lhs,
			const comparable& rhs)
		{
			auto&& left = static_cast<const Derived&>(lhs);
			auto&& right = static_cast<const Derived&>(rhs);
			return !(left > right);
		}
		
		friend bool operator>=(
			const comparable& lhs,
			const comparable& rhs)
		{
			auto&& left = static_cast<const Derived&>(lhs);
			auto&& right = static_cast<const Derived&>(rhs);
			return !(left < right);
		}
	};
	
	// Requires:
	// - size_type size() const
	// - void emplace_back(Args&&... args)
	// - iterator erase_(const_iterator begin, const_iterator end)
	// - iterator insert_(const_iterator pos, InputIterator begin, InputIterator end)
	template<typename Derived, typename Types>
	struct resize_functionality
	{
		void resize(typename Types::size_type new_size)
		{
			auto self = static_cast<Derived*>(this);
			const auto old_size = self->size();
			if(new_size > old_size)
			{
				for(typename Types::size_type i = 0; i < new_size - old_size; ++i)
					self->emplace_back();
			}
			else if(new_size < old_size)
			{
				auto i = self->begin();
				std::advance(i, new_size);
				self->erase_(i, self->end());
			}
		}
		
		void resize(typename Types::size_type new_size, const typename Types::value_type& el)
		{
			auto self = static_cast<Derived*>(this);
			const auto old_size = self->size();
			if(new_size > old_size)
			{
				self->insert_(self->end(), new_size - old_size, el);
			}
			else if(new_size < old_size)
			{
				auto i = self->begin();
				std::advance(i, new_size);
				self->erase_(i, self->end());
			}
		}
	};
	
	// erase and clear functionality
	// Requires:
	// - iterator erase_(const_iterator begin, const_iterator end)
	template<typename Derived, typename Types>
	struct erase_modifiers
	{
		void clear()
		{
			auto self = static_cast<Derived*>(this);
			return self->erase(self->begin(), self->end());
		}
		
		typename Types::iterator erase(typename Types::const_iterator pos)
		{
			auto self = static_cast<Derived*>(this);
			return self->erase(pos, std::next(pos));
		}
		
		typename Types::iterator erase(typename Types::const_iterator begin, typename Types::const_iterator end)
		{
			auto self = static_cast<Derived*>(this);
			return self->erase_(begin, end);
		}
	};
	
	// size, empty, and max_size for facades
	template<typename Derived, typename Types>
	struct size_getters
	{
		bool empty() const
		{
			auto self = static_cast<const Derived*>(this);
			return self->begin() == self->end();
		}
		
		typename Types::size_type max_size() const
		{
			return std::numeric_limits<typename Types::size_type>::max();
		}
		
		typename Types::size_type size() const
		{
			auto self = static_cast<const Derived*>(this);
			return static_cast<typename Types::size_type>(std::distance(self->begin(), self->end()));
		}
	};
	
	// at and operator[] for facades
	// Requires:
	// - C::iterator must be RandomAccessIterator
	template<typename Derived, typename Types>
	struct random_accessible
	{
		typename Types::reference operator[](typename Types::size_type pos)
		{
			auto self = static_cast<Derived*>(this);
			return *(pos + self->begin());
		}
		
		typename Types::const_reference operator[](typename Types::size_type pos) const
		{
			return (*const_cast<random_accessible*>(this))[pos];
		}
		
		typename Types::reference at(typename Types::size_type pos)
		{
			auto self = static_cast<Derived*>(this);
			if(pos >= self->size())
				throw std::out_of_range(std::string(typeid(Derived).name()) + " out of range");
			return (*self)[pos];
		}
		
		typename Types::const_reference at(typename Types::size_type pos) const
		{
			return const_cast<random_accessible*>(this)->at(pos);
		}
	};
	
	// front() accessor for facades
	template<typename Derived, typename Types>
	struct front_accessible
	{
		typename Types::reference front()
		{
			auto self = static_cast<Derived*>(this);
			return self->begin();
		}
		
		typename Types::const_reference front() const
		{
			auto self = static_cast<const Derived*>(this);
			return self->begin();
		}
	};
	
	// support for appending and removing front element
	// Requires:
	// - void emplace_front(Args&&... args)
	// - void pop_front()
	template<typename Derived, typename Types>
	struct front_pushable
	{
		void push_front(const typename Types::value_type& val)
		{
			auto self = static_cast<Derived*>(this);
			self->emplace_front(val);
		}
		
		void push_front(typename Types::value_type&& val)
		{
			auto self = static_cast<Derived*>(this);
			self->emplace_front(std::move(val));
		}
	};
	
	// back() accessor for facades
	template<typename Derived, typename Types>
	struct back_accessible
	{
		typename Types::reference back()
		{
			auto self = static_cast<Derived*>(this);
			auto tmp = self->end(); --tmp; return *tmp;
		}
		
		typename Types::const_reference back() const
		{
			auto self = static_cast<Derived*>(this);
			auto tmp = self->end(); --tmp; return *tmp;
		}
	};
	
	// support for appending and removing last element
	// Requires:
	// - void emplace_back(Args&&... args)
	// - void pop_back()
	template<typename Derived, typename Types>
	struct back_pushable
	{
		void push_back(const typename Types::value_type& val)
		{
			auto self = static_cast<Derived*>(this);
			self->emplace_back(val);
		}
		
		void push_back(typename Types::value_type&& val)
		{
			auto self = static_cast<Derived*>(this);
			self->emplace_back(std::move(val));
		}
	};
	
	// Requires:
	// - void assign_(const_iterator pos, InputIterator begin, InputIterator end)
	template<typename Derived, typename Types>
	struct initializer_list_assignment
	{
		initializer_list_assignment& operator=(const initializer_list_assignment& other) = default;
		initializer_list_assignment& operator=(initializer_list_assignment&& other) = default;
		initializer_list_assignment& operator=(std::initializer_list<typename Types::value_type> ilist)
		{
			auto self = static_cast<Derived*>(this);
			self->assign_(ilist.begin(), ilist.end());
			return *this;
		}
	};
	
	// basic container facade
	// Requires:
	// (what's in container_facade)
	// - typedef ??? iterator;
	// - typedef ??? const_iterator
	// - iterator begin();
	// - const_iterator begin() const;
	// - iterator end();
	// - const_iterator end() const;
	// - default constructor
	// - Big Five
	// - typedef ??? value_type;
	template<typename Derived, typename Types, template<typename, typename> class... Traits>
	struct container_facade : public Traits<Derived, Types>...
	{
		
	};
	
	template<
		typename ValueType,
		typename Iterator,
		typename ConstIterator,
		typename SizeType = std::size_t,
		typename Reference = ValueType&,
		typename ConstReference = const ValueType&>
	class container
	{
	public:
		// TYPES
		typedef ValueType value_type;
		typedef Iterator iterator;
		typedef ConstIterator const_iterator;
		typedef Reference reference;
		typedef ConstReference const_reference;
		typedef SizeType size_type;
		typedef typename std::iterator_traits<Iterator>::difference_type difference_type;
		static_assert(std::is_convertible<iterator, const_iterator>::value, "iterator must be convertible to const_iterator");
	};
	
	// Requires:
	// - const overloaded begin() and end() member functions
	template<typename Derived, typename Types>
	struct const_iterator_getters
	{
		typename Types::const_iterator cbegin() const
		{
			auto self = static_cast<const Derived*>(this);
			return self->begin();
		}
		
		typename Types::const_iterator cend() const
		{
			auto self = static_cast<const Derived*>(this);
			return self->end();
		
		}
	};
	
	// Requires:
	// - noexcept move assignment operator
	template<typename Derived, typename Types>
	struct move_based_swap
	{
		void swap(Derived& other)
		{
			auto self = static_cast<Derived*>(this);
			std::swap(*self, other);
		}
	};
	
	template<typename T>
	class singleton_iterator
	{
		const T* val;
		std::size_t c;
	public:
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef value_type* pointer;
		typedef value_type& reference;
		typedef std::input_iterator_tag iterator_category;
		
		singleton_iterator() {}
		singleton_iterator(const T* val, std::size_t c) :
			val(val),
			c(c)
		{
			
		}
		
		friend bool operator==(const singleton_iterator& lhs, const singleton_iterator& rhs)
		{
			return lhs.c == rhs.c;
		}
		
		friend bool operator!=(const singleton_iterator& lhs, const singleton_iterator& rhs)
		{
			return !(lhs == rhs);
		}
		
		reference operator*() { return *val; }
		pointer operator->() { return *val; }
		
		singleton_iterator& operator++()
		{
			++c;
			return *this;
		}
		
		singleton_iterator operator++(int)
		{
			singleton_iterator temp = *this;
			++(*this);
			return temp;
		}
	};
	
	// enough for these purposes, also minimal effort required by C++ standard
	template<typename T>
	struct is_input_iterator : public std::integral_constant<bool, !std::is_integral<T>::value>
	{
		
	};
	
	// Requires:
	// - iterator insert_(const_iterator pos, InputIterator begin, InputIterator end)
	// - iterator emplace_(const_iterator pos, Args&&... args)
	template<typename Derived, typename Types>
	struct sequence_container_insert
	{
		typename Types::iterator insert(typename Types::const_iterator pos, const typename Types::value_type& v)
		{
			auto self = static_cast<Derived*>(this);
			return self->emplace(pos, v);
		}
		
		typename Types::iterator insert(typename Types::const_iterator pos, typename Types::value_type&& v)
		{
			auto self = static_cast<Derived*>(this);
			return self->emplace(pos, std::move(v));
		}
		
		typename Types::iterator insert(typename Types::const_iterator pos, typename Types::size_type count, const typename Types::value_type& value )
		{
			auto self = static_cast<Derived*>(this);
			singleton_iterator<const typename Types::value_type> b(std::addressof(value), 0), e(nullptr, count);
			self->insert(self->end(), b, e);
		}
		
		typename Types::iterator insert(typename Types::const_iterator pos, std::initializer_list<typename Types::value_type> il)
		{
			auto self = static_cast<Derived*>(this);
			return self->emplace(pos, il.begin(), il.end());
		}
		
		template<typename InputIterator, typename std::enable_if<
			wiertlo::is_input_iterator<InputIterator>::value
		>::type* = nullptr>
		typename Types::iterator insert(typename Types::const_iterator pos, InputIterator begin, InputIterator end)
		{
			auto self = static_cast<Derived*>(this);
			return self->insert_(pos, begin, end);
		}
	};
	
	// Requires:
	// - void assign_(InputIterator begin, InputIterator end)
	template<typename Derived, typename Types>
	struct sequence_container_assign
	{
		void assign(typename Types::size_type count, const typename Types::value_type& value)
		{
			auto self = static_cast<Derived*>(this);
			singleton_iterator<const typename Types::value_type> b(std::addressof(value), 0), e(nullptr, count);
			self->assign(b, e);
		}
		
		template<typename InputIterator, typename std::enable_if<is_input_iterator<InputIterator>::value>::type* = nullptr>
		void assign(InputIterator first, InputIterator last)
		{
			auto self = static_cast<Derived*>(this);
			self->assign_(first, last);
		}
		
		void assign(std::initializer_list<typename Types::value_type> ilist)
		{
			auto self = static_cast<Derived*>(this);
			self->assign(ilist.begin(), ilist.end());
		}
	};
	
	// Requires:
	// - const overloaded iterator find(const key_type& key)
	template<typename Derived, typename Types>
	struct associative_accessors
	{
		typename Types::value_type& at(const typename Types::key_type& key)
		{
			auto self = static_cast<Derived*>(this);
			auto p = self->find(key);
			if(p == self->end())
				return *p;
			else
				throw std::out_of_range(std::string(typeid(Derived).name()) + " out of range access");
		}
		
		const typename Types::value_type& at(const typename Types::key_type& key) const
		{
			return const_cast<associative_accessors*>(this)->at(key);
		}
	};
	
	/*
	// facade for associative containers
	// NOTE: this is only a subset of what C++ standard calls AssociativeContainers. For the facade based on the C++ standard concept, see comparison_based_associative_container_facade
	
	// 
	// User must implement:
	//typedef ??? key_type;
	//typedef ??? mapped_type;
	template<typename Derived, template<typename> class... Traits>
	class associative_container_facade : public container_facade<Derived, equality_comparable, initializer_list_assignment, Traits...>
	{
		// AT
		
		
		// operator[]
		typename Types::value_type& operator[](const typename Types::key_type& key)
		{
			auto self = static_cast<Derived*>(this);
			return self->try_emplace(key).first->second;
		}
		
		typename Types::value_type& operator[](typename Types::key_type&& key)
		{
			auto self = static_cast<Derived*>(this);
			return self->try_emplace(std::move(key)).first->second;
		}
		
		// INSERT
		std::pair<typename Types::iterator, bool> insert(typename Types::const_reference value)
		{
			auto self = static_cast<Derived*>(this);
			return self->emplace(value);
		}
		
		template<typename P, typename std::enable_if<
			std::is_constructible<typename Types::value_type, P&&>::value
		>::type* = nullptr>
		std::pair<typename Types::iterator, bool> insert(P&& value)
		{
			auto self = static_cast<Derived*>(this);
			return self->emplace(std::forward<P>(value));
		}
		
		std::pair<typename Types::iterator, bool> insert(typename Types::value_type&& value)
		{
			auto self = static_cast<Derived*>(this);
			return self->emplace(std::move(value));
		}
		
		typename Types::iterator insert(typename Types::const_iterator hint, const typename Types::value_type& value)
		{
			auto self = static_cast<Derived*>(this);
			self->emplace_hint(hint, value);
		}
		
		template<typename P, typename std::enable_if<
			std::is_constructible<typename Types::value_type, P&&>::value
		>::type* = nullptr>
		typename Types::iterator insert(typename Types::const_iterator hint, P&& value)
		{
			auto self = static_cast<Derived*>(this);
			self->emplace_hint(hint, std::forward<P>(value));
		}
		
		typename Types::iterator insert(typename Types::const_iterator hint, typename Types::value_type&& value)
		{
			auto self = static_cast<Derived*>(this);
			self->emplace_hint(hint, std::move(value));
		}
		
		void insert(std::initializer_list<typename Types::value_type> ilist)
		{
			auto self = static_cast<Derived*>(this);
			self->insert(ilist.begin(), ilist.end());
		}
		
		// User must implement:
		//template<typename InputIterator>
		//void insert(InputIterator begin, InputIterator end)
		
		// INSERT_OR_ASSIGN
		
		template<typename M>
		std::pair<typename Types::iterator, bool> insert_or_assign(const typename Types::key_type& k, M&& obj)
		{
			
		}
		
		template<typename M>
		std::pair<typename Types::iterator, bool> insert_or_assign(typename Types::key_type&& k, M&& obj)
		{
			
		}
		
		template<typename M>
		typename Types::iterator insert_or_assign(typename Types::const_iterator hint, const typename Types::key_type& k, M&& obj)
		{
			auto self = static_cast<Derived*>(this);
			return self->insert_or_assign(k, std::forward<M>(obj));
		}
		
		template<typename M>
		typename Types::iterator insert_or_assign(typename Types::const_iterator hint, typename Types::key_type&& k, M&& obj)
		{
			auto self = static_cast<Derived*>(this);
			return self->insert_or_assign(k, std::forward<M>(obj));
		}
		
		// EMPLACE_HINT
		template<typename... Args>
		typename Types::iterator emplace_hint(typename Types::const_iterator hint, Args&&... args)
		{
			auto self = static_cast<Derived*>(this);
			return self->emplace(std::forward<Args>(args)...).first;
		}
		
		// TRY_EMPLACE
		template<typename... Args>
		std::pair<typename Types::iterator, bool> try_emplace(const typename Types::key_type& k, Args&&... args)
		{
			
		}
		
		template<typename... Args>
		std::pair<typename Types::iterator, bool> try_emplace(typename Types::key_type&& k, Args&&... args)
		{
			
		}
		
		template<typename... Args>
		typename Types::iterator try_emplace(typename Types::const_iterator hint, const typename Types::key_type& k, Args&&... args)
		{
			auto self = static_cast<Derived*>(this);
			return self->try_emplace(k, std::forward<Args>(args)...);
		}
	};
	
	// facade for associative containers with comparison based keys
	template<typename Derived, template<typename> class... Traits>
	class comparison_based_associative_container_facade : public associative_container_facade<Derived, comparable, Traits...>
	{
	public:
		// CONSTRUCTORS
		
		template<typename... Args>
		typename Types::iterator try_emplace(typename Types::const_iterator hint, typename Types::key_type&& k, Args&&... args)
		{
			auto self = static_cast<Derived*>(this);
			return self->try_emplace(std::move(k), std::forward<Args>(args)...);
		}
		
		typename Types::size_type count(const typename Types::key_type& key) const
		{
			auto self = static_cast<Derived*>(this);
			auto r = self->equal_range(key);
			return std::distance(r.first, r.second);
		}
	};
	
	// facade for associative containers with hash based keys
	// NOTE: this doesn't provide the bucket interface
	template<typename Derived, template<typename> class... Traits>
	class hash_based_associative_container_facade : public associative_container_facade<Derived, comparable, Traits...>
	{
		
	};*/
}
#endif