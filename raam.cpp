#include "raam.h"


Raam::Raam(gkGameObject* object, bool pickable, const char* animName, gkGameObject* pH) :
	InteractableObject(object, pickable),
	isOpened(false),
	canBeUsed(true),
	blocked(false),
	placeHolder(pH),
	obstructionObject(NULL)
{
	getObj()->addAnimation(animName);
	door = getObj()->getAnimationPlayer(animName);
}

Raam::~Raam()
{

}

void Raam::setObstruction(gkGameObject* obstruction) {
	obstructionObject = obstruction;

	obstructionObject->setPosition(placeHolder->getWorldPosition());
	obstructionObject->setOrientation(placeHolder->getOrientation());
	
	//if (obstructionObject->getScale() > placeHolder->getScale())
		//obstructionObject->setScale(placeHolder->getScale());

	Raam::block();
}

bool Raam::hasObstruction() const {
	return (obstructionObject != NULL);
}

void Raam::removeObstruction() {
	obstructionObject = NULL;

	Raam::unBlock();
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

gkGameObject* Raam::getPlaceHolder() const {
	return placeHolder;
}