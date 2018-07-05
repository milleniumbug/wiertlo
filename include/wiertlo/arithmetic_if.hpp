#ifndef HEADERbe01135f18fa4eefbe08220e93a0a256
#define HEADERbe01135f18fa4eefbe08220e93a0a256

namespace wiertlo
{
	template<typename T, typename FN, typename F0, typename FP>
	void arif(T value, FN negative, F0 zero, FP positive)
	{
		if(value > 0) { positive(); return; }
		if(value < 0) { negative(); return; }
		zero();
	}
}
#endif