#include "raam.h"

Raam::Raam(gkGameObject* object, const char* animName, gkGameObject* pH) :
	InteractableObject(object, animName),
	placeHolder(pH),
	obstructionObject(NULL)
{
	//getObj()->addAnimation(animName);
	//objectAnimation = getObj()->getAnimationPlayer(animName);
	timeToUndo = 3;
	momentToUndo = 0;
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



void Raam::tick() {
	if (hasObstruction() && objectAnimation->getTimePosition() >= 0.4)
		getObj()->pauseAnimations();
}


gkGameObject* Raam::getPlaceHolder() const {
	return placeHolder;
}

gkGameObject* Raam::getObstruction() const {
	return obstructionObject;
}