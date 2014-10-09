#ifndef LEVEL_DEFINE
#define LEVEL_DEFINE

#include "Controller.h"
#include "player.h"

class InteractableObject;

class Level : public Controller
{
private:	
	Player* player;
	std::vector<InteractableObject*> interactableObjects;

public: 
    Level(char* lvlPath);

	void tick(gkScalar delta); 
    void loadLevel();
}; 

#endif
