#include "StudentWorld.h"
#include "Actor.h"
#include <string>
#include <cstdlib>
#include <random>
#include <queue>
using namespace std;

// Return a random int from min to max, inclusive
int randInt(int min, int max)
{
    if (max < min)
        swap(max, min);
    static random_device rd;
    static mt19937 generator(rd());
    uniform_int_distribution<> distro(min, max);
    return distro(generator);
}
///////////////////
int min(int a, int b)
{
    if (a<b)    return a;
    return b;
}
int max(int a, int b)
{
    if (a>b)    return a;
    return b;
}
bool within(int ax, int ay, int bx, int by, int r)
{
    if ((ax-bx)*(ax-bx)+(ay-by)*(ay-by) <= r*r)
        return true;
    return false;
}
char StudentWorld::Actorexist(int x, int y)
{
    for (list<Actor*>::iterator p = ++m_actor.begin();p!=m_actor.end();p++)
        if ((*p)->getX() == x && (*p)->getY() == y)
            return (*p)->getname();
    return '0';
}
void getp(int &a, int &b)
{
    a = randInt(0,60);
    b = randInt(0,60);
}
void StudentWorld::randomp(int &a, int &b)
{
    for (;;)
    {   getp(a,b);
        int i=0;
        for (; i<4; i++)
        {   int j=0;
            for (; j<4; j++)
            {  if (!existdirt(a+i, b+j))
                break;
                for (list<Actor*>::iterator p = ++m_actor.begin();p!=m_actor.end();p++)
                {   if (within((*p)->getX(),(*p)->getY(),a,b,6))
                    {   j=6;
                        break;
                    }
                }
                
                
            }
            if (j!=4)
                break;
        }
        if (i==4)
            break;
        
    }

}
void StudentWorld::forpool(int &a, int &b)
{
    for (;;)
    {   getp(a,b);
        int i=0;
        for (; i<4; i++)
        {   int j=0;
            for (; j<4; j++)
            {  if (existdirt(a+i, b+j))
                break;
            }
            if (j!=4)
                break;
        }
        if (i==4)
            break;
        
    }

}
bool StudentWorld::detectable(int x, int y)
{
    if (within(m_frackman->getX(),m_frackman->getY(),x,y,4))
        return true;
    return false;
}
bool StudentWorld::pickable(int x, int y)
{
    if (within(m_frackman->getX(),m_frackman->getY(),x,y,3))
        return true;
    return false;
}

void StudentWorld::scan(int x, int y)
{
    for (list<Actor*>:: iterator p= ++m_actor.begin(); p!=m_actor.end();p++)
    {   if((*p)->getState() != 0 && (*p) != nullptr)
            if ( (*p)->getname() == 'G' || (*p)->getname() == 'O' )
                if (within(x,y,(*p)->getX(),(*p)->getY(),12))
                    (*p)->setVisible(true);
    }

    
}


