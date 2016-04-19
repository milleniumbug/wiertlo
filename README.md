# wiertlo
C++11 and C++14 utility pack

Header description
------------------

- `<wiertlo/arithmetic_if.hpp>` - FORTRAN-style three-way arithmetic if.
- `<wiertlo/case_of.hpp>` - `switch`-style flow control without fall-through.
- `<wiertlo/construct.hpp>` - less error-prone in-place construction.
- `<wiertlo/defs.hpp>` - C++ template typedefs for built-in types.
- `<wiertlo/deleter_from_function.hpp>` - simplify wrapping legacy C API with `std::unique_ptr`.
- `<wiertlo/enum.hpp>` - improved enums. You need to include `<wiertlo/enum_enable.hpp>` beforehand
- `<wiertlo/interval.hpp>` - verify if a variable is in a given interval. Support for half-open and closed intervals.
- `<wiertlo/lambda_visitor.hpp>` - factory function for creating a `StaticVisitor` suitable for usage in `boost::apply_visitor` from lambdas provided in the argument list.
- `<wiertlo/map_ops.hpp>` - generate the simplified access function for maps for any `optional` type, also `key(kvp)` and `value(kvp)` helpers.
- `<wiertlo/make.hpp>` - common factory functions
- `<wiertlo/meta.hpp>` - metaprogramming library: type lists and type traits.
- `<wiertlo/noisy.hpp>` - log all calls to Big Five.
- `<wiertlo/one_based_array.hpp>` - array decorator to make them one-based.
- `<wiertlo/overload_set.hpp>` - (C++14) pass entire overload sets into standard algorithms.
- `<wiertlo/pimpl_handle.hpp>` - generic class for PIMPL idiom
- `<wiertlo/shared_member.hpp>` - share ownership of a subobject with the enclosing object.
- `<wiertlo/tagged_ptr.hpp>` - dirty low-level pointer tagging.
- `<wiertlo/tuple.hpp>` - tuple algorithms (C++14 recommended for polymorphic lambdas).
- `<wiertlo/value_ptr.hpp>` - copyable smart pointer with value semantics. 

Design rationale
----------------

- Make abstractions so simple they can be introduced in minutes.
- Don't aim for half-smart behaviour if you can't be smart - be dumb instead.
- No header interdependencies inside the library - every header must be independent so users can cut out single headers, even at the cost of small DRY violations.
- Always aim for DRY otherwise.
- While small corrections to require C++11 instead of C++14 are acceptable, heroic sacrifices and working out compiler bugs are not.

Name...?
--------

wiertło is Polish for "drill bit"
