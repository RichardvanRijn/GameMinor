#pragma once
#include "GameObject.h"

class InteractableObject : public GameObject
{
public:
	InteractableObject(gkGameObject* object);
	virtual ~InteractableObject();

	virtual void interact() = 0;

};

