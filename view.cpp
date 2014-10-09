#include "view.h"
#include "gkEngine.h"
#include "OgreKit.h"
#include "gkApplication.h"

const gkScalar View::tick = gkAppData::gkFixedTickDelta * .25f;

View::View(gkCamera* viewCam) :
	view(viewCam)
{
	
}

View::View(gkCamera* viewCam, const float viewHeight, const float upThreshold, const float downThreshold) :
	view(viewCam),
	viewHeight(viewHeight),
	thresholdUp(upThreshold),
	thresholdDown(downThreshold)
{

}

View::~View()
{
	delete view;
	delete mouse;
}

void View::setViewpoint(gkVector3 pos) {
	pos.z += viewHeight;
	
	view->setPosition(pos);
}

void View::setView(gkCamera* viewCam) {
	view = viewCam;
}

void View::setViewHeight(const float height) {
	viewHeight = height;
}

void View::setThreshold(const float upThreshold, const float downThreshold) {
	thresholdUp = upThreshold;
	thresholdDown = downThreshold;
}

void View::setViewControl(gkMouse* control) {
	mouse = control;
}

void View::moveView() {
	gkQuaternion viewOrientation = view->getOrientation();
	gkVector3 viewDirection = (viewOrientation.xAxis(), viewOrientation.yAxis(), viewOrientation.zAxis());

	if(mouse->relative.x != 0.f) {		
		view->roll(-gkRadian(mouse->relative.x * tick));
	}

	if (mouse->relative.y != 0.f && ((viewDirection.z <= thresholdDown || mouse->relative.y < 0)) 
		&& (viewDirection.z > thresholdUp || mouse->relative.y > 0))
	{		
		view->pitch(-gkRadian(mouse->relative.y * tick), TRANSFORM_LOCAL);
	}
}

bool View::mouseIsMoved() {
	return mouse->mouseMoved();
}

gkCamera* const View::getView() const {
	return view;
}

gkVector3 View::getViewDirection() const {
	return (view->getOrientation().xAxis(), view->getOrientation().yAxis(), view->getOrientation().zAxis());
}

gkVector3 View::getViewPosition() const{
	return(view->getPosition());
}