#include "GameObject.h"
#include "Controller.h"
#include "OgreKit.h"

GameObject::GameObject(gkScene* m_scene, GameObject* p)
{
    obj = m_scene->cloneObject(p->obj, 0, true);
}
GameObject::GameObject(gkScene* m_scene, const char* fname, const char* name)
{
    gkBlendFile* f = gkBlendLoader::getSingleton().loadFile(gkUtils::getFile(fname), "", LEVEL_GROUP_NAME);
    obj = f->getMainScene()->getObject(name);
    m_scene->addObject(obj);
}
void GameObject::tick()
{
    obj->setPosition(position);
}
