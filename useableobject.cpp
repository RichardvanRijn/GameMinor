#include "useableobject.h"


UseableObject::UseableObject(gkGameObject* object, bool canBePicked):
	GameObject(object),
	pickable(canBePicked)
{

}

UseableObject::~UseableObject()
{

}

void UseableObject::interact() {

}

void UseableObject::tick() {

}

void UseableObject::UndoInteract() {

}

bool UseableObject::isPickable() {
	return pickable;
}

bool UseableObject::isBlocked(){
	return blocked;
}