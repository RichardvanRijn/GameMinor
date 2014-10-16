#pragma once
#include "useableobject.h"
#include "level.h"					//Is wel echt nodig!

class Door : public UseableObject
{
public:
	Door(gkGameObject* object, bool pickable, const char* animName);
	virtual ~Door();

	void interact();
	void UndoInteract();

private:
	gkAnimationPlayer* door;
	bool isOpened;
	bool canBeUsed;
};

