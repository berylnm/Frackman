#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
class StudentWorld;
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp


class Actor : public GraphObject
{
    public:
        Actor(int imageID, int startX, int startY,StudentWorld*s,int state,char name, Direction dir = right, double size = 1.0, unsigned int depth = 0);
        ~Actor(){}
        virtual void doSomething() = 0;
        int getState() const;
        void setState(int state);
        void setdead();
        void setlife(int a);
        int getlife() const;
        virtual void beannoyed(char c){}
        virtual void stare(){}
        virtual bool movable(int&a, int&b, Direction dir);
        StudentWorld* getWorld();
        char getname();
    
    private:
        StudentWorld* m_s;
        int m_state;            //0:dead 1:temporary 2:permanent 3:waiting
        int m_h;
        char m_n;               //'F' frackman  'P' pool 'S' sonar 'T' boulder 'G' gold 'B' barrel
                                //'D' dirt
    
};

void supposemove(int &x, int &y, Actor::Direction dir);

class People : public Actor
{
    public:
        People(int imageID,int startX, int startY,StudentWorld*s,char name, Direction dir);
        ~People(){}
        void beannoyed(char ch);
        virtual void annoy() = 0;
        virtual void doSomething(){}
    
};

class FrackMan : public People
{
    public:
        FrackMan(StudentWorld*s);
        ~FrackMan(){}
        virtual void doSomething();
        bool movable(int x, int y, Direction dir);
        void getsgs(char c);
        void annoy();
        int getsquirt() const {return m_squirt;}
        int getgold() const {return m_gold;}
        int getsonar() const {return m_sonar;}
    private:
        int m_squirt;
        int m_gold;
        int m_sonar;
};
class Protester: public People
{
    public:
        Protester(int imageID, StudentWorld*s, char name);
        ~Protester(){}
        bool commonA();
        virtual bool differentA() = 0;
        bool commonB();
        void commonC();
        void stare();
        void runsoutstep();
        int getnumstep(){return numStep;}
        void decrementstep(){numStep--;}
    private:
        void basicaction();
        void annoy();
        bool yell();
    
        bool chase();
        bool intersection();
    
        int m_tick;
        int numStep;
        
        int perpendicular;
    
};
class Regularp : public Protester
{
    public:
        Regularp(StudentWorld *s);
        ~Regularp(){}
    
        void doSomething();
private:
    bool differentA();
};
class Hardcorep: public Protester
{
    public:
        Hardcorep(StudentWorld *s);
        ~Hardcorep(){}
    
        void doSomething();
    private:
        bool follow();
        bool differentA();
            
};
class Goodies : public Actor
{
    public:
        Goodies(int image, int x, int y, StudentWorld *s,int state,char name);
        ~Goodies(){}
    private:
    

};
class Barrel: public Goodies
{
    public:
        Barrel(int x, int y, StudentWorld* s);
        ~Barrel(){}
        void doSomething();
    
};
class Gold: public Goodies
{
    public:
        Gold(int x, int y, StudentWorld *s, int state);
        ~Gold(){}
        void doSomething();
};
class Tempic: public Goodies
{
    public:
        Tempic(int image,int x, int y,StudentWorld *s,char name);
        ~Tempic(){}
        void doSomething();
    
};
class Sonar: public Tempic
{
    public:
        Sonar(StudentWorld* s);
        ~Sonar(){}
};
class Pool: public Tempic
{
    public:
        Pool(int x, int y, StudentWorld* s);
        ~Pool(){}
    
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
        void doSomething(){};
};








#endif // ACTOR_H_
