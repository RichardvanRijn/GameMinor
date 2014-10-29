#pragma once
#include "useableobject.h"

class PickableObject : public UseableObject
{
public:
	PickableObject(gkGameObject* object);
	~PickableObject();
	bool isPickable();
	void setPickable(bool);
private:
	bool pickable;
};

