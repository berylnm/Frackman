#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"


Actor::Direction randdir()
{
    int i= randInt(1,4);
    switch(i)
    {
        case 1: return Actor::left; break;
        case 2: return Actor::right; break;
        case 3: return Actor::up; break;
        case 4: return Actor::down; break;
    }
    return Actor::none;
}
void supposemove(int &x, int &y, Actor::Direction dir)
{
    int d = 0;
    if (dir == Actor::left) d=1;
    if (dir == Actor::right) d=2;
    if (dir == Actor::up) d=3;
    if (dir == Actor::down) d=4;
    switch(d)
    {
        case 1:
            x=x-1;
            break;
        case 2:
            x=x+1;
            break;
        case 3:
            y=y+1;
            break;
        case 4:
            y=y-1;
            break;
    }

}
// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp
Actor::Actor(int imageID, int startX, int startY, StudentWorld *s, int state,char name, Direction dir , double size, unsigned int depth):GraphObject(imageID,startX,startY,dir,size,depth),m_s(s),m_state(state),m_h(0),m_n(name){}
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
void Actor::setState(int state)
{
    m_state = state;
}
void Actor::doSomething()
{return;}
void Actor::setlife(int a)
{
    m_h += a;
}
int Actor::getlife() const
{
    return m_h;
}
char Actor::getname()
{
    return m_n;
}
bool Actor::movable(int &x, int &y, Direction dir)
{
    int a=x, b=y;
}
bool Frackman::movable(int x, int y, Direction dir)
{   int a=x, b=y;
    supposemove(x,y,dir);
    if (getWorld()->existboulder(x, y))
    {
        return false;
    }

    if (x>=0 && x<=60 && y>=0 && y<=60)
    {  moveTo(x,y);
        return true;
    }
    moveTo(a,b);
    return false;
}
bool Squirt::movable(int x, int y, Direction dir)
{   
    supposemove(x,y,dir);
    if (getWorld()->existboulder(x, y) || getWorld()-> overlap(x,y))
    {
        return false;
    }
    if (x>=0 && x<=60 && y>=0 && y<=60 )
    {
        moveTo(x,y);
        return true;
    }
    return false;

}
People::People(int imageID,int startX, int startY, StudentWorld *s,char name,Direction dir)
:Actor(imageID,startX,startY,s,2,name,dir,1,0)
{
    setVisible(true);
}

void People::beannoyed(char ch)
{
    if (ch == 'p')    setlife(-2);
    if (ch == 'b')    setlife(-100);
    annoy();
}

    
FrackMan::FrackMan(StudentWorld* s)
:People(IID_PLAYER,30,60,s,'F',right),m_squirt(100),m_gold(0),m_sonar(1)
{   setlife(10);}

void FrackMan::doSomething()
{
    if (getState()==0)
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
                    movable(getX(),getY(),getDirection());
                    break;
                case KEY_PRESS_RIGHT:
                    if (getDirection()!=right)
                    {    setDirection(right);
                        moveTo(getX(),getY());
                    }
                     movable(getX(),getY(),getDirection());
                    break;
                case KEY_PRESS_UP:
                    if (getDirection()!=up)
                    {    setDirection(up);
                        moveTo(getX(),getY());
                    }
                    movable(getX(),getY(),getDirection());
                    break;
                case KEY_PRESS_DOWN:
                    if (getDirection()!=down)
                    {    setDirection(down);
                        moveTo(getX(),getY());
                    }
                    movable(getX(),getY(),getDirection());
                    break;
                case KEY_PRESS_SPACE:
                    if (m_squirt!=0)
                    {    getWorld()->creatsquirt(getX(), getY(),getDirection());
                         m_squirt--;
                    }
                    break;
                case KEY_PRESS_TAB:
                    if (m_gold!=0)
                    {
                        getWorld()->leavegold(getX(),getY());
                        m_gold--;
                    }
               
            }
        }
       
    }
    
    
}
void FrackMan::annoy()
{
    if (getlife() <= 0)
    {
        setdead();
        getWorld()->playSound(SOUND_PLAYER_GIVE_UP);
        return;
    }
}
void FrackMan::getsgs(char c)
{
    if (c == 's')
        m_sonar++;
    if (c == 'p')
        m_squirt +=5;
    if (c=='g')
        m_gold++;
}

