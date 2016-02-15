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
                dirt[i][j]= new Dirt(i,j);
            }
        }
        else
        {   for (int j=0; j<60; j++)
            {
                dirt[i][j] = new Dirt(i,j);
            }
        
        }
    }
    frackman = new FrackMan;
    return 1;
}
