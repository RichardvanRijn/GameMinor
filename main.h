#ifndef _gkApplication_h_
#define _gkApplication_h_

#include "gkMathUtils.h"

class gkGameLevel;
class GameObject;
class gkGameController;

#define GK_CPP_VERBOSE_LOG false

namespace gkAppData
{
	static const gkScalar gkFixedTickDelta    = 1.f / 60.f;
	static const gkScalar gkFixedTickDelta2   = 2.f* gkFixedTickDelta;
	static const gkScalar gkCameraTol         = 0.25f;
};


#endif//_gkApplication_h_
