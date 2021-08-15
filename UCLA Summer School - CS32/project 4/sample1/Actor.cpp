#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"
#include <algorithm>
#include <queue>
using namespace std;

// --------------------------------Actor-------------------------------
Actor::Actor(int imageID, int startX, int startY, Direction dir, double size, unsigned int depth)
: GraphObject(imageID, startX, startY, dir, size, depth)
{
    setVisible(true);
    m_alive = true;
    m_killedByBoulder = false;
}

Actor::~Actor() {}

bool Actor::isAlive()
{
    return m_alive;
}

void Actor::setDead()
{
    m_alive = false;
}

StudentWorld* Actor::getWorld()
{
    return m_world;
}

void Actor::setWorld(StudentWorld* world)
{
    m_world = world;
}

void Actor::setHP(int points)
{
    m_hitPoints = points;
}

int Actor::getHP()
{
    return m_hitPoints;
}

void Actor::decreaseHP(int points)
{
    m_hitPoints -= points;
}

bool Actor::isProtester()
{
    return false;
}

void Actor::getsAnnoyed(int points)
{
}

void Actor::foundGold()
{
}

void Actor::bonkedByBoulder()
{
    m_killedByBoulder = true;
}

bool Actor::isKilledByBoulder()
{
    return m_killedByBoulder;
}

// --------------------------------Earth-------------------------------
Earth::Earth(int x, int y) : Actor(TID_EARTH, x, y, right, 0.25, 3)
{
}

void Earth::doSomething() {}

Earth::~Earth() {}

// --------------------------------TunnelMan-------------------------------
TunnelMan::TunnelMan(StudentWorld* world) : Actor(TID_PLAYER, 30, 60, right, 1.0, 0)
{
    setWorld(world);
    setHP(10);
    m_waterCount = 5;
    m_nSonar = 1;
}

int TunnelMan::getWaterCount()
{
    return m_waterCount;
}

void TunnelMan::changeWaterCount(int num)
{
    m_waterCount += num;
}

TunnelMan::~TunnelMan() {}

void TunnelMan::doSomething()
{
    if (!isAlive())
        return;
    
    int val;
    // valid input
    if (getWorld()->getKey(val))
    {
        if (!isAlive())
            return;
        
        Direction cur = getDirection();
        switch(val)
        {
            // up
            case KEY_PRESS_UP:
                // facing same direction and can move
                if (cur == up && getY() < 60
                    && !getWorld()->overlapWithBoulder(getX(), getY()+1))
                {
                    // move along this direction
                    moveTo(getX(), getY()+1);
                }
                // facing different direction or out of bound
                // or would run into boulder, doesn't move
                else
                    moveTo(getX(), getY());
                
                // delete any earth objects holding overlapping position
                getWorld()->hideEarthOverlap(getX(), getY());
                // reset direction
                setDirection(up);
                break;
               
            // down
            case KEY_PRESS_DOWN:
                if (cur == down && getY() > 0
                    && !getWorld()->overlapWithBoulder(getX(), getY()-1))
                {
                    moveTo(getX(), getY()-1);
                }
                else
                    moveTo(getX(), getY());
                
                getWorld()->hideEarthOverlap(getX(), getY());
                setDirection(down);
                break;
                
            // left
            case KEY_PRESS_LEFT:
                if (cur == left && getX() > 0
                    && !getWorld()->overlapWithBoulder(getX()-1, getY()))
                {
                    moveTo(getX()-1, getY());
                }
                else
                    moveTo(getX(), getY());
                
                getWorld()->hideEarthOverlap(getX(), getY());
                setDirection(left);
                break;
                
            // right
            case KEY_PRESS_RIGHT:
                if (cur == right && getX() < 60
                    && !getWorld()->overlapWithBoulder(getX()+1, getY()))
                {
                    moveTo(getX()+1, getY());
                }
                else
                    moveTo(getX(), getY());
                
                getWorld()->hideEarthOverlap(getX(), getY());
                setDirection(right);
                break;
            
            // space
            // fire a squirt
            case KEY_PRESS_SPACE:
                // has water in squirt gun
                if (getWaterCount() > 0)
                {
                    changeWaterCount(-1);
                    getWorld()->playSound(SOUND_PLAYER_SQUIRT);
                
                    int squirtX, squirtY;
                    Direction dir = getDirection();
                    // potential starting location of squirt
                    if (dir == up)
                    {
                        squirtX = getX();
                        squirtY = getY()+4;
                    }
                    else if (dir == down)
                    {
                        squirtX = getX();
                        squirtY = getY()-4;
                    }
                    else if (dir == left)
                    {
                        squirtX = getX()-4;
                        squirtY = getY();
                    }
                    else if (dir == right)
                    {
                        squirtX = getX()+4;
                        squirtY = getY();
                    }

                    // doesn't run into boulder and doesn't have earth and is within bounds
                    if ((!getWorld()->runIntoBoulder(squirtX, squirtY)
                        && !getWorld()->runIntoEarth(squirtX, squirtY)
                        && getWorld()->withinBounds(squirtX, squirtY)))
                    {
                        // create Squirt object 4 squares in front of TunnelMan
                        getWorld()->addActor(new Squirt(squirtX, squirtY, dir, getWorld()));
                    }
                }
                break;
                
            case 'z':
            case 'Z':
                // has sonar charge
                if (m_nSonar > 0)
                {
                    m_nSonar--;
                    // illuminate all hidden objects
                    getWorld()->illuminate();
                }
                break;
                
            case KEY_PRESS_TAB:
                // has gold
                if (getWorld()->numGold() > 0)
                {
                    // create gold, set owner to player
                    Gold* g = new Gold(this, getX(), getY(), getWorld());
                    // update pickup state
                    g->notPickupAbleByPlayer();
                    // add gold in world
                    getWorld()->addActor(g);
                    // gold count decreases
                    getWorld()->dropsGold();
                }
                break;
                
        }
        
    }
}

