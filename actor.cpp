#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp
Actor::Actor(int imageID, int startX, int startY, StudentWorld *s, int state,Direction dir , double size, unsigned int depth):GraphObject(imageID,startX,startY,dir,size,depth),m_s(s),m_state(state){}
StudentWorld* Actor::getWorld()
{
    return m_s;
}
void Actor::setdead()
{
    m_state = 0;
    setVisible(false);
}
int Actor::getState() const
{
    return m_state;
}
void Actor::doSomething()
{return;}


People::People(int imageID,int startX, int startY, StudentWorld *s,Direction dir,int hit)
:Actor(imageID,startX,startY,s,2,dir,1,0),m_h(hit)
{
    setVisible(true);
}
bool People::isalive()
{
    return m_h;
}
void People::beannoyed(char ch)
{
    if (ch == 'p')    m_h -= 2;
    if (ch == 'b')    m_h -= 100;
}

    
FrackMan::FrackMan(StudentWorld* s)
:People(IID_PLAYER,30,60,s,right,10),m_squirt(5),m_gold(0),m_sonar(1){}

void FrackMan::doSomething()
{
    if (!isalive())
        return;
    if (getWorld()->cleanf(getX(),getY()))
        getWorld()->playSound(SOUND_DIG);
    int ch;
    if (getWorld()->getKey(ch) == true)
    {
        {switch(ch)// user hit a key this tick! switch (ch)
            {
                case KEY_PRESS_LEFT:
                    if (getDirection()!=left)
                    {    setDirection(left);
                        moveTo(getX(),getY());
                    }
                    else if (movable(getX(),getY(),ch))
                        moveTo(getX()-1,getY());
                    else
                        moveTo(getX(),getY());
                    break;
                case KEY_PRESS_RIGHT:
                    if (getDirection()!=right)
                    {    setDirection(right);
                        moveTo(getX(),getY());
                    }
                    else if (movable(getX(),getY(),ch))
                        moveTo(getX()+1,getY());
                    else
                        moveTo(getX(),getY());
                    break;
                case KEY_PRESS_UP:
                    if (getDirection()!=up)
                    {    setDirection(up);
                        moveTo(getX(),getY());
                    }
                    else if (movable(getX(),getY(),ch))
                        moveTo(getX(),getY()+1);
                    else
                        moveTo(getX(),getY());
                    break;
                case KEY_PRESS_DOWN:
                    if (getDirection()!=down)
                    {    setDirection(down);
                        moveTo(getX(),getY());
                    }
                    else if (movable(getX(),getY(),ch))
                        moveTo(getX(),getY()-1);
                    else
                        moveTo(getX(),getY());
                    break;
                case KEY_PRESS_SPACE:
                    if (m_squirt!=0)
                    {    getWorld()->creatsquirt(getX(), getY(),getDirection());
                         m_squirt--;
                    }
            }
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
    if (x>=0 && x<=60 && y>=0 && y<=60)
        return true;
    return false;
}

Squirt::Squirt(int x, int y, Direction dir,StudentWorld* s)
:Actor(IID_WATER_SPURT,x,y,s,2,dir,1,1),m_trvl(4)
{
    setVisible(true);
}
void Squirt::doSomething()
{   getWorld()->playSound(SOUND_FALLING_ROCK);
    if (m_trvl == 0)
    {   setdead();return;}
    else
    if (getWorld()->getActor(getX(), getY()) == 1)
    {   setdead();return;}
    else
    {   if (getDirection() == left)    moveTo(getX()-1, getY());
        else if(getDirection() == right)    moveTo(getX()+1,getY());
        else if(getDirection() == up) moveTo(getX(), getY()+1);
        else if( getDirection() == down) moveTo(getX(), getY()-1);
        getWorld()->playSound(SOUND_FALLING_ROCK);
        m_trvl--;
    }

}
Boulder::Boulder(int x, int y, StudentWorld* s)
:Actor(IID_BOULDER,x,y,s,2,down,1,1)
{
    setVisible(true);
}
void Boulder::doSomething()
{
    
}
Dirt::Dirt(int startX, int startY,StudentWorld* s)
:Actor(IID_DIRT,startX,startY,s,2,right,0.25,3)
{
    setVisible(true);
}
