#ifndef _gkGameLevel_h_
#define _gkGameLevel_h_


#include "gkEngine.h"
#include "main.h"
#include "gkInput.h"
#include "OgreKit.h"
#include "GameObject.h"

#include "Animation/gkAnimationManager.h"

#define LEVEL_GROUP_NAME "CppDemo"

class Controller : public gkEngine::Listener,
	public gkInstancedManager::InstancedListener,
	public gkResourceManager::ResourceListener
{
public:

	Controller();
	virtual ~Controller();
	virtual void loadLevel();

protected:

	gkCamera* m_camera; 
	gkGameObject* m_zRot; 
	gkGameObject* m_xRot;

	gkGameObject* m_cube;

	gkGameObject* m_deur;

	gkAnimationPlayer* deur[1];

	gkScene* m_scene;

	gkKeyboard* m_keyboard;
	gkMouse* m_mouse;
	virtual void tick(gkScalar delta);
	static void gkPrintfSCALAR(gkScalar x) {char str[100]; sprintf(str, "%f", x); gkPrintf(str); }

    utArray<GameObject*> gamePlayers;

    virtual const char* levelName() = 0;
};
#endif