void TunnelMan::getsAnnoyed(int points)
{
    decreaseHP(points);
    if (getHP() <= 0)
    {
        setDead();
        getWorld()->playSound(SOUND_PLAYER_GIVE_UP);
    }
}

// --------------------------------Boulder-------------------------------
Boulder::Boulder(int x, int y, StudentWorld* world) : Actor(TID_BOULDER, x, y, down, 1.0, 1)
{
    m_state = STABLE;
    setWorld(world);
}

Boulder::~Boulder() {}

void Boulder::doSomething()
{
    if (!isAlive())
        return;
    
    if (m_state == STABLE)
    {
        for (int x = getX(); x < getX()+4; x++)
        {
            // Earth object below Boulder is alive
            // do nothing
            if (getWorld()->getEarthAt(x, getY()-1)->isAlive())
                return;
        }
        // all 4 Earth objects below are gone
        m_state = WAITING;
        m_waitingTime = 0;
    }
    
    else if (m_state == WAITING)
    {
        if (m_waitingTime == 30)
        {
            m_state = FALLING;
            getWorld()->playSound(SOUND_FALLING_ROCK);
        }
        else
            m_waitingTime++;
    }
    
    else if (m_state == FALLING)
    {
        // reaches bottom or would run into another Boulder or Earth
        if (getY() == 0 || getWorld()->runIntoBoulder(getX(), getY()-1)
            || getWorld()->overlapWithEarth(getX(), getY()-1))
        {
            setDead();
        }
        else
        {
            // Boulder is within a radius of 3.0 of TunnelMan
            if (getWorld()->calcRadius(getWorld()->getPlayer()->getX(),
                                       getWorld()->getPlayer()->getY(),
                                       getX(), getY()) <= 3.0)
                getWorld()->getPlayer()->getsAnnoyed(100);
            
            // hits Boulders
            getWorld()->hitsProtester(this, 100);
            
            // keep falling
            moveTo(getX(), getY()-1);
        }
    }
}

// --------------------------------Squirt-------------------------------
Squirt::Squirt(int x, int y, Direction dir, StudentWorld* world) :
Actor(TID_WATER_SPURT, x, y, dir, 1.0, 1)
{
    setWorld(world);
    m_travelDis = 4;
}

Squirt::~Squirt() {}

