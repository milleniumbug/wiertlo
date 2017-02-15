#include <iostream>
#include <wiertlo/nonown_ptr.hpp>

struct A { long long a = 5; virtual void print() const { std::cout << "A " << a << "\n"; } };
struct B : A { long long b = 4; void print() const override { std::cout << "B " << a << " " << b << "\n"; } };

int main()
{
	// wiertlo::nonown_ptr
	// Intended to be used for refactoring legacy projects,
	// especially where you use raw pointers with unspecified ownership
	// you can gradually check every raw pointer in your codebase
	// and replace it with nonown_ptr, unique_ptr or shared_ptr as you go

	// Features of wiertlo::nonown_ptr

	// 1. No pointer arithmetic (unless it's wiertlo::nonown_ptr<T[]>)
	{
		int a[] = { 1, 2, 3, 4, 5 };
		wiertlo::nonown_ptr<int> p2(&a[1]);
		// p2 = p2 + 1; // won't compile
		// p2++; // so won't this
		// p2[0] = 42; // and this
		// 0[p2] = 42; // AND EVEN THIS
	}
	// 2. No implicit array decay for nonown_ptr<T>
	{
		int a[] = { 1, 2, 3, 4, 5 };
		// wiertlo::nonown_ptr<int> p3(a); // won't compile
		wiertlo::nonown_ptr<int[]> p3(a);
	}
	// 3. nonown_ptr<T[]> can't point to arrays of derived type
	{
		B b[20];
		A* raw = b;
		raw->print();
		// raw[1].print(); // FAIL
		// wiertlo::nonown_ptr<A[]> badptr(b); // won't compile
		wiertlo::nonown_ptr<B[]> ptr(b); // won't compile
		//wiertlo::nonown_ptr<A[]> badptr2(ptr); // won't compile
	}
	// 4. Can't accidentally call delete on it
	{
		int* unspecified_ownership = new int;
		wiertlo::nonown_ptr<int> badly_used_supposedly_nonowning_ptr = new int;
		*unspecified_ownership = 42;
		*badly_used_supposedly_nonowning_ptr = 1337;
		if(badly_used_supposedly_nonowning_ptr)
			std::cout << "Valid\n";
		std::cout << *badly_used_supposedly_nonowning_ptr << "\n";
		std::cout << badly_used_supposedly_nonowning_ptr.get() << "\n";
		// delete badly_used_supposedly_nonowning_ptr; // won't compile
		delete unspecified_ownership;
	}
	// 5. default-initialization of wiertlo::nonown_ptr nullifies it
	{
		wiertlo::nonown_ptr<int> nullpointer;
		if(nullpointer)
			std::cout << "Valid\n";
		if(!nullpointer)
			std::cout << "Null\n";
	}
	// 6. Conversions between related types
	{
		B b;
		B b2[2];
		wiertlo::nonown_ptr<B> p = &b;
		wiertlo::nonown_ptr<A> q = p;
		q->print();
		wiertlo::nonown_ptr<B[]> pa = b2;
		pa[1].print();
		// wiertlo::nonown_ptr<B[]> badptr1 = p;
		// wiertlo::nonown_ptr<B> badptr2 = pa;
		// wiertlo::nonown_ptr<A> badptr3 = pa;
	}
	// TODO:
	// 7. void pointers work just like regular void*
	{
		int val = 42;
		wiertlo::nonown_ptr<int> p = &val;
		wiertlo::nonown_ptr<void> vp(p);
		// auto rep = static_cast<wiertlo::nonown_ptr<int>>(vp);

	}
}