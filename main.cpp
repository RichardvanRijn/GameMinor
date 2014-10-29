#include "main.h"
#include "menu.h"
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
    prefs.fullscreen = true;
    prefs.wintitle = "Opa Killer";
    prefs.debugFps = true;
	gkEngine eng(&prefs);
	eng.initialize();
	Controller* menu = new Menu("menu.blend");
	menu->loadLevel();
	//eng.addListener(menu);
    //Controller* game = new Level("kamers.blend");
	//game->loadLevel();
	eng.addListener(menu);
	eng.initializeStepLoop();
	while(eng.stepOneFrame());
	//delete game;
	delete menu;
	eng.finalize();
	return 0;
}
