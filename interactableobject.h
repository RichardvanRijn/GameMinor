#pragma once
#include "useableobject.h"

class InteractableObject : public UseableObject
{
public:
	InteractableObject(gkGameObject* object, bool canBePicked);
	~InteractableObject();
};

