#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include "Actor.h"
#include <list>
using namespace std;
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir)
	 : GameWorld(assetDir)
	{
    }

    virtual int init();
	/*{
		return GWSTATUS_CONTINUE_GAME;
	}*/

    virtual int move();
	/*{
		  // This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
		  // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
		decLives();
        return GWSTATUS_PLAYER_WON;
    }*/

	virtual void cleanUp()
	{
	}
    

private:
    list <Actor*> m_actor;
    FrackMan* m_frackman;
    Dirt* m_dirt[64][60];
};

#endif // STUDENTWORLD_H_
