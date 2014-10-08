#ifndef _GameObject_h_
#define _GameObject_h_

#include "gkEngine.h"
#include "main.h"
#include "Controller.h"


class GameObject
{
public:
	GameObject(gkGameObject* object);
	GameObject(gkScene* m_scene, GameObject* p);    
	~GameObject();

    virtual void setPosition(gkVector3 pos);
	void setObj(gkGameObject* object);

    const char* getObjName() const;    
    gkVector3 getPosition() const;
	gkGameObject* getObj() const;

    virtual void tick();

private:
    gkGameObject *obj;
    gkVector3 position;    

};


#endif
