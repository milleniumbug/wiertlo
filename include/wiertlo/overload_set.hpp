#ifndef HEADER003A3D7920834CF9BB4DE19FB45139AD
#define HEADER003A3D7920834CF9BB4DE19FB45139AD

#include <utility>
#include <type_traits>

// Emulation of Xeo's overload set proposal with macros and C++14 polymorphic lambdas
#define WIERTLO_OVERLOAD_SET(function) ([](auto&&... x) -> decltype(( function(std::forward<decltype(x)>(x)...) )) { return function(std::forward<decltype(x)>(x)...); })

#endif