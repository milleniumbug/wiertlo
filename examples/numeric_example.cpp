#include <wiertlo/numeric.hpp>
#include <wiertlo/make.hpp>
#include <cassert>
#include <limits>

void numeric()
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

	auto time_components = wiertlo::make_array<int>(60, 60, 24);
	assert(wiertlo::decompose(time_components, 0) == wiertlo::make_array<int>(0, 0, 0, 0));
	assert(wiertlo::decompose(time_components, 59) == wiertlo::make_array<int>(59, 0, 0, 0));
	assert(wiertlo::decompose(time_components, 60) == wiertlo::make_array<int>(0, 1, 0, 0));
	assert(wiertlo::decompose(time_components, 61) == wiertlo::make_array<int>(1, 1, 0, 0));
	assert(wiertlo::decompose(time_components, 3661) == wiertlo::make_array<int>(1, 1, 1, 0));
	assert(wiertlo::decompose(time_components, 100000) == wiertlo::make_array<int>(40, 46, 3, 1));

	assert(wiertlo::wrap(0, 360) == 0);
	assert(wiertlo::wrap(-1, 360) == 359);
	assert(wiertlo::wrap(-359, 360) == 1);
	assert(wiertlo::wrap(-360, 360) == 0);
	assert(wiertlo::wrap(-361, 360) == 359);
	assert(wiertlo::wrap(5, 360) == 5);
	assert(wiertlo::wrap(365, 360) == 5);
	assert(wiertlo::wrap(725, 360) == 5);

	assert(wiertlo::float_less<>()(4.0, 5.0));
	assert(!wiertlo::float_less<>()(5.0, 5.0));
	assert(!wiertlo::float_less<>()(6.0, 5.0));
	assert(wiertlo::float_less<>()(6.0, std::numeric_limits<double>::quiet_NaN()));
	assert(!wiertlo::float_less<>()(std::numeric_limits<double>::quiet_NaN(), 6.0));
	assert(!wiertlo::float_less<>()(std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN()));

	assert(wiertlo::float_less<double>()(4.0, 5.0));
	assert(!wiertlo::float_less<double>()(5.0, 5.0));
	assert(!wiertlo::float_less<double>()(6.0, 5.0));
	assert(wiertlo::float_less<double>()(6.0, std::numeric_limits<double>::quiet_NaN()));
	assert(wiertlo::float_less<double>()(std::numeric_limits<double>::infinity(), std::numeric_limits<double>::quiet_NaN()));
	assert(wiertlo::float_less<double>()(-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::quiet_NaN()));
	assert(!wiertlo::float_less<double>()(std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::infinity()));
	assert(!wiertlo::float_less<double>()(std::numeric_limits<double>::quiet_NaN(), -std::numeric_limits<double>::infinity()));
	assert(!wiertlo::float_less<double>()(std::numeric_limits<double>::quiet_NaN(), 6.0));
	assert(!wiertlo::float_less<double>()(std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN()));
}

int main()
{
    numeric();
}