#pragma once
#include "InteractableObject.h"
//#include "level.h"					//Is wel echt nodig!

class Door : public InteractableObject
{
public:
	Door(gkGameObject* object, const char* animName);
	virtual ~Door();



};

