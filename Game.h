#ifndef GAME_DEFINE
#define GAME_DEFINE

#include "Controller.h"

class Game : public Controller
{
private:
	
public:
	void tick(gkScalar delta);
	void loadLevel();
	const char* levelName() { return "kamers"; }
};

#endif