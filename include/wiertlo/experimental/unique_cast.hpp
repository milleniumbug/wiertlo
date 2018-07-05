#pragma once
#include <memory>

namespace wiertlo
{
	template<typename To, typename From>
	bool dynamic_casted_move(std::unique_ptr<From>& from, std::unique_ptr<To>& to)
	{
		auto raw_to = dynamic_cast<To*>(from.get());
		if(raw_to)
		{
			from.release();
			to.reset(raw_to);
		}
		return raw_to;
	}
}