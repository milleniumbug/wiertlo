#include <iostream>
#include <utility>
#include <cmath>
#include <wiertlo/defs.h>

using namespace wiertlo::cpp_style_declarations;

int sum(int a, int b)
{
	return a + b;
}

// template argument deduction still works - thanks to C++11 "using" aliases
template<typename Ret, typename... Args>
Ret invoke(function_ptr<Ret(Args...)> f, universal_ref<Args>... args)
{
	return f(std::forward<Args>(args)...);
}

// countof macro that yields a compile-time constant
// beware: fails for local types in C++03
// JUST LOOK AT IT
template <typename T, size_t N>
char ( &crazy_people_declaring_countof_helper( T (&array)[N] ))[N];
#define crazy_countof( array ) (sizeof( crazy_people_declaring_countof_helper( array ) ))

// more reasonable code
template <typename T, size_t N>
c_array<char,N>& much_better_declared_countof_helper(c_array<T,N>& array);
// or ref<c_array<char,N>> much_better_declared_countof_helper(ref<c_array<T,N>> array);
#define countof( array ) (sizeof( much_better_declared_countof_helper( array ) ))

c_array_infer_size<int> arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
c_array<int, 10> arr2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
c_array<c_array<int, 2>, 3> arr3 = { {0,1}, {2,3}, {3,4} };
constexpr std::size_t arr_size_1 = crazy_countof(arr);
constexpr std::size_t arr_size_2 = countof(arr);

static_assert(arr_size_1 == arr_size_2 && arr_size_1 == 10, "element count doesn't match");

int main()
{
	int int_var = 42;
	// replacement syntax for declarations
	// now it is identical to user-defined templates
	// also, no more missing asterisk bugs.
	//
	// int* a,b; // a is a pointer to int, b is int
	// ptr<int> a,b; // both a and b are pointers to int
	//
	// (i hate C declaration syntax with passion)
	ptr<int> ptr1 = nullptr, ptr2 = &int_var;
	function_ptr<int(int,int)> f = sum;
	//function_ptr<int> dataptr = &a; // fails

	{
		//old syntax
		const char* const old_clpcstr = "immutable pointer to immutable string literal";
		//new syntax
		const ptr<const char> new_clpcstr = "immutable pointer to immutable string literal";
		static_assert(std::is_same<decltype(old_clpcstr), decltype(new_clpcstr)>::value, "");
		//old syntax
		const char* old_lpcstr = "mutable pointer to immutable string literal";
		//new syntax
		ptr<const char> new_lpcstr = "mutable pointer to immutable string literal";
		static_assert(std::is_same<decltype(old_lpcstr), decltype(new_lpcstr)>::value, "");
	}

	std::cout << invoke(f,2,5) << "\n";
	std::cout << f(2,5) << "\n";
	if(ptr1)
	{
		std::cout << *ptr1;
	}
	if(ptr2)
	{
		std::cout << *ptr2;
	}

	{
		// how a signal(3) is declared
		void (*how_crazy_people_declare_signal_with_old_syntax(int sig, void (*handler)(int)))(int);
		// how it could be
		function_ptr<void(int)> how_crazy_people_declare_signal_with_new_syntax(int sig, function_ptr<void(int)> handler);
		// of course, normal people use typedefs...
		// which is still better than new syntax with no typedefs
		{
			typedef void (*signal_handler)(int);
			signal_handler old_syntax_signal_normal(int sig, signal_handler handler);
		}
		// even then, the clarity can be improved
		{
			typedef function_ptr<void(int)> signal_handler;
			using signal_handler_new = function_ptr<void(int)>;
			signal_handler new_syntax_signal_normal(int sig, signal_handler handler);
		}
	}

}