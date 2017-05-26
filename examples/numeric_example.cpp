#include <wiertlo/numeric.hpp>
#include <cassert>
#include <limits>

int main()
{
	assert(wiertlo::integral_compare(static_cast<unsigned>(0), static_cast<unsigned>(0)) == 0);
	assert(wiertlo::integral_compare(static_cast<unsigned>(5), static_cast<unsigned>(5)) == 0);
	assert(wiertlo::integral_compare(static_cast<unsigned>(5), static_cast<unsigned>(0)) > 0);
	assert(wiertlo::integral_compare(static_cast<unsigned>(0), static_cast<unsigned>(5)) < 0);

	assert(wiertlo::integral_compare(static_cast<unsigned char>(0), static_cast<unsigned>(0)) == 0);
	assert(wiertlo::integral_compare(static_cast<unsigned char>(5), static_cast<unsigned>(5)) == 0);
	assert(wiertlo::integral_compare(static_cast<unsigned char>(5), static_cast<unsigned>(0)) > 0);
	assert(wiertlo::integral_compare(static_cast<unsigned char>(0), static_cast<unsigned>(5)) < 0);

	assert(wiertlo::integral_compare(static_cast<unsigned>(0), static_cast<unsigned char>(0)) == 0);
	assert(wiertlo::integral_compare(static_cast<unsigned>(5), static_cast<unsigned char>(5)) == 0);
	assert(wiertlo::integral_compare(static_cast<unsigned>(5), static_cast<unsigned char>(0)) > 0);
	assert(wiertlo::integral_compare(static_cast<unsigned>(0), static_cast<unsigned char>(5)) < 0);

	assert(wiertlo::integral_compare(static_cast<signed>(-42), static_cast<signed>(-42)) == 0);
	assert(wiertlo::integral_compare(static_cast<unsigned>(5), static_cast<signed>(5)) == 0);
	assert(wiertlo::integral_compare(static_cast<unsigned>(5), static_cast<signed>(-42)) > 0);
	assert(wiertlo::integral_compare(static_cast<signed>(-42), static_cast<signed>(5)) < 0);

	assert(wiertlo::integral_compare(static_cast<signed char>(0), static_cast<unsigned char>(0)) == 0);
	assert(wiertlo::integral_compare(static_cast<signed char>(5), static_cast<unsigned char>(5)) == 0);
	assert(wiertlo::integral_compare(static_cast<signed char>(5), static_cast<unsigned char>(0)) > 0);
	assert(wiertlo::integral_compare(static_cast<signed char>(0), static_cast<unsigned char>(5)) < 0);

	assert(wiertlo::integral_compare(static_cast<signed char>(0), static_cast<char>(0)) == 0);
	assert(wiertlo::integral_compare(static_cast<signed char>(5), static_cast<char>(5)) == 0);
	assert(wiertlo::integral_compare(static_cast<signed char>(5), static_cast<char>(0)) > 0);
	assert(wiertlo::integral_compare(static_cast<signed char>(0), static_cast<char>(5)) < 0);

	assert(wiertlo::integral_compare(static_cast<char>(0), static_cast<unsigned char>(0)) == 0);
	assert(wiertlo::integral_compare(static_cast<char>(5), static_cast<unsigned char>(5)) == 0);
	assert(wiertlo::integral_compare(static_cast<char>(5), static_cast<unsigned char>(0)) > 0);
	assert(wiertlo::integral_compare(static_cast<char>(0), static_cast<unsigned char>(5)) < 0);


	assert(wiertlo::wrap(0, 360) == 0);
	assert(wiertlo::wrap(-1, 360) == 359);
	assert(wiertlo::wrap(-359, 360) == 1);
	assert(wiertlo::wrap(-360, 360) == 0);
	assert(wiertlo::wrap(-361, 360) == 359);
	assert(wiertlo::wrap(5, 360) == 5);
	assert(wiertlo::wrap(365, 360) == 5);
	assert(wiertlo::wrap(725, 360) == 5);
}