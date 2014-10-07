#include "main.h"
#include "Game.h"
#include "Opdracht1.h"
#include "gkLogger.h"
#include "gkUserDefs.h"
#include "Graphics/gkHUDManager.h"
#include "gkMemoryTest.h"

int main(int argc, char** argv)
{
	TestMemory;
	gkLogger::enable("AppCppDemo.log", GK_CPP_VERBOSE_LOG);
	gkUserDefs prefs;
	prefs.rendersystem = OGRE_RS_D3D9;
//	prefs.fullscreen = true;
    prefs.wintitle = "Opa";
	prefs.debugFps = true;
	gkEngine eng(&prefs);
	eng.initialize(); //Setup everything. Ogre, gk etc.
    Controller* game = new Game();
	game->loadLevel();
	eng.addListener(game); //Connect game tick callbacks
	eng.initializeStepLoop();
	while(eng.stepOneFrame());
	delete game;
	eng.finalize();
	return 0;
}