#include <wiertlo/string_interface.hpp>
#include <iostream>
#include <cassert>

int main()
{
	const std::string s = "the lazy fox jumped over the broken car";
	{
		auto needles = wiertlo::find_all(s, std::string("the"));
		assert(std::distance(needles.begin(), needles.end()) == 2);
	}
	{
		auto needles = wiertlo::find_all(s, wiertlo::single('e'));
		assert(std::distance(needles.begin(), needles.end()) == 5);
	}
	{
		std::string r;
		wiertlo::replaced_all(s, wiertlo::find_all(s, std::string("the")), std::string("a"), std::back_inserter(r));
		assert(r == "a lazy fox jumped over a broken car");
	}
	{
		std::string r = s;
		auto all = wiertlo::find_all(r, std::string("the"));
		auto first = *all.begin();
		wiertlo::replace(r, first, std::string("overly"));
		assert(r == "overly lazy fox jumped over the broken car");
	}
}