#pragma once
#include "useableobject.h"
#include <time.h>

class InteractableObject : public UseableObject
{
public:
	InteractableObject(gkGameObject* object, const char*);
	~InteractableObject();

	virtual void act(bool toOpen);

	virtual void interact();
	virtual void UndoInteract();
	void setMomentToUndo();
	
	bool isOpen();
	bool isBlocked();

	void block();
	void unBlock();

protected:
	bool isOpened;
	bool canBeUsed;
	int timeToUndo;
	int momentToUndo;
	bool blocked;
};

