# wiertlo

[![Join the chat at https://gitter.im/wiertlo/Lobby](https://badges.gitter.im/wiertlo/Lobby.svg)](https://gitter.im/wiertlo/Lobby?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
C++11 and C++14 utility pack

Header description
------------------

- `<wiertlo/arithmetic_if.hpp>` - FORTRAN-style three-way arithmetic if.
- `<wiertlo/baretype.hpp>` - `decltype`-like macro for the common use case of accessing the unqualified type.
- `<wiertlo/case_of.hpp>` - `switch`-style flow control without fall-through.
- `<wiertlo/comp_from_key.hpp>` - Make a compare function from a key function.
- `<wiertlo/construct.hpp>` - less error-prone in-place construction.
- `<wiertlo/defs.hpp>` - C++ template typedefs for built-in types.
- `<wiertlo/deleter_from_function.hpp>` - simplify wrapping legacy C API with `std::unique_ptr`.
- `<wiertlo/enum.hpp>` - improved enums. You need to include `<wiertlo/enum_enable.hpp>` beforehand
- `<wiertlo/interval.hpp>` - verify if a variable is in a given interval. Support for half-open and closed intervals.
- `<wiertlo/lambda_visitor.hpp>` - factory function for creating a `StaticVisitor` suitable for usage in `boost::apply_visitor` from lambdas provided in the argument list.
- `<wiertlo/make.hpp>` - common factory functions
- `<wiertlo/map_ops.hpp>` - generate the simplified access function for maps for any `optional` type, also `key(kvp)` and `value(kvp)` helpers.
- `<wiertlo/meta.hpp>` - metaprogramming library: type lists and type traits.
- `<wiertlo/noisy.hpp>` - log all calls to Big Five.
- `<wiertlo/one_based_array.hpp>` - array decorator to make them one-based.
- `<wiertlo/overload_set.hpp>` - (C++14) pass entire overload sets into standard algorithms.
- `<wiertlo/pimpl_handle.hpp>` - generic class for PIMPL idiom
- `<wiertlo/shared_member.hpp>` - share ownership of a subobject with the enclosing object.
- `<wiertlo/shitty_range.hpp>` - World's Simplest Range Library™.
- `<wiertlo/string.hpp>` - string utilities.
- `<wiertlo/strong_typedef.hpp>` - create distinct types.
- `<wiertlo/tagged_ptr.hpp>` - dirty low-level pointer tagging.
- `<wiertlo/unique_handle.hpp>` - generalization of `std::unique_ptr` to arbitrary handles (like file descriptors)
- `<wiertlo/tuple.hpp>` - tuple algorithms (C++14 recommended for polymorphic lambdas).
- `<wiertlo/value_ptr.hpp>` - copyable smart pointer with value semantics.
- `<wiertlo/void.hpp>` - workarounds for `void` being a special snowflake.

**NOTICE:** the headers not listed in the above list are considered non-public and/or beta. They may even not compile. They may be also subject to changes. You have been warned.

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
