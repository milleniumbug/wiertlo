#include <wiertlo/pretty_print.hpp>
#include <wiertlo/demangled.hpp>
#include <cassert>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

enum class Asdf
{
	A, B, C
};

template<typename T, typename U>
void testRaw(const T& actual, const U& expected)
{
	if(actual != expected)
	{
		std::cout << "TEST FAILURE:\n";
		std::cout << "actual  : " << actual << "\n";
		std::cout << "expected: " << expected << "\n";
		std::cout << "\n\n";
		assert(false);
	}
}

template<typename T, typename U>
void testRawAny(const T& actual, const U& expecteds)
{
	auto it = std::find_if(expecteds.begin(), expecteds.end(), [&](auto& expected){
		return actual == expected;
	});
	if(it == expecteds.end())
	{
		std::cout << "TEST FAILURE:\n";
		std::cout << "actual  : " << actual << "\n";
		std::cout << "MATCHED NONE OF THE EXPECTEDS\n";
		std::cout << "\n\n";
		assert(false);
	}
}

template<typename T>
void test(const T& value, const std::string& expected)
{
	auto actual = wiertlo::pretty::sprint<wiertlo::pretty::cpp_expression_format<wiertlo::RTTINamePolicy>>(value);
	testRaw(actual, expected);
}

int main()
{
	test(true, "true");
	test(false, "false");
	test(std::string("\nhello world"), "std::string(\"\\nhello world\")");
	test(std::string("\"hello\\world"), "std::string(\"\\\"hello\\\\world\")");
	test(std::string("\"hello\\world"), "std::string(\"\\\"hello\\\\world\")");
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
	test(std::make_unique<int>(42), "std::make_unique<int>(42)");
	test(Asdf::A, "Asdf(0)");
	{
		auto actual = wiertlo::pretty::sprint<wiertlo::pretty::cpp_expression_format<wiertlo::RTTINamePolicy>>(std::vector<int>({ 1, 2, 3, 4 }));
		testRawAny(actual, std::vector<std::string>{
			"std::vector<int,std::allocator<int> >({1,2,3,4})",
			"std::vector<int, std::allocator<int> >({1,2,3,4})"
		});
	}
	{
		auto actual = wiertlo::pretty::sprint<wiertlo::pretty::cpp_expression_format<wiertlo::RTTINamePolicy>>(std::vector<std::vector<bool>>({ std::vector<bool>{ false, false, true }, std::vector<bool>{ true }}));
		testRawAny(actual, std::vector<std::string>{
			"std::vector<std::vector<bool,std::allocator<bool> >,std::allocator<std::vector<bool,std::allocator<bool> > > >({std::vector<bool,std::allocator<bool> >({false,false,true}),std::vector<bool,std::allocator<bool> >({true})})",
			"std::vector<std::vector<bool, std::allocator<bool> >, std::allocator<std::vector<bool, std::allocator<bool> > > >({std::vector<bool, std::allocator<bool> >({false,false,true}),std::vector<bool, std::allocator<bool> >({true})})"
		});
	}
	test(std::array<int, 4>{1,2,3,4}, "std::array<int,4>{1,2,3,4}");
	test(std::make_pair(42, std::string("lol")), "std::make_pair(42,std::string(\"lol\"))");
	test(std::make_tuple(), "std::make_tuple()");
	test(std::make_tuple(42,std::string("lol")), "std::make_tuple(42,std::string(\"lol\"))");
}