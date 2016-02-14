#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp


class Actor : public GraphObject
{
    public:
        Actor(int imageID, int startX, int startY, Direction dir = right, double size = 1.0, unsigned int depth = 0);
        ~Actor();
        virtual void doSomething() = 0;
    
    
};

class People : public Actor
{
    public:
        People(int imageID,int startX, int startY, Direction dir,int hit);
        ~People();
        int geth() const;
        void beannoyed();
        void boulderhit();
    
    private:
        int m_h;
};
class FrackMan : public People
{
    public:
        FrackMan();
        ~FrackMan();
        virtual void doSomething();
    private:
        int m_squirt;
        int m_gold;
        int m_sonar;
};

class Dirt : public Actor
{
    public:
        Dirt(int startX, int startY);
        ~Dirt(){}
};
























#endif // ACTOR_H_
