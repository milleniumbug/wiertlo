#pragma once
#include <iostream>
#include <sstream>
#include <type_traits>
#include <limits>
#include <climits>
#include <initializer_list>
#include <cstddef>
#include <algorithm>

namespace wiertlo
{
	namespace pretty
	{
		namespace detail
		{
			// helpers
			inline std::string c_string_literal_without_quotes_from_string(const char* literal, std::size_t size)
			{
				std::string result;
				static_assert(CHAR_BIT == 8, "8 bit chars assumed");

				auto printable = [](unsigned char ch)
				{
					return
						ch >= 32 && ch < 127; // printable;
				};
				for(std::size_t i = 0; i < size; ++i)
				{
					const auto ch = literal[i];
					const auto uch = static_cast<unsigned char>(ch);
					if(ch == '\n')
					{
						result += "\\n";
					}
					else if(ch == '\r')
					{
						result += "\\r";
					}
					else if(ch == '\?')
					{
						result += "\\?";
					}
					else if(ch == '\t')
					{
						result += "\\t";
					}
					else if(ch == '\'')
					{
						result += "\\\'";
					}
					else if(ch == '\"')
					{
						result += "\\\"";
					}
					else if(ch == '\\')
					{
						result += "\\\\";
					}
					else if(printable(uch))
					{
						result += ch;
					}
					else
					{
						auto hexchars = "0123456789ABCDEF";
						result += "\\x";
						result += hexchars[uch / 16];
						result += hexchars[uch % 16];
					}
				}
				return result;
			}

			template<typename T1, typename T2 = void, typename T3 = void, typename T4 = void>
			struct void_type
			{
				typedef void type;
			};

			template<typename T1, typename T2 = void, typename T3 = void, typename T4 = void>
			using void_t = typename void_type<T1, T2, T3, T4>::type;

			// like numeric_limits, but according to standard,
			// and what we can safely display as a literal
			// hence, the safe_limits<int>::min() is -32767
			// because int can be as low as 16 bits
			// also -32768 can be long, because it's a literal
			// with unary negation operator applied
			// which means -32768 is long, not int, on platforms with
			// 16 bit ints
			template<typename Numeric>
			struct safe_limits
			{
				// interface:
				// static Numeric min()
				// minimal value that can be safely displayed as a literal
				// static Numeric max()
				// maximal value that can be safely displayed as a literal
				// static const char* type_name()
				// the name of the type, preferably as a single token, 
				// or multi token if there's no single token way to spell it
				// static const char* suffix()
				// a suffix that can be attached to a decimal literal to make it of type Numeric
				// or nullptr, if there's no such thing
			};

			template<>
			struct safe_limits<int>
			{
				typedef int type;

				static type min()
				{
					return -32767;
				}

				static type max()
				{
					return 32767;
				}

				static const char* type_name()
				{
					return "int";
				}

				static const char* suffix()
				{
					return "";
				}
			};

			template<>
			struct safe_limits<long>
			{
				typedef long type;

				static type min()
				{
					return -2147483647;
				}

				static type max()
				{
					return 2147483647;
				}

				static const char* type_name()
				{
					return "long";
				}

				static const char* suffix()
				{
					return "l";
				}
			};

			template<>
			struct safe_limits<long long>
			{
				typedef long long type;

				static type min()
				{
					return -9223372036854775807;
				}

				static type max()
				{
					return 9223372036854775807;
				}

				static const char* type_name()
				{
					return "long long";
				}

				static const char* suffix()
				{
					return "ll";
				}
			};

			template<>
			struct safe_limits<short>
			{
				typedef short type;

				static type min()
				{
					return -32767;
				}

				static type max()
				{
					return 32767;
				}

				static const char* type_name()
				{
					return "short";
				}

				static const char* suffix()
				{
					return nullptr;
				}
			};

			template<>
			struct safe_limits<signed char>
			{
				typedef signed char type;

				static type min()
				{
					return -127;
				}

				static type max()
				{
					return 127;
				}

				static const char* type_name()
				{
					return "signed char";
				}

				static const char* suffix()
				{
					return nullptr;
				}
			};

			template<>
			struct safe_limits<unsigned>
			{
				typedef unsigned type;

				static type min()
				{
					return 0;
				}

				static type max()
				{
					return 65535u;
				}

				static const char* type_name()
				{
					return "unsigned";
				}

				static const char* suffix()
				{
					return "u";
				}
			};

			template<>
			struct safe_limits<unsigned long>
			{
				typedef unsigned type;

				static type min()
				{
					return 0;
				}

				static type max()
				{
					return 4294967295ul;
				}

				static const char* type_name()
				{
					return "unsigned long";
				}

				static const char* suffix()
				{
					return "ul";
				}
			};

			template<>
			struct safe_limits<unsigned long long>
			{
				typedef unsigned long long type;

				static type min()
				{
					return 0;
				}

				static type max()
				{
					return 18446744073709551615ull;
				}

				static const char* type_name()
				{
					return "unsigned long long";
				}

				static const char* suffix()
				{
					return "ull";
				}
			};

			template<>
			struct safe_limits<unsigned short>
			{
				typedef unsigned short type;

				static type min()
				{
					return 0;
				}

				static type max()
				{
					return 65535;
				}

				static const char* type_name()
				{
					return "unsigned short";
				}

				static const char* suffix()
				{
					return nullptr;
				}
			};

			template<>
			struct safe_limits<unsigned char>
			{
				typedef unsigned char type;

				static type min()
				{
					return 0;
				}

				static type max()
				{
					return 255;
				}

				static const char* type_name()
				{
					return "unsigned char";
				}

				static const char* suffix()
				{
					return nullptr;
				}
			};

			template<typename T, typename = void>
			struct is_container
			{
				static const bool value = false;
			};

