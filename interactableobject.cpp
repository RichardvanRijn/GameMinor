#include "interactableobject.h"


InteractableObject::InteractableObject(gkGameObject* object, bool canBePicked):
	GameObject(object),
	pickable(canBePicked)
{

}

InteractableObject::~InteractableObject()
{

}

void InteractableObject::interact() {

}

bool InteractableObject::isPickable() {
	return pickable;
}
