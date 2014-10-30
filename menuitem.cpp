#include "menuitem.h"


MenuItem::MenuItem(std::string naam)
{
	overlayManagerMenu = Ogre::OverlayManager::getSingletonPtr();
	defaultColour = Ogre::ColourValue(0.6, 0.6, 0.6);
	highlightColour = Ogre::ColourValue(1.0, 1.0, 1.0);
}


MenuItem::~MenuItem()
{
}
