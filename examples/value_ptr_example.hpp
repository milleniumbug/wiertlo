#pragma once
#include <wiertlo/value_ptr.hpp>
#include <string>
#include <iosfwd>

struct MyResourceImpl;
class MyResource
{
private:
	wiertlo::value_ptr<MyResourceImpl> impl;
public:
	MyResource(std::string name);
	void refresh();
	void display();
	void serialize(std::ostream& os);
};