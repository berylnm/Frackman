#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp
Actor::Actor(int imageID, int startX, int startY, StudentWorld *s, Direction dir , double size, unsigned int depth):GraphObject(imageID,startX,startY,dir,size,depth),m_s(s){}
StudentWorld* Actor::getWorld()
{
    return m_s;
}
void Actor::doSomething()
{return;}


People::People(int imageID,int startX, int startY, StudentWorld *s, Direction dir,int hit)
:Actor(imageID,startX,startY,s,dir,1,0),m_h(hit){
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

FrackMan::FrackMan(StudentWorld* s)
:People(IID_PLAYER,30,60,s,right,10),m_squirt(5),m_gold(0),m_sonar(1){}

void FrackMan::doSomething()
{
    if (geth() == 0)
        return;
    int ch;
    if (getWorld()->getKey(ch) == true)
    {
        if (movable(getX(),getY(),ch))
        {switch(ch)// user hit a key this tick! switch (ch)
            {
                case KEY_PRESS_LEFT:
                    if (getDirection()!=left)
                    {    setDirection(left);
                        moveTo(getX(),getY());
                    }
                    else
                    moveTo(getX()-1,getY());
                    break;
                case KEY_PRESS_RIGHT:
                    if (getDirection()!=right)
                    {    setDirection(right);
                        moveTo(getX(),getY());
                    }
                    moveTo(getX()+1,getY());
                    break;
                case KEY_PRESS_UP:
                    if (getDirection()!=up)
                    {    setDirection(up);
                        moveTo(getX(),getY());
                    }

                    moveTo(getX(),getY()+1);
                    break;
                case KEY_PRESS_DOWN:
                    if (getDirection()!=down)
                    {    setDirection(down);
                        moveTo(getX(),getY());
                    }

                    moveTo(getX(),getY()-1);
                    break;
            }
        }
        else
        {
            moveTo(getX(),getY());
        }
    }
    
    
}
bool FrackMan::movable(int x, int y, int ch)
{
    switch(ch)
    {
        case KEY_PRESS_LEFT:
            x=x-1;
            break;
        case KEY_PRESS_RIGHT:
            x=x+1;
            break;
        case KEY_PRESS_UP:
            y=y+1;
        case KEY_PRESS_DOWN:
            y=y-1;
            break;
            
    }
    if (x>=0 && x<62 && y>=0 && y<60)
        return true;
    return false;
}



Dirt::Dirt(int startX, int startY,StudentWorld* s)
:Actor(IID_DIRT,startX,startY,s,right,0.25,3)
{
    setVisible(true);
}
