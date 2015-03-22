#ifndef HEADER2499DC283D654FB086461D0FE8712029
#define HEADER2499DC283D654FB086461D0FE8712029

#include <cstddef>

template<typename T>
class OneBasedArrayView
{
    T* a;
public:
    auto operator[](std::size_t pos) -> decltype((*a)[pos-1]) { return (*a)[pos-1]; }
    auto operator[](std::size_t pos) const -> decltype((*a)[pos-1]) { return (*a)[pos-1]; }
    OneBasedArrayView(T& c) { a = &c; }
};

template<typename T>
OneBasedArrayView<T> make_one_based(T& a) { return OneBasedArrayView<T>(a); }

template<typename T>
OneBasedArrayView<const T> make_one_based(const T& a) { return OneBasedArrayView<const T>(a); }

#endif