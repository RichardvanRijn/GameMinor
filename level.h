#ifndef LEVEL_DEFINE
#define LEVEL_DEFINE

#include "Controller.h"
#include "player.h"

class Level : public Controller
{
private:	
	Player* player;

public: 
    Level(char* lvlPath);

	void tick(gkScalar delta); 
    void loadLevel();
}; 

#endif
