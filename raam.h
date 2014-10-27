#pragma once
#include "InteractableObject.h"
#include "level.h"

class Raam : public InteractableObject
{
public:

	Raam(gkGameObject* object, const char* animName, gkGameObject* pH);
	virtual ~Raam();


	void setPlaceHolder(gkGameObject* object);
	void setObstruction(gkGameObject* obstruction);
	void removeObstruction();
	
	bool hasObstruction() const;

	
	void tick();
	gkGameObject* getPlaceHolder() const;
	gkGameObject* getObstruction() const;

private:
	gkGameObject* placeHolder, *obstructionObject;
};
