#include "GameObject.h"
#include "Controller.h"
#include "OgreKit.h"

GameObject::GameObject(gkGameObject* object) :
	obj(object)
{

}

GameObject::GameObject(gkScene* m_scene, GameObject* p)
{
    obj = m_scene->cloneObject(p->obj, 0, true);    
}

GameObject::~GameObject() {
	delete obj;
}

void GameObject::tick()
{
    obj->setPosition(position);
}

void GameObject::setPosition(gkVector3 pos) {
    position = pos;
}

void GameObject::setObj(gkGameObject* object) {
	obj = object;
}

gkVector3 GameObject::getPosition() const {
    return position;
}

const char* GameObject::getObjName() const {
    return obj->getName().c_str();
}

gkGameObject* GameObject::getObj() const {
	return obj;
}
