#include "InteractableObject.h"


InteractableObject::InteractableObject(gkGameObject* object, bool canBePicked) :
	UseableObject(object, canBePicked)	
{
}


InteractableObject::~InteractableObject()
{
}
