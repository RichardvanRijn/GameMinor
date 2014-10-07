#include "Opdracht1.h"

const gkScalar BouncyBall::ballsize = .5f;
const gkScalar Opdracht1::k1 = .8f;
const gkScalar Opdracht1::h1 = 10.0f;
const gkScalar Opdracht1::h2 = 10.0f;
const gkScalar Opdracht1::h3 = 6.0f;

void Opdracht1::tick(gkScalar delta)
{
    ball1->Move();
    ball2->Move();
    ball3->Move();
    BounceIfNeeded(ball2, ball3);
	Controller::tick(delta); 
}
void Opdracht1::loadLevel()
{
	Controller::loadLevel(); 
    ball1 = new BouncyBall(m_scene, gkVector3(0, 0, h1), gkVector3(0, 0, 0), 1.0, k1);
    ball2 = new BouncyBall(m_scene, ball1, gkVector3(0, 3, h2), gkVector3(0, 0, 0), 1.0, 1.0);
    ball3 = new BouncyBall(m_scene, ball1, gkVector3(0, 3, h3), gkVector3(0, 0, .1), 1.0, 1.0);
    gamePlayers.push_back(ball1);
    gamePlayers.push_back(ball2);
    gamePlayers.push_back(ball3);
}
void Opdracht1::BounceIfNeeded(BouncyBall* b1, BouncyBall* b2)
{
    // Opdracht:
    // Laat de stuiterballen botsen als dat nodig is
    
}
void BouncyBall::Move()
{
    // Opdracht:
    // Laat de zwaartekracht de bal bewegen en stuiter op de grond
    
}
