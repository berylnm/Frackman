#include "StudentWorld.h"
#include "Actor.h"
#include <string>
using namespace std;

void askactortodosth(Actor* a);
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
    return 1;
}
int StudentWorld::move()
{
    askactortodosth(m_frackman);
    decLives();
    return GWSTATUS_CONTINUE_GAME ;
    
}
void askactortodosth(Actor* a)
{
    a->doSomething();
}
