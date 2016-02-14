#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp




People::People(int imageID,int startX, int startY, Direction dir,int hit)
:Actor(imageID,startX,startY,dir,1,0),m_h(hit){
    setVisible(true);
}
int People::geth() const
{
    return m_h;
}
void People::beannoyed()
{
    m_h -= 2;
}
void People::boulderhit()
{
    m_h -= 100;
}

FrackMan::FrackMan()
:People(IID_PLAYER,30,60,right,10),m_squirt(5),m_gold(0),m_sonar(1){}

void FrackMan::doSomething()
{
    if (geth() == 0)
        return;
    if ()
}



Dirt::Dirt(int startX, int startY)
:Actor(IID_DIRT,startX,startY,right,0.25,3)
{
    setVisible(true);
}
