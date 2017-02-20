# Frackman
report
1.

Actor.h  Actor.cpp
Actor class: The base class for all classes in Actor.h  
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
	
	1) virtual void doSomething() = 0;
		I chose to define doSomething as a virtual function because all Actors in this game except dirt must have a doSomething function, and each type of actor defines their own special version of it. Because user should not create an Actor object, so I set doSomething as a pure virtual function and make Actor an abstract base class, and dirt’s doSomething function does nothing.
 	2) int getState() const;
		return the state of the Actor
		Every Actor has its state and this function return the state. There are no difference between different Actors.
	3) void setState(int state);
		Modify the state of the Actor
		Every Actor should be able to modify its state.  0:dead 1:temporary 2:permanent 3:waiting. Specifically state 3 for boulder.
	4) void setdead();
		Set the state of Actor to dead and invisible
		Every Actor should be able to set itself to death and make itself invisible by using this function.
	5)void setlife(int a);
		Modify the life of Actor
		Every Actor should have a data representing its life point and a function to modify the life. For People class, protesters and frackman each has hit points as their life. For inanimate objects, data life represents the time they left before death when they in temporary state.
	6) int getlife() const;
		Return the life of Actor
		Every Actor should have a function to return the life in order to judge their state.
        	7) virtual void beannoyed(char c){}
		do nothing
		Although only People should have function beannoyed, I decide to put this function in Actor class and set it as virtual because I need to call it when iterating through the actor list in StudentWorld. And it will be compile error if Actor does not have such function. So except the People version, the version of this function in the other classes as well as Actor does nothing.
      	 8)  virtual void stare(){}
		do nothing
		Although only Protester could should have function stare, I decide to put this function in Actor class and set it as virtual because I need to call it when iterating through the actor list in StudentWorld. And it will be compile error if Actor does not have such function. So except the Protester version, the version of this function in the other classes as well as Actor does nothing.
      	9) virtual bool movable(int&a, int&b, Direction dir);
		if it will overlap with dirt or boulder after moving in the giving direction
			return false
		else 
		if it is within the oil field
			return true;

		I decide to set this function virtual because Frackman has its unique rule of moving, while other Actors such as Protester and Squirt move in this way.
	

	10) StudentWorld* getWorld();
		get the studentWorld where Actors are created
		All Actors should have getWorld function in order to return some result to studentWorld
        	11)char getname();
		get the type of certain Actor
		Most actors have their unique name for studentWorld to distinguish.
 	'F' frackman  'P' pool 'S' sonar 'T' boulder 'G' gold 'B' barrel 'D' dirt
People class: the base class for Frackman and Protester
	void beannoyed(char ch);
        	virtual void annoy() = 0;
        	virtual void doSomething(){}	

 	1)void beannoyed(char ch);
		if it’s annoyed by squirt or shouting
			decrement the hit point by 2
		if it’s annoyed by falling boulder
			decrement the hit point by 100
		All People should have a function beannoyed, which modify the hit point of people
       	2) virtual void annoy() = 0;
		I chose to define annoy as a pure virtual function because all People in this game must have an annoy function, and each type of People defines their own special version of it.
	3) virtual void doSomething(){}
Frackman class
	virtual void doSomething();
        	bool movable(int x, int y, Direction dir);
        	void getsgs(char c);
        	void annoy();
        	int getsquirt() const ;
       	int getgold() const;
        	int getsonar() const ;
 	
	1)void doSomething();
		the order of its action conforms to the description of spec
       	2) bool movable(int x, int y, Direction dir);
		if it will overlap with boulder after moving to the given direction	
			return false
		else if it’s within the oil field
			return true
     	3) void getsgs(char c);
		increment of goodies that frackman has
		only frackman need this function
            

	4)void annoy();
		if its life is less equal than 0
			setdead and play the sound of player give up
        
       	5)	int getsquirt() const;	return the number of squirt frackman has
        		int getgold() const;	return the number of gold frackman has
       		 int getsonar() const ;	return the number of sonar frackman has
Protester class: base class for Regularp and Hardcorep
 public: 
	bool commonA();
        	bool differentA() ;
        	bool commonB();
	void commonC();
        	void stare();
           void runsoutstep();
           int getnumstep()
          void decrementstep()

	1)bool common A()
		if Protester is dead
			return true
		if it’s resting 
			return true
		set its tick to non-resting state
		if it’s in the leaving-the-oil-field-state
			if it reach the endpoint
				setdead and return true
			else
				get the designed direction from certain array in studentworld
				move a step toward the direction
				return true
		if it’s on normal state
			if it could yell at frackman
				return true
	I decide to put this function in Protester class because this part contains actions shared by regularProtester and hardcoreprotester

	2) commonB
		If it could chase frackman
			return true
		return false
	I decide to put this function in Protester class because this part contains actions shared by regular Protester and hardcore protester, but hardcore protester need to use it after testing its own tracking way
	3) differentA
		It is pure virtue because hardcore protester and regular protester have their own version of it
	4)commonB
		doing step 6,7,8,9,10 in as described in doSomething in spec
	5)stare()
		make tick equals to the given value after picking the gold
	6)void runsoutstep()
		repeatedly generate a new direction until protester could move at least one step at that direction, set direction to the generated one
	7)int numstep()
		return number of step protester could go
	8)void decrementstep
		decrement number of step by one
		 
