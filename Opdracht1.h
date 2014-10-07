#ifndef OPDRACHT1_DEFINE
#define OPDRACHT1_DEFINE

#include "Controller.h"

struct BouncyBall : public GameObject
{
    gkVector3 speed;
    gkScalar mass;
    gkScalar k;
    BouncyBall(gkScene* m_scene, gkVector3 position_, gkVector3 speed_, gkScalar mass_, gkScalar k_) : GameObject(m_scene, "bouncy.blend", "SphereBouncy"), speed(speed_), mass(mass_), k(k_) { position = position_; }
    BouncyBall(gkScene* m_scene, BouncyBall* other, gkVector3 position_, gkVector3 speed_, gkScalar mass_, gkScalar k_) : GameObject(m_scene, other), speed(speed_), mass(mass_), k(k_) { position = position_; }
    static const gkScalar ballsize;
    void Move();
};

class Opdracht1 : public Controller
{
private: 
    BouncyBall *ball1, *ball2, *ball3;
    static const gkScalar h1, h2, h3;
    static const gkScalar k1;
public: 
	void tick(gkScalar delta); 
	void loadLevel(); 
    const char* levelName() {return "Opdracht1"; }
    void BounceIfNeeded(BouncyBall* b1, BouncyBall* b2);
}; 

#endif
