#include <iostream>
#include <memory>
#include <wiertlo/deleter_from_function.hpp>


// We have a non-RAII managed resource, and we want to wrap it in std::unique_ptr
typedef int Resource;
Resource res;
Resource* create_resource()
{
	std::cout << "Resource created!\n";
	return &res;
}

void destroy_resource(Resource* res)
{
	std::cout << "Resource destroyed!\n";
}

int main()
{
	// APPROACH 1: WRONG
	// `std::default_deleter` deletes with `delete` the resource, obviously wrong
	{
		//std::unique_ptr<Resource> ptr(create_resource());
	}
	// APPROACH 2: WRONG
	// doesn't compile
	{
		//std::unique_ptr<Resource, decltype(destroy_resource)> ptr(create_resource());
	}
	// APPROACH 3: WRONG
	// `sizeof ptr` increases for no good reason, as the function pointer is not stateless
	{
		std::unique_ptr<Resource, decltype(&destroy_resource)> ptr(create_resource(), &destroy_resource);
	}
	// APPROACH 4: CORRECT, but requires boilerplate and naming the type of function object
	{
		struct Deleter
		{
			void operator()(Resource* res) const
			{
				destroy_resource(res);
			}
		};
		std::unique_ptr<Resource, Deleter> ptr(create_resource());
	}
	// APPROACH 5: CORRECT, but requires naming the lambda, and repeating the name again in the constructor
	{
		auto deleter = [](Resource* res){ destroy_resource(res); };
		std::unique_ptr<Resource, decltype(deleter)> ptr(create_resource(), deleter);
	}
	// APPROACH 6: CORRECT
	{
		std::unique_ptr<Resource, WIERTLO_DELETER_FROM_FUNCTION(destroy_resource)> ptr(create_resource());	
	}
}