#include "raam.h"


Raam::Raam(gkGameObject* object, const char* animName) :
InteractableObject(object),
isOpened(false),
canBeUsed(false),
blocked(false)
{
	getObj()->addAnimation(animName);
	door = getObj()->getAnimationPlayer(animName);
}


Raam::~Raam()
{
}

void Raam::interact(){
	if ((door->isDone() || door->getTimePosition() == 0) && blocked == false){
		canBeUsed = true;
	}
	if (canBeUsed == true && isOpened == false){
		door->reset();
		door->setMode(AK_ACT_END);
		getObj()->playAnimation(door, 0);
		isOpened = true;
		canBeUsed = false;
	}
	else if (canBeUsed == true && isOpened == true){
		door->reset();
		door->setMode(AK_ACT_INVERSE);
		getObj()->playAnimation(door, 0);
		isOpened = false;
		canBeUsed = false;
	}
}

bool Raam::isOpen(){
	return isOpened;
}

bool Raam::isBlocked(){
	return blocked;
}

void Raam::block(){
	blocked = true;
}

void Raam::unBlock(){
	blocked = false;
}