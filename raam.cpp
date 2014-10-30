#include "raam.h"

Raam::Raam(gkGameObject* object, const char* animName, gkGameObject* pH) :
	InteractableObject(object, animName),
	placeHolder(pH),
	obstructionObject(NULL)
{
	//getObj()->addAnimation(animName);
	//objectAnimation = getObj()->getAnimationPlayer(animName);
	timeToUndo = 2;
	momentToUndo = 0;
	timeToUnblock = 4;
	healthLoss = 5;
}

Raam::~Raam()
{
}

void Raam::setObstruction(PickableObject* obstruction) {
	obstructionObject = obstruction;

	obstructionObject->getObj()->setPosition(placeHolder->getWorldPosition());
	obstructionObject->getObj()->setOrientation(placeHolder->getOrientation());
	
	//if (obstructionObject->getScale() > placeHolder->getScale())
		//obstructionObject->setScale(placeHolder->getScale());
	act(false);

	obstructionObject->getObj()->getPhysicsController()->suspend(true);

	Raam::block();
}

bool Raam::hasObstruction() const {
	return (obstructionObject != NULL);
}

void Raam::removeObstruction() {
	if (hasObstruction())
	{
		obstructionObject->getObj()->getPhysicsController()->suspend(false);
		obstructionObject->getObj()->setLinearVelocity(gkVector3(0, 0, -0.01));
		obstructionObject->setPickable(true);
		obstructionObject = NULL;
		getObj()->resumeAnimations();
		isOpened = false;

		Raam::unBlock();
	}
}



void Raam::tick() {
	if (hasObstruction() && objectAnimation->getTimePosition() >= 0.4)
		getObj()->pauseAnimations();
}


gkGameObject* Raam::getPlaceHolder() const {
	return placeHolder;
}

PickableObject* Raam::getObstruction() const {
	return obstructionObject;
}