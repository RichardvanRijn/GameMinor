#include "PickableObject.h"


PickableObject::PickableObject(gkGameObject* object, bool canBePicked):
	UseableObject(object, canBePicked)
{
}


PickableObject::~PickableObject()
{
}
