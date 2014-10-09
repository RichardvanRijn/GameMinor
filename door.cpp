#include "door.h"


Door::Door(gkGameObject* object) :
	InteractableObject(object),
	isOpened(false),
	canBeUsed(false)
{

}

Door::~Door()
{

}

void Door::interact(){
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


