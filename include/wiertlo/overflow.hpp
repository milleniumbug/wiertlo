#ifndef HEADER423971b7fcd486dd93cf75b5af1670c8
#define HEADER423971b7fcd486dd93cf75b5af1670c8


namespace wiertlo
{
	namespace overflow_policy
	{
		struct strict {};
		struct strict_but_no_ranges {};
		struct implementation_defined_behaviour_acceptable {};
		struct saturation {};
		struct unsafe_ignore {};
	}
}

#endif