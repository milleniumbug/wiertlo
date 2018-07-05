#include <iostream>
#include <vector>
#include <deque>
#include <memory>
#include <utility>
#include <string>
#include <wiertlo/one_based_array.hpp>

int main()
{
	using wiertlo::make_one_based;
	auto display_zero = [](std::string name, auto&& what){ std::cout << name << " " << typeid(what).name() << " " << what[0] << " " << what[1] << " " << what[2] << "\n"; };
	auto display_one = [](std::string name, auto&& what){ std::cout << name << " " << typeid(what).name() << " " << what[1] << " " << what[2] << " " << what[3] << "\n"; };
#define DISPLAY(what) display_zero(#what, what), display_one(#what "_one_based", what ## _one_based)
	{
		// the one based array uses value semantics by default
		std::vector<int> vector = { 1, 5, 7 };
		auto vector_one_based = make_one_based(vector);
		const std::vector<int> const_vector = { 1, 5, 7 };
		auto const_vector_one_based = make_one_based(const_vector);
		vector_one_based[1] = 42;
		// const_vector_one_based[1] = 42; // compile error
		DISPLAY(vector);
		DISPLAY(const_vector);
	}

	{
		// ...unless you use std::ref to make a reference
		std::deque<int> deque = { 1, 5, 7 };
		auto deque_one_based = make_one_based(std::ref(deque));
		const std::deque<int> const_deque = { 1, 5, 7 };
		auto const_deque_one_based = make_one_based(const_deque);
		deque_one_based[1] = 42;
		DISPLAY(deque);
		DISPLAY(const_deque);
	}

	{
		// Limitation: you can't have views of C-Arrays, you have use reference semantics
		int c_array[] = { 1, 5, 7 };
		auto c_array_one_based = make_one_based(std::ref(c_array));
		const int const_c_array[] = { 1, 5, 7 };
		auto const_c_array_one_based = make_one_based(std::ref(const_c_array));
	}

#undef DISPLAY
}