#ifndef HEADERA6932539C2624202B5FE6AD9400F1CE4
#define HEADERA6932539C2624202B5FE6AD9400F1CE4

namespace wiertlo
{
	namespace detail
	{
		template<typename Function, Function f>
		struct DeleterFromFunction
		{
		    template<typename T>
		    void operator()(T&& x) const
		    {
		        f(std::forward<T>(x));
		    }
		};
	}
}
#define WIERTLO_DELETER_FROM_FUNCTION(Function) wiertlo::detail::DeleterFromFunction<decltype(Function)*, Function>

#endif