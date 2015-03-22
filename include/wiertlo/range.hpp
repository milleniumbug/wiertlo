#ifndef HEADERE4561CDE4BDE47E2B26DD98B193E95F2
#define HEADERE4561CDE4BDE47E2B26DD98B193E95F2

#include <iterator>
#include <wiertlo/adl_invoke.hpp>

#define WIERTLO_RANGE(cont) WIERTLO_INVOKE_WITH_STD_ADL(begin, cont), WIERTLO_INVOKE_WITH_STD_ADL(end, cont)

#endif