Protester::Protester(int imageID,StudentWorld*s, char name)
:People(imageID,60,60,s,name,left),m_tick(max(0, 3 -getWorld()->getLevel()/4)),numStep(randInt(8,60)),shouting(0),perpendicular(0){}

void Protester::commonA()
{
    if (getState() == 0)
        return;
    if (getState() == 1)
        return;

    if (m_tick != 0)
    {
        m_tick--;
        return;
    }

    m_tick = max(0, 3 -getWorld()->getLevel()/4);   //different from the spec but ...
    
    if (yell())
        return;
    else
        shouting--;
    if (chase())
        return;
    numStep--;
    if (numStep <=0)
        runsoutstep();
    else if (!intersection())
        perpendicular--;
    int a = getX(),b=getY();
    if (movable(a, b, getDirection()))
    {
        supposemove(a, b, getDirection());
        moveTo(a,b);
    }
    else
        numStep = 0;
    
    return;
    
}
void Protester::basicaction()
{
    
    
    if (getState() == 1)
    {    if (getX() == 60 && getY() == 60)
        {   setdead();  return;}
        //move the exist path
        return;
    }
   
}
void Protester::annoy()
{
    if (getState() == 1)
        return;
    if (getlife() <= 0)
    {
        setState(2);
        getWorld()->playSound(SOUND_PROTESTER_GIVE_UP);
        m_tick = 0;
        if (getlife() <= -95)
            getWorld()->increaseScore(500);
        else
        {   if (getname() == 'R')
                getWorld()->increaseScore(100);
            else
                getWorld()->increaseScore(250);
        }
        return;
    }
    else
    {   getWorld()->playSound(SOUND_PROTESTER_ANNOYED);
        m_tick =  min(50, 100-getWorld()->getLevel() * 10);
        return;
    }
}

//need a funciton in student world to inform frackman
bool Protester::yell()
{
    if (getWorld()->couldyell(getX(), getY(), getDirection()) && shouting <=0)
    {
    getWorld()->playSound(SOUND_PROTESTER_YELL);
    getWorld()->getattack('p');
    shouting = 15;
    m_tick =  min(50, 100 - getWorld()->getLevel() * 10);
    return true;
    }
    return  false;
}
bool Protester::movable(int x, int y, Direction dir)
{
    
    supposemove(x,y,dir);
    if (getWorld()->existboulder(x, y) || getWorld()-> overlap(x,y))
    {
        return false;
    }
    if (x>=0 && x<=60 && y>=0 && y<=60 )
    {
        return true;
    }
    return false;

}
//continue step 8
void Protester::runsoutstep()
{
    for(;;)
    {   Direction dir = randdir();
            if (movable(getX(),getY(),dir))
            {
                setDirection(dir);
                numStep = randInt(8, 60);
                return;
            }
    }
  
}
//continue step 8
bool Protester::intersection()
{
    if (perpendicular > 0)
        return false;
    Direction dir = getWorld()->couldturn(getX(), getY(), getDirection());
    if (dir != none)
    {
        setDirection(dir);
        numStep = randInt(8, 60);
        perpendicular = 200;
        return true;
    }
    return false;
}
//IF TRUE, immediately return
bool Protester::chase()
{   int a=getX(),b=getY();
    Direction dir =getWorld()->couldchase(getX(), getY());
    if (dir != none)
    {
        setDirection(dir);
        supposemove(a,b,dir);
        moveTo(a,b);
        numStep = 0;
        return true;
    }
    return false;
        
}

Regularp::Regularp(StudentWorld *s)
:Protester(IID_PROTESTER,s,'R'){setlife(5);}

void Regularp::doSomething()
{
    commonA();
}

Hardcorep::Hardcorep(StudentWorld *s)
:Protester(IID_HARD_CORE_PROTESTER,s,'H'){setlife(20);}

void Hardcorep::doSomething()
{
    commonA();
}

