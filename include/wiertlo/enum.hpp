#ifndef WIERTLO_ENUM_INCLUDED
#error "#include <wiertlo/enum_enable.hpp> to enable this functionality"
#define WIERTLO_ENUM_ERROR
#endif

#ifndef WIERTLO_ENUM_NAME
#error "enum name needs to be defined"
#define WIERTLO_ENUM_ERROR
#endif

#ifndef WIERTLO_ENUM_LIST
#error "enum's list of values needs to be defined"
#define WIERTLO_ENUM_ERROR
#endif

#ifndef WIERTLO_ENUM_TYPE
#define WIERTLO_ENUM_TYPE_DECLARATION using underlying_type = ::wiertlo::detail::enumeration::self_referring_handle<_unique_type_>
#else
#define WIERTLO_ENUM_TYPE_DECLARATION using underlying_type = WIERTLO_ENUM_TYPE
#endif

#ifndef WIERTLO_ENUM_ERROR
class WIERTLO_ENUM_NAME
{
	private: struct _unique_type_ {};

	public: WIERTLO_ENUM_TYPE_DECLARATION;

	public: static constexpr std::size_t count()
	{
		#define WIERTLO_ENUM_VALUE(name, value) 1,
		#define WIERTLO_ENUM(name) 1,
		return ::wiertlo::detail::enumeration::sum(WIERTLO_ENUM_LIST 0);
		#undef WIERTLO_ENUM_VALUE
		#undef WIERTLO_ENUM
	}

	#ifdef WIERTLO_ENUM_AUTONUMBER
	private: static underlying_type& _number_()
	{
		static underlying_type n = underlying_type();
		return n;
	}

	private: static underlying_type _get_next_number_()
	{
		return _number_()++;
	}

	private: static underlying_type& _set_next_number_(underlying_type value)
	{
		_number_() = value;
		return _number_();
	}
	#define WIERTLO_ENUM_VALUE(name, value) static const underlying_type& name() { static const auto x = _set_next_number_(value); return x; }
	#define WIERTLO_ENUM(name) static const underlying_type& name() { static const auto x = _get_next_number_(); return x; }
	public: WIERTLO_ENUM_LIST
	#undef WIERTLO_ENUM_VALUE
	#undef WIERTLO_ENUM
	#else
	#define WIERTLO_ENUM_VALUE(name, value) static const underlying_type& name() { static const auto x = value; return x; }
	#define WIERTLO_ENUM(name) static const underlying_type& name() { static const underlying_type x; return x; }
	public: WIERTLO_ENUM_LIST
	#undef WIERTLO_ENUM_VALUE
	#undef WIERTLO_ENUM
	#endif

	private: using _string_to_enum_map_type_ = std::map<const ::wiertlo::detail::enumeration::string_type*, const underlying_type*, ::wiertlo::detail::enumeration::indirect_less>;
	#define WIERTLO_ENUM_VALUE(name, value) _string_to_enum_map_type_::value_type(&to_string(name()), &name()),
	#define WIERTLO_ENUM(name) _string_to_enum_map_type_::value_type(&to_string(name()), &name()),
	private: static const _string_to_enum_map_type_& _string_to_enum_map_()
	{
		static const _string_to_enum_map_type_ m = { WIERTLO_ENUM_LIST };
		return m;
	}

	public: static const underlying_type& from_string(const ::wiertlo::detail::enumeration::string_type& repr)
	{
		#ifdef WIERTLO_ENUM_RUNTIME_ASSERT_ON_NON_BIJECTIVE_ENUM_MAPPINGS
		assert(_is_bijective_());
		#endif
		return *_string_to_enum_map_().at(&repr);
	}
	#undef WIERTLO_ENUM_VALUE
	#undef WIERTLO_ENUM

	private: using _enum_to_string_map_type_ = std::map<const underlying_type*, ::wiertlo::detail::enumeration::string_type, ::wiertlo::detail::enumeration::indirect_less>;
	#define WIERTLO_ENUM_VALUE(name, value) _enum_to_string_map_type_::value_type(&name(), #name),
	#define WIERTLO_ENUM(name) _enum_to_string_map_type_::value_type(&name(), #name),
	private: static const _enum_to_string_map_type_& _enum_to_string_map_()
	{
		static const _enum_to_string_map_type_ m = { WIERTLO_ENUM_LIST };
		return m;
	}

	public: static const ::wiertlo::detail::enumeration::string_type& to_string(const underlying_type& value)
	{
		#ifdef WIERTLO_ENUM_RUNTIME_ASSERT_ON_NON_BIJECTIVE_ENUM_MAPPINGS
		assert(_is_bijective_());
		#endif
		return _enum_to_string_map_().at(&value);
	}
	#undef WIERTLO_ENUM_VALUE
	#undef WIERTLO_ENUM

	#define WIERTLO_ENUM_VALUE(name, value) &name(),
	#define WIERTLO_ENUM(name) &name(),
	private: static const std::vector<const underlying_type*>& _values_cont_()
	{
		static const std::vector<const underlying_type*> values_arr = { WIERTLO_ENUM_LIST };
		return values_arr;
	}

	public: static ::wiertlo::detail::enumeration::indirect_range<const std::vector<const underlying_type*>> values()
	{
		return ::wiertlo::detail::enumeration::indirect_range<const std::vector<const underlying_type*>>(&_values_cont_());
	}
	#undef WIERTLO_ENUM_VALUE
	#undef WIERTLO_ENUM

	public: static const underlying_type& min()
	{
		return *_enum_to_string_map_().begin()->first;
	}

	public: static const underlying_type& max()
	{
		return *_enum_to_string_map_().rbegin()->first;
	}

	public: static const underlying_type& first()
	{
		return *_values_cont_().front();
	}

	public: static const underlying_type& last()
	{
		return *_values_cont_().back();
	}

	private: static bool _is_bijective_()
	{
		return count() == _string_to_enum_map_().size() && count() == _enum_to_string_map_().size();
	}
};
#endif

#undef WIERTLO_ENUM_RUNTIME_ASSERT_ON_NON_BIJECTIVE_ENUM_MAPPINGS
#undef WIERTLO_ENUM_TYPE_DECLARATION
#undef WIERTLO_ENUM_ERROR
#undef WIERTLO_ENUM_AUTONUMBER
#undef WIERTLO_ENUM_TYPE
#undef WIERTLO_ENUM_LIST
#undef WIERTLO_ENUM_NAME