#ifndef HEADER90F0E2E5C95D48D0A89175C05F12B72E
#define HEADER90F0E2E5C95D48D0A89175C05F12B72E

#include <tuple>
#include <utility>

namespace wiertlo
{
	namespace tuple
	{
		template<typename Tuple, typename Function, std::size_t Index>
		struct map_impl
		{
#define FIRST_ARG \
	std::make_tuple(f(std::get< std::tuple_size<Tuple>::value - Index>(tuple)))
#define SECOND_ARG \
	map_impl<Tuple, Function, Index-1>::do_it(tuple, f)
			static auto do_it(Tuple& tuple, Function f) ->
				decltype(std::tuple_cat(FIRST_ARG, SECOND_ARG))
			{
				// force sequential evaluation
				auto&& a = FIRST_ARG;
				auto&& b = SECOND_ARG;
				return std::tuple_cat(a, b);
			}
		};
#undef SECOND_ARG
#undef FIRST_ARG

		template<typename Tuple, typename Function>
		struct map_impl<Tuple, Function, 0>
		{
			static std::tuple<> do_it(Tuple& tuple, Function f)
			{
				return std::tuple<>();
			}
		};

#define RETURN_EXPR map_impl<Tuple, Function, std::tuple_size<Tuple>::value>::do_it(tuple, f)
		template<typename Tuple, typename Function>
		auto map(Tuple& tuple, Function f) ->
			decltype(RETURN_EXPR)
		{
			return RETURN_EXPR;
		}
#undef RETURN_EXPR


		template<typename Tuple, typename Function, std::size_t Index, typename = void>
		struct for_each_impl_one_arg
		{
			static void do_it(Tuple& tuple, Function f)
			{
				f(std::get< std::tuple_size<Tuple>::value - Index >(tuple));
				for_each_impl_one_arg<Tuple, Function, Index-1>::do_it(tuple, f);
			}
		};

		template<typename Tuple, typename Function>
		struct for_each_impl_one_arg<Tuple, Function, 0>
		{
			static void do_it(Tuple& tuple, Function f)
			{
				
			}
		};

		template<typename Tuple, typename Function, std::size_t Index, typename = void>
		struct for_each_impl_two_arg
		{
			static void do_it(Tuple& tuple, Function f)
			{
				f(std::get< std::tuple_size<Tuple>::value - Index >(tuple), std::tuple_size<Tuple>::value - Index);
				for_each_impl_two_arg<Tuple, Function, Index-1>::do_it(tuple, f);
			}
		};

		template<typename Tuple, typename Function>
		struct for_each_impl_two_arg<Tuple, Function, 0>
		{
			static void do_it(Tuple& tuple, Function f)
			{
				
			}
		};

		template<typename Tuple, typename Function>
		void foreach(Tuple& tuple, Function f)
		{
			for_each_impl_one_arg<Tuple, Function, std::tuple_size<Tuple>::value>::do_it(tuple, f);
		}

		template<typename Tuple, typename Function>
		void foreach_with_index(Tuple& tuple, Function f)
		{
			for_each_impl_two_arg<Tuple, Function, std::tuple_size<Tuple>::value>::do_it(tuple, f);
		}

	}
}

#endif