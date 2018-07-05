#ifndef WIERTLO_COMPILER_HINTS_HPP_B0672D8E18FC40DBB6C9BFD852851368
#define WIERTLO_COMPILER_HINTS_HPP_B0672D8E18FC40DBB6C9BFD852851368

#include <cassert>

#define WIERTLO_STRINGIFY1(x) #x
#define WIERTLO_STRINGIFY2(x) WIERTLO_STRINGIFY1(x)
#define WIERTLO_STRINGIFY3(x) WIERTLO_STRINGIFY2(x)
#define WIERTLO_STRINGIFY4(x) WIERTLO_STRINGIFY3(x)
#define WIERTLO_STRINGIFY5(x) WIERTLO_STRINGIFY4(x)
#define WIERTLO_STRINGIFY6(x) WIERTLO_STRINGIFY5(x)
#define WIERTLO_STRINGIFY7(x) WIERTLO_STRINGIFY6(x)
#define WIERTLO_STRINGIFY8(x) WIERTLO_STRINGIFY7(x)
#define WIERTLO_STRINGIFY9(x) WIERTLO_STRINGIFY8(x)
#define WIERTLO_STRINGIFY10(x) WIERTLO_STRINGIFY9(x)
#define WIERTLO_STRINGIFY11(x) WIERTLO_STRINGIFY10(x)
#define WIERTLO_STRINGIFY12(x) WIERTLO_STRINGIFY11(x)
#define WIERTLO_STRINGIFY13(x) WIERTLO_STRINGIFY12(x)
#define WIERTLO_STRINGIFY14(x) WIERTLO_STRINGIFY13(x)
#define WIERTLO_STRINGIFY15(x) WIERTLO_STRINGIFY14(x)
#define WIERTLO_STRINGIFY16(x) WIERTLO_STRINGIFY15(x)
#define WIERTLO_LINESTR WIERTLO_STRINGIFY2(__LINE__)
// for consistency
#define WIERTLO_FILESTR __FILE__

#ifdef _MSC_VER
#define WIERTLO_ASSUME(...) do { if(!!(__VA_ARGS__)) { assert(false); __assume(0); } } while(0)
#else
#define WIERTLO_ASSUME(...) do { if(!!(__VA_ARGS__)) { assert(false); __builtin_unreachable(); } } while(0)
#endif

#ifdef _MSC_VER
#define WIERTLO_UNREACHABLE do { assert(false); __assume(0); } while(0)
#else
#define WIERTLO_UNREACHABLE do { assert(false); __builtin_unreachable(); } while(0)
#endif

#ifdef _MSC_VER
#define WIERTLO_LIKELY(...) __VA_ARGS__
#elif defined(__clang__) || defined(__GNUC__)
#define WIERTLO_LIKELY(...) __builtin_expect(!!(__VA_ARGS__), 1)
#else
#define WIERTLO_LIKELY(...) __VA_ARGS__
#endif

#ifdef _MSC_VER
#define WIERTLO_UNLIKELY(...) __VA_ARGS__
#elif defined(__clang__) || defined(__GNUC__)
#define WIERTLO_UNLIKELY(...) __builtin_expect(!!(__VA_ARGS__), 0)
#else
#define WIERTLO_UNLIKELY(...) __VA_ARGS__
#endif

#ifdef _MSC_VER
#define WIERTLO_FORCE_INLINE __force_inline
#elif defined(__clang__) || defined(__GNUC__)
#define WIERTLO_FORCE_INLINE __attribute__((always_inline))
#else
#define WIERTLO_FORCE_INLINE // TODO
#endif

#define WIERLO_UNUSED_ARGUMENT(x) static_cast<void>(x)

#ifdef _WIN32
#define WIERTLO_DLLEXPORT __declspec(dllexport)
#else
#define WIERTLO_DLLEXPORT 
#endif

#ifdef _WIN32
#define WIERTLO_DLLIMPORT __declspec(dllimport)
#else
#define WIERTLO_DLLIMPORT
#endif

#ifdef _MSC_VER
#define WIERTLO_DEBUG_BREAK __debugbreak()
#else
#define WIERTLO_DEBUG_BREAK // TODO
#endif

#ifdef _MSC_VER
#define WIERTLO_DEPRECATED_FUNCTION(...) __declspec(deprecated) __VA_ARGS__
#elif defined(__clang__) || defined(__GNUC__)
#define WIERTLO_DEPRECATED_FUNCTION(...) __VA_ARGS__ __attribute__ ((deprecated))
#endif

#endif