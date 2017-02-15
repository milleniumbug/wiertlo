#include <wiertlo/container_facade.hpp>
#include <wiertlo/noisy.hpp>
#include <iostream>
#include <algorithm>
#include <cassert>

template<typename T, std::size_t MaxSize>
struct static_vector_typedefs : wiertlo::container<
	T,
	T*,
	const T*>
{
	
};

template<typename T, std::size_t MaxSize>
class static_vector :
	public static_vector_typedefs<T, MaxSize>,
	public wiertlo::container_facade<
		static_vector<T, MaxSize>,
		static_vector_typedefs<T, MaxSize>,
		wiertlo::const_iterator_getters,
		wiertlo::equality_comparable,
		wiertlo::size_getters,
		wiertlo::reversible,
		wiertlo::front_accessible,
		wiertlo::back_accessible,
		wiertlo::back_pushable,
		wiertlo::random_accessible,
		wiertlo::comparable,
		wiertlo::erase_modifiers,
		wiertlo::sequence_container_assign,
		wiertlo::sequence_container_insert>
{
private:
	typedef static_vector_typedefs<T, MaxSize> types;
	typedef wiertlo::container_facade<
		static_vector<T, MaxSize>,
		static_vector_typedefs<T, MaxSize>,
		wiertlo::const_iterator_getters,
		wiertlo::equality_comparable,
		wiertlo::size_getters,
		wiertlo::reversible,
		wiertlo::front_accessible,
		wiertlo::back_accessible,
		wiertlo::back_pushable,
		wiertlo::random_accessible,
		wiertlo::comparable> facade;
	alignas(T) char buffer[sizeof(T)*MaxSize];
	std::size_t s = 0;
public:
	typename types::iterator begin()
	{
		return reinterpret_cast<typename types::iterator>(buffer);
	}
	
	typename types::const_iterator begin() const
	{
		return reinterpret_cast<typename types::const_iterator>(buffer);
	}
	
	typename types::iterator end()
	{
		return reinterpret_cast<typename types::iterator>(buffer) + s;
	}
	
	typename types::const_iterator end() const
	{
		return reinterpret_cast<typename types::const_iterator>(buffer) + s;
	}
	
	typename types::size_type max_size() const
	{
		return MaxSize;
	}
	
	typename types::size_type capacity() const
	{
		return MaxSize;
	}
	
	template<typename... Args>
	void emplace_back(Args&&... args)
	{
		::new(static_cast<void*>(end())) T(std::forward<Args>(args)...);
		++s;
	}
	
	template<typename InputIterator>
	typename types::iterator insert_(typename types::const_iterator pos, InputIterator begin, InputIterator end)
	{
		auto afterb = end;
		auto afterit = afterb;
		auto aftere = this->end();
		for(auto it = begin; it != end; ++it)
		{
			
		}
	}
	
	void pop_back()
	{
		(end()-1)->~T();
		--s;
	}
	
	template<typename InputIterator>
	void assign_(InputIterator begin, InputIterator end)
	{
		this->clear();
		this->insert(begin, end);
	}
	
	typename types::iterator erase_(typename types::const_iterator begin, typename types::const_iterator end)
	{
		auto afterb = end;
		auto afterit = afterb;
		auto aftere = this->end();
		auto it = const_cast<typename types::iterator>(begin);
		for(; bool(it != end) && bool(afterit != aftere); ++it, void(), ++afterit)
		{
			*it = std::move(*afterit);
		}
		for(; it != end; ++it)
		{
			it->~T();
		}
	}
	
	void swap(static_vector& other)
	{
		
	}
	
	static_vector(const static_vector& other)
	{
		
	}
	
	static_vector& operator=(const static_vector& other)
	{
		
	}
	
	static_vector(static_vector&& other)
	{
		
	}
	
	static_vector& operator=(static_vector&& other)
	{
		
	}
	
	~static_vector()
	{
		while(!this->empty())
			pop_back();
	}
	
	static_vector() {}
};

/*template<typename Key, typename Value, typename Indexer, typename Allocator>
class Trie : public wiertlo::associative_container_facade<Trie<Key, Value, Indexer, Allocator>>
{
private:
	typedef wiertlo::associative_container_facade<Trie<Key, Value, Indexer, Allocator>> facade;
	
public:
	typedef Key key_type;
	typedef Value mapped_type;
	typedef std::pair<const Key, Value> value_type;
	typedef Allocator allocator_type;
	// typedef ??? key_compare;
	typedef value_type* iterator;
	typedef const value_type* const_iterator;
	
	typename facade::allocator_type get_allocator() const
	{
		
	}
	
	iterator begin()
	{
		
	}
	
	const_iterator begin() const
	{
		
	}
	
	iterator end()
	{
		
	}
	
	const_iterator end() const
	{
		
	}
	
	using facade::erase;
	iterator erase(const_iterator begin, const_iterator end)
	{
		
	}
	
	typename facade::size_type erase(const key_type& key)
	{
		
	}
	
	using facade::insert;
	template<typename InputIterator>
	void insert(InputIterator begin, InputIterator end)
	{
		
	}
	
	template<typename... Args>
	std::pair<iterator, bool> emplace(Args&&... args)
	{
		
	}
	
	iterator find(const Key& key)
	{
		
	}
	
	const_iterator find(const Key& key) const
	{
		
	}
	
	std::pair<iterator, iterator> equal_range(const Key& key)
	{
		
	}
	
	std::pair<const_iterator, const_iterator> equal_range(const Key& key) const
	{
		
	}
};*/

template<typename T>
struct instance_counter
{
private:
	static int& instance_count()
	{
		static int val = 0;
		return val;
	}
public:
	static int count()
	{
		return instance_count();
	}
	
	instance_counter()
	{
		++instance_count();
	}
	
	~instance_counter()
	{
		--instance_count();
	}
	
	instance_counter(const instance_counter&)
	{
		++instance_count();
	}
	
	instance_counter& operator=(const instance_counter&)
	{
		return *this;
	}
};

struct test
{
	instance_counter<test> c;
	wiertlo::noisy<test> n;
	int value;
	
	operator int() const
	{
		return value;
	}
	
	test() : value(0)
	{
		
	}
	
	test(int value) :
		value(value)
	{
		
	}
};

int main()
{
	assert(instance_counter<test>::count() == 0);
	{
		static_vector<test, 15> v;
		assert(v.max_size() == 15);
		assert(v.size() == 0);
		assert(v.empty());
		v.push_back(decltype(v)::value_type(4));
		v.push_back(decltype(v)::value_type(5));
		assert(v.front().value == 4);
		assert(v[0].value == 4);
		assert(v[1].value == 5);
		assert(v.at(0).value == 4);
		assert(v.at(1).value == 5);
		assert(v.size() == 2);
		v.pop_back();
		assert(v.size() == 1);
		v.emplace_back();
		assert(v.back().value == 0);
		assert(v.size() == 2);
		static_vector<test, 15> w;
		w.emplace_back(4);
		w.emplace_back(5);
		w.emplace_back();
		w.erase(w.begin()+1);
		assert(v == w);
	}
	assert(instance_counter<test>::count() == 0);
}