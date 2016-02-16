#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
class StudentWorld;
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp


class Actor : public GraphObject
{
    public:
        Actor(int imageID, int startX, int startY,StudentWorld*s,int state,Direction dir = right, double size = 1.0, unsigned int depth = 0);
        ~Actor(){}
        virtual void doSomething();
        int getState() const;
        void setdead();
        StudentWorld* getWorld();
    
    private:
        StudentWorld* m_s;
        int m_state;            //0:dead 1:temporary 2:permanent 3:waiting
    
};

class People : public Actor
{
    public:
        People(int imageID,int startX, int startY,StudentWorld*s, Direction dir,int hit);
        ~People(){}
        bool isalive();
        void beannoyed(char ch);
        //virtual void attck() ;
    
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
class Protester : public People
{
    public:
        Protester(StudentWorld *s);
        ~Protester();
    
};
class Regularp : public Protester
{
    
};
class Hardcorep: public Protester
{
    
};
class Goodies : public Actor
{
    public:
        Goodies(StudentWorld *s);
        ~Goodies();
    private:
    

};
class Barrel: public Goodies
{
    
};
class Gold: public Goodies
{
    
};

class Plsn : public Goodies
{
    public:
        Plsn(StudentWorld *s);
        ~Plsn();
    private:
};
class Sonar: public Plsn
{
    Sonar(StudentWorld *s);
    ~Sonar();
};
class Pool: public Plsn
{
    
};
class Squirt : public Actor
{
    public:
        Squirt(int x, int y, Direction dir,StudentWorld *s);
        ~Squirt(){}
        void doSomething();
    private:
        int m_trvl;
    
};
class Boulder: public Actor
{
    public:
        Boulder(int x, int y, StudentWorld* s);
        ~Boulder(){}
    void doSomething();
};




class Dirt : public Actor
{
    public:
        Dirt(int startX, int startY,StudentWorld*s);
        ~Dirt(){}
};
























#endif // ACTOR_H_
