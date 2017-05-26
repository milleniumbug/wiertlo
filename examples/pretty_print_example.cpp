#include <wiertlo/pretty_print.hpp>
#include <cassert>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

void test_impl(const std::string& actual, const std::string& expected)
{
	assert(actual == expected);
}

#define TEST(expr, expected) do \
{\
	auto actual = wiertlo::pretty::sprint<wiertlo::pretty::cpp_expression_format<>>(expr); \
	test_impl(actual, expected); \
	std::cout << actual << ";\n"; \
}\
while(false)

int main()
{
	TEST(true, "true");
	TEST(false, "false");
	TEST(::std::string("\nhello world"), "::std::string(\"\\nhello world\")");
	TEST(::std::string("\"hello\\world"), "::std::string(\"\\\"hello\\\\world\")");
	TEST(::std::string("\"hello\\world"), "::std::string(\"\\\"hello\\\\world\")");
	TEST('a', "\'a\'");
	TEST('\n', "\'\\n\'");
	TEST(42, "42");
	TEST(42u, "42u");
	TEST(42ul, "42ul");
	TEST(42ull, "42ull");
	TEST(static_cast<short>(42), "static_cast<short>(42)");
	TEST(32768, "static_cast<int>(32768)");
	TEST(-32767, "-32767");
	TEST(-32768, "static_cast<int>(-32768)");
	TEST(::std::make_unique<int>(42), "::std::make_unique<?!?!?!>(42)");
	//TEST(::std::vector<int>({ 1, 2, 3, 4 }), "?!?!?!({1,2,3,4})");
}