			template<typename T>
			struct is_container<T, void_t<
				decltype(std::declval<T>().begin()),
				decltype(std::declval<T>().end()),
				decltype(std::declval<typename T::value_type>()),
				decltype(T{ std::initializer_list<typename T::value_type>() })>>
			{
				static const bool value = true;
			};
		}

		// This format serializes the object into a form compilable with a C++ compiler
		// Following assumptions are made:
		// (target compiler = the compiler which compiles the serialized form,
		//  source compiler = the compiler which compiled the executable which runs the pretty printer)
		// - target compiler uses C++14
		// - the resolved typedef names will match the source compiler
		// (which means `std::size_t(0)` can be serialized into `0u`, `0ul` or `0ull`,
		// depending on your source compiler)
		// - serialized form for a given type can use all the functions/classes which are
		// introduced by the header which defines that type
		template<typename NameFromTypePolicy = void, typename T = void, typename Enabler = void>
		struct cpp_expression_format
		{
			template<typename U>
			struct rebind
			{
				typedef cpp_expression_format<NameFromTypePolicy, U> type;
			};
		};

		template<typename Format, typename T>
		std::ostream& print(std::ostream& os, const T& value)
		{
			typedef typename Format::template rebind<T>::type FormatForT;
			FormatForT::print(os, value);
			return os;
		}

		template<typename Format, typename T>
		std::string sprint(const T& value)
		{
			std::stringstream ss;
			print<Format>(ss, value);
			return ss.str();
		}
	}
}

// scalar
namespace wiertlo
{
	namespace pretty
	{
		template<typename NameFromTypePolicy>
		struct cpp_expression_format<NameFromTypePolicy, bool, void> : cpp_expression_format<NameFromTypePolicy>
		{
			static void print(std::ostream& os, bool value)
			{
				os << (value ? "true" : "false");
			}
		};

		template<typename NameFromTypePolicy>
		struct cpp_expression_format<NameFromTypePolicy, char, void> : cpp_expression_format<NameFromTypePolicy>
		{
			static void print(std::ostream& os, char value)
			{
				os << "'" << detail::c_string_literal_without_quotes_from_string(&value, 1) << "'";
			}
		};

		template<typename NameFromTypePolicy>
		struct cpp_expression_format<NameFromTypePolicy, std::nullptr_t, void> : cpp_expression_format<NameFromTypePolicy>
		{
			static void print(std::ostream& os, std::nullptr_t)
			{
				os << "nullptr";
			}
		};

		template<typename NameFromTypePolicy, typename Numeric>
		struct cpp_expression_format<NameFromTypePolicy, Numeric, detail::void_t<typename detail::safe_limits<Numeric>::type>> : cpp_expression_format<NameFromTypePolicy>
		{
			static void print(std::ostream& os, Numeric value)
			{
				typedef detail::safe_limits<Numeric> limits;
				std::ostream withManipulatorsRemoved(os.rdbuf());
				if(limits::min() <= value && value <= limits::max())
				{
					const char* suffix = limits::suffix();
					if(suffix)
						withManipulatorsRemoved << value << suffix;
					else
						withManipulatorsRemoved << "static_cast<" << limits::type_name() << ">(" << value << ")";
				}
				else
				{
					withManipulatorsRemoved << "static_cast<" << limits::type_name() << ">(" << value << ")";
				}
			}
		};

		template<typename NameFromTypePolicy, typename Enum>
		struct cpp_expression_format<NameFromTypePolicy, Enum, typename std::enable_if<std::is_enum<Enum>::value>::type> : cpp_expression_format<NameFromTypePolicy>
		{
			static void print(std::ostream& os, Enum value)
			{
				auto underlying = typename std::underlying_type<Enum>::type(value);
				os << NameFromTypePolicy::template get_name<Enum>() << "(";
				wiertlo::pretty::print<cpp_expression_format<NameFromTypePolicy>>(os, underlying);
				os << ")";
			}
		};
	}
}

// smart pointers
#include <memory>
namespace wiertlo
{
	namespace pretty
	{
		template<typename NameFromTypePolicy, typename T>
		struct cpp_expression_format<NameFromTypePolicy, std::unique_ptr<T>, void> : cpp_expression_format<NameFromTypePolicy>
		{
			static void print(std::ostream& os, const std::unique_ptr<T>& value)
			{
				os << "std::make_unique<" << NameFromTypePolicy::template get_name<T>() << ">(";
				wiertlo::pretty::print<cpp_expression_format<NameFromTypePolicy>>(os, *value);
				os << ")";
			}
		};
	}
}

// containers
#include <string>
namespace wiertlo
{
	namespace pretty
	{
		template<typename NameFromTypePolicy>
		struct cpp_expression_format<NameFromTypePolicy, std::string, void> : cpp_expression_format<NameFromTypePolicy>
		{
			static void print(std::ostream& os, const std::string& value)
			{
				os << "std::string(\"" << detail::c_string_literal_without_quotes_from_string(value.data(), value.size()) << "\")";
			}
		};

		template<typename NameFromTypePolicy, typename Container>
		struct cpp_expression_format<
			NameFromTypePolicy,
			Container,
			detail::void_t<typename std::enable_if<detail::is_container<Container>::value>::type>
		> : cpp_expression_format<NameFromTypePolicy>
		{
			static void print(std::ostream& os, const Container& value)
			{
				os << NameFromTypePolicy::template get_name<Container>() << "({";
				bool first = true;
				for(auto&& x : value)
				{
					if(!first)
					{
						os << ",";
					}
					wiertlo::pretty::print<cpp_expression_format<NameFromTypePolicy>>(os, x);
					first = false;
				}
				os << "})";
			}
		};
	}
}