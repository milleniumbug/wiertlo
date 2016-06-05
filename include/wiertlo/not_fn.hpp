#ifndef WIERTLO_NOT_FN_HPP_C7E09E066E924528B30733E1ACD6945F
#define WIERTLO_NOT_FN_HPP_C7E09E066E924528B30733E1ACD6945F

#include <utility>

namespace wiertlo
{
	namespace detail
	{
		template<typename F>
		struct not_fn_type
		{
		private:
			F fun;
		public:
			template<typename... Args>
			auto operator()(Args&&... args) const -> decltype(!fun(std::forward<Args>(args)...))
			{
				return !fun(std::forward<Args>(args)...);
			}
			
			template<typename... Args>
			auto operator()(Args&&... args) -> decltype(!fun(std::forward<Args>(args)...))
			{
				return !fun(std::forward<Args>(args)...);
			}
			
			not_fn_type(F&& fun) :
				fun(std::move(fun))
			{
				
			}
			
			not_fn_type(const F& fun) :
				fun(fun)
			{
				
			}
		};
		
		template<typename T>
		struct unqualified
		{
			typedef typename std::remove_cv<typename std::remove_reference<T>::type>::type type;
		};
	}
	
	template<typename Function>
	detail::not_fn_type<typename detail::unqualified<Function>::type> not_fn(Function&& f)
	{
		return detail::not_fn_type<typename detail::unqualified<Function>::type>(std::forward<Function>(f));
	}
}

#endif