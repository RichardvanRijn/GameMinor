#include "PickableObject.h"


PickableObject::PickableObject(gkGameObject* object):
	UseableObject(object)
{
}


PickableObject::~PickableObject()
{
}

bool PickableObject::isPickable(){
	return pickable;
}

void PickableObject::setPickable(bool pick){
	pickable = pick;
}