Regularp class
	void doSomething();
		call commonA() commonB() and commonC() in order
		do as spec told
Hardcorep class:
	void doSomething();
		call commonA() follow() commonB() and commonC() in order
		do as spec says
Class Goodies
	create this class in order to save time on initialization

Class boulder/barrel/squirt/gold
	void doSomething();
		do what the spec says
	
class Tempic: the base class for pool and sonar
	void doSomething();
		do as what pool and sonar supposed to do in the spec, distinguishing between the two type with typename
			
		
StudentWorld.cpp StudentWorld.h
int init();
	create the oil field and frackman
	display text
void cleanUp();
	delete the reamaining Actors
int move();
	display text
	design the path for dying protester to leave
	if there are not enough protester in the oil field
		randomly create either hardcore protester or regular protester
	Randomly distribute pool and sonar knit
	let every Actor do something
	delete the dead actors
	testing and deciding whether to continue, to end or to get to the next level 

   void setDisplaytext();
	setting the form of the text
 	
    //access to dirt class
    bool existdirt(int x, int y);
	if it exists dirt at position(x,y)
		return true
	return false
	
    bool cleanf(int x,int y);
	delete the 4*4 squares of dirt at (x,y)
    bool overlap(int x, int y);
	if there are dirt in the 4*4 squares of dirt at (x,y)
		return true
	return false
    
//access to frackman
    void leavegold(int x, int y);
	create a gold item which starts out in temporary state
    bool existfrack(int x, int y);
	if (x,y) is the position of frackman
		return true
	return false
    void getSth(char c);
	increase frackman’s hold of gold, sonar or squirt
    char Actorexist(int x, int y);
	return the type name of the Actor at (x,y)
    void getattack(char c);
	inform frackman that it’s annoyed by c
    
    //access to boudler
    bool existboulder(int x, int y);
	if (x,y) is within 3 unit of  any boulder
		return true
	return false
   bool hit(int x, int y);
	test and inform if either frackman or protester is within the radius of 3 of a falling boulder
    
    //initialize and creat
    void forpool(int &a, int &b);
	create a pool at dirt-free 4*4 squares
    //access to squirt
    void creatsquirt(int x, int y,Actor::Direction dir);
	play the squirt sound and if possible, create a squirt object if it would not meet boundary, dirt or boulder
    bool waterAttack(int x, int y);
	test and inform and return true if protester at (x,y) is within the attack distance of squirt
    
    //test for radius
    bool detectable(int x, int y); 
	 return true if distance between (x,y) and frackman is within 4
    bool pickable(int x, int y);    //radius <=3
	return if distance between (x,y) and frackman is within 3
    void scan(int x, int y);        //radius <=12
	return if distance between (x,y) and frackman is within 12
    
    //access to protester
    bool canbribe(int x, int y);
	return true if distance between a protester and gold is within 3
	increase the score
    
Actor::Direction couldchase(int x, int y);
	if protester is in horizontal or vertical line (x,y) and could move to their without obstacle
		return the direction that get closer to (x,y)
    Actor::Direction couldturn(int x, int y, Actor::Direction dir);
	if protester could turn to a perpendicular direction and could move at least a step forward
		return the perpendicular direction( could be randomly chosen )
    bool couldyell(int x, int y, Actor::Direction dir);
		return true if protester is within radius of 4 of frackman and facing it
    void  designpath(int er, int ec,Actor::Direction p[61][61]);
		starting from (er,ec)
	repeatedly until visit all the block that are not occupied by dirt or boulder
		store the relative direction of current block its unvisited neighbor block in the given array, mark it as visited
    Actor::Direction  getpath(int x, int y);
	get the direction in the exist path array
    Actor::Direction  gettrace(int x, int y);
	get the direction in the tracking array
    int track(int x, int y);
	return how many step does the certain route tack
2.
	I could not make squirt visible when it attack the protester
	
3.
	the digit of the display score in spec differs from the game, following the spec anyway
4.
	Testing frackman by controlling it moving up,down,right,left. When it reaches the boundary, it would keep making action but not moving. When it reach boulder, it will stuck at one certain position and action. It could make squirt and place gold. Could be annoyed by Protester or boulder to death.

	Protester has its own way of existing the oil field. Could be annoyed by Protester or boulder to leave the field. Hardcore protester could chase frackman in its own way. Could turn or devise some new steps

	Squirt could move and disappear when it travels enough distance or meet protester, dirt or boulder

	Boulder would fall if there’s no supporting dirt, and could hurt frackman or protester

	Gold could either be picked and detected by frackman or bribe Protester and disappear if is not picked in certain ticks

	Sonar and Pool will be created randomly and would disappear if it’s not being picked in certain ticks

	Dirt could be cleaned.
