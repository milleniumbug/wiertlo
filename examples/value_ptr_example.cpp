#include <iostream>
#include "value_ptr_example.h"

struct MyResourceImpl
{
	unsigned resx;
	unsigned resy;
	int state;

	std::string name;
};

MyResource::MyResource(std::string nam) :
	impl(new MyResourceImpl)
{
	impl->resx = 300;
	impl->resy = 200;
	impl->state = 0;
	impl->name = nam;
}

void MyResource::refresh()
{
	++(impl->state);
}

void MyResource::display()
{
	serialize(std::cout);
}

void MyResource::serialize(std::ostream& os)
{
	os << "(my-resource :resx " << impl->resx << " :resy " << impl->resy << " :state " << impl->state << " :name \"" << impl->name << "\")\n";
}

//EXPECTED OUTPUT:
/*
(my-resource :resx 300 :resy 200 :state 10 :name "Mario")
(my-resource :resx 300 :resy 200 :state 0 :name "Luigi")
(my-resource :resx 300 :resy 200 :state 10 :name "Mario")
(my-resource :resx 300 :resy 200 :state 10 :name "Mario")
(my-resource :resx 300 :resy 200 :state 10 :name "Mario")
(my-resource :resx 300 :resy 200 :state 110 :name "Mario")
*/

int main()
{
	MyResource res1("Mario"), res2("Luigi");
	for(int i = 0; i < 10; ++i) res1.refresh();
	res1.display();
	res2.display();

	res2 = res1;

	res1.display();
	res2.display();

	for(int i = 0; i < 100; ++i) res2.refresh();
	res1.display();
	res2.display();	
}