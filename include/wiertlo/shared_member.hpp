#ifndef WIERTLO_SHARED_MEMBER_HPP_E2C33170594F47018B7AAA84168DB217
#define WIERTLO_SHARED_MEMBER_HPP_E2C33170594F47018B7AAA84168DB217

#include <memory>

namespace wiertlo
{
	// shared_member
	//
	// Returns a shared_ptr that shares ownership with a passed pointer, but
	// points to a member object of the pointed object. If the passed shared_ptr is
	// null, returns nullptr. If the passed pointer to member object is null,
	// the behaviour is undefined.
	template<typename T, typename Member>
	std::shared_ptr<Member> shared_member(std::shared_ptr<T> ptr, Member T::*member)
	{
		// using std::shared_ptr's aliasing constructor
		// see https://www.justsoftwaresolutions.co.uk/cplusplus/shared-ptr-secret-constructor.html
		if(ptr)
			return std::shared_ptr<Member>(ptr, &(ptr.get()->*member));
		else
			return nullptr;
	}
}

#endif