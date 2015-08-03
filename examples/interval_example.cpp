#include <iostream>
#include <functional>
#include <algorithm>
#include <iterator>
#include <wiertlo/interval.hpp>
#include <wiertlo/overload_set.hpp>

// for demonstration
void allow() {}

int main()
{
	int value = 42;
	// old way - you repeat `value` twice.
	if(value <= 0 && value >= 50)
		allow();

	using wiertlo::make_interval; // factory function for UpperExclusiveInterval<T, U>
	using wiertlo::make_inclusive_interval; // factory function for InclusiveInterval<T, U>
	using wiertlo::is_between;

	// new way - you don't repeat the variable name
	if(is_between(value, make_inclusive_interval(0, 50)))
		allow();

	// It ~~composes~~:
	std::vector<wiertlo::UpperExclusiveInterval<double, double>> ranges = { make_interval(-1.0, 1.0), make_interval(0.0, 42.0), make_interval(-3.0, 3.0), make_interval(0.0, 5.0) };
	std::vector<int> values = { 4, 12, 0, 5 };

	std::cout << std::boolalpha;
	std::transform(values.begin(), values.end(), ranges.begin(), std::ostream_iterator<bool>(std::cout, " "), WIERTLO_OVERLOAD_SET(is_between));
}