#include <wiertlo/experimental/unique_cast.hpp>
#include <memory>
#include <iostream>
#include <cassert>

struct B { virtual ~B() {} };
struct D : B { void f() { std::cout << "Hello"; } };

int main()
{
	std::unique_ptr<B> bp = std::make_unique<D>();
	std::unique_ptr<D> dp;
	if(wiertlo::dynamic_casted_move(bp, dp))
	{
		dp->f();
	}
	else
	{
		assert(false);
	}
}