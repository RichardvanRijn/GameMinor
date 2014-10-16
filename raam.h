//#pragma once
#include "useableobject.h"

class Raam : public UseableObject
{
public:
	Raam(gkGameObject* object, bool pickable, const char* animName);
	virtual ~Raam();

	void interact();

	bool isOpen();
	bool isBlocked();

	void block();
	void unBlock();

private:
	gkAnimationPlayer* door;
	bool isOpened;
	bool canBeUsed;
	bool blocked;
};