void Squirt::doSomething()
{
    if (!isAlive())
        return;
    
    // already traveled full distance
    if (m_travelDis == 0)
    {
        setDead();
        return;
    }
    
    if (getWorld()->hitsProtester(this, 2))
    {
        setDead();
        return;
    }
    
    Direction cur = getDirection();
    if (cur == up)
    {
        // attempt to move out of bound or run into Boulder or earth
        if (getY() == VIEW_HEIGHT-1
            || getWorld()->runIntoBoulder(getX(), getY()+1)
            || getWorld()->runIntoEarth(getX(), getY()+1))
        {
            setDead();
        }
        else
        {
            // keep moving
            moveTo(getX(), getY()+1);
            m_travelDis--;
        }
    }
    else if (cur == down)
    {
        // attempt to move out of bound or run into Boulder or earth
        if (getY() == 0
            || getWorld()->runIntoBoulder(getX(), getY()-1)
            || getWorld()->runIntoEarth(getX(), getY()-1))
        {
            setDead();
        }
        else
        {
            // keep moving
            moveTo(getX(), getY()-1);
            m_travelDis--;
        }
    }
    else if (cur == left)
    {
        // attempt to move out of bound or run into Boulder or earth
        if (getX() == 0
            || getWorld()->runIntoBoulder(getX()-1, getY())
            || getWorld()->runIntoEarth(getX()-1, getY()))
        {
            setDead();
        }
        else
        {
            // keep moving
            moveTo(getX()-1, getY());
            m_travelDis--;
        }
    }
    else if (cur == right)
    {
        // attempt to move out of bound or run into Boulder or earth
        if (getX() == VIEW_WIDTH-1
            || getWorld()->runIntoBoulder(getX()+1, getY())
            || getWorld()->runIntoEarth(getX()+1, getY()))
        {
            setDead();
        }
        else
        {
            // keep moving
            moveTo(getX()+1, getY());
            m_travelDis--;
        }
    }
}

// --------------------------------Goodie-------------------------------
Goodie::Goodie(int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) : Actor(imageID, startX, startY, dir, size, depth)
{
}

bool Goodie::isVisible()
{
    return m_visible;
}

void Goodie::changeVisibility(bool v)
{
    m_visible = v;
}

void Goodie::tickPassed()
{
    m_lifetime--;
    if (m_lifetime == 0)
        setDead();
}

void Goodie::setLifetime(int ticks)
{
    m_lifetime = ticks;
}

bool Goodie::discoveredGoodie()
{
    // is not visible and TunnelMan is within a radius of 4.0
    if (!isVisible() && getWorld()->calcRadius
        (getX(), getY(), getWorld()->getPlayer()->getX(), getWorld()->getPlayer()->getY()) <= 4.0)
    {
        setVisible(true);
        changeVisibility(true);
        return true;
    }
    return false;
}

Goodie::~Goodie() {}

bool Goodie::pickUpGoodie(Actor* a, int sound, int score)
{
    // within a radius of 3.0 from TunnelMan or Protester
    if (getWorld()->calcRadius(getX(), getY(), a->getX(), a->getY()) <= 3.0)
    {
        setDead();
        getWorld()->playSound(sound);
        getWorld()->increaseScore(score);
        // update inventory
        informWorld();
        return true;
    }
    return false;
}

// --------------------------------Barrel-------------------------------
Barrel::Barrel(int x, int y, StudentWorld* world) : Goodie(TID_BARREL, x, y, right, 1.0, 2)
{
    setWorld(world);
    setVisible(false);
    changeVisibility(false);
}

Barrel::~Barrel() {}

void Barrel::informWorld()
{
    getWorld()->foundBarrel();
}

void Barrel::doSomething()
{
    if (!isAlive())
        return;
    
    if (discoveredGoodie())
        return;
    
    // check if player within 3.0 radius, if so, got goodie
    pickUpGoodie(getWorld()->getPlayer(), SOUND_FOUND_OIL, 1000);
}

// --------------------------------Sonar-------------------------------
Sonar::Sonar(StudentWorld *world) : Goodie(TID_SONAR, 0, 60, right, 1.0, 2)
{
    setWorld(world);
    setLifetime(max(100, static_cast<int>(300-10*getWorld()->getLevel())));
}

