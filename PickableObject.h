#pragma once
#include "useableobject.h"

class PickableObject : public UseableObject
{
public:
	PickableObject(gkGameObject* object, bool canBePicked);
	~PickableObject();
};

