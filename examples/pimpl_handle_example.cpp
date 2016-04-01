#include <iostream>
#include "pimpl_handle_example.hpp"

int main()
{
	hidden a;
	hidden b = std::move(a);
	b.g("test");
	b.f();
}

struct hidden::impl : wiertlo::pimpl_implementation_mixin<hidden::pimpl_handle_type, hidden::impl>
{
	static impl_type& get_impl(pimpl_handle_type& handle) { return *get_handle(handle); }
	
	std::string mine;
};

hidden::hidden() :
	pi(impl::create_pimpl_handle(std::make_unique<hidden::impl>()))
{
	
}

void hidden::f()
{
	auto& i = impl::get_impl(pi);
	std::cout << "asdf:" << i.mine;
}

void hidden::g(std::string a)
{
	auto& i = impl::get_impl(pi);
	i.mine = a;
}