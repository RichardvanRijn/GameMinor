#pragma once
#include "GameObject.h"
#include "Animation\gkAnimation.h"
//#include "PickableObject.h"

class UseableObject : public GameObject
{
public:
	UseableObject();
	UseableObject(gkGameObject* object);
	virtual ~UseableObject();

	bool isPickable(UseableObject*);
	virtual bool animationDone();
	virtual void tick();
	gkVector3 initialPosition;

protected:
	gkAnimationPlayer* objectAnimation;
};
