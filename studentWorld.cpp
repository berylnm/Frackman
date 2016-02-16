#include "StudentWorld.h"
#include "Actor.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
    return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp

int StudentWorld::init()
{
    for (int i=0; i<64; i++)
    {   if (i>=30 && i<=33)
    {
        for (int j=0; j<4; j++)
        {
            m_dirt[i][j]= new Dirt(i,j,this);
        }
    }
    else
    {   for (int j=0; j<60; j++)
        {
        m_dirt[i][j] = new Dirt(i,j,this);
        }
        
        }
    }
    m_frackman = new FrackMan(this);
    m_actor.push_back(m_frackman);
    m_actor.push_back(new Boulder(14,20,this));
    cleanf(14,20);
    
    return 1;
}
int StudentWorld::move()
{
    
    for (list<Actor*>:: iterator p= m_actor.begin(); p!=m_actor.end();p++)
    {   if((*p)->getState() != 0)
        (*p)->doSomething();
    }
   for (list<Actor*>:: iterator p= m_actor.begin(); p!=m_actor.end();p++)
   {
       if ((*p)->getState()== 0)
       {   delete (*p);
           p = m_actor.erase(p);
       }

   }
    decLives();
    return GWSTATUS_CONTINUE_GAME ;
    
}

void StudentWorld::cleanUp()
{
    for (int i=0;i<64;i++)
    {
        for (int j=0; j<60; j++)
            if (m_dirt[i][j]!=nullptr)
                delete m_dirt[i][j];
    }
    delete m_frackman;
}
int StudentWorld::getActor(int x, int y)
{
    if (m_dirt[x][y]!= nullptr)
        return 1;
    else
        return 0;
}



bool StudentWorld::cleanf(int x, int y)
{   int k = 0;
    for (int i=0;x+i<64&&i<=3;i++)
    {   for (int j=0; y+j<60&&j<=3; j++)
    {
        if (m_dirt[x+i][y+j] != nullptr)
        {    delete m_dirt[x+i][y+j];
            m_dirt[x+i][y+j]= nullptr;
            k=1;
        }
    }
    }
    return k;
}
void StudentWorld::creatsquirt(int x, int y,Actor::Direction dir)
{   if (dir == Actor::left)    x=x-4;
    if (dir == Actor::right)   x=x+4;
    if (dir == Actor::up)      y=y+4;
    if (dir == Actor::down)    y=y-4;
    Squirt *s=new Squirt(x,y,dir,this);
    playSound(SOUND_PLAYER_SQUIRT);
    m_actor.push_back(s);
}
