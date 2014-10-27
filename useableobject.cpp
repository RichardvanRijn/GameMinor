#include "useableobject.h"


UseableObject::UseableObject(gkGameObject* object, bool canBePicked):
	GameObject(object),
	pickable(canBePicked),
	initialPosition(object->getPosition())
{

}

UseableObject::~UseableObject()
{

}

void UseableObject::interact() {

}

void UseableObject::tick() {
	if (getObj()->getWorldPosition().z <= -1) {
		getObj()->setPosition(initialPosition);
	}
}

void UseableObject::UndoInteract() {

}

bool UseableObject::isPickable() {
	return pickable;
}

bool UseableObject::isBlocked(){
	return blocked;
}