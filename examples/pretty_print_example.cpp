#include <wiertlo/pretty_print.hpp>
#include <cassert>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

void test(const std::string& actual, const std::string& expected)
{
	assert(actual == expected);
}

int main()
{
	test(wiertlo::pretty::sprint<wiertlo::pretty::cpp_expression_format<>>(true), "true");
	test(wiertlo::pretty::sprint<wiertlo::pretty::cpp_expression_format<>>(false), "false");
	test(wiertlo::pretty::sprint<wiertlo::pretty::cpp_expression_format<>>(::std::string("\nhello world")), "::std::string(\"\\nhello world\")");
	test(wiertlo::pretty::sprint<wiertlo::pretty::cpp_expression_format<>>(::std::string("\"hello\\world")), "::std::string(\"\\\"hello\\\\world\")");
	test(wiertlo::pretty::sprint<wiertlo::pretty::cpp_expression_format<>>(::std::string("\"hello\\world")), "::std::string(\"\\\"hello\\\\world\")");
	test(wiertlo::pretty::sprint<wiertlo::pretty::cpp_expression_format<>>('a'), "\'a\'");
	test(wiertlo::pretty::sprint<wiertlo::pretty::cpp_expression_format<>>('\n'), "\'\\n\'");
	test(wiertlo::pretty::sprint<wiertlo::pretty::cpp_expression_format<>>(42), "42");
	test(wiertlo::pretty::sprint<wiertlo::pretty::cpp_expression_format<>>(42u), "42u");
	test(wiertlo::pretty::sprint<wiertlo::pretty::cpp_expression_format<>>(42ul), "42ul");
	test(wiertlo::pretty::sprint<wiertlo::pretty::cpp_expression_format<>>(42ull), "42ull");
	test(wiertlo::pretty::sprint<wiertlo::pretty::cpp_expression_format<>>(static_cast<short>(42)), "static_cast<short>(42)");
	test(wiertlo::pretty::sprint<wiertlo::pretty::cpp_expression_format<>>(32768), "static_cast<int>(32768)");
	test(wiertlo::pretty::sprint<wiertlo::pretty::cpp_expression_format<>>(-32767), "-32767");
	test(wiertlo::pretty::sprint<wiertlo::pretty::cpp_expression_format<>>(-32768), "static_cast<int>(-32768)");
	test(wiertlo::pretty::sprint<wiertlo::pretty::cpp_expression_format<>>(::std::make_unique<int>(42)), "::std::make_unique<?!?!?!>(42)");
	//test(wiertlo::pretty::sprint<wiertlo::pretty::cpp_expression_format<>>(::std::vector<int>({1,2,3,4})), "?!?!?!({1,2,3,4})");
}