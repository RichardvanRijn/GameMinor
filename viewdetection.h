#pragma once
#include "OgreRay.h"
#include "OgreSceneManager.h"
#include "gkEngine.h"

typedef Ogre::RaySceneQueryResult DetectionResult;
typedef Ogre::RaySceneQueryResult::const_iterator DetectionIterator;
typedef Ogre::RaySceneQueryResultEntry DetectedObject;

class ViewDetection
{
public:
	ViewDetection(Ogre::SceneManager* manager, gkVector3 origin, gkVector3 direction);
	~ViewDetection();

	void setViewDistance(float maxDistance);
	void addExcludedObject(const char* objectName);

	void detectObjects();
	bool objectsSpotted() const;

	DetectionResult& getDetectedObjects() const;

private:
	Ogre::Ray *detection;
	Ogre::SceneManager* viewManager;

	float viewDistance;
	std::list<const char*> excludedObjects;
	DetectionResult& detectedObjects;

	DetectionIterator& filterObjects(DetectionResult& result);

	bool isInvalidObject(DetectedObject object) const;
	bool isExcludedObject(DetectedObject object) const;
	bool positionedInDistance(DetectedObject object) const;
};

