#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"
#include <algorithm>
#include <queue>
using namespace std;
// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

//// Actor ////
// constructor
Actor::Actor(int imageID, int startX, int startY, Direction dir, double size, unsigned int depth)
: GraphObject(imageID, startX, startY, dir, size, depth)
{
    setVisible(true);
    m_alive = true;
    m_killedByBoulder = false;
}

// accessors
bool Actor::isAlive()
{
    return m_alive;
}

StudentWorld* Actor::getWorld()
{
    return m_world;
}

int Actor::getHP()
{
    return m_hitPoints;
}

// mutators
void Actor::setDead()
{
    m_alive = false;
}

void Actor::setWorld(StudentWorld* world)
{
    m_world = world;
}

void Actor::setHP(int points)
{
    m_hitPoints = points;
}

void Actor::decreaseHP(int points)
{
    m_hitPoints = m_hitPoints - points;
}

// functions
bool Actor::isProtester()
{
    return false;
}

void Actor::findGold() {}

void Actor::getAnnoyed(int points) {}

void Actor::bonkedByBoulder()
{
    m_killedByBoulder = true;
}

bool Actor::killedByBoulder()
{
    return m_killedByBoulder;
}

// destructor
Actor::~Actor() {}

//// Earth ////
// constructor
Earth::Earth(int x, int y) : Actor(TID_EARTH, x, y, right, 0.25, 3) {}

// functions
void Earth::doSomething() {}

// destructor
Earth::~Earth() {}

//// TunnelMan ////
// constructor
TunnelMan::TunnelMan(StudentWorld* world) : Actor(TID_PLAYER, 30, 60, right, 1.0, 0)
{
    setWorld(world);
    setHP(10);
    m_water = 5;
    m_sonar = 1;
}

// accessors
int TunnelMan::numWater()
{
    return m_water;
}

int TunnelMan::numSonar()
{
    return m_sonar;
}

// mutators
void TunnelMan::changeNumSonar()
{
    m_sonar = m_sonar + 2;
}

void TunnelMan::changeNumWater(int num)
{
    m_water = m_water + num;
}

// functions
void TunnelMan::doSomething()
{
    if (!isAlive()) return;
    
    int val;
    // valid input
    if (getWorld()->getKey(val))
    {
        if (!isAlive()) return;
        
        Direction cur = getDirection();
        switch(val)
        {
            // UP
            case KEY_PRESS_UP:
                // facing same direction and can move
                if (cur == up && getY() < 60 && !getWorld()->overlapBoulder(getX(), getY()+1))
                {
                    // move along this direction
                    moveTo(getX(), getY()+1);
                }
                // facing different direction or out of bound
                // or would run into boulder, doesn't move
                else moveTo(getX(), getY());
                
                // delete any earth objects holding overlapping position
                getWorld()->hideEarthOverlap(getX(), getY());
                // reset direction
                setDirection(up);
                break;
               
            // DOWN
            case KEY_PRESS_DOWN:
                if (cur == down && getY() > 0 && !getWorld()->overlapBoulder(getX(), getY()-1))
                {
                    moveTo(getX(), getY()-1);
                }
                else moveTo(getX(), getY());
                
                getWorld()->hideEarthOverlap(getX(), getY());
                setDirection(down);
                break;
                
            // LEFT
            case KEY_PRESS_LEFT:
                if (cur == left && getX() > 0 && !getWorld()->overlapBoulder(getX()-1, getY()))
                {
                    moveTo(getX()-1, getY());
                }
                else moveTo(getX(), getY());
                
                getWorld()->hideEarthOverlap(getX(), getY());
                setDirection(left);
                break;
                
            // RIGHT
            case KEY_PRESS_RIGHT:
                if (cur == right && getX() < 60 && !getWorld()->overlapBoulder(getX()+1, getY()))
                {
                    moveTo(getX()+1, getY());
                }
                else moveTo(getX(), getY());
                
                getWorld()->hideEarthOverlap(getX(), getY());
                setDirection(right);
                break;
            
            // SPACE
            // fire a squirt
            case KEY_PRESS_SPACE:
                if (numWater() > 0)
                {
                    changeNumWater(-1);
                    getWorld()->playSound(SOUND_PLAYER_SQUIRT);
                
                    int squirtX, squirtY;
                    Direction dir = getDirection();
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

                    // doesn't run into boulder and doesn't have earth and is in bounds
                    if ((!getWorld()->runIntoBoulder(squirtX, squirtY) && !getWorld()->runIntoEarth(squirtX, squirtY) && getWorld()->inBounds(squirtX, squirtY)))
                    {
                        getWorld()->addActor(new Squirt(squirtX, squirtY, dir, getWorld()));
                    }
                }
                break;
            // Z           
            case 'z':
            case 'Z':
                if (m_sonar > 0)
                {
                    m_sonar--;
                    getWorld()->illuminate();
                    getWorld()->playSound(SOUND_SONAR);
                }
                break;
            // TAB        
            case KEY_PRESS_TAB:
                if (getWorld()->numGold() > 0)
                {
                    Gold* g = new Gold(this, getX(), getY(), getWorld());
                    // update state
                    g->notPickupAbleByPlayer();
                    // add gold
                    getWorld()->addActor(g);
                    // gold count decreases
                    getWorld()->dropGold();
                }
                break;
        }
        
    }
}

