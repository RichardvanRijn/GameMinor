#pragma once
#include "GameObject.h"

class UseableObject : public GameObject
{
public:
	UseableObject();
	UseableObject(gkGameObject* object, bool canBePicked);
	virtual ~UseableObject();

	virtual void interact();
	virtual void UndoInteract();
	bool isPickable();
	virtual bool isBlocked();

private:
	bool pickable;
	bool blocked;
	int timeToUnblock;
	int timeToUndo;

};
