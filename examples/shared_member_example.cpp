#include <iostream>
#include <map>
#include <memory>
#include <cassert>
#include <wiertlo/shared_member.hpp>
#include <wiertlo/noisy.hpp>

struct A
{
    wiertlo::noisy<int> a;
    wiertlo::noisy<long> b;
    wiertlo::noisy<A> c;
};

int main()
{
    {
        auto ptr = std::make_shared<A>();
        auto other = wiertlo::shared_member(ptr, &A::a);
        assert(ptr.use_count() == 2);
        assert(other.use_count() == 2);
        assert(&ptr->a == other.get());
        auto other2 = wiertlo::shared_member(ptr, &A::c);
        assert(ptr.use_count() == 3);
        assert(other.use_count() == 3);
        assert(other2.use_count() == 3);
        assert(&ptr->c == other2.get());
    }
    {
        std::shared_ptr<A> ptr;
        auto other = wiertlo::shared_member(ptr, &A::a);
        assert(ptr.use_count() == 0);
        assert(other.use_count() == 0);
        assert(!ptr);
        assert(!other);
    }
}