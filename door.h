#pragma once
#include "interactableobject.h"

class Door : public InteractableObject
{
public:
	Door(gkGameObject* object, const char* animName);
	virtual ~Door();

	void interact();

private:
	gkAnimationPlayer* door;
	bool isOpened;
	bool canBeUsed;
};