void TunnelMan::getAnnoyed(int points)
{
    decreaseHP(points);
    if (getHP() <= 0)
    {
        setDead();
        getWorld()->playSound(SOUND_PLAYER_GIVE_UP);
    }
}

// destructor
TunnelMan::~TunnelMan() {}

//// Boulder ////
// constructor
Boulder::Boulder(int x, int y, StudentWorld* world) : Actor(TID_BOULDER, x, y, down, 1.0, 1)
{
    m_state = Stable;
    setWorld(world);
}

// functions
void Boulder::doSomething()
{
    if (!isAlive()) return;
    
    if (m_state == Stable)
    {
        for (int x = getX(); x < getX() + 4; x++)
        {
            if (getWorld()->getEarthAt(x, getY() - 1)->isAlive()) return;
        }
        m_state = Waiting;
        m_waitingTime = 0;
    }
    
    else if (m_state == Waiting)
    {
        if (m_waitingTime == 30)
        {
            m_state = Falling;
            getWorld()->playSound(SOUND_FALLING_ROCK);
        }
        else m_waitingTime++;
    }
    
    else if (m_state == Falling)
    {

        // reaches bottom or would run into another Boulder or Earth
        if (getY() == 0 || getWorld()->runIntoBoulder(getX(), getY() - 1) || getWorld()->overlapEarth(getX(), getY() - 1))
        {
            setDead();
        }
        else
        {
            // kill TunnelMan
            if (getWorld()->getRadius(getWorld()->getPlayer()->getX(), getWorld()->getPlayer()->getY(), getX(), getY()) <= 3.0)
            {
                getWorld()->getPlayer()->getAnnoyed(100);
            }
            // kill Protester
            else
            {
                getWorld()->hitsProtester(this, 100);
            }
            moveTo(getX(), getY() - 1);
        }
    }
}


// destructor
Boulder::~Boulder() {}

//// Squirt ////
// constructor
Squirt::Squirt(int x, int y, Direction dir, StudentWorld* world) :
Actor(TID_WATER_SPURT, x, y, dir, 1.0, 1)
{
    setWorld(world);
    m_travelDis = 4;
}

// functions
void Squirt::doSomething()
{
    if (!isAlive())
        return;
    
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
        if (getY() == VIEW_HEIGHT-1 || getWorld()->runIntoBoulder(getX(), getY()+1) || getWorld()->runIntoEarth(getX(), getY()+1))
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
        if (getY() == 0 || getWorld()->runIntoBoulder(getX(), getY()-1) || getWorld()->runIntoEarth(getX(), getY()-1))
        {
            setDead();
        }
        else
        {
            moveTo(getX(), getY()-1);
            m_travelDis--;
        }
    }
    else if (cur == left)
    {
        if (getX() == 0 || getWorld()->runIntoBoulder(getX()-1, getY()) || getWorld()->runIntoEarth(getX()-1, getY()))
        {
            setDead();
        }
        else
        {
            moveTo(getX()-1, getY());
            m_travelDis--;
        }
    }
    else if (cur == right)
    {
        if (getX() == VIEW_WIDTH-1 || getWorld()->runIntoBoulder(getX()+1, getY()) || getWorld()->runIntoEarth(getX()+1, getY()))
        {
            setDead();
        }
        else
        {
            moveTo(getX()+1, getY());
            m_travelDis--;
        }
    }
}

// destructor
Squirt::~Squirt() {}

//// Goodie ////
// constructor
Goodie::Goodie(int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) : Actor(imageID, startX, startY, dir, size, depth) {}

// mutators
void Goodie::changeVisibility(bool v)
{
    m_visible = v;
}

void Goodie::setLifetime(int ticks)
{

    m_lifetime = ticks;
}

// functions
bool Goodie::isVisible()
{
    return m_visible;
}

void Goodie::tickPassed()
{
    m_lifetime--;
    if (m_lifetime == 0) setDead();
}

bool Goodie::discoveredGoodie()
{
    // is not visible and TunnelMan is in a radius of 4.0
    if (!isVisible() && getWorld()->getRadius
        (getX(), getY(), getWorld()->getPlayer()->getX(), getWorld()->getPlayer()->getY()) <= 4.0)
    {
        setVisible(true);
        changeVisibility(true);
        return true;
    }
    return false;
}

bool Goodie::pickUpGoodie(Actor* a, int sound, int score)
{
    // in a radius of 3.0 from TunnelMan or Protester
    if (getWorld()->getRadius(getX(), getY(), a->getX(), a->getY()) <= 3.0)
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

// destructor
Goodie::~Goodie() {}

//// Barrel of Oil ////
// constructor
Barrel::Barrel(int x, int y, StudentWorld* world) : Goodie(TID_BARREL, x, y, right, 1.0, 2)
{
    setWorld(world);
    setVisible(false);
    changeVisibility(false);
}

// functions
void Barrel::doSomething()
{
    if (!isAlive()) return;
    
    if (discoveredGoodie()) return;
    
    // check if player in 3.0 radius
    pickUpGoodie(getWorld()->getPlayer(), SOUND_FOUND_OIL, 1000);
}

void Barrel::informWorld()
{
    getWorld()->findBarrel();
}

// destructor
Barrel::~Barrel() {}

//// Sonar Kit ////
// constructor
Sonar::Sonar(StudentWorld *world) : Goodie(TID_SONAR, 0, 60, right, 1.0, 2)
{
    setWorld(world);
    setLifetime(max(100, static_cast<int>(300-10*getWorld()->getLevel())));
}

// functions
void Sonar::doSomething()
{
    if (!isAlive()) return;

    if (pickUpGoodie(getWorld()->getPlayer(), SOUND_GOT_GOODIE, 75)) return;

    // lifetime decreases and check if life expires
    tickPassed();
}

void Sonar::informWorld()
{
    getWorld()->getPlayer()->changeNumSonar();
}

// destructor
Sonar::~Sonar() {}

//// Water Pool ////
// constructor
Water::Water(int x, int y, StudentWorld* world) : Goodie(TID_WATER_POOL, x, y, right, 1.0, 2)
{
    setWorld(world);
    setLifetime(max(100, static_cast<int>(300-10*getWorld()->getLevel())));
}

// functions
void Water::doSomething()
{
    if (!isAlive()) return;

    if (pickUpGoodie(getWorld()->getPlayer(), SOUND_GOT_GOODIE, 100)) return;

    tickPassed();
}

void Water::informWorld()
{
    getWorld()->getPlayer()->changeNumWater(5);
}

// destructor
Water::~Water() {}

//// Gold Nugget ////
// constructor
Gold::Gold(Actor* owner,int x, int y, StudentWorld* world) : Goodie(TID_GOLD, x, y, right, 1.0, 2)
{
    setWorld(world);
    setVisible(false);
    changeVisibility(false);
    m_owner = owner;
    // gold in temp state has lifetime of 100 ticks
    setLifetime(100);
    m_canPickedUpByPlayer = true;
}

// mutators
void Gold::setOwner(Actor *a)
{
    m_owner = a;
}

void Gold::notPickupAbleByPlayer()
{
    m_canPickedUpByPlayer = false;
}

// functions
void Gold::doSomething()
{
    if (!isAlive()) return;
    
    if (discoveredGoodie()) return;
    
    //able by player
    if (m_canPickedUpByPlayer)
    {
        if (pickUpGoodie(getWorld()->getPlayer(), SOUND_GOT_GOODIE, 10)) return;
    }
    //able by protester
    else
    {
        if (getWorld()->protesterPicksUpGold(this)) return;
        // not picked up by protesters, decrease lifetime
        tickPassed();
    }
    
}

void Gold::informWorld()
{
    // picked up by player
    if (m_canPickedUpByPlayer)
        getWorld()->getGold();
    // picked up by protesters
    else
    {
        m_owner->findGold();
    }
}

// destructor
Gold::~Gold() {}

//// Protester ////
Location::Location(int col, int row)
{
    m_col = col;
    m_row = row;
}

// constructor
Protester::Protester(int imageID, StudentWorld* world) : Actor(imageID, 60, 60, left, 1.0, 0)
{
    setWorld(world);
    setHP(5);
    m_ticksToWaitBetweenMoves = max(0, static_cast<int>(3-getWorld()->getLevel()/4));
    m_leaveTheOilField = false;
    m_shoutTick = 0;
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

// mutators
void Protester::switchToLeave()
{
    m_leaveTheOilField = true;
}

void Protester::setTicksWhenGetStunned(int ticks)
{
    m_ticksWhenGetStunned = ticks;
}

// functions
void Protester::doSomething()
{
    m_shoutTick++;
    m_ticksSinceLastTurn++;
    m_stunnedTicks--;
    m_ticksWhenGetStunned--;

    if (!isAlive()) return;

    if (m_leaveTheOilField)
    {
        // protester leave
        if (getX() == 60 && getY() == 60)
        {
            setDead();
            // update current number of protesters
            getWorld()->protesterDies();
            for (int x = 0; x < VIEW_WIDTH - 3; x++)
            {
                for (int y = 0; y < VIEW_HEIGHT - 3; y++)
                {
                    // (x, y) has a previous location
                    delete m_previous[x][y];
                }
            }
            return;
        }
        else
        {
            getExitLocation(60, 60);
            moveAlongPath();
            return;
        }
    }

    if (m_ticksWhenGetStunned > 0 || m_stunnedTicks > 0 || getWorld()->numTicks() % (m_ticksToWaitBetweenMoves + 1) != 0) return;

    // check if within 4.0 radius of TunnelMan
    if (getWorld()->getRadius(getX(), getY(), getWorld()->getPlayer()->getX(), getWorld()->getPlayer()->getY()) <= 4.0)
    {
        // check if protester is facing TunnelMan's direction
        if ((getDirection() == up && getY() < getWorld()->getPlayer()->getY())
            || (getDirection() == down && getY() > getWorld()->getPlayer()->getY())
            || (getDirection() == left && getX() > getWorld()->getPlayer()->getX())
            || (getDirection() == right && getX() < getWorld()->getPlayer()->getX()))
        {
            if (m_shoutTick > 60)
            {
                getWorld()->playSound(SOUND_PROTESTER_YELL);
                getWorld()->getPlayer()->getAnnoyed(2);
                m_shoutTick = 0;
            }
            return;
        }
    }

    if (getPathToTunnelMan()) return;

    // direct line of sight, 4.0 units away and no obstacles in the way
    if ((getX() == getWorld()->getPlayer()->getX() || getY() == getWorld()->getPlayer()->getY())
        && getWorld()->getRadius(getX(), getY(), getWorld()->getPlayer()->getX(), getWorld()->getPlayer()->getY()) > 4.0
        && getWorld()->noObstacles(getX(), getY(), getWorld()->getPlayer()->getX(), getWorld()->getPlayer()->getY()))
    {

        Direction cur = turnToTarget(getX(), getY(), getWorld()->getPlayer()->getX(), getWorld()->getPlayer()->getY());
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

        setDirection(directionConversion(dir));
        m_numSquaresToMove = rand() % 53 + 8;
    }

    else
    {
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
        m_numSquaresToMove = 0;
        return;
    }

    moveToward(getDirection());
}

void Protester::getExitLocation(int x, int y)
{
    queue<Location> q;
    q.push(Location(x, y));
    bool visited[61][61];
    for (int i = 0; i < 61; i++)
    {
        for (int j = 0; j < 61; j++)
        {
            visited[i][j] = true;
        }
    }

    int curX, curY;
    while (!q.empty())
    {
        curX = q.front().m_col;
        curY = q.front().m_row;
        q.pop();

        if (curX == getX() && curY == getY()) return;
        if (curX == 59 && curY == 60) {
            int z = 10;
        }
        // UP
        if (curY < VIEW_HEIGHT - 4 && !getWorld()->overlapEarth(curX, curY + 1)
            && !m_visited[curX][curY + 1])
        {
            // mark as visited
            m_visited[curX][curY + 1] = true;
            q.push(Location(curX, curY + 1));
            m_previous[curX][curY + 1] = new Location(curX, curY);
        }

        // DOWN
        if (curY > 0 && !getWorld()->overlapEarth(curX, curY - 1)
            && !m_visited[curX][curY - 1])
        {
            m_visited[curX][curY - 1] = true;
            q.push(Location(curX, curY - 1));
            m_previous[curX][curY - 1] = new Location(curX, curY);
        }

        // LEFT
        if (curX > 0 && !getWorld()->overlapEarth(curX - 1, curY)
            && !m_visited[curX - 1][curY])
        {
            m_visited[curX - 1][curY] = true;
            q.push(Location(curX - 1, curY));
            m_previous[curX - 1][curY] = new Location(curX, curY);
        }

        // RIGHT
        if (curX < VIEW_WIDTH - 4 && !getWorld()->overlapEarth(curX + 1, curY)
            && !m_visited[curX + 1][curY])
        {
            m_visited[curX + 1][curY] = true;
            q.push(Location(curX + 1, curY));
            m_previous[curX + 1][curY] = new Location(curX, curY);
        }
    }
}

void Protester::getTunnelManLocation(int x, int y)
{
    queue<Location> q;
    q.push(Location(x, y));
    bool visited[61][61];
    for (int i = 0; i < 61; i++)
    {
        for (int j = 0; j < 61; j++)
        {
            visited[i][j] = true;
        }
    }

    int curX, curY;
    while (!q.empty())
    {
        curX = q.front().m_col;
        curY = q.front().m_row;
        q.pop();

        if (curX == getX() && curY == getY()) return;
        if (curX == 59 && curY == 60) {
            int z = 10;
        }
        // UP
        if (curY < VIEW_HEIGHT - 4 && !getWorld()->overlapEarth(curX, curY + 1)
            && !getWorld()->overlapBoulder(curX, curY + 1)
            && !m_visited[curX][curY + 1])
        {
            // mark as visited
            m_visited[curX][curY + 1] = true;
            q.push(Location(curX, curY + 1));
            m_previous[curX][curY + 1] = new Location(curX, curY);
        }

        // DOWN
        if (curY > 0 && !getWorld()->overlapEarth(curX, curY - 1)
            && !getWorld()->overlapBoulder(curX, curY - 1)
            && !m_visited[curX][curY - 1])
        {
            m_visited[curX][curY - 1] = true;
            q.push(Location(curX, curY - 1));
            m_previous[curX][curY - 1] = new Location(curX, curY);
        }

        // LEFT
        if (curX > 0 && !getWorld()->overlapEarth(curX - 1, curY)
            && !getWorld()->overlapBoulder(curX - 1, curY)
            && !m_visited[curX - 1][curY])
        {
            m_visited[curX - 1][curY] = true;
            q.push(Location(curX - 1, curY));
            m_previous[curX - 1][curY] = new Location(curX, curY);
        }

        // RIGHT
        if (curX < VIEW_WIDTH - 4 && !getWorld()->overlapEarth(curX + 1, curY)
            && !getWorld()->overlapBoulder(curX + 1, curY)
            && !m_visited[curX + 1][curY])
        {
            m_visited[curX + 1][curY] = true;
            q.push(Location(curX + 1, curY));
            m_previous[curX + 1][curY] = new Location(curX, curY);
        }
    }
}

void Protester::moveAlongPath()
{
    // target location coordinates
    int targetX = m_previous[getX()][getY()]->m_col;
    int targetY = m_previous[getX()][getY()]->m_row;

    // set direction
    Direction dir = turnToTarget(getX(), getY(), targetX, targetY);

    // move along that direction
    moveToward(dir);
}

int Protester::calcSteps(int targetX, int targetY)
{
    int steps = 0;
    int curX = getX();
    int curY = getY();

    while (curX != targetX && curY != targetY)
    {
        curX = m_previous[curX][curY]->m_col;
        curY = m_previous[curX][curY]->m_row;
        steps++;
    }

    return steps;
}

Actor::Direction Protester::turnToTarget(int x, int y, int targetX, int targetY)
{
    if (targetX == x)
    {
        // DOWN
        if (targetY < y)
        {
            setDirection(down);
            return down;
        }
        // UP
        else
        {
            setDirection(up);
            return up;
        }
    }
    else
    {
        // LEFT
        if (targetX < x)
        {
            setDirection(left);
            return left;
        }
        // RIGHT
        else
        {
            setDirection(right);
            return right;
        }
    }
}

void Protester::moveToward(Direction dir)
{
    if (dir == up) moveTo(getX(), getY()+1);
    else if (dir == down) moveTo(getX(), getY()-1);
    else if (dir == left) moveTo(getX()-1, getY());
    else if (dir == right) moveTo(getX()+1, getY());
}

bool Protester::canMoveToward(Direction dir)
{
    if (dir == up)
    {
        if (getY() < VIEW_HEIGHT-4 && !getWorld()->overlapBoulder(getX(), getY()+1) && !getWorld()->overlapEarth(getX(), getY()+1)) return true;
    }
    else if (dir == down)
    {
        if (getY() > 0 && !getWorld()->overlapBoulder(getX(), getY()-1) && !getWorld()->overlapEarth(getX(), getY()-1)) return true;
    }
    else if (dir == left)
    {
        if (getX() > 0 && !getWorld()->overlapBoulder(getX()-1, getY()) && !getWorld()->overlapEarth(getX()-1, getY())) return true;
    }
    else if (dir == right)
    {
        if (getX() < VIEW_WIDTH-4 && !getWorld()->overlapBoulder(getX()+1, getY()) && !getWorld()->overlapEarth(getX()+1, getY())) return true;
    }
    return false;
}

Actor::Direction Protester::directionConversion(int dir)
{
    switch(dir)
    {
        case Dir_UP:
            return up;
            break;
        case Dir_DOWN:
            return down;
            break;
        case Dir_LEFT:
            return left;
            break;
        case Dir_RIGHT:
            return right;
            break;
    }
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
            setDirection(directionConversion(Dir_LEFT));
        else if (canMoveToward(right))
            setDirection(directionConversion(Dir_RIGHT));
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
            setDirection(directionConversion(Dir_UP));
        else if (canMoveToward(down))
            setDirection(directionConversion(Dir_DOWN));
        else
            return false;
    }
    return true;
}

bool Protester::isProtester()
{
    return true;
}

void Protester::getAnnoyed(int points)
{
    // leaving state cannot get annoyed
    if (!m_leaveTheOilField)
    {
        decreaseHP(points);

        if (getHP() > 0)
        {
            getWorld()->playSound(SOUND_PROTESTER_ANNOYED);
            // set to stunned
            m_stunnedTicks = max(50, static_cast<int>(100-getWorld()->getLevel()*10));
        }
        else
        {
            // transition to leaving state
            m_leaveTheOilField = true;
            getWorld()->playSound(SOUND_PROTESTER_GIVE_UP);
            m_ticksToWaitBetweenMoves = 0;
            // killed by boulder
            if (killedByBoulder()) getWorld()->increaseScore(500);
            // killed by squirts
            else playerEarnsPoints();
        }
    }
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

// destructor
Protester::~Protester() {}

//// Regular Protester ////
// constructor
RegularProtester::RegularProtester(StudentWorld* world) : Protester(TID_PROTESTER, world) {}

// functions
bool RegularProtester::getPathToTunnelMan()
{
    return false;
}

void RegularProtester::findGold()
{
    getWorld()->increaseScore(25);
    switchToLeave();
}

void RegularProtester::playerEarnsPoints()
{
    getWorld()->increaseScore(100);
}

// destructor
RegularProtester::~RegularProtester() {}

//// Hardcore Protester ////
// constructor
HardcoreProtester::HardcoreProtester(StudentWorld* world) : Protester(TID_HARD_CORE_PROTESTER, world)
{
    m_steps = static_cast<int>(16+getWorld()->getLevel()*2);
    setTicksWhenGetStunned(0);
}

// functions
bool HardcoreProtester::getPathToTunnelMan()
{
    // only perfrom maze search when player is more than 4.0 units away
    if (getWorld()->getRadius(getX(), getY(), getWorld()->getPlayer()->getX(), getWorld()->getPlayer()->getY()) <= 4.0) return false;
    
    bool moved = false;

    // get the path to player's location
    getExitLocation(getWorld()->getPlayer()->getX(), getWorld()->getPlayer()->getY());
    if (calcSteps(getWorld()->getPlayer()->getX(), getWorld()->getPlayer()->getY()) <= m_steps)
    {
        moveAlongPath();
        moved = true;
    }
    // clear
    resetField();
    return moved;
    
}

void HardcoreProtester::findGold()
{
    getWorld()->increaseScore(50);
    setTicksWhenGetStunned(max(50, static_cast<int>(100-getWorld()->getLevel()*10)));
}

void HardcoreProtester::playerEarnsPoints()
{
    getWorld()->increaseScore(250);
}

// destructor
HardcoreProtester::~HardcoreProtester() {}