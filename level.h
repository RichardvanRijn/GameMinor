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
	bool isInteractable(DetectedObject object) const;

public: 
    Level(char* lvlPath);
	~Level();
	void tick(gkScalar delta); 
    void loadLevel();
	
	InteractableObject* findInteractableObject(DetectionResult& spottedObjects);

	
}; 

#endif
