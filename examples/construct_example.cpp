#include <wiertlo/construct.hpp>
#include <type_traits>
#include <vector>

int main()
{
	alignas(std::vector<int>) char pool[sizeof(std::vector<int>)*5];
	// run-time assertion on misaligned memory
	wiertlo::construct<std::vector<int>>(pool+1);
}