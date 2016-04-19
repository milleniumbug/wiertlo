#ifndef WIERTLO_LAMBDA_VISITOR_HPP_37650BC841CB40B6B9FD6D8B07B585E4
#define WIERTLO_LAMBDA_VISITOR_HPP_37650BC841CB40B6B9FD6D8B07B585E4

namespace wiertlo
{
	// lambda visitor, thanks to
	// R. Martinho Fernandes http://stackoverflow.com/a/7868427/1012936
	// and lurscher http://stackoverflow.com/a/7870614/1012936
	
	template <typename ReturnType, typename... Lambdas>
	struct lambda_visitor;
	
	template <typename ReturnType, typename Lambda1, typename... Lambdas>
	struct lambda_visitor<ReturnType, Lambda1, Lambdas...>
	    : public lambda_visitor<ReturnType, Lambdas...>, public Lambda1
	{
		using Lambda1::operator();
		using lambda_visitor<ReturnType, Lambdas...>::operator();
		lambda_visitor(Lambda1 l1, Lambdas... lambdas)
		    : lambda_visitor<ReturnType, Lambdas...>(lambdas...), Lambda1(l1)
		{
		}
	};
	
	
	template <typename ReturnType, typename Lambda1>
	struct lambda_visitor<ReturnType, Lambda1>
	    : public Lambda1
	{
		typedef ReturnType result_type;
		
		using Lambda1::operator();
		lambda_visitor(Lambda1 l1)
		    : Lambda1(l1)
		{
		}
	};
	
	
	template <typename ReturnType>
	struct lambda_visitor<ReturnType>
	{
		typedef ReturnType result_type;
		
		lambda_visitor() {}
	};
	
	template <typename ReturnType, typename... Lambdas>
	lambda_visitor<ReturnType, Lambdas...> make_lambda_visitor(Lambdas... lambdas)
	{
		return lambda_visitor<ReturnType, Lambdas...>(lambdas...);
	}
}

#endif