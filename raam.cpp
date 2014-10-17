#include "raam.h"
#include "door.h"

Raam::Raam(gkGameObject* object, bool pickable, const char* animName, gkGameObject* pH) :
	UseableObject(object, pickable),
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
	act(false);

	obstructionObject->getPhysicsController()->suspend(true);

	Raam::block();
}

bool Raam::hasObstruction() const {
	return (obstructionObject != NULL);
}

void Raam::removeObstruction() {
	obstructionObject->getPhysicsController()->suspend(false);
	obstructionObject->setLinearVelocity(gkVector3(0, 0, -0.01));
	obstructionObject = NULL;
	getObj()->resumeAnimations();
	isOpened = false;
	
	Raam::unBlock();
}

void Raam::act(bool toOpen) {
	door->reset();

	if (toOpen)
		door->setMode(AK_ACT_END);
	else
		door->setMode(AK_ACT_INVERSE);

	getObj()->playAnimation(door, 0);
}

void Raam::tick() {
	if (hasObstruction() && door->getTimePosition() >= 0.4)
		getObj()->pauseAnimations();
	
}

void Raam::interact(){		
	if ((door->isDone() || door->getTimePosition() == 0) && blocked == false){
		canBeUsed = true;
	}
	if (canBeUsed == true && isOpened == false){
		act(true);
		isOpened = true;
		canBeUsed = false;
	}
	else if (canBeUsed == true && isOpened == true){
		act(false);
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

gkGameObject* Raam::getObstruction() const {
	return obstructionObject;
}