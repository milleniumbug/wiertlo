#ifndef WIERTLO_NOISY_HPP_E9E22037161B4CEA869273970DA6FE93
#define WIERTLO_NOISY_HPP_E9E22037161B4CEA869273970DA6FE93

#include <typeinfo>
#include <iostream>
#include <utility>

namespace wiertlo
{
    namespace detail {
        struct default_logger {
            template <typename STR>
            void operator()(STR&& str) {
                std::cout << std::forward<STR>(str);
            }
        };
    }
    
	/// noisy
	///
	/// A class logs all of the calls to Big Five and the default constructor
	/// The name of the template parameter, received as if by call
	/// to `typeid(T).name()`, is displayed in the logs.
	template<typename T, typename LOG = detail::default_logger>
	struct noisy : private LOG
	{
		noisy& operator=(noisy&&) noexcept {
		    LOG::operator()("operator=(noisy<");
		    LOG::operator()(typeid(T).name());
		    LOG::operator()(">&&)\n");
		    return *this; 
		}
		
		noisy& operator=(const noisy&) {
		    LOG::operator()("operator=(const noisy<"); 
		    LOG::operator()(typeid(T).name());
		    LOG::operator()(">&)\n"); 
		    return *this; 
		}
		
		noisy(const noisy&) {
		    LOG::operator()("noisy(const noisy<");
		    LOG::operator()(typeid(T).name());
		    LOG::operator()(">&)\n"); 
		}
		
		noisy(noisy&&) noexcept {
		    LOG::operator()("noisy(noisy<");
		    LOG::operator()(typeid(T).name());
		    LOG::operator()(">&&)\n");
		}
		
		~noisy() {
		    LOG::operator()("~noisy<");
		    LOG::operator()(typeid(T).name());
		    LOG::operator()(">()\n");
		}
		
		noisy() {
		    LOG::operator()("noisy<");
		    LOG::operator()(typeid(T).name());
		    LOG::operator()(">()\n"); 
		}
	};
}

#endif