Sonar::~Sonar() {}

void Sonar::informWorld()
{
    getWorld()->gotSonarKit();
}

void Sonar::doSomething()
{
    if (!isAlive())
        return;
    
    if (pickUpGoodie(getWorld()->getPlayer(), SOUND_GOT_GOODIE, 75))
        return;
    
    // lifetime decreases and check if life expires
    tickPassed();
}

// --------------------------------Water-------------------------------
Water::Water(int x, int y, StudentWorld* world) : Goodie(TID_WATER_POOL, x, y, right, 1.0, 2)
{
    setWorld(world);
    setLifetime(max(100, static_cast<int>(300-10*getWorld()->getLevel())));
}

Water::~Water() {}

void Water::informWorld()
{
    getWorld()->getPlayer()->changeWaterCount(5);
}

void Water::doSomething()
{
    if (!isAlive())
        return;
    
    if (pickUpGoodie(getWorld()->getPlayer(), SOUND_GOT_GOODIE, 100))
        return;
    
    // lifetime decreases and check if life expires
    tickPassed();
}

// --------------------------------Gold-------------------------------
Gold::Gold(Actor* owner,int x, int y, StudentWorld* world) : Goodie(TID_GOLD, x, y, right, 1.0, 2)
{
    setWorld(world);
    // start invisible
    setVisible(false);
    changeVisibility(false);
    // start pickup-able by player
    m_owner = owner;
    // gold in temp state has lifetime of 100 ticks
    setLifetime(100);
    m_pickupAbleByPlayer = true;
    
}

void Gold::setOwner(Actor *a)
{
    m_owner = a;
}

void Gold::notPickupAbleByPlayer()
{
    m_pickupAbleByPlayer = false;
}

Gold::~Gold() {}

void Gold::informWorld()
{
    // picked up by player
    if (m_pickupAbleByPlayer)
        getWorld()->playerFoundGold();
    // picked up by protesters
    else
    {
        // inform the protester
        m_owner->foundGold();
    }
}

void Gold::doSomething()
{
    if (!isAlive())
        return;
    
    if (discoveredGoodie())
        return;
    
    // pickup-able by player
    if (m_pickupAbleByPlayer)
    {
        if (pickUpGoodie(getWorld()->getPlayer(), SOUND_GOT_GOODIE, 10))
            return;
    }
    
    // pickup-able by protesters
    else
    {
        if (getWorld()->protesterPicksUpGold(this))
            return;
        // not picked up by protesters, decrease lifetime
        tickPassed();
    }
    
}

// --------------------------------Protester-------------------------------
Location::Location(int col, int row)
{
    m_col = col;
    m_row = row;
}

Protester::Protester(int imageID, StudentWorld* world) : Actor(imageID, 60, 60, left, 1.0, 0)
{
    setWorld(world);
    setHP(5);
    m_ticksToWait = max(0, static_cast<int>(3-getWorld()->getLevel()/4));
    m_leaving = false;
    m_shoutCountdown = 0;
    m_numSquaresToMove = rand() % 53 + 8;
    m_ticksSinceLastTurn = 200;
    m_stunnedTicks = 0;
    
    for (int x = 0; x < VIEW_WIDTH-3; x++)
    {
        for (int y = 0; y < VIEW_HEIGHT-3; y++)
        {
            m_previous[x][y] = NULL;
            m_visited[x][y] = false;
        }
    }
}

void Protester::switchToLeaving()
{
    m_leaving = true;
}

void Protester::setTicksToStare(int ticks)
{
    m_ticksToStare = ticks;
}

Actor::Direction Protester::turnToTarget(int x, int y, int targetX, int targetY)
{
    // up or down
    if (targetX == x)
    {
        // down
        if (targetY < y)
        {
            setDirection(down);
            return down;
        }
        // up
        else
        {
            setDirection(up);
            return up;
        }
    }
    // left or right
    else
    {
        // left
        if (targetX < x)
        {
            setDirection(left);
            return left;
        }
        // right
        else
        {
            setDirection(right);
            return right;
        }
    }
}

