#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp
Actor::Actor(int imageID, int startX, int startY, Direction dir , double size, unsigned int depth):GraphObject(imageID,startX,startY,dir,size,depth)
{
}
StudentWorld* Actor::getWorld()
{
    return m_s;
}



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
    int ch;
    if (getWorld()->getKey(ch) == true)
    {
            switch(ch)// user hit a key this tick! switch (ch)
            {
            case KEY_PRESS_LEFT:
                    moveTo(getX()-1,getY());
                    break;
            case KEY_PRESS_RIGHT:
                    moveTo(getX()+1,getY());
                    break;
            case KEY_PRESS_UP:
                    moveTo(getX(),getY()+1);
            case KEY_PRESS_DOWN:
                    moveTo(getX(),getY()-1);
            }
    }
}



Dirt::Dirt(int startX, int startY)
:Actor(IID_DIRT,startX,startY,right,0.25,3)
{
    setVisible(true);
}
