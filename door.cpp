#include "door.h"


Door::Door(gkGameObject* object, const char* animName) :
	InteractableObject(object),
	isOpened(false),
	canBeUsed(false)
{
	getObj()->addAnimation(animName);
	door = getObj()->getAnimationPlayer(animName);
}

Door::~Door()
{
	
}

//deur[0]->isDone() || deur[0]->getTimePosition()
void Door::interact(){
	if (door->isDone() || door->getTimePosition() == 0){
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


