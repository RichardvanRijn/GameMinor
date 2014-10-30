#pragma once
#include "OgreOverlayManager.h"
#include "OgreOverlayElement.h"
#include "Ogre.h"


class GUIman
{
public:
	GUIman();
	~GUIman();

	void setHealthCaption(std::string newCaption);
	void setMoneyCaption(std::string newCaption);
	void showButtonE(bool show);

private:
	Ogre::Overlay* GameOverlay;
	Ogre::OverlayElement* HealthOverlay;
	Ogre::OverlayElement* MoneyOverlay;
	Ogre::OverlayElement* Button;
};

