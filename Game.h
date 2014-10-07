#ifndef GAME_DEFINE
#define GAME_DEFINE

#include "Controller.h"

//struct BouncyBall : public GameObject
//{
//	gkVector3 speed;
//	gkScalar mass;
//	gkScalar k;
//	BouncyBall(gkScene* m_scene, gkVector3 position_, gkVector3 speed_, gkScalar mass_, gkScalar k_) : GameObject(m_scene, "bouncy.blend", "SphereBouncy"), speed(speed_), mass(mass_), k(k_) { position = position_; }
//	BouncyBall(gkScene* m_scene, BouncyBall* other, gkVector3 position_, gkVector3 speed_, gkScalar mass_, gkScalar k_) : GameObject(m_scene, other), speed(speed_), mass(mass_), k(k_) { position = position_; }
//	static const gkScalar ballsize;
//	void Move();
//};

class Game : public Controller
{
private:
	
public:
	void tick(gkScalar delta);
	void loadLevel();
	const char* levelName() { return "kamers"; }
};

#endif