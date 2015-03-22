#include <iostream>
#include <vector>
#include <deque>
#include <memory>
#include <wiertlo/one_based_array_view.hpp>

int main()
{
    int a[] = { 1, 5, 7 };
    auto a_view = make_one_based(a);
    const int b[] = { 1, 5, 7 };
    auto b_view = make_one_based(b);
    std::vector<int> c = { 1, 5, 7 };
    auto c_view = make_one_based(c);
    const std::vector<int> d = { 1, 5, 7 };
    auto d_view = make_one_based(d);
    std::deque<int> e = { 1, 5, 7 };
    auto e_view = make_one_based(e);
    const std::deque<int> f = { 1, 5, 7 };
    auto f_view = make_one_based(f);
    a_view[1] = 2;
    c_view[1] = 3;
    e_view[1] = 4;
    std::cout << a_view[1] << " " << a_view[2] << " " << a_view[3] << "\n";
    std::cout << b_view[1] << " " << b_view[2] << " " << b_view[3] << "\n";
    std::cout << c_view[1] << " " << c_view[2] << " " << c_view[3] << "\n";
    std::cout << d_view[1] << " " << d_view[2] << " " << d_view[3] << "\n";
    std::cout << e_view[1] << " " << e_view[2] << " " << e_view[3] << "\n";
    std::cout << f_view[1] << " " << f_view[2] << " " << f_view[3] << "\n";
}