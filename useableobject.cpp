#include "useableobject.h"
#include "PickableObject.h"

UseableObject::UseableObject(gkGameObject* object):
	GameObject(object),
	initialPosition(object->getPosition())
{
}

UseableObject::~UseableObject()
{
}

void UseableObject::tick() {
	if (getObj()->getWorldPosition().z <= -1) {
		getObj()->setPosition(initialPosition);
	}
}

bool UseableObject::isPickable(UseableObject* tempUsableObj) {
	PickableObject* tempPickableObj = dynamic_cast <PickableObject*> (tempUsableObj);
	return (tempPickableObj != NULL);
}

bool UseableObject::animationDone(){
	return (objectAnimation->isDone());
}