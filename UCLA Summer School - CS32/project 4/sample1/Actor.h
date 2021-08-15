#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
#include <queue>

const int STABLE = 0;
const int WAITING = 1;
const int FALLING = 2;

const int DIR_UP = 3;
const int DIR_DOWN = 4;
const int DIR_LEFT = 5;
const int DIR_RIGHT = 6;

class StudentWorld;

// --------------------------------Actor-------------------------------
class Actor: public GraphObject
{
public:
    // constructor
    Actor(int imageID, int startX, int startY, Direction dir, double size, unsigned int depth);

    // destructor
    virtual ~Actor();
    virtual void doSomething() = 0;
    
    // accessors
    bool isAlive();
    StudentWorld* getWorld();
    int getHP();
    
    // mutators
    void setDead();
    void setWorld(StudentWorld* world);
    void setHP(int points);
    
    virtual bool isProtester();
    virtual void getsAnnoyed(int points);
    void bonkedByBoulder();
    virtual void foundGold();
    
protected:
    void decreaseHP(int points);
    bool isKilledByBoulder();

private:
    bool m_alive;
    StudentWorld* m_world;
    int m_hitPoints;
    bool m_killedByBoulder;
};

// --------------------------------Earth-------------------------------
class Earth : public Actor
{
public:
    // constructor
    Earth(int x, int y);
    // destructor
    virtual ~Earth();
    virtual void doSomething();
    
private:

};

// --------------------------------TunnelMan-------------------------------
class TunnelMan : public Actor
{
public:
    // constructor
    TunnelMan(StudentWorld* world);
    
    // accessors
    int getWaterCount();
    
    // mutators
    void changeWaterCount(int num);
    
    virtual void doSomething();
    virtual void getsAnnoyed(int points);
    
    // destructor
    virtual ~TunnelMan();
    
protected:

private:
    int m_waterCount;
    int m_score;
    int m_nSonar;
};

// --------------------------------Boulder-------------------------------
class Boulder : public Actor
{
public:
    Boulder(int x, int y, StudentWorld* world);
    
    virtual void doSomething();
    
    virtual ~Boulder();
    
private:
    int m_state;
    int m_waitingTime;
};

// --------------------------------Squirt-------------------------------
class Squirt : public Actor
{
public:
    // constructor
    Squirt(int x, int y, Direction dir, StudentWorld* world);
    
    virtual void doSomething();
    
    // destructor
    virtual ~Squirt();
    
private:
    int m_travelDis;
};


// --------------------------------Goodie-------------------------------
class Goodie : public Actor
{
public:
    // constructor
    Goodie(int imageID, int startX, int startY, Direction dir, double size, unsigned int depth);
    
    // mutators
    void changeVisibility(bool v);
    void setLifetime(int ticks);
    
    virtual void doSomething() = 0;
    
    // destructor
    virtual ~Goodie();
    
protected:
    bool isVisible();
    void tickPassed();
    bool pickUpGoodie(Actor* a, int sound, int score);
    bool discoveredGoodie();

private:
    bool m_visible;
    int m_lifetime;
    virtual void informWorld() = 0;

};

// --------------------------------Barrels of Oil-------------------------------
class Barrel : public Goodie
{
public:
    // constructor
    Barrel(int x, int y, StudentWorld* world);
    
    virtual void doSomething();
    
    // destructor
    virtual ~Barrel();
    
private:
    virtual void informWorld();
};

// --------------------------------Sonar Kit-------------------------------
class Sonar : public Goodie
{
public:
    // constructor
    Sonar(StudentWorld *world);
    
    virtual void doSomething();
    
    // destructor
    virtual ~Sonar();
    
private:
    virtual void informWorld();
};

// --------------------------------Water Pool-------------------------------
class Water : public Goodie
{
public:
    // constructor
    Water(int x, int y, StudentWorld* world);
    
    virtual void doSomething();
    
    // destructor
    virtual ~Water();
    
private:
    virtual void informWorld();
};


// --------------------------------Gold Nuggets-------------------------------
class Gold : public Goodie
{
public:
    // constructor
    Gold(Actor* owner, int x, int y, StudentWorld* world);
    
    // mutators
    void setOwner(Actor* a);
    void notPickupAbleByPlayer();
    
    virtual void doSomething();
    virtual void informWorld();
    
    // destructor
    virtual ~Gold();
    
private:
    Actor* m_owner;
    bool m_pickupAbleByPlayer;
};

// --------------------------------Protester-------------------------------
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
    
    // destructor
    virtual ~Protester();
    
    // mutators
    void switchToLeaving();
    void setTicksToStare(int ticks);
    
    virtual void doSomething();
    void findLocation(int x, int y);
    int calcSteps(int targetX, int targetY);
    Direction turnToTarget(int x, int y, int targetX, int targetY);
    void moveToward(Direction dir);
    bool canMoveToward(Direction dir);
    Direction directionConversion(int dir);
    bool atIntersection();
    virtual bool isProtester();
    virtual void getsAnnoyed(int points);
    void moveAlongPath();
    virtual void playerEarnsPoints() = 0;
    void resetField();

private:
    int m_ticksToWait;
    Location* m_previous[VIEW_WIDTH-3][VIEW_HEIGHT-3];
    bool m_visited[VIEW_WIDTH-3][VIEW_HEIGHT-3];
    bool m_leaving;
    int m_shoutCountdown;
    int m_numSquaresToMove;
    int m_ticksSinceLastTurn;
    int m_stunnedTicks;
    virtual bool findTunnelMan() = 0;
    int m_ticksToStare;
    virtual void foundGold() = 0;
    
};

// --------------------------------Regular Protester-------------------------------
class RegularProtester : public Protester
{
public:
    // constructor
    RegularProtester(StudentWorld* world);
    
    // destructor
    virtual ~RegularProtester();
    
private:
    virtual bool findTunnelMan();
    virtual void foundGold();
    virtual void playerEarnsPoints();
};

// --------------------------------Hardcore Protester-------------------------------
class HardcoreProtester : public Protester
{
public:
    // constructor
    HardcoreProtester(StudentWorld* world);
    
    // destructor
    virtual ~HardcoreProtester();
    
private:
    int m_nSteps;
    
    virtual bool findTunnelMan();
    virtual void foundGold();
    virtual void playerEarnsPoints();
};

#endif // ACTOR_H_
