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
	virtual void removeObstruction();
	void setMomentToUndo();
	
	bool isOpen();
	bool isBlocked();

	void block();
	void unBlock();

	int healthDamage();

protected:
	bool isOpened;
	bool canBeUsed;
	int timeToUndo;
	int momentToUndo;
	int timeToUnblock;
	bool blocked;
	int healthLoss;
};

