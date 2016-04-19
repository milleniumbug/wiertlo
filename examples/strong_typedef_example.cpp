#include <iostream>
#include <vector>
#include <string>
#include <wiertlo/strong_typedef.hpp>

// Mixin for creating types similar enough,
// but distinct enough for purposes of overload resolution
struct user_id : wiertlo::strong_typedef<user_id, int>
{
	using wiertlo::strong_typedef<user_id, int>::strong_typedef;
};

// For simple cases of non-templated strong typedefs a macro is provided:
WIERTLO_STRONG_TYPEDEF(group_id, int);

std::ostream& operator<<(std::ostream& os, user_id id)
{
	std::cout << "user_id(" << id.get() << ")";
	return os;
}

std::ostream& operator<<(std::ostream& os, group_id id)
{
	std::cout << "group_id(" << id.get() << ")";
	return os;
}

// An optional stateless precondition function object can be provided
// as the third template parameter, which will be called on construction
// with the underlying value
// very convenient for function arguments
struct empty_container_exception : std::invalid_argument
{
	using std::invalid_argument::invalid_argument;
};

struct nonempty_precondition
{
	template<typename Collection>
	void operator()(const Collection& c) const
	{
		if(c.empty())
			throw empty_container_exception("Non-empty collection required");
	}
};

template<typename Collection>
struct nonempty_collection : wiertlo::strong_typedef<nonempty_collection<Collection>, Collection, nonempty_precondition>
{
	using wiertlo::strong_typedef<nonempty_collection<Collection>, Collection, nonempty_precondition>::strong_typedef;
};

int main()
{
	try
	{
		nonempty_collection<std::vector<int>> n = std::vector<int>(); // throws exception
	}
	catch(const empty_container_exception& ex)
	{
		std::cout << ex.what() << "\n\n";
	}

	{
		nonempty_collection<std::vector<int>> n = std::vector<int>{ 1, 2, 3, 4, 5 };
		std::cout << n.get()[0] << "\n";
	}

	{
		int a = 5;
		user_id b(a);
		group_id c(a);
		std::cout << a << " " << b << " " << c << "\n";
	}
}