#include <wiertlo/meta.hpp>

using namespace wiertlo::meta;

// Length
static_assert(
	Length<
		TypeList<int, long, short, void>>::value == 4, "");

// Concat
static_assert(
	std::is_same<
		Concat<
			TypeList<int>,
			TypeList<long, char>>::type,
		TypeList<int, long, char>>::value, "");

static_assert(
	std::is_same<
		Concat<
			TypeList<int>,
			TypeList<long, char>,
			TypeList<long, long>>::type,
		TypeList<int, long, char, long, long>>::value, "");

// Contains
static_assert(
	Contains<
		TypeList<char, int, int, char16_t, wchar_t, char>,
		int>::value, "");

static_assert(
	!Contains<
		TypeList<char, int, int, char16_t, wchar_t, char>,
		char32_t>::value, "");

static_assert(
	!Contains<
		TypeList<>,
		char32_t>::value, "");

static_assert(
	Contains<
		TypeList<int>,
		int>::value, "");

// Find
static_assert(
	Find<
		TypeList<char, int, int, char16_t, wchar_t, char>,
		char>::value == 0, "");

static_assert(
	Find<
		TypeList<char, int, int, char16_t, wchar_t, char>,
		int>::value == 1, "");

static_assert(
	Find<
		TypeList<char, int, int, char16_t, wchar_t, char>,
		char16_t>::value == 3, "");

static_assert(
	Find<
		TypeList<char, int, int, char16_t, wchar_t, char>,
		wchar_t>::value == 4, "");

// FindIf
static_assert(
	FindIf<
		TypeList<void, void, void, int, char, void>,
		std::is_integral>::value == 3, "");

// Map
static_assert(
	std::is_same<
		Map<
			std::remove_reference,
			TypeList<int&, long&, char&>>::type,
		TypeList<int, long, char>>::value, "");

// Reduce
template<typename Left, typename Right>
struct Add;

template<typename Type, Type LeftVal, Type RightVal>
struct Add<std::integral_constant<Type, LeftVal>, std::integral_constant<Type, RightVal>>
{
	typedef std::integral_constant<Type, LeftVal+RightVal> type;
};

static_assert(
	Reduce<
		Add,
		std::integral_constant<int, 0>,
		TypeList<>>::type::value == 0, "");

static_assert(
	Reduce<
		Add,
		std::integral_constant<int, 0>,
		TypeList<
			std::integral_constant<int, 1>,
			std::integral_constant<int, 2>>>::type::value == 3, "");

// Reduce1
static_assert(
	Reduce1<
		Add,
		TypeList<
			std::integral_constant<int, 1>,
			std::integral_constant<int, 2>,
			std::integral_constant<int, 3>,
			std::integral_constant<int, 4>>>::type::value == 10, "");

// Filter
static_assert(
	std::is_same<
		Filter<
			std::is_reference,
			TypeList<
				int,
				void*,
				int&,
				long&>>::type,
		TypeList<int&, long&>>::value,"");

// PushBack
static_assert(
	std::is_same<
		PushBack<
			TypeList<int, int>,
			long>::type,
		TypeList<int, int, long>>::value, "");

// Front
static_assert(
	std::is_same<
		typename Front<TypeList<int, int, long>>::type,
		int>::value, "");

// Back
static_assert(
	std::is_same<
		typename Back<TypeList<int, int, long>>::type,
		long>::value, "");

// PushFront
static_assert(
	std::is_same<
		PushFront<
			TypeList<int, int>,
			long>::type,
		TypeList<long, int, int>>::value, "");

// PopBack
static_assert(
	std::is_same<
		PopBack<
			TypeList<long, int, int>>::type,
		TypeList<long, int>>::value, "");

// PopFront
static_assert(
	std::is_same<
		PopFront<
			TypeList<long, int, int>>::type,
		TypeList<int, int>>::value, "");

// IterateN
static_assert(
	std::is_same<
		IterateN<std::add_pointer, int, 4>::type,
		TypeList<
			int,
			int*,
			int**,
			int***>>::value, "");

// Iota
static_assert(
	std::is_same<
		Iota<int, 4>::type,
		TypeList<
			std::integral_constant<int, 0>,
			std::integral_constant<int, 1>,
			std::integral_constant<int, 2>,
			std::integral_constant<int, 3>>>::value, "");

// Reverse
static_assert(
	std::is_same<
		Reverse<TypeList<int, long, char>>::type,
		TypeList<char, long, int>>::value, "");

int main()
{

}