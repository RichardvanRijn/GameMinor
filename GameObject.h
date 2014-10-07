#ifndef _GameObject_h_
#define _GameObject_h_

#include "gkEngine.h"
#include "main.h"
#include "Controller.h"


class GameObject
{
protected:
    gkGameObject *obj;
public:
    GameObject(gkScene* m_scene, GameObject* p);
    GameObject(gkScene* m_scene, const char* fname, const char* name);
    gkVector3 position;
    virtual void tick();
};


#endif