void Protester::moveToward(Direction dir)
{
    if (dir == up)
        moveTo(getX(), getY()+1);
    
    else if (dir == down)
        moveTo(getX(), getY()-1);
    
    else if (dir == left)
        moveTo(getX()-1, getY());
    
    else if (dir == right)
        moveTo(getX()+1, getY());
}

bool Protester::canMoveToward(Direction dir)
{
    if (dir == up)
    {
        if (getY() < VIEW_HEIGHT-4
            && !getWorld()->overlapWithBoulder(getX(), getY()+1)
            && !getWorld()->overlapWithEarth(getX(), getY()+1))
            return true;
    }
    else if (dir == down)
    {
        if (getY() > 0
            && !getWorld()->overlapWithBoulder(getX(), getY()-1)
            && !getWorld()->overlapWithEarth(getX(), getY()-1))
            return true;
    }
    else if (dir == left)
    {
        if (getX() > 0
            && !getWorld()->overlapWithBoulder(getX()-1, getY())
            && !getWorld()->overlapWithEarth(getX()-1, getY()))
        {
            return true;
        }
    }
    else if (dir == right)
    {
        if (getX() < VIEW_WIDTH-4
            && !getWorld()->overlapWithBoulder(getX()+1, getY())
            && !getWorld()->overlapWithEarth(getX()+1, getY()))
            return true;
    }
    return false;
}

Actor::Direction Protester::directionConversion(int dir)
{
    switch(dir)
    {
        case DIR_UP:
            return up;
            break;
        case DIR_DOWN:
            return down;
            break;
        case DIR_LEFT:
            return left;
            break;
        case DIR_RIGHT:
            return right;
            break;
    }
    // never reached
    return right;
}

bool Protester::atIntersection()
{
    Direction cur = getDirection();
    if (cur == up || cur == down)
    {
        // if both perpendicular directions are open
        if (canMoveToward(left) && canMoveToward(right))
            // choose left or right randomly
            setDirection(directionConversion(rand() % 2 + 5));
        else if (canMoveToward(left))
            setDirection(directionConversion(DIR_LEFT));
        else if (canMoveToward(right))
            setDirection(directionConversion(DIR_RIGHT));
        else
            return false;
    }
    else if (cur == left || cur == right)
    {
        // if both perpendicular directions are open
        if (canMoveToward(up) && canMoveToward(down))
            // choose up or down randomly
            setDirection(directionConversion(rand() % 2 + 3));
        else if (canMoveToward(up))
            setDirection(directionConversion(DIR_UP));
        else if (canMoveToward(down))
            setDirection(directionConversion(DIR_DOWN));
        else
            return false;
    }
    return true;
}

bool Protester::isProtester()
{
    return true;
}

void Protester::getsAnnoyed(int points)
{
    // leaving state cannot get annoyed
    if (!m_leaving)
        {
        decreaseHP(points);
        // not fully annoyed
        if (getHP() > 0)
        {
            getWorld()->playSound(SOUND_PROTESTER_ANNOYED);
            // set to stunned
            m_stunnedTicks = max(50, static_cast<int>(100-getWorld()->getLevel()*10));
        }
    
        // fully annoyed
        else
        {
            // transition to leaving state
            m_leaving = true;
            getWorld()->playSound(SOUND_PROTESTER_GIVE_UP);
            // set resting ticks to zero
            m_ticksToWait = 0;
            // death by boulder
            if (isKilledByBoulder())
                getWorld()->increaseScore(500);
            // death by squirts
            else
                playerEarnsPoints();
        }
    }
}

Protester::~Protester() {}

