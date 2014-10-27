#include "InteractableObject.h"
#include "level.h"


InteractableObject::InteractableObject(gkGameObject* object, const char* animName) :
	UseableObject(object), 
	isOpened(false), 
	canBeUsed(false)
{
	getObj()->addAnimation(animName);
	objectAnimation = getObj()->getAnimationPlayer(animName);
	blocked = false;
}


InteractableObject::~InteractableObject()
{
}

void InteractableObject::act(bool toOpen){
	objectAnimation->reset();

	if (toOpen)
		objectAnimation->setMode(AK_ACT_END);
	else
		objectAnimation->setMode(AK_ACT_INVERSE);

	getObj()->playAnimation(objectAnimation, 0);
}

void InteractableObject::interact(){
	if (objectAnimation->isDone() || objectAnimation->getTimePosition() == 0 && blocked == false){
		canBeUsed = true;
	}
	if (canBeUsed == true && isOpened == false){
		act(true);
		isOpened = true;
		canBeUsed = false;
	}
}

void InteractableObject::UndoInteract(){
	if (momentToUndo == 0){
		setMomentToUndo();
	}

	if (momentToUndo <= time(NULL)) {
		if (objectAnimation->isDone() || objectAnimation->getTimePosition() == 0 && blocked == false){
			canBeUsed = true;
		}
		if (canBeUsed == true && isOpened == true){
			act(false);
			isOpened = false;
			canBeUsed = false;
			momentToUndo = 0;
		}
	}
}

bool InteractableObject::isOpen(){
	return isOpened;
}

bool InteractableObject::isBlocked(){
	return blocked;
}

void InteractableObject::block(){
	blocked = true;
}

void InteractableObject::unBlock(){
	blocked = false;
}

void InteractableObject::setMomentToUndo(){
	momentToUndo = time(NULL) + timeToUndo;
}