#ifndef PIMPL_EXAMPLE_HPP
#define PIMPL_EXAMPLE_HPP

#include <wiertlo/pimpl_handle.hpp>

class hidden
{
private:
	struct impl;
	typedef wiertlo::pimpl_handle<impl> pimpl_handle_type;
	pimpl_handle_type pi;
	
public:
	hidden();
	void f();
	void g(std::string a);
};

#endif