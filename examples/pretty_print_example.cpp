#include <wiertlo/pretty_print.hpp>
#include <cassert>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

void replaceAll(std::string& source, const std::string& from, const std::string& to)
{
	std::string newString;
	newString.reserve(source.length());  // avoids a few memory allocations

	std::string::size_type lastPos = 0;
	std::string::size_type findPos;

	while(std::string::npos != (findPos = source.find(from, lastPos)))
	{
		newString.append(source, lastPos, findPos - lastPos);
		newString += to;
		lastPos = findPos + from.length();
	}

	// Care for the rest after last occurrence
	newString += source.substr(lastPos);

	source.swap(newString);
}

struct free_deleter
{
	template<typename T>
	void operator()(T* ptr)
	{
		free(ptr);
	}
};

#ifndef _MSC_VER
#include <cxxabi.h>
#endif

struct RTTINamePolicy
{
	template<typename T>
	static std::string get_name()
	{
		
#ifndef _MSC_VER
		int status;
		std::size_t length;
		std::unique_ptr<char, free_deleter> demangled(abi::__cxa_demangle(typeid(T).name(), nullptr, &length, &status));
		if(status != 0)
			throw "FUCK";
		std::string s = demangled.get();
#else
		std::string s = typeid(T).name();
#endif
		// TODO: don't break on identifiers like `lolenum`
		replaceAll(s, "enum ", "");
		replaceAll(s, "struct ", "");
		replaceAll(s, "class ", "");
		replaceAll(s, "union ", "");
		return s;
	}
};

enum class Asdf
{
	A, B, C
};

template<typename T, typename U>
void testRaw(const T& actual, const U& expected)
{
	if(actual != expected)
	{
		std::cout << "TEST FAILURE: ";
		std::cout << "actual: " << actual << "\n";
		std::cout << "expected: " << expected << "\n";
		std::cout << "\n\n";
		assert(false);
	}
}

template<typename T>
void test(const T& value, const std::string& expected)
{
	auto actual = wiertlo::pretty::sprint<wiertlo::pretty::cpp_expression_format<RTTINamePolicy>>(value);
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
		auto actual = wiertlo::pretty::sprint<wiertlo::pretty::cpp_expression_format<RTTINamePolicy>>(std::vector<int>({ 1, 2, 3, 4 }));
		// both are acceptable
		replaceAll(actual, "int, std::allocator<int>", "int,std::allocator<int>");
		testRaw(actual, "std::vector<int,std::allocator<int> >({1,2,3,4})");
	}
}