#include <wiertlo/pretty_print.hpp>
#include <cassert>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

template<typename T>
void test(const T& value, const std::string& expected)
{
	auto actual = wiertlo::pretty::sprint<wiertlo::pretty::cpp_expression_format<>>(value); \
	assert(actual == expected);
	std::cout << actual << ";\n";
}

int main()
{
	test(true, "true");
	test(false, "false");
	test(::std::string("\nhello world"), "::std::string(\"\\nhello world\")");
	test(::std::string("\"hello\\world"), "::std::string(\"\\\"hello\\\\world\")");
	test(::std::string("\"hello\\world"), "::std::string(\"\\\"hello\\\\world\")");
	test('a', "\'a\'");
	test('\n', "\'\\n\'");
	test(42, "42");
	test(42u, "42u");
	test(42ul, "42ul");
	test(42ull, "42ull");
	test(static_cast<short>(42), "static_cast<short>(42)");
	test(32768, "static_cast<int>(32768)");
	test(-32767, "-32767");
	test(-32768, "static_cast<int>(-32768)");
	test(::std::make_unique<int>(42), "::std::make_unique<?!?!?!>(42)");
	//test(::std::vector<int>({ 1, 2, 3, 4 }), "?!?!?!({1,2,3,4})");
}