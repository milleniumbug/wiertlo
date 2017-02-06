#include <wiertlo/comp_from_key.hpp>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

struct Person
{
	std::string first_name;
	std::string last_name;
	int age;
};

int main()
{
	{
		std::vector<std::vector<int>> vecvec = { { 0 }, {}, { 0, 42, 23, 55 }, { 0, 0 } };
		std::sort(vecvec.begin(), vecvec.end(), wiertlo::comp_from_key([](auto&& vec){ return vec.size(); }));
		for(auto&& vec : vecvec)
		{
			std::cout << vec.size() << "\n";
		}
	}
	std::cout << "\n\n";
	{
		std::vector<Person> people = { Person{"John", "Rambo", 42}, Person{"Joffrey", "Baratheon", 14}, Person{"Kyle", "Reese", 25} };
		std::sort(people.begin(), people.end(), wiertlo::comp_from_key(std::mem_fn(&Person::age), std::greater<>()));
		for(auto&& person : people)
		{
			std::cout << person.first_name << " " << person.last_name << ", " << person.age << "\n";
		}
	}
}