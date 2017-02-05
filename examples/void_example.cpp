#include <wiertlo/void.hpp>

int f() { return 42; }
void g() { }

int main()
{
	int a = wiertlo::unvoid_apply(f);
	wiertlo::unit b = wiertlo::unvoid_apply(g);
}