Goodies::Goodies(int image, int x, int y, StudentWorld* s,int state,char name )
:Actor(image,x,y,s,state,name,right,1,2){}

Barrel::Barrel(int x, int y, StudentWorld* s)
:Goodies(IID_BARREL,x,y,s,2,'O'){}

void Barrel::doSomething()
{
    if (getState() == 0)
        return;
    if (getWorld()->pickable(getX(), getY()))
    {
        setdead();
        getWorld()->getSth('B');
        return;
    }
    if (getWorld()->detectable (getX(), getY()))
    {
        setVisible(true);
        return;
    }

}



Gold::Gold(int x, int y, StudentWorld* s,int state)
:Goodies(IID_GOLD,x,y,s,2,'G')
{
    
    if (state == 1)
    {   setState(1);
        setVisible(true);
        setlife(100);
    }
}
void Gold::doSomething()
{
    if (getState() == 0)
        return;

    
    if (getState() == 1)
    {
        if (getWorld()->canbribe(getX(), getY()))
        {
            setdead();
            getWorld()->playSound(SOUND_PROTESTER_FOUND_GOLD);
            getWorld()->increaseScore(25);
            return;
        }
    }
    
    if (getState() == 2)
    {      if (getWorld()->pickable(getX(), getY()))
        {
            setdead();
            getWorld()->getSth('G');
            return;
        }
        if (getWorld()->detectable (getX(), getY()))
        {
            setVisible(true);
            return;
        }
    }
    
    
        
}
Tempic::Tempic(int image, int x, int y,StudentWorld* s, char name)
:Goodies(image, x, y, s,1,name)
{
    setVisible(true);
    setlife(min(100,300-10*getWorld()->getLevel()));
}
void Tempic::doSomething()
{
    if (getState() == 0)
        return;
    if (getWorld()->pickable(getX(), getY()))
    {     setdead();
            getWorld()->getSth(getname());
            return;
    
    }
        if (getlife() == 0)
            setdead();
        else
            //to short a life span compared to the game
            setlife(-1);
}

Sonar::Sonar(StudentWorld* s)
:Tempic(IID_SONAR,0,60,s,'S'){}

Pool::Pool(int x, int y, StudentWorld* s)
:Tempic(IID_WATER_POOL,x,y,s,'P'){}

Squirt::Squirt(int x, int y, Direction dir,StudentWorld* s)
:Actor(IID_WATER_SPURT,x,y,s,2,'Q',dir,1,1),m_trvl(4)
{
    setVisible(true);
}
void Squirt::doSomething()
{   if (getWorld()->waterAttack(getX(),getY()))
    {
        setdead();
        return;
    }
    if (m_trvl == 0)
    {
        setdead();
        return;
    }
    if (movable(getX(),getY(),getDirection()))
    {   m_trvl--;
         return;
    }
    setdead();
    return;
    
}
Boulder::Boulder(int x, int y, StudentWorld* s)
:Actor(IID_BOULDER,x,y,s,2,'B',down,1,1)
{
    setVisible(true);
}
void Boulder::doSomething()
{
    if (getState() == 0 )
        return;
    if (getState() == 2)
    {
        for (int i=0;i<4;i++)
        {   if (getWorld()->existdirt(getX()+i, getY()-1))
                return;
        }
        setState(1);
    }
    if (getState() == 1)
    {   if (getlife() >=30)
            setState(3);
        else
            setlife(1);
        return;
    }
    if (getlife() == 31)
        getWorld()->playSound(SOUND_FALLING_ROCK);
    if (getState() == 3)
    {       getWorld()->hit(getX(),getY());
            int a=getX(),b=getY();
            supposemove(a, b, down);
            {   if (getWorld()->overlap(a,b) ||b<0)
                {   setdead();
                    return;
                }
            }
        setlife(1);
       moveTo(getX(),getY()-1);
            return;
    }
        
}
    
Dirt::Dirt(int startX, int startY,StudentWorld* s)
:Actor(IID_DIRT,startX,startY,s,2,'D',right,0.25,3)
{
    setVisible(true);
}
