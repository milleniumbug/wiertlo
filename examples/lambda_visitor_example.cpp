#include <iostream>
#include <map>
#include <vector>
#include <boost/variant.hpp>
#include <wiertlo/lambda_visitor.hpp>

int main()
{
	boost::variant<std::vector<int>, std::map<int, int>> v = std::vector<int>();
	int x;
	boost::apply_visitor(wiertlo::make_lambda_visitor<void>(
		[&](const std::vector<int>& o)
		{
			x = 1;
		},
		[&](const std::map<int, int>& o)
		{
			x = 4;
		}), v);
	std::cout << x << "\n";
	std::cout << boost::apply_visitor(wiertlo::make_lambda_visitor<std::string>(
		[&](const std::vector<int>& o)
		{
			return std::string("vector");
		},
		[&](const std::map<int, int>& o)
		{
			return std::string("map");
		}), v) << "\n";
}