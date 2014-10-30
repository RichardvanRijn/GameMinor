#ifndef _gkGameLevel_h_
#define _gkGameLevel_h_

#include "gkEngine.h"
#include "main.h"
#include "gkInput.h"
#include "GameObject.h"
#include "OgreKit.h"

class Controller : public gkEngine::Listener,
	public gkInstancedManager::InstancedListener,
	public gkResourceManager::ResourceListener
{
public:
    Controller(char* lvlPath);
	virtual ~Controller();
    virtual void loadLevel();
	void loadLevel(Controller* oldController);

protected:
	const char* pathToLevel;
	gkScene* m_scene;
	gkKeyboard* m_keyboard;
	gkMouse* m_mouse;

	virtual void tick(gkScalar delta);
};
#endif
