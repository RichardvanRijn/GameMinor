//#pragma once
#include "useableobject.h"

class Raam : public UseableObject
{
public:
	Raam(gkGameObject* object, bool pickable, const char* animName, gkGameObject* pH);
	virtual ~Raam();

	void interact();
	void act(bool toOpen);

	bool isOpen();
	bool isBlocked();

	void setPlaceHolder(gkGameObject* object);
	void setObstruction(gkGameObject* obstruction);
	void removeObstruction();
	
	bool hasObstruction() const;

	void block();
	void unBlock();
	
	void tick();
	gkGameObject* getPlaceHolder() const;
	gkGameObject* getObstruction() const;

private:
	gkAnimationPlayer* door;

	gkGameObject* placeHolder, *obstructionObject;

	bool isOpened;
	bool canBeUsed;
	bool blocked;
};
