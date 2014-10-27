#include "door.h"



Door::Door(gkGameObject* object, const char* animName) :
	InteractableObject(object, animName)
{
	//getObj()->addAnimation(animName);
	//objectAnimation = getObj()->getAnimationPlayer(animName);
	timeToUndo = 6;
	momentToUndo = 0;
}

Door::~Door()
{
	
}





