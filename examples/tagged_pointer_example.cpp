#include <iostream>
#include <iomanip>
#include <cassert>
#include <memory>
#include <wiertlo/tagged_pointer.hpp>

template<typename T>
void print_ptr(tagged_pointer<T> p, std::string name)
{
	std::cout << p.get() << " " << (p ? std::to_string(*p) : "N/A") << " " << p.tag() << " - " << name << "\n";
}

#define PRINT_TAGGED_POINTER(p) print_ptr(p, #p)

void basic_usage()
{
	int a_value = 42;
	int* a_pointer = &a_value;
	tagged_pointer<int> p(&a_value);
	assert(p);
	assert(p.get() == a_pointer);
	assert(p.tag() == 0);
	PRINT_TAGGED_POINTER(p);

	auto q = p;
	q.set_tag(1);

	assert(q);
	assert(q.get() == a_pointer);
	assert(q.tag() == 1);
	PRINT_TAGGED_POINTER(p);
	PRINT_TAGGED_POINTER(q);

	*p = 256;
	assert(p);
	assert(p.get() == a_pointer);
	assert(p.tag() == 0);
	assert(q);
	assert(q.get() == a_pointer);
	assert(q.tag() == 1);
	PRINT_TAGGED_POINTER(p);
	PRINT_TAGGED_POINTER(q);

	assert(p == q);
	std::cout << std::boolalpha << (p == q) << "\n";

	// testing platform-specific assumptions
	static const int maximum = tagged_pointer<int>::max_tag_value;
	static_assert(maximum >= 3, "");

	tagged_pointer<int> np = nullptr;
	np.set_tag(3);
	assert(!np);
	assert(np.tag() == 3);
	PRINT_TAGGED_POINTER(np);
}

void testing_comparisons()
{
	int a_value = 42;
	tagged_pointer<int> p(&a_value);
	tagged_pointer<int> np_def;
	tagged_pointer<int> np_exp(nullptr);

	assert(
		!np_def &&
		!np_exp &&
		np_def == np_exp &&
		np_def == nullptr &&
		nullptr == np_def &&
		np_exp == nullptr &&
		nullptr == np_exp);

	assert(
		p &&
		p != nullptr &&
		nullptr != p &&
		!(p == nullptr) &&
		!(nullptr == p));
}

void using_with_std_unique_ptr()
{
	struct tag_deleter
	{
		typedef tagged_pointer<int> pointer;

		void operator()(pointer p) const
		{
			std::cout << "DELETED " << p.get() << "\n";
			delete p.get();
		}
	};

	// tagged_pointer's constructor is currently implicit
	// that decision is not set in stone yet.
	std::unique_ptr<int, tag_deleter> p(new int(42));
	assert(*p == 42);
	assert(p.get().tag() == 0);
	std::cout << p.get().get() << " " << *p << " " << p.get().tag() << " - p\n";

	const int x = 3;
	// p.get() returns a copy, so don't do this: 
	// p.get().set_tag(x)
	// instead do it the longer way (wrap in a function for your own sanity)
	p.reset(tagged_pointer<std::remove_reference<decltype(p)>::type::element_type>(p.release(), x));

	assert(*p == 42);
	assert(p.get().tag() == 3);
	std::cout << p.get().get() << " " << *p << " " << p.get().tag() << " - p\n";
}

int main()
{
	basic_usage();
	testing_comparisons();
	using_with_std_unique_ptr();
}