#include "Controller.h"
#include "GameObject.h"
#include "gkGameObjectManager.h"
#include "OgreKit.h"

#include "Animation/gkAnimationManager.h"

static const gkScalar gkGlobalActionBlend = 35.98765f;
static const gkScalar start = 0.5f;
static const gkScalar end = 1.5f;

Controller::Controller() : m_scene(0), m_camera(0), m_zRot(0), m_xRot(0), m_cube(0)
{
	m_keyboard = gkWindowSystem::getSingleton().getKeyboard();
	m_mouse    = gkWindowSystem::getSingleton().getMouse();
}

Controller::~Controller()
{
	for (UTsize i = 0; i < gamePlayers.size(); i++)
		delete gamePlayers[i];
	gamePlayers.clear();
	if (m_scene)
		gkSceneManager::getSingleton().destroy(m_scene->getResourceHandle());
}

void Controller::loadLevel(void)
{
    gkPrintf(levelName());
    gkBlendFile* mapData = gkBlendLoader::getSingleton().loadFile(gkUtils::getFile("kamers.blend"), levelName(), LEVEL_GROUP_NAME);
	gkScene* sc = mapData->getMainScene();
	m_cube		= sc->getObject("banaan");
	m_deur		= sc->getObject("deur");
	m_camera	= sc->getObject("Camera")->getCamera();
	
	m_scene = (gkScene*)gkSceneManager::getSingleton().create("OpdrachtLevel");

	gkSceneManager::getSingleton().copyObjects(sc, m_scene);
//	m_scene->setHorizonColor(gkColor(0.2f, 0.2f, 0.2f));
//	m_scene->setAmbientColor(gkColor(1.0f, 1.0f, 1.0f));

	m_scene->addObject(sc->getObject("Lamp")->getLight());
	m_scene->addObject(m_camera);
	
	m_scene->addObject(m_deur);

	m_scene->addObject(m_cube);

	//m_scene->setMainCamera(m_camera); 

	m_deur->addAnimation("Deuropen");
	deur[0] = m_deur->getAnimationPlayer("Deuropen");
	m_scene->createInstance(); // will automaticly instance all added objects
	m_camera->setClip(start, end);
}
void Controller::tick(gkScalar delta)
{
	static float movespeed = 2;
	static float cameraheight = 0.6;
	static float cameragimbleup = -.5;
	static float cameragimbledown = .8;
	static int tickcounter = 0;
	static int tickbuffer = 0;

	if (m_mouse->mouseMoved())
	{
		const gkScalar tick = gkAppData::gkFixedTickDelta * .25f;

		gkQuaternion cameraqua = m_camera->getOrientation();
		gkVector3 cameravect = (cameraqua.xAxis(), cameraqua.yAxis(), cameraqua.zAxis());
		
		if (m_mouse->relative.x != 0.f){
			m_camera->roll(-gkRadian(m_mouse->relative.x * tick));
		}
		if (m_mouse->relative.y != 0.f && ((cameravect.z <= cameragimbledown || m_mouse->relative.y < 0)) && (cameravect.z > cameragimbleup || m_mouse->relative.y > 0)){
			m_camera->pitch(-gkRadian(m_mouse->relative.y * tick), TRANSFORM_LOCAL);
		}
	}

	if (m_keyboard->isKeyDown(KC_PKEY) && tickcounter == 0){
		m_deur->playAnimation(deur[0], gkGlobalActionBlend, AK_ACT_END);
		tickcounter++;
	}
	if (tickcounter > 0 && tickcounter < 20){
		tickcounter++;
	}
	else {
		tickcounter = 0;
		m_deur->stopAnimation(deur[0]);
	}

	gkVector3 cameraworld = m_cube->getWorldPosition();
	cameraworld.z += cameraheight;
	m_camera->setPosition(cameraworld);

	static gkVector3 totalspeed;
	gkVector3 buffer = m_cube->getLinearVelocity();
	if (m_keyboard->isKeyDown(KC_WKEY)){
		gkQuaternion cameraqua = m_camera->getOrientation();
		gkVector3 cameravect = (cameraqua.xAxis(), cameraqua.yAxis(), cameraqua.zAxis());
		totalspeed.x = -movespeed * cameravect.x;
		totalspeed.y = -movespeed * cameravect.y;
	}
	else if (m_keyboard->isKeyDown(KC_SKEY)){
		gkQuaternion cameraqua = m_camera->getOrientation();
		gkVector3 cameravect = (cameraqua.xAxis(), cameraqua.yAxis(), cameraqua.zAxis());
		totalspeed.x = movespeed * cameravect.x;
		totalspeed.y = movespeed * cameravect.y;
	}
	if (m_keyboard->isKeyDown(KC_AKEY)){
		gkQuaternion cameraqua = m_camera->getOrientation();
		gkVector3 cameravect = (cameraqua.xAxis(), cameraqua.yAxis(), cameraqua.zAxis());
		totalspeed.x += movespeed * cameravect.y;
		totalspeed.y += -movespeed * cameravect.x;
		totalspeed *= 0.5;
	}
	else if (m_keyboard->isKeyDown(KC_DKEY)){
		gkQuaternion cameraqua = m_camera->getOrientation();
		gkVector3 cameravect = (cameraqua.xAxis(), cameraqua.yAxis(), cameraqua.zAxis());
		totalspeed.x += -movespeed * cameravect.y;
		totalspeed.y += movespeed * cameravect.x;
		totalspeed *= 0.5;
	}
	if ((!m_keyboard->isKeyDown(KC_AKEY) && !m_keyboard->isKeyDown(KC_SKEY) && !m_keyboard->isKeyDown(KC_DKEY) && !m_keyboard->isKeyDown(KC_WKEY)) && (totalspeed != gkVector3(0,0,0)) ){
		gkVector3 reverse = m_cube->getLinearVelocity();
		m_cube->setLinearVelocity(-0.1 * reverse);
		totalspeed.x = 0;
		totalspeed.y = 0;
		totalspeed.z = buffer.z;
	}
	totalspeed.z = buffer.z;
	std::cout << totalspeed << std::endl;
	m_cube->setLinearVelocity(totalspeed);

	for (UTsize i = 0; i < gamePlayers.size(); i++)
        gamePlayers[i]->tick();

	if (m_keyboard->isKeyDown(KC_ESCKEY))
		gkEngine::getSingleton().requestExit();
}