void Protester::findLocation(int x, int y)
{
    // exit as starting location, protester's location and ending location
    queue<Location> q;
    q.push(Location(x, y));
    m_visited[x][y] = true;
    
    int curX, curY;
    while (!q.empty())
    {
        curX = q.front().m_col;
        curY = q.front().m_row;
        q.pop();
        
        // starting location equals ending location
        if (curX == getX() && curY == getY())
        {
            return;
        }
        
        // next step is within bounds, doesn't overlap with earth or boulders, is unvisited
        // up
        if (curY < VIEW_HEIGHT-4 && !getWorld()->overlapWithEarth(curX, curY+1)
            && !getWorld()->overlapWithBoulder(curX, curY+1)
            && !m_visited[curX][curY+1])
        {
            // mark as visited
            m_visited[curX][curY+1] = true;
            // insert it to queue
            q.push(Location(curX, curY+1));
            // its predecessor is (curX, curY)
            m_previous[curX][curY+1] = new Location(curX, curY);
        }
        
        // down
        if (curY > 0 && !getWorld()->overlapWithEarth(curX, curY-1)
            && !getWorld()->overlapWithBoulder(curX, curY-1)
            && !m_visited[curX][curY-1])
        {
            // mark as visited
            m_visited[curX][curY-1] = true;
            // insert it to queue
            q.push(Location(curX, curY-1));
            // its predecessor is (curX, curY)
            m_previous[curX][curY-1] = new Location(curX, curY);
        }
        
        // left
        if (curX > 0 && !getWorld()->overlapWithEarth(curX-1, curY)
            && !getWorld()->overlapWithBoulder(curX-1, curY)
            && !m_visited[curX-1][curY])
        {
            // mark as visited
            m_visited[curX-1][curY] = true;
            // insert it to queue
            q.push(Location(curX-1, curY));
            // its predecessor is (curX, curY)
            m_previous[curX-1][curY] = new Location(curX, curY);
        }
        
        // right
        if (curX < VIEW_WIDTH-4 && !getWorld()->overlapWithEarth(curX+1, curY)
            && !getWorld()->overlapWithBoulder(curX+1, curY)
            && !m_visited[curX+1][curY])
        {
            // mark as visited
            m_visited[curX+1][curY] = true;
            // insert it to queue
            q.push(Location(curX+1, curY));
            // its predecessor is (curX, curY)
            m_previous[curX+1][curY] = new Location(curX, curY);
        }
    }
}

int Protester::calcSteps(int targetX, int targetY)
{
    int steps = 0;
    int curX = getX();
    int curY = getY();
    
    while (curX != targetX && curY != targetY)
    {
        // move one step forward
        curX = m_previous[curX][curY]->m_col;
        curY = m_previous[curX][curY]->m_row;
        steps++;
    }
        
    return steps;
}

void Protester::moveAlongPath()
{
    // target location coordinates
    int targetX = m_previous[getX()][getY()]->m_col;
    int targetY = m_previous[getX()][getY()]->m_row;
    
    // set direction
    turnToTarget(getX(), getY(), targetX, targetY);
    
    // move along that direction
    moveTo(targetX, targetY);
}

void Protester::resetField()
{
    for (int x = 0; x < VIEW_WIDTH-3; x++)
    {
        for (int y = 0; y < VIEW_HEIGHT-3; y++)
        {
            // clear previous locations
            delete m_previous[x][y];
            m_previous[x][y] = NULL;
            // clear marks
            m_visited[x][y] = false;
        }
    }
}

void Protester::doSomething()
{
    m_shoutCountdown--;
    m_ticksSinceLastTurn++;
    m_stunnedTicks--;
    m_ticksToStare--;
    
    if (!isAlive())
        return;
    
    // leaving state
    if (m_leaving)
    {
        // protester at exit
        if (getX() == 60 && getY() == 60)
        {
            setDead();
            // decrease current number of protesters
            getWorld()->protesterDied();
            // delete previous locations
            for (int x = 0; x < VIEW_WIDTH-3; x++)
            {
                for (int y = 0; y < VIEW_HEIGHT-3; y++)
                {
                    // (x, y) has a previous location
                    delete m_previous[x][y];
                }
            }
            return;
        }
        
        findLocation(60, 60);
        moveAlongPath();
        
        return;
    }
    
    // resting state or stunned state or staring at gold
    if (m_ticksToStare > 0 || m_stunnedTicks > 0 || getWorld()->getTicks() % (m_ticksToWait+1) != 0)
        return;
    
    // check if within 4.0 radius of TunnelMan
    if (getWorld()->calcRadius(getX(), getY(),
        getWorld()->getPlayer()->getX(), getWorld()->getPlayer()->getY()) <= 4.0)
    {
        // check if protester is facing TunnelMan's direction
        if ((getDirection() == up && getY() < getWorld()->getPlayer()->getY())
            || (getDirection() == down && getY() > getWorld()->getPlayer()->getY())
            || (getDirection() == left && getX() > getWorld()->getPlayer()->getX())
            || (getDirection() == right && getX() < getWorld()->getPlayer()->getX()))
        {
            if (m_shoutCountdown <= 0)
            {
                getWorld()->playSound(SOUND_PROTESTER_YELL);
                getWorld()->getPlayer()->getsAnnoyed(2);
            }
            m_shoutCountdown = 15;
            return;
        }
    }
    
    // performed maze search
    if (findTunnelMan())
        return;

    // direct line of sight, 4.0 units away and no obstacles in the way
    if ((getX() == getWorld()->getPlayer()->getX()
         || getY() == getWorld()->getPlayer()->getY())
        && getWorld()->calcRadius(getX(), getY(),
        getWorld()->getPlayer()->getX(), getWorld()->getPlayer()->getY()) > 4.0
        && getWorld()->noObstacles(getX(), getY(),
        getWorld()->getPlayer()->getX(), getWorld()->getPlayer()->getY()))
    {

        Direction cur = turnToTarget(getX(), getY(),
                        getWorld()->getPlayer()->getX(), getWorld()->getPlayer()->getY());
        moveToward(cur);
        m_numSquaresToMove = 0;
        return;
    }
    
    m_numSquaresToMove--;
    if (m_numSquaresToMove <= 0)
    {
        int dir;
        do
        {
            dir = rand() % 4 + 3;
        } while (!canMoveToward(directionConversion(dir)));
        
        // can move to this direction
        setDirection(directionConversion(dir));
        m_numSquaresToMove = rand() % 53 + 8;
    }
    
    else
    {
        // haven't made a turn in the last 200 ticks
        if (m_ticksSinceLastTurn >= 200)
        {
            // at intersection, picked a new direction
            if (atIntersection())
            {
                m_numSquaresToMove = rand() % 53 + 8;
                m_ticksSinceLastTurn = 0;
            }
        }
    }
    
    if (!canMoveToward(getDirection()))
    {
        // pick a new direction during next non-resting tick
        m_numSquaresToMove = 0;
        return;
    }
    
    moveToward(getDirection());
}

// --------------------------------Regular Protester-------------------------------
RegularProtester::RegularProtester(StudentWorld* world) : Protester(TID_PROTESTER, world)
{
}

RegularProtester::~RegularProtester() {}

bool RegularProtester::findTunnelMan()
{
    return false;
}

void RegularProtester::foundGold()
{
    getWorld()->increaseScore(25);
    switchToLeaving();
}

void RegularProtester::playerEarnsPoints()
{
    getWorld()->increaseScore(100);
}

// --------------------------------Hardcore Protester-------------------------------
HardcoreProtester::HardcoreProtester(StudentWorld* world) : Protester(TID_HARD_CORE_PROTESTER, world)
{
    m_nSteps = static_cast<int>(16+getWorld()->getLevel()*2);
    setTicksToStare(0);
}

HardcoreProtester::~HardcoreProtester() {}

bool HardcoreProtester::findTunnelMan()
{
    // only perfrom maze search when player is more than 4.0 units away
    if (getWorld()->calcRadius(getX(), getY(), getWorld()->getPlayer()->getX(), getWorld()->getPlayer()->getY()) <= 4.0)
        return false;
    
    bool moved = false;
    // find a path to player's location
    findLocation(getWorld()->getPlayer()->getX(), getWorld()->getPlayer()->getY());
    // within m_nSteps
    if (calcSteps(getWorld()->getPlayer()->getX(), getWorld()->getPlayer()->getY()) <= m_nSteps)
    {
        moveAlongPath();
        moved = true;
    }
    // clear previous and marks
    resetField();
    return moved;
    
}

void HardcoreProtester::foundGold()
{
    getWorld()->increaseScore(50);
    // stare at gold
    setTicksToStare(max(50, static_cast<int>(100-getWorld()->getLevel()*10)));
}

void HardcoreProtester::playerEarnsPoints()
{
    getWorld()->increaseScore(250);
}
