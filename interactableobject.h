#pragma once
#include "GameObject.h"

class Player;

class InteractableObject : public GameObject
{
public:
	InteractableObject(gkGameObject* object, bool canBePicked);
	virtual ~InteractableObject();

	virtual void interact();
	bool isPickable();

private:
	bool pickable;

};

