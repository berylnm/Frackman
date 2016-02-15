#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
class StudentWorld;
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp


class Actor : public GraphObject
{
    public:
        Actor(int imageID, int startX, int startY,StudentWorld*s,Direction dir = right, double size = 1.0, unsigned int depth = 0);
        ~Actor(){}
        virtual void doSomething();
        StudentWorld* getWorld();
    private:
        StudentWorld* m_s;
    
};

class People : public Actor
{
    public:
        People(int imageID,int startX, int startY,StudentWorld*s, Direction dir,int hit);
        ~People(){}
        int geth() const;
        void beannoyed();
        void boulderhit();
    
    private:
        int m_h;
};
class FrackMan : public People
{
    public:
        FrackMan(StudentWorld*s);
        ~FrackMan(){}
        virtual void doSomething();
        bool movable(int x, int y, int ch);
    private:
        int m_squirt;
        int m_gold;
        int m_sonar;
};

class Dirt : public Actor
{
    public:
        Dirt(int startX, int startY,StudentWorld*s);
        ~Dirt(){}
};
























#endif // ACTOR_H_
