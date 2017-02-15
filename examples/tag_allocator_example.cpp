#include <wiertlo/tag_allocator.hpp>
#include <map>
#include <iostream>
#include <vector>
#include <string>
#include <list>

struct A {};
struct B {};

void a()
{
	auto request = [](const std::string& s){ return std::string("unsafe data\n"); };
	std::map<std::string, std::string> recordset;
	auto encode = [](const std::string& s){ return std::string(s.begin()+2, s.end()); };
	auto write = [](const std::string& s){ std::cout.write(s.data(), s.size()); };
	// adapted from https://www.joelonsoftware.com/2005/05/11/making-wrong-code-look-wrong/
	std::string us = request("name");
	std::string usName = us;
	recordset["usName"] = usName;
	std::string sName = encode(recordset["usName"]);
	write(sName);

	for(auto&& record : recordset)
	{
		write(record.second); // let's hope no one will do that
	}
}

void b()
{
	struct safe {};
	typedef std::basic_string<char, std::char_traits<char>, wiertlo::tag_allocator<char, safe>> safe_string;
	auto request = [](const std::string& s){ return std::string("unsafe data\n"); };
	std::map<std::string, std::string> recordset;
	auto encode = [](const std::string& s){ return safe_string(s.begin()+2, s.end()); };
	auto write = [](const safe_string& s){ std::cout.write(s.data(), s.size()); };
	// adapted from https://www.joelonsoftware.com/2005/05/11/making-wrong-code-look-wrong/
	std::string us = request("name");
	std::string usName = us;
	recordset["usName"] = usName;
	safe_string sName = encode(recordset["usName"]);
	write(sName);

	for(auto&& record : recordset)
	{
		//write(record.second); // fails to compile
		write(encode(record.second));
	}
}

int main()
{
	{
		std::vector<int, wiertlo::tag_allocator<int, A>> left, left2;
		std::vector<int, wiertlo::tag_allocator<int, B>> right;
		left.push_back(4);
		right.push_back(42);
		left = left2; // should be fine
		//left = right; // should fail to compile
	}
	{
		std::list<int, wiertlo::tag_allocator<int, A>> left, left2;
		std::list<int, wiertlo::tag_allocator<int, B>> right;
		left.push_back(4);
		right.push_back(42);
		left = left2; // should be fine
		//left = right; // should fail to compile
	}
	a();
	b();
}