GameWorld* createStudentWorld(string assetDir)
{
    return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp

int StudentWorld::init()
{
    m_oil = min(2 + getLevel(), 20);
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
    //for boudler
    for (int i = 0; i<min(getLevel()/2+2,6);i++)
    {   int a,b;
        randomp(a,b);
        m_actor.push_back(new Boulder(a,b,this));
        cleanf(a,b);
    }
    //for gold
    for (int i = 0; i<max(5-getLevel()/2,2); i++)
    {   int a,b;
        randomp(a,b);
        m_actor.push_back(new Gold(a,b,this,2));
    }
    //for barrel
    for (int i = 0; i<m_oil;i++)
    {
        int a,b;
        randomp(a,b);
        m_actor.push_back(new Barrel(a,b,this));
    }
    p_tick = 0;
    m_p = 0;
    setDisplaytext();
    designpath(60,60,pathexist);
    return 1;
}
int StudentWorld::move()
{   setDisplaytext();
    designpath(60,60,pathexist);
    
    if (m_p <= min(15, 2 + getLevel() * 1.5))
    {
        if (p_tick == 0)
        {
            int prb =  min(90, getLevel() * 10 + 30);
            prb = randInt(0,prb);
            if (prb == 0)
                m_actor.push_back(new Hardcorep(this));
            else
               m_actor.push_back(new Regularp(this));
            p_tick = max(25, 200 - getLevel());
            m_p++;
        }
        else p_tick--;
    }
    
    //during each tick, add pool/sonar
    int prob = getLevel() * 25 + 300;
    prob = randInt(0, prob);
    if (prob == 0)
    {
        prob = randInt(0, 4);
        if (prob == 0)
             m_actor.push_back(new Sonar(this));
        else
        {   int a,b;
            forpool(a,b);
            m_actor.push_back(new Pool(a,b,this));
        }
        
    }
    for (list<Actor*>:: iterator p= m_actor.begin(); p!=m_actor.end();p++)
    {   if((*p)->getState() != 0 && (*p) != nullptr)
        (*p)->doSomething();
    }
   for (list<Actor*>:: iterator p= m_actor.begin(); p!=m_actor.end();p++)
   {
       if ((*p)->getState()== 0 && (*p) != nullptr)
       {    if ((*p)->getname() == 'R' || (*p)->getname() == 'H')
                    m_p--;
           delete (*p);
           p = --m_actor.erase(p);
       }

   }
    if (m_frackman->getState() == 0)
    {
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    if (m_oil == 0)
    {
        playSound(SOUND_FINISHED_LEVEL);
        return GWSTATUS_FINISHED_LEVEL;
    }
    
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
    for (list<Actor*>::iterator p = m_actor.begin(); p!=m_actor.end(); p++)
    {
        if ((*p) != nullptr)
        { delete (*p);
            p = --m_actor.erase(p);
        }
    }
}
bool StudentWorld::existdirt(int x, int y)
{
    if (m_dirt[x][y]!= nullptr)
        return true;
    return false;
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
{    playSound(SOUND_PLAYER_SQUIRT);
    if (dir == Actor::left)
    {   for (int i=0; i<5; i++)
        {
            if (existdirt(x-i, y))
                return;
        }
       
        x=x-4;
    }
    if (dir == Actor::right)
    {   for (int i=0; i<5; i++)
        {
        if (existdirt(x+i, y))
            return;
        }
        
        x=x+4;
    }
    if (dir == Actor::up)
    {   for (int i=0; i<5; i++)
        {
        if (existdirt(x, y+i))
            return;
        }
        y=y+4;
    }

    if (dir == Actor::down)
    {   for (int i=0; i<5; i++)
        {
        if (existdirt(x, y-i))
            return;
        }
        y=y-4;
    }
    if (x>=0 && x<=64 && y>=0 && y<=60 && !existboulder(x, y))
    {Squirt *s=new Squirt(x,y,dir,this);
    m_actor.push_back(s);
    }
    else
        return;
}
StudentWorld::~StudentWorld()
{}
void StudentWorld::leavegold(int x, int y)
{
    m_actor.push_back(new Gold(x,y,this,1));
}
bool StudentWorld::existfrack(int x, int y)
{
    return (m_frackman->getX() == x && m_frackman->getY()== y);
}
void StudentWorld::getSth(char c)
{
    switch (c)
    {
       case 'P':
            playSound(SOUND_GOT_GOODIE);
            m_frackman->getsgs('p');
            increaseScore(100);
            break;
        case 'S':
            playSound(SOUND_GOT_GOODIE);
            m_frackman->getsgs('s');
            increaseScore(75);
            break;
        case 'B':
            playSound(SOUND_FOUND_OIL);
            m_oil--;
            increaseScore(1000);
            break;
        case 'G':
            playSound(SOUND_GOT_GOODIE);
            m_frackman->getsgs('g');
            break;
            
            
    }
}
bool StudentWorld::canbribe(int x, int y)
{
    for (list<Actor*>::iterator p = ++m_actor.begin();p!=m_actor.end();p++)
    {
        if ((*p)->getname() == 'R' || (*p)->getname() == 'H')
            {
                if (within((*p)->getX(),(*p)->getY(),x,y,3) && (*p)->getname() == 'R')
                {
                    (*p)->setState(1);
                    increaseScore(25);
                    return true;
                }
            else
                if (within((*p)->getX(),(*p)->getY(),x,y,3) && (*p)->getname() == 'H')
                {
                    increaseScore(50);
                    (*p)->stare();
                    return true;
                }
                
                
            }
    }
    return false;
}
bool StudentWorld::existboulder(int x, int y)
{
    for (list<Actor*>::iterator p = m_actor.begin();p!=m_actor.end();p++)
    {    if ((*p)->getname() == 'B' && within((*p)->getX(),(*p)->getY(),x,y,3))
            return true;
    }
    return false;

}
void StudentWorld::getattack(char c)
{
    m_frackman->beannoyed(c);
}
Actor::Direction StudentWorld::couldchase(int x, int y)
{
    if (m_frackman->getX() != x && m_frackman->getY() != y)
        return Actor::none;
    if (m_frackman->getX() == x)
    {
        if ( y > m_frackman->getY() )
        {
            for (; y>=m_frackman->getY(); y--)
            {    if (overlap(x,y) || existboulder(x,y))
                return Actor::none;
            }
            return Actor::down;
        }
        else
        {
            for (; y<=m_frackman->getY(); y++)
            {   if (overlap(x,y) || existboulder(x,y))
                    return Actor::none;
            }
            return Actor::up;
        }
    }
    if (m_frackman->getY() == y)
    {
        if ( x > m_frackman->getX() )
        {
            for (; x>=m_frackman->getX(); x--)
            {    if (overlap(x,y) || existboulder(x,y))
                return Actor::none;
            }
            return Actor::left;
        }
        else
        {
            for (; x<=m_frackman->getX(); x++)
            {   if (overlap(x,y) ||existboulder(x,y))
                return Actor::none;
            }
            return Actor::right;
        }

    }
    return Actor::none;
    
}

Actor::Direction StudentWorld::couldturn(int x, int y, Actor::Direction dir)
{   int rand = randInt(0,1);
    int i=0;
    if (dir == Actor::right || dir == Actor::left)
    {   int a=x,b=y;
        supposemove(a,b,Actor::up);
            if (!overlap(a,b) && !existboulder(a,b) && a<=60 && a>=0 && b<= 60 && b>= 0)
                i=i+1;
        supposemove(x,y,Actor::down);
        if (!overlap(x,y) && !existboulder(x,y) && x>=0 && x<=60 && y>=0 && y<=60 )
                i=i+2;
        switch(i)
        {
            case 0: return Actor::none; break;
            case 1: return Actor::up; break;
            case 2: return Actor::down; break;
            case 3:
                if (rand == 0)
                    return Actor::up;
                else
                    return Actor::down;
                break;
        }
    }
     if (dir == Actor::up || dir == Actor::down)
     {
         {   int a=x,b=y;
             supposemove(a,b,Actor::left);
             if (!overlap(a,b) && !existboulder(a,b)&& a<=60 && a>=0 && b<= 60 && b>= 0)
                 i=i+1;
             supposemove(x,y,Actor::right);
             if (!overlap(x,y) && !existboulder(x,y) && x>=0 && x<=60 && y>=0 && y<=60)
                 i=i+2;
             switch(i)
             {
                 case 0: return Actor::none; break;
                 case 1: return Actor::left; break;
                 case 2: return Actor::right; break;
                 case 3:
                     if (rand == 0)
                         return Actor::left;
                     else
                         return Actor::right;
                     break;
             }
         }

     }
    return Actor::none;
}
bool StudentWorld::couldyell(int x, int y, Actor::Direction dir)
{
    int a= x-m_frackman->getX(), b= y-m_frackman->getY();
    if (a<-4 || a>4 || b<-4 || b>4)
        return false;
    if (a<0 && a>=-4 && dir == Actor::right && !overlap(x+1,y))
        return true;
     if (a>=0 && a<=4 && dir == Actor::left && !overlap(x-1,y))
         return true;
    if (b<0 && b>=-4 && dir ==Actor::up && !overlap(x,y+1))
        return true;
    if (b>=0 && b<=4 && dir == Actor::down && !overlap(x,y-1))
        return true;
    return false;
}


//sth different from the game in format, maybe the space
void StudentWorld::setDisplaytext()
{
    string s;
    string a[7];
    string score = to_string(getScore());
    a[0] = to_string(getLevel());
    a[1] = to_string(m_frackman->getsquirt());
    a[2] = to_string(m_frackman->getgold());
    a[3] = to_string(m_frackman->getsonar());
    a[4] = to_string(m_oil);
    a[5] = to_string(getLives()); // 1 digit long
    a[6] = to_string( m_frackman->getlife() * 10); // three digit long
    s += "Scr: ";
    int lth = score.size();
    while(lth < 8)
    {
        s+="0";
        lth++;
    }
    s += score;
    for (int i=0;i<5;i++)
    {   if (a[i].size() < 2)
        a[i] = " " + a[i];
        
    }
    if (a[6].size() < 3)
    {
        a[6] = " "+ a[6];
    }
    s += "  Lvl:"+a[0]+"  Lives: "+a[5]+"  Hlth:"+a[6]+"%  Water:"+a[1]+"  Gold:"+a[2]+"  Sonar:"+a[3]+"  Oil Left:"+a[4];
    
    // Next, create a string from your statistics, of the form:
    // “Scr: 0321000 Lvl: 52 Lives: 3 Hlth: 80% Water: 20 Gld: 3 Sonar: 1 Oil Left: 2”
    //string s = someFunctionYouUseToFormatThingsNicely(score, level, lives, health, squirts, gold, sonar, barrelsLeft);
    // Finally, update the display text at the top of the screen with your // newly created stats
    setGameStatText(s); // calls our provided GameWorld::setGameStatText
}
bool StudentWorld::hit(int x, int y)
{
    if (pickable(x, y))
        (m_frackman->beannoyed('b'));
    
    for (list<Actor*>::iterator p = ++m_actor.begin();p!=m_actor.end();p++)
    {
        if ((*p)->getname() == 'R' || (*p)->getname() == 'H')
        {
             if ((*p)->getState() == 2 &&within((*p)->getX(),(*p)->getY(),x,y,3))
             {
                 (*p)->beannoyed('b');
                 return true;
             }
            else
                continue;
            
            
        }
    }
    return false;
}
bool StudentWorld::waterAttack(int x, int y)
{
    for (list<Actor*>::iterator p = ++m_actor.begin();p!=m_actor.end();p++)
    {
        if ((*p)->getname() == 'R' || (*p)->getname() == 'H')
        {
            if ((*p)->getState() == 2 && within((*p)->getX(),(*p)->getY(),x,y,3))
            {
                (*p)->beannoyed('p');
                return true;
            }
            else
                continue;
            
            
        }
    }
    return false;
}
bool StudentWorld::overlap(int x, int y)
{
    for (int i=0;x+i<64&&i<=3;i++)
        {   for (int j=0; y+j<60&&j<=3; j++)
        {
            if (m_dirt[x+i][y+j] != nullptr)
                return true;
        }
        }
    return false;

}
void StudentWorld::designpath(int er, int ec,Actor::Direction p[61][61])
{
    for (int i=0; i<=60; i++)
    {
        for (int j=0;j<=60;j++)
            p[i][j] = Actor::none;
    }
    queue<Coord> q;
    q.push(Coord(er,ec));
    while (!q.empty())
    {
        Coord temp = q.front();
        q.pop();
        
        if (!existdirt(temp.r()-1,temp.c()) && !overlap(temp.r()-1,temp.c()) && temp.r()-1>=0 && p[temp.r()-1][temp.c()] == Actor::none)
        {  q.push (Coord(temp.r()-1,temp.c()));
            p[temp.r()-1][temp.c()]= Actor::right;
        }
        
        if (!existdirt(temp.r(),temp.c()-1) && !overlap(temp.r(),temp.c()-1) && temp.c()-1>=0 &&p[temp.r()][temp.c()-1] == Actor::none)
        {  q.push (Coord(temp.r(),temp.c()-1));
            p[temp.r()][temp.c()-1]= Actor::up;
        }
        if (!existdirt(temp.r()+1,temp.c()) && !overlap(temp.r()+1,temp.c()) && temp.r()+1 <=60 &&p[temp.r()+1][temp.c()] == Actor::none)
        {  q.push (Coord(temp.r()+1,temp.c()));
            p[temp.r()+1][temp.c()]= Actor::left;
        }
        if (!existdirt(temp.r(),temp.c()+1) && !overlap(temp.r(),temp.c()+1) && temp.c()+1<=60 &&p[temp.r()][temp.c()+1] == Actor::none)
        {  q.push (Coord(temp.r(),temp.c()+1));
            p[temp.r()][temp.c()+1]= Actor::down;
        }
    }
    
    
}
int StudentWorld::track(int x, int y)
{   int i=0;
    designpath(m_frackman->getX(), m_frackman->getY(), Tracking);
    while (x!=m_frackman->getX() && y!=m_frackman->getY())
    {
        switch(Tracking[x][y])
        {
            case Actor::left: x=x-1; break;
            case Actor::right: x=x+1; break;
            case Actor::up:    y=y+1; break;
            case Actor::down: y=y-1; break;
            case Actor::none: return -1;
        }
        i++;
    }
    return i;
}
Actor::Direction StudentWorld::getpath(int x, int y)
{
    return pathexist[x][y];
}

Actor::Direction StudentWorld::gettrace(int x, int y)
{
    return Tracking[x][y];
}