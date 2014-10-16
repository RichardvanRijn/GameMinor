#ifndef LEVEL_DEFINE
#define LEVEL_DEFINE

#include <deque>
#include "Controller.h"
#include "player.h"

class UseableObject;

class Level : public Controller
{
private:	
	Player* player;
	std::vector<UseableObject*> UseableObjects;
	DomSystem* GrannyGuard;
	deque < UseableObject* > toDoList;
	

public: 
    Level(char* lvlPath);
	~Level();
	void tick(gkScalar delta); 
    void loadLevel();
	deque < UseableObject* >& giveList();
	UseableObject* giveFirstProblem();
	void addObject(UseableObject*);
}; 

#endif
