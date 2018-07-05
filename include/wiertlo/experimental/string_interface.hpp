#ifndef HEADER48d736a2c6754cb09c733231d34c8d38
#define HEADER48d736a2c6754cb09c733231d34c8d38

#include <string>
#include <cassert>
#include <type_traits>
#include <algorithm>
#include <array>
#include <vector>

namespace wiertlo
{
	// stable subrange of a random access container
	// "stable" means the 
	template<typename RandomAccessContainer>
	class substring
	{
		RandomAccessContainer* container_;
		typename RandomAccessContainer::size_type begin_;
		typename RandomAccessContainer::size_type length_;
	public:
		RandomAccessContainer& container()
		{
			return *container_;
		}

		substring(RandomAccessContainer& container, typename RandomAccessContainer::const_iterator b, typename RandomAccessContainer::const_iterator e) :
			container_(&container)
		{
			begin_ = b - container.begin();
			length_ = e - b;
		}

		auto begin() const { return container_->begin() + begin_; }
		auto end() const { return container_->begin() + begin_ + length_; }
		auto from() const { return begin_; }
		auto to() const { return begin_ + length_; }
		auto size() const { return length_; }
	};

	template<typename OutputContainer, typename InputContainer>
	OutputContainer materialize(InputContainer&& input)
	{
		using std::begin;
		using std::end;
		return OutputContainer(begin(input), end(input));
	}

	template<typename Element>
	std::array<Element, 1> single(Element&& el)
	{
		return std::array<Element, 1>{std::forward<Element>(el)};
	}

	template<
		typename RandomAccessContainer,
		typename Needle,
		typename Substring = substring<typename std::remove_reference<RandomAccessContainer&&>::type>>
		std::vector<Substring> find_all(RandomAccessContainer&& haystack, Needle&& needle)
	{
		static_assert(std::is_lvalue_reference<RandomAccessContainer&&>::value, "passing temporary ranges not supported");
		std::vector<Substring> range;
		const auto distance = std::distance(needle.begin(), needle.end());
		using std::begin;
		using std::end;
		// not using free begin/end on needle on purpose
		// otherwise find_all(a_string, "the") compiles, but does the wrong thing
		auto first = std::search(begin(haystack), end(haystack), needle.begin(), needle.end());
		while(first != end(haystack))
		{
			range.push_back(Substring(haystack, first, first + distance));
			first = std::search(std::next(first), end(haystack), needle.begin(), needle.end());
		}
		return range;
	}

	// Requires: the substrings are ordered by `from()`, substrings don't overlap
	template<typename OutputIterator, typename RandomAccessContainer, typename Substrings, typename What>
	void replaced_all(RandomAccessContainer& cont, Substrings&& substrings, What&& what, OutputIterator out)
	{
		using std::begin;
		using std::end;
		const auto b = begin(cont);
		auto i = b;
		const auto e = end(cont);
		auto sentinel = substring<RandomAccessContainer>(cont, cont.end(), cont.end());
		auto next_substring = [&, sit = substrings.begin(), send = substrings.end()]() mutable
		{
			return sit != send ? &*sit++ : &sentinel;
		};
		auto substring = next_substring();
		while(i != e)
		{
			const auto index = i - b;
			if(index < substring->from())
				*out++ = *i++;
			else
			{
				i += substring->size();
				out = std::copy(what.begin(), what.end(), out);
				substring = next_substring();
			}
		}
	}

	template<typename RandomAccessContainer, typename Substring, typename What>
	void replace(RandomAccessContainer& cont, Substring substring, What&& what)
	{
		auto what_size = std::distance(what.begin(), what.end());
		cont.insert(substring.end(), what.begin(), what.end());
		cont.erase(substring.begin(), substring.end());
	}

}

#endif