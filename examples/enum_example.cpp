#include <iostream>
#include <typeindex>
// if your compiler supports it, you can make from_string and to_string accept/return std::experimental::string_view instead of std::string
#define WIERTLO_ENUM_USE_EXPERIMENTAL_STRING_VIEW
// you need to include this header before - don't worry if you forget this, you'll be reminded this at compile-time
#include <wiertlo/enum_enable.hpp>

// Options:
// WIERTLO_ENUM_NAME
//     name of the enum
// WIERTLO_ENUM_LIST
//     list of values declared with WIERTLO_ENUM or WIERTLO_ENUM_VALUE
// WIERTLO_ENUM_TYPE (type, optional)
//     type of the values in the enum (must be Comparable)
//     if you don't specify a type, a unique Comparable type is used (it has all relational operators)
// WIERTLO_ENUM_AUTONUMBER (#define flag, optional)
//     use autonumbering just like regular enums do
//     (requires WIERTLO_ENUM_TYPE to be assignable type with postfix operator++)
// WIERTLO_ENUM_RUNTIME_ASSERT_ON_NON_BIJECTIVE_ENUM_MAPPINGS (#define flag, optional)
//     make operations which require bijective enum mappings
//     assert on non-bijective mapping between names and values

// INTERFACE FOR THE DECLARED ENUM
// constexpr std::size_t enum_name::count()
//     how many enumeration values were declared
// const WIERTLO_ENUM_TYPE& enum_name::first() 
//     first of the declared values (in the declared order)
// const WIERTLO_ENUM_TYPE& enum_name::last() 
//     last of the declared values (in the declared order)
// const WIERTLO_ENUM_TYPE& enum_name::min()
//     minimal of the declared values (according to operator<)
// const WIERTLO_ENUM_TYPE& enum_name::max() 
//     maximal of the declared values (according to operator<)
// const std::string& enum_name::to_string(const WIERTLO_ENUM_TYPE& enum_value) 
//     string representation of the enum value. 
//     Only works reliably if the mapping between names and values is bijective.
//     You can enable WIERTLO_ENUM_RUNTIME_ASSERT_ON_NON_BIJECTIVE_ENUM_MAPPINGS to check.
// const WIERTLO_ENUM_TYPE& enum_name::from_string(const std::string& string_repr) 
//     enum value of the given string representation.
//     Only works reliably if the mapping between names and values is bijective.
//     You can enable WIERTLO_ENUM_RUNTIME_ASSERT_ON_NON_BIJECTIVE_ENUM_MAPPINGS to check.
// /* unspecified forward range type */ enum_name::values()
//     returns an iterable (having .begin() and .end() member functions) range over all enum values.

struct A { virtual void print() const { std::cout << "A\n"; } };
struct B : A { void print() const override { std::cout << "B\n"; } };
struct C : A { void print() const override { std::cout << "C\n"; } };

bool operator<(const A& lhs, const A& rhs)
{
	return std::type_index(typeid(lhs)) < std::type_index(typeid(rhs));
}

int main()
{
	// It works in declarative context
	// #define WIERTLO_ENUM_RUNTIME_ASSERT_ON_NON_BIJECTIVE_ENUM_MAPPINGS
	#define WIERTLO_ENUM_AUTONUMBER
	#define WIERTLO_ENUM_TYPE int
	#define WIERTLO_ENUM_NAME sounds
	#define WIERTLO_ENUM_LIST \
		WIERTLO_ENUM(alien_die) \
		WIERTLO_ENUM(player_die) \
		WIERTLO_ENUM(building_explosion) \
		WIERTLO_ENUM_VALUE(gun_shot, 50) \
		WIERTLO_ENUM_VALUE(cannon_shot, 50) \
		WIERTLO_ENUM_VALUE(ricochet, -20) \
		WIERTLO_ENUM_VALUE(game_win, 25)
	#include <wiertlo/enum.hpp>

	std::cout << "first enum value " << sounds::first() << "\n";
	std::cout << "last enum value " << sounds::last() << "\n";
	std::cout << "min enum value " << sounds::min() << "\n";
	std::cout << "max enum value " << sounds::max() << "\n";
	std::cout << "enum values count " << sounds::count() << "\n";
	std::cout << "cannon_shot enum value " << sounds::cannon_shot() << "\n";
	for(auto& x : sounds::values())
	{
		std::cout << sounds::to_string(x) << " " << x << " " << sounds::from_string(sounds::to_string(x)) << "\n" << std::flush;
	}

	// not usable (at least, for now) in switch statements (not a big loss) and in constexpr contexts (ouch)
	// use <wiertlo/case_of.hpp>

	#define WIERTLO_ENUM_NAME stuff
	#define WIERTLO_ENUM_LIST \
		WIERTLO_ENUM(a) \
		WIERTLO_ENUM(b) \
		WIERTLO_ENUM(c)
	#include <wiertlo/enum.hpp>
	#define WIERTLO_ENUM_NAME more_stuff
	#define WIERTLO_ENUM_LIST \
		WIERTLO_ENUM(a) \
		WIERTLO_ENUM(b) \
		WIERTLO_ENUM(c)
	#include <wiertlo/enum.hpp>

	std::cout << (stuff::a() == stuff::b()) << " " << (stuff::a() != stuff::c()) << "\n";
	// std::cout << (stuff::a() == more_stuff::a()) // a compiler error

	// wiertlo::enum supports polymorphism
	#define WIERTLO_ENUM_TYPE A
	#define WIERTLO_ENUM_NAME poly
	#define WIERTLO_ENUM_LIST \
		WIERTLO_ENUM_VALUE(a, A()) \
		WIERTLO_ENUM_VALUE(b, B()) \
		WIERTLO_ENUM_VALUE(c, C())
	#include <wiertlo/enum.hpp>

	for(auto& x : poly::values())
	{
		x.print();
	}
}