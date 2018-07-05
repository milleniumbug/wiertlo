#pragma once
#include <string>

#ifndef _MSC_VER
#include <cxxabi.h>
#endif

namespace wiertlo
{
	namespace detail
	{
		inline void replaceAll(std::string& source, const std::string& from, const std::string& to)
		{
			std::string newString;
			newString.reserve(source.length());  // avoids a few memory allocations

			std::string::size_type lastPos = 0;
			std::string::size_type findPos;

			while(std::string::npos != (findPos = source.find(from, lastPos)))
			{
				newString.append(source, lastPos, findPos - lastPos);
				newString += to;
				lastPos = findPos + from.length();
			}

			// Care for the rest after last occurrence
			newString += source.substr(lastPos);

			source.swap(newString);
		}

		struct free_deleter
		{
			template<typename T>
			void operator()(T* ptr)
			{
				free(ptr);
			}
		};
	}

	inline std::string demangled(const std::type_info& ti)
	{
#ifndef _MSC_VER
		int status;
		std::size_t length;
		std::unique_ptr<char, detail::free_deleter> demangled(abi::__cxa_demangle(ti.name(), nullptr, &length, &status));
		if(status != 0)
			throw "FUCK";
		std::string s = demangled.get();
#else
		std::string s = ti.name();
#endif
		return s;
	}

	// for use with <wiertlo/pretty_print.hpp>
	struct RTTINamePolicy
	{
		template<typename T>
		static std::string get_name()
		{
			std::string s = demangled(typeid(T));
			// TODO: don't break on identifiers like `lolenum`
			detail::replaceAll(s, "enum ", "");
			detail::replaceAll(s, "struct ", "");
			detail::replaceAll(s, "class ", "");
			detail::replaceAll(s, "union ", "");
			return s;
		}
	};
}