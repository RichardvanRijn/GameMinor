#ifndef LEVEL_DEFINE
#define LEVEL_DEFINE

#include <deque>
#include "Controller.h"
#include "player.h"
#include <iostream>
#include "Ogre.h"
#include <algorithm>
#include "OgreOverlayManager.h"
#include "useableobject.h"
#include "PickableObject.h"
#include "raam.h"
#include "door.h"
#include "InteractableObject.h"
#include "OgreQuaternion.h"
#include <regex>
#include "DomSystem.h"



class Level : public Controller
{
private:	
	Player* player;
	std::vector<UseableObject*> UseableObjects;
	DomSystem* GrannyGuard;


public: 
    Level(char* lvlPath);
	~Level();
	void tick(gkScalar delta); 
    void loadLevel();
}; 

#endif
