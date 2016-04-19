#include <iostream>
#include <string>
#include <wiertlo/string.hpp>

int main()
{
	// Unless specified otherwise, functions in this header accept
	// any string with an API resembling the one of `std::string`, for example:
	// - std::experimental::string_view
	// - boost::string_ref
	// - Glib::ustring
	// Addendum: const char* is not
	std::string a = "ABCDEFGH";
	// Positions:    01234567
	// string slicing. the arguments are respectively
	// position of the first letter in the resulting string, and
	// position of the first letter after it that's NOT in the resulting string
	// this is in contrast to .substr(offset, length)
	std::cout << wiertlo::slice(a, 2, 5) << "\n"; // "CDE"
	// For convenience, this function accepts any signed or unsigned integer
	// Negative numbers count from the end, like Python slices do.
	std::cout << wiertlo::slice(a, 0, -1) << "\n"; // "ABCDEFG"
	// Out-of-range values return empty string
	std::cout << wiertlo::slice(a, 500, 1000) << "\n"; // ""
	// If `end` refers to the character which is before the character referred by `begin`,
	// the return value is unspecified
	//std::cout << wiertlo::slice(a, 2, 1) << "\n"; // unspecified

	// wiertlo::trim_left
	// wiertlo::trim_right
	// wiertlo::trim
	// removes all leading (trim_left); trailing (trim_right);
	// both leading and trailing (trim):
	// newlines, tab characters and spaces OR characters passed as a second argument
	std::string b = "    \n \t     TEST  ";
	std::cout << wiertlo::trim_left(b) << "\n"; // "TEST  "
	std::cout << wiertlo::trim(b) << "\n"; // "TEST"

	std::string c = "//   !   TEST--------";
	std::cout << wiertlo::trim(c, std::string("/-")) << "\n"; // "   !   TEST"
}