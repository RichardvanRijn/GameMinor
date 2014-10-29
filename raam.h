#pragma once
#include "InteractableObject.h"
#include "level.h"

class Raam : public InteractableObject
{
public:

	Raam(gkGameObject* object, const char* animName, gkGameObject* pH);
	virtual ~Raam();


	void setPlaceHolder(gkGameObject* object);
	void setObstruction(PickableObject* obstruction);
	void removeObstruction();
	
	bool hasObstruction() const;

	
	void tick();
	gkGameObject* getPlaceHolder() const;
	PickableObject* getObstruction() const;

private:
	gkGameObject* placeHolder;
	PickableObject* obstructionObject;
};
