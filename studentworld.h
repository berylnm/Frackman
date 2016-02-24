#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include "Actor.h"
#include <list>
using namespace std;
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
int min(int a, int b);
int max(int a, int b);
int randInt(int min, int max);
void within(Actor *a);
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
    void randomp(int &a, int &b);
    virtual int move();
    /*{
     // This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
     // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
     decLives();
     return GWSTATUS_PLAYER_WON;
     }*/
    
    virtual void cleanUp();
    void setDisplaytext();
    
    
    //access to dirt class
    bool existdirt(int x, int y);
    bool cleanf(int x,int y);
    bool overlap(int x, int y);
    //access to frackman
    void leavegold(int x, int y);
    bool existfrack(int x, int y);
    void getSth(char c);
    char Actorexist(int x, int y);
    void getattack(char c);
    
    //access to boudler
    bool existboulder(int x, int y);
    bool hit(int x, int y);

    
    //initialize and creat
    void forpool(int &a, int &b);
    //access to squirt
    void creatsquirt(int x, int y,Actor::Direction dir);
    bool waterAttack(int x, int y);
    
    //test for radius
    bool detectable(int x, int y);  //radius <=4
    bool pickable(int x, int y);    //radius <=3
    void scan(int x, int y);        //radius <=12
    
    //access to protester
    bool canbribe(int x, int y);
    Actor::Direction couldchase(int x, int y);
    Actor::Direction couldturn(int x, int y, Actor::Direction dir);
    bool couldyell(int x, int y, Actor::Direction dir);
    void initialPath(Actor *a);
    Actor::Direction  designpath(Actor *a,int x, int y);
    Actor::Direction  getpath(int x, int y);
    

    ~StudentWorld();
    
    
private:
    list <Actor*> m_actor;
    FrackMan* m_frackman;
    Dirt* m_dirt[64][61];
    int m_oil;
    Actor::Direction path[64][61];
    int p_tick;
    int m_p;
};


#endif // STUDENTWORLD_H_
