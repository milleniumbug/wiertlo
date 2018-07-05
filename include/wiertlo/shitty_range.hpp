#ifndef HEADERE4561CDE4BDE47E2B26DD98B193E95F2
#define HEADERE4561CDE4BDE47E2B26DD98B193E95F2

// essentially an extended version of
// #define R(c) c.begin(), c.end()
// to make it fail properly on temporaries
// and support arrays and custom types with free begin() function

#include <iterator>
#include <type_traits>

namespace wiertlo
{
	namespace detail
	{
		namespace adl_tricks
		{
			using std::begin;
			using std::end;

			struct AdlBegin
			{
				template<typename Cont>
				auto operator()(Cont&& c) -> decltype(begin(c))
				{
					static_assert(std::is_lvalue_reference<Cont&&>::value, "passing temporary ranges not supported");
					return begin(c);
				}

				static AdlBegin mvp_barrier() { return AdlBegin(); }
			};

			struct AdlEnd
			{
				template<typename Cont>
				auto operator()(Cont&& c) -> decltype(end(c))
				{
					static_assert(std::is_lvalue_reference<Cont&&>::value, "passing temporary ranges not supported");
					return end(c);
				}

				static AdlEnd mvp_barrier() { return AdlEnd(); }
			};
		}
	}
}

#define WIERTLO_SHITTY_RANGE(...) ::wiertlo::detail::adl_tricks::AdlBegin::mvp_barrier()(__VA_ARGS__), ::wiertlo::detail::adl_tricks::AdlEnd::mvp_barrier()(__VA_ARGS__)

#endif