#pragma once
#include "gkCamera.h"
#include "gkInput.h"

class View
{
public:
	View(gkCamera* viewCam);
	View(gkCamera* viewCam, const float viewHeight,
		const float upThreshold,
		const float downThreshold);

	~View();

	void setViewpoint(gkVector3 pos);
	void setView(gkCamera* viewCam);
	void setViewControl(gkMouse* mouse);
	void setThreshold(float upThreshold, float downThreshold);
	void setViewHeight(float height);

	void moveView();
	
	bool mouseIsMoved();

	gkCamera* const getView() const;
	
	gkVector3 getViewDirection() const;
	gkVector3 getViewPosition() const;

private:
	float viewHeight;
	float thresholdUp;
	float thresholdDown;
	static const gkScalar tick;

	gkCamera* view;
	gkMouse* mouse;
};

