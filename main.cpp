#include "main.h"
#include "level.h"
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
    prefs.fullscreen = false;
    prefs.wintitle = "Game";
    prefs.debugFps = true;
	gkEngine eng(&prefs);
	eng.initialize();
    Controller* game = new Level("kamers.blend");
	game->loadLevel();
	eng.addListener(game);
	eng.initializeStepLoop();
	while(eng.stepOneFrame());
	delete game;
	eng.finalize();
	return 0;
}
