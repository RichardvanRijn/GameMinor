#pragma once
#include "OgreRay.h"
#include "OgreSceneManager.h"
#include "gkEngine.h"

typedef Ogre::RaySceneQueryResult& DetectionResult;
typedef Ogre::RaySceneQueryResult::const_iterator DetectionIterator;

class ViewDetection
{
public:
	ViewDetection(Ogre::SceneManager* manager, gkVector3 origin, gkVector3 direction);
	~ViewDetection();

	void setViewDistance(float maxDistance);
	void setExcludedObjects(const char* *objects);

	std::pair<DetectionResult, DetectionIterator&> detectObjects();
	
private:
	Ogre::Ray *detection;
	Ogre::SceneManager* viewManager;

	float viewDistance;

	DetectionIterator& filterObjects(DetectionResult result);
	bool positionedInDistance(Ogre::RaySceneQueryResultEntry& object) const;
};

