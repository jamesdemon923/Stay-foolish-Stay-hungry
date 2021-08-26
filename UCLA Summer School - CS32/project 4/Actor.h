#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
#include <queue>
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

const int Stable = 0;
const int Waiting = 1;
const int Falling = 2;

const int Dir_UP = 3;
const int Dir_DOWN = 4;
const int Dir_LEFT = 5;
const int Dir_RIGHT = 6;

class StudentWorld;

//// Actor ////
class Actor: public GraphObject
{
public:
    // constructor
    Actor(int imageID, int startX, int startY, Direction dir, double size, unsigned int depth);

    // accessors
    bool isAlive();
    StudentWorld* getWorld();
    int getHP();
    
    // mutators
    void setDead();
    void setWorld(StudentWorld* world);
    void setHP(int points);
	void decreaseHP(int points);

    // functions
    virtual bool isProtester();
	virtual void findGold();
    virtual void getAnnoyed(int points);
	void bonkedByBoulder();
    bool killedByBoulder();
    virtual void doSomething() = 0;

    // destructor
    virtual ~Actor();

private:
    bool m_alive;
    StudentWorld* m_world;
    int m_hitPoints;
    bool m_killedByBoulder;
};

//// Earth ////
class Earth : public Actor
{
public:
    // constructor
    Earth(int x, int y);

    // functions
    virtual void doSomething();

    // destructor
    virtual ~Earth();
};

//// TunnelMan
class TunnelMan : public Actor
{
public:
    // constructor
    TunnelMan(StudentWorld* world);
    
    // accessors
    int numWater();
    int numSonar();

    // mutators
    void changeNumSonar();
    void changeNumWater(int num);
    
    // functions
    virtual void doSomething();
    virtual void getAnnoyed(int points);
    
    // destructor
    virtual ~TunnelMan();

private:
    int m_water;
    int m_score;
    int m_sonar;
};

//// Boulder ////
class Boulder : public Actor
{
public:
    // constructor
    Boulder(int x, int y, StudentWorld* world);
    
    // functions
    virtual void doSomething();
    
    // destructor
    virtual ~Boulder();

private:
    int m_state;
    int m_waitingTime;
};

//// Squirt ////
class Squirt : public Actor
{
public:
    // constructor
    Squirt(int x, int y, Direction dir, StudentWorld* world);
    
    // functions
    virtual void doSomething();

    // destructor
    virtual ~Squirt();
    
private:
    int m_travelDis;
};

//// Goodie ////
class Goodie : public Actor
{
public:
    // constructor
    Goodie(int imageID, int startX, int startY, Direction dir, double size, unsigned int depth);
    
    // mutators
    void changeVisibility(bool v);
    void setLifetime(int ticks);
    
    // functions
    virtual void doSomething() = 0;
    virtual void informWorld() = 0;
    bool isVisible();
    void tickPassed();
    bool discoveredGoodie();
    bool pickUpGoodie(Actor* a, int sound, int score);

    // destructor
    virtual ~Goodie();
    
private:
    bool m_visible;
    int m_lifetime;
};

//// Barrel of Oil ////
class Barrel : public Goodie
{
public:
    // constructor
    Barrel(int x, int y, StudentWorld* world);
    
    // functions
    virtual void doSomething();
    virtual void informWorld();

    // destructor
    virtual ~Barrel();
};

//// Sonar Kit ////
class Sonar : public Goodie
{
public:
    // constructor
    Sonar(StudentWorld *world);
    
    // functions
    virtual void doSomething();
    virtual void informWorld();

    // destructor
    virtual ~Sonar();
};

//// Water Pool ////
class Water : public Goodie
{
public:
    // constructor
    Water(int x, int y, StudentWorld* world);
    
    // functions
    virtual void doSomething();
    virtual void informWorld();

    // destructor
    virtual ~Water();
};

//// Gold Nugget ////
class Gold : public Goodie
{
public:
    // constructor
    Gold(Actor* owner, int x, int y, StudentWorld* world);
    
    // mutators
    void setOwner(Actor* a);
    void notPickupAbleByPlayer();
    
    // functions
    virtual void doSomething();
    virtual void informWorld();

    // destructor
    virtual ~Gold();
   
private:
    Actor* m_owner;
    bool m_canPickedUpByPlayer;
};

//// Protester ////
struct Location
{
    Location(int col, int row);
    int m_col, m_row;
};

class Protester : public Actor
{
public:
    // constructor
    Protester(int imageID, StudentWorld* world);
    
    // mutators
    void switchToLeave();
    void setTicksWhenGetStunned(int ticks);
    
	// functions
    virtual void doSomething();
    void getExitLocation(int x, int y);
    void getTunnelManLocation(int x, int y);
    void moveAlongPath();
    int calcSteps(int targetX, int targetY);
    Direction turnToTarget(int x, int y, int targetX, int targetY);
    void moveToward(Direction dir);
    bool canMoveToward(Direction dir);
    Direction directionConversion(int dir);
    bool atIntersection();
    virtual bool isProtester();
    virtual void getAnnoyed(int points);
    virtual bool getPathToTunnelMan() = 0;
    virtual void findGold() = 0;
    virtual void playerEarnsPoints() = 0;
    void resetField();

    // destructor
    virtual ~Protester();

private:
    int m_ticksToWaitBetweenMoves;
    Location* m_previous[VIEW_WIDTH-3][VIEW_HEIGHT-3];
    bool m_visited[VIEW_WIDTH-3][VIEW_HEIGHT-3];
    bool m_leaveTheOilField;
    int m_shoutTick;
    int m_numSquaresToMove;
    int m_ticksSinceLastTurn;
    int m_stunnedTicks;
    int m_ticksWhenGetStunned;
};

//// Regular Protester ////
class RegularProtester : public Protester
{
public:
    // constructor
    RegularProtester(StudentWorld* world);

    // functions
    virtual bool getPathToTunnelMan();
    virtual void findGold();
    virtual void playerEarnsPoints();

    // destructor
    virtual ~RegularProtester();
};

//// Hardcore Protester ////
class HardcoreProtester : public Protester
{
public:
    // constructor
    HardcoreProtester(StudentWorld* world);
    
    // functions
    virtual bool getPathToTunnelMan();
    virtual void findGold();
    virtual void playerEarnsPoints();

    // destructor
    virtual ~HardcoreProtester();
    
private:
    int m_steps;
};
#endif // ACTOR_H_
