//#pragma once
#include "useableobject.h"

class Raam : public UseableObject
{
public:
	Raam(gkGameObject* object, bool pickable, const char* animName, gkGameObject* pH);
	virtual ~Raam();

	void interact();

	bool isOpen();
	bool isBlocked();

	void setPlaceHolder(gkGameObject* object);
	void setObstruction(gkGameObject* obstruction);
	void removeObstruction();
	
	bool hasObstruction() const;

	void block();
	void unBlock();

	gkGameObject* getPlaceHolder() const;

private:
	gkAnimationPlayer* door;

	gkGameObject* placeHolder, *obstructionObject;

	bool isOpened;
	bool canBeUsed;
	bool blocked;
};
