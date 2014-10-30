#include "door.h"



Door::Door(gkGameObject* object, const char* animName) :
	InteractableObject(object, animName)
{
	//getObj()->addAnimation(animName);
	//objectAnimation = getObj()->getAnimationPlayer(animName);
	timeToUndo = 3;
	momentToUndo = 0;
	healthLoss = 1;
}

Door::~Door()
{
	
}





