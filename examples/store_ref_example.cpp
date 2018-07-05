// store_reference_wrapper is like std::reference_wrapper, except it has an `explicit` constructor
// also the feature is in the name - it's for making it clear that you're storing a non-owning reference
// to the object

#include <wiertlo/experimental/store_ref.hpp>

struct wow {};
struct stuff { wow* p; };

stuff create_stuff(wow* p) { stuff a = { p }; return a; }
stuff create_stuff(wow& p) { stuff a = { &p }; return a; }
stuff create_stuff(wiertlo::store_reference_wrapper<wow> p) { stuff a = { &p.get() }; return a; }

int main()
{
	{
		// take by reference
		// SFML stores references this way and you have to read the documentation to know this
		wow a_thingy;
		auto stuff = create_stuff(a_thingy);
	}
	{
		// take by pointer
		// it's taking the address there but it's not explicit enough
		wow a_thingy;
		auto stuff = create_stuff(&a_thingy);
	}
	{
		// use wiertlo::store_reference_wrapper
		// it's clear that a function stores a reference that may outlive the object
		wow a_thingy;
		auto stuff = create_stuff(wiertlo::store_ref(a_thingy));
	}
}