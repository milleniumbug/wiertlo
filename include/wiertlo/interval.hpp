#ifndef HEADER6fb6815595e78acb09e8a19b6c70dbda
#define HEADER6fb6815595e78acb09e8a19b6c70dbda

namespace wiertlo
{
	template<typename T, typename Interval>
	bool is_between(T value, Interval interval)
	{
		return above_lower_bound(value, interval) && below_upper_bound(value, interval);
	}

#define WIERTLO_INTERNAL_DETAIL_DEFINE_INTERVAL_CLASS(class_name, make_function_name) \
	template<typename U, typename V> \
	struct class_name \
	{ \
		U lower_bound; \
		V upper_bound; \
		 \
		class_name(U lower, V upper) : \
			lower_bound(lower), \
			upper_bound(upper) \
		{ \
			 \
		} \
	}; \
	 \
	template<typename U, typename V> \
	class_name<U, V> make_function_name(U lower, V upper) \
	{ \
		return class_name<U, V>(lower, upper); \
	}

	WIERTLO_INTERNAL_DETAIL_DEFINE_INTERVAL_CLASS(InclusiveInterval, make_inclusive_interval)
	WIERTLO_INTERNAL_DETAIL_DEFINE_INTERVAL_CLASS(UpperExclusiveInterval, make_interval)
#undef WIERTLO_INTERNAL_DETAIL_DEFINE_INTERVAL_CLASS

	template<typename T, typename U, typename V>
	bool above_lower_bound(T value, InclusiveInterval<U, V> interval)
	{
		return value >= interval.lower_bound;
	}

	template<typename T, typename U, typename V>
	bool below_upper_bound(T value, InclusiveInterval<U, V> interval)
	{
		return value <= interval.upper_bound;
	}

	template<typename T, typename U, typename V>
	bool above_lower_bound(T value, UpperExclusiveInterval<U, V> interval)
	{
		return value >= interval.lower_bound;
	}

	template<typename T, typename U, typename V>
	bool below_upper_bound(T value, UpperExclusiveInterval<U, V> interval)
	{
		return value < interval.upper_bound;
	}
}

#endif