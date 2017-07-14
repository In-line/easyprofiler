#ifndef FIX_MINMAX_H
#define FIX_MINMAX_H

// SDK defines its own max/min, but it creates conflicts.
#ifdef max
	#undef max
#endif

#ifdef min
	#undef min
#endif

#include <algorithm>

using std::max;
using std::min;

#endif //FIX_MINMAX_H
