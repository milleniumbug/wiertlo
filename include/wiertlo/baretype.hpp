#ifndef HEADER54a2c8e037ec4dd9bd3cb55515a75128
#define HEADER54a2c8e037ec4dd9bd3cb55515a75128

#include <type_traits>

#define WIERTLO_BARETYPE(...) std::remove_cv_t<std::remove_reference_t<decltype((__VA_ARGS__))>>

#endif