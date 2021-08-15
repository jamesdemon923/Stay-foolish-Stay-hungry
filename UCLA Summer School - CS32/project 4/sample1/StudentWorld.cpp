#include "StudentWorld.h"
#include "Actor.h"
#include "GameConstants.h"
#include "GameController.h"
#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

void StudentWorld::setDisplayText()
{
    int level = getLevel();
    int lives = getLives();
    int health = m_player->getHP()*10;
    int squirts = m_player->getWaterCount();
    int gold = m_nGold;
    int barrelsLeft = m_nBarrels;
    int sonar = m_nSonar;
    int score = getScore();
    
    ostringstream oss;
    oss << "Scr: ";
    oss.fill('0');
    oss << setw(6) << score << "  ";
    oss.fill(' ');
    oss << "Lvl: ";
    oss << setw(2) << level << "  ";
    oss << "Lives: ";
    oss << setw(1) << lives << "  ";
    oss << "Hlth: ";
    oss << setw(3) << health << "%  ";
    oss << "Wtr: ";
    oss << setw(2) << squirts << "  ";
    oss << "Gld: ";
    oss << setw(2) << gold << "  ";
    oss << "Sonar: ";
    oss << setw(2) << sonar << "  ";
    oss << "Oil left: ";
    oss << setw(2) << barrelsLeft << "  ";
    

    string s = oss.str();
    setGameStatText(s);
}

Earth* StudentWorld::getEarthAt(int x, int y)
{
    return m_earth[x][y];
}

TunnelMan* StudentWorld::getPlayer()
{
    return m_player;
}

void StudentWorld::addActor(Actor* a)
{
    m_actors.push_back(a);
}

void StudentWorld::foundBarrel()
{
    m_nBarrels--;
}

void StudentWorld::decreasePoints(int points)
{
    m_hitPoints -= points;
}

void StudentWorld::gotSonarKit()
{
    m_nSonar += 2;
}

void StudentWorld::hideEarthAt(int x, int y)
{
    m_earth[x][y]->setVisible(false);
    m_earth[x][y]->setDead();
}

int StudentWorld::numGold()
{
    return m_nGold;
}

void StudentWorld::dropsGold()
{
    m_nGold--;
}

void StudentWorld::hideEarthOverlap(int x, int y)
{
    for (int col = x; col < x+4; col++)
    {
        for (int row = y; row < y+4; row++)
        {
            // location is within m_earth array and earth exists
            if (col >=0 && col < VIEW_WIDTH && row>=0 && row < VIEW_HEIGHT-4
                && m_earth[col][row]->isAlive())
            {
                // remove overlap earth
                hideEarthAt(col, row);
                // play digging sound
                playSound(SOUND_DIG);
            }
        }
    }
}

int StudentWorld::calcRadius(int x1, int y1, int x2, int y2)
{
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

bool StudentWorld::validPos(int x, int y)
{
    vector<Actor*>::iterator it = m_actors.begin();
    while (it != m_actors.end())
    {
        // too close to another distributed object
        if (calcRadius(x, y, (*it)->getX(), (*it)->getY()) <= 6.0)
            return false;
        it++;
    }
    
    return true;
}

bool StudentWorld::withinEarth(int x, int y)
{
    for (int col = x; col < x+4; col++)
    {
        for (int row = y; row < y+4; row++)
        {
            // no visible earth at (col, row)
            if (row >= VIEW_HEIGHT-4 || !m_earth[col][row]->isAlive())
                return false;
        }
    }
    return true;
}

bool StudentWorld::overlapWithEarth(int x, int y)
{
    for (int col = x; col < x+4; col++)
    {
        for (int row = y; row < y+4; row++)
        {
            // has visible earth at (col, row)
            if (row < VIEW_HEIGHT-4 && col < VIEW_WIDTH && m_earth[col][row]->isAlive())
                return true;
        }
    }
    return false;
}

bool StudentWorld::overlapWithBoulder(int x, int y)
{
    for (int i = 0; i < m_nBoulders; i++)
    {
        if (m_actors[i]->isAlive() && calcRadius(x, y, m_actors[i]->getX(), m_actors[i]->getY()) <= 3.0)
            return true;
    }
    return false;
}

bool StudentWorld::runIntoBoulder(int x, int y)
{
    for (int i = 0; i < m_nBoulders; i++)
    {
        if (m_actors[i]->isAlive() && x == m_actors[i]->getX() && y == m_actors[i]->getY())
            return true;
    }
    return false;
}

bool StudentWorld::withinBounds(int x, int y)
{
    for (int col = x; col < x+4; col++)
    {
        for (int row = y; row < y+4; row++)
        {
            // (col, row) out of bound
            if (!(x>-1 && x<VIEW_WIDTH && y>-1 && y<VIEW_HEIGHT))
                return false;
        }
    }
    
    return true;
}

bool StudentWorld::runIntoEarth(int x, int y)
{
    // top 4 rows are always empty
    if (y >= VIEW_HEIGHT-4)
        return false;
    
    return m_earth[x][y]->isAlive();
}

void StudentWorld::illuminate()
{
    vector<Actor*>::iterator it = m_actors.begin();
    while (it != m_actors.end())
    {
        // active objects within radius 12.0 of TunnelMan
        if (calcRadius(getPlayer()->getX(), getPlayer()->getY(),
                          (*it)->getX(), (*it)->getY()) <= 12.0 && (*it)->isAlive())
            (*it)->setVisible(true);
        it++;
    }
}

int StudentWorld::getTicks()
{
    return m_ticksCount;
}

bool StudentWorld::noObstacles(int x1, int y1, int x2, int y2)
{
    // vertical
    if (x1 == x2)
    {
        if (y2 < y1)
        {
            int temp = y1;
            y1 = y2;
            y2 = temp;
        }
        for (int i = y1; i < y2; i++)
        {
            if (overlapWithEarth(x1, i) || overlapWithBoulder(x1, i))
                return false;
        }
        return true;
    }
    
    // horizontal
    else
    {
        if (x2 < x1)
        {
            int temp = x1;
            x1 = x2;
            x2 = temp;
        }
        for (int i = x1; i < x2; i++)
        {
            if (overlapWithEarth(i, y1) || overlapWithBoulder(i, y1))
                return false;
        }
        return true;
    }
}

void StudentWorld::protesterDied()
{
    m_nCurProtesters--;
}

bool StudentWorld::hitsProtester(Actor *a, int points)
{
    vector<Actor*>::iterator it = m_actors.begin();
    bool protestersAnnoyed = false;
    while (it != m_actors.end())
    {
        if ((*it)->isProtester() && calcRadius(a->getX(), a->getY(),
                                               (*it)->getX(), (*it)->getY()) <= 3.0)
        {
            (*it)->getsAnnoyed(points);
            // is boulder
            if (points == 10)
            {
                (*it)->bonkedByBoulder();
            }
            protestersAnnoyed = true;
        }
        it++;
    }
    
    return protestersAnnoyed;
}

void StudentWorld::playerFoundGold()
{
    m_nGold++;
}

bool StudentWorld::protesterPicksUpGold(Gold* g)
{
    for (int i = 0; i < m_actors.size(); i++)
    {
        // the actor is a protester
        if (m_actors[i]->isProtester())
        {
            // doesn't increase score here
            // increase player's score in Regular and Hardcore Protester class
            if (calcRadius(g->getX(), g->getY(), m_actors[i]->getX(), m_actors[i]->getY()) <= 3.0)
            {
                g->setDead();
                playSound(SOUND_PROTESTER_FOUND_GOLD);
                
                // the protester who just picked up the gold becomes its owner
                g->setOwner(m_actors[i]);
                g->informWorld();
            
                return true;
            }
        }
    }
    return false;
}

// constructor
StudentWorld::StudentWorld(std::string assetDir) : GameWorld(assetDir)
{
    m_player = NULL;
}

Location StudentWorld::generateViableCoord(int Xmin, int Xmax, int Ymin, int Ymax)
{
    int Xa = Xmax-Xmin+1;
    int Xb = Xmin;
    
    int Ya = Ymax-Ymin+1;
    int Yb = Ymin;
    
    int x;
    int y;
    do {
        // randomly generate coordinates
        x = rand() % Xa + Xb;
        y = rand() % Ya + Yb;
    } while (!validPos(x, y) || !withinEarth(x, y));
    
    return Location(x, y);
}

int StudentWorld::init()
{
    m_ticksCount = -1;
    m_nProtesters = min(15, static_cast<int>(2+getLevel()*1.5));
    m_nBoulders = min(static_cast<int>(getLevel()/2+2), 9);
    m_nTotalGold = max(static_cast<int>(5-getLevel()/2), 2);
    m_nBarrels = min(static_cast<int>(2+getLevel()), 21);
    m_nCurProtesters = 0;
    m_probHardcore = min(90, static_cast<int>(getLevel()*10+30));
    
    // inventory
    m_nSonar = 1;
    m_nGold = 0;
    
    // fill oil field with Earth objects
    for (int x = 0; x < VIEW_WIDTH; x++)
    {
        for (int y = 0; y < VIEW_HEIGHT-4; y++)
        {
            m_earth[x][y] = new Earth(x, y);
        }
    }

    // clear out Earth for mine shaft
    for (int x = 30; x < 34; x++)
    {
        for (int y = 4; y < 60; y++)
        {
            hideEarthAt(x, y);
        }
    }

    // create player
    m_player = new TunnelMan(this);
    
    // distribute Boulders
    for (int i = 0; i < m_nBoulders; i++)
    {
        Location loc = generateViableCoord(0, 60, 20, 56);
        
        // not close to other boulders and within earth
        m_actors.push_back(new Boulder(loc.m_col,loc.m_row, this));
        // clear out earth under current boulder
        hideEarthOverlap(loc.m_col, loc.m_row);
    }
    
    // distribute Barrels
    for (int i = 0; i < m_nBarrels; i++)
    {
        Location loc = generateViableCoord(0, 60, 0, 56);

        // not close to other boulders and within earth
        m_actors.push_back(new Barrel(loc.m_col, loc.m_row, this));
    }
    
    // distribute gold nuggets
    for (int i = 0; i < m_nTotalGold; i++)
    {
        Location loc = generateViableCoord(0, 60, 0, 56);
        
        // not close to other boulders and within earth
        m_actors.push_back(new Gold(getPlayer(), loc.m_col, loc.m_row, this));
    }
    
    return GWSTATUS_CONTINUE_GAME;
}


int StudentWorld::move()
{
    setDisplayText();
    
    // update ticks
    m_ticksCount++;
    m_nTicksToAddProtesters--;
    
    // add new object
    int G = getLevel() * 25 + 300;
    // 1 in G chance to add goodie
    if (rand() % G == 0)
    {
        // 1/5 chance add sonar
        if (rand() % 5 == 0)
            m_actors.push_back(new Sonar(this));
        // 4/5 chance add water pool
        else
        {
            int x;
            int y;
            do {
                // randomly generate coordinates
                x = rand() % VIEW_WIDTH;
                y = rand() % VIEW_HEIGHT-3;
            } while (overlapWithEarth(x, y) || overlapWithBoulder(x, y));
            
            // earth-less and boulder-less location
            m_actors.push_back(new Water(x, y, this));
        }
    }
    
    // add protester at first tick
    // or if not enough protesters and waited at least T ticks
    if (m_ticksCount == 0 || (m_nCurProtesters < m_nProtesters
                              && m_nTicksToAddProtesters <= 0))
    {
        // add regular protester
        if (rand() % 99 > m_probHardcore)
        {
            m_actors.push_back(new RegularProtester(this));
        }
        // add hardcore protester
        else
            m_actors.push_back(new HardcoreProtester(this));
    
        // update number of protesters in the field
        m_nCurProtesters++;
        // reset m_nTicksToAddProtesters
        m_nTicksToAddProtesters = max(25, static_cast<int>(200-getLevel()));
    }
    
    // ask the player to do something
    getPlayer()->doSomething();
    
    // ask each active Actor to do something
    vector<Actor*>::iterator it = m_actors.begin();
    while (it != m_actors.end())
    {
        if ((*it)->isAlive())
        {
            (*it)->doSomething();
            // player died
            if (!m_player->isAlive())
            {
                decLives();
                return GWSTATUS_PLAYER_DIED;
            }
            // finish level
            if (m_nBarrels == 0)
            {
                playSound(SOUND_FINISHED_LEVEL);
                return GWSTATUS_FINISHED_LEVEL;
            }
        }
        it++;
    }

    // remove dead Actors
    it = m_actors.begin();
    while (it != m_actors.end())
    {
        if (!(*it)->isAlive())
            (*it)->setVisible(false);
        it++;
    }

    // return proper result
    // player died
    if (!m_player->isAlive())
    {
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    
    // finish level
    if (m_nBarrels == 0)
    {
        playSound(SOUND_FINISHED_LEVEL);
        return GWSTATUS_FINISHED_LEVEL;
    }
    
    return GWSTATUS_CONTINUE_GAME;
    
}

void StudentWorld::cleanUp()
{
    // delete all Earth objects
    for (int x = 0; x < 60; x++)
        for (int y = 0; y < 60; y++)
            delete m_earth[x][y];
    
    // delete player
    delete m_player;
    
    // delete actors
    vector<Actor*>::iterator it = m_actors.begin();
    while (it != m_actors.end())
    {
        (*it)->setVisible(false);
        it++;
    }
    m_actors.clear();
}

StudentWorld::~StudentWorld()
{
    // delete all Earth objects
    for (int x = 0; x < 60; x++)
        for (int y = 0; y < 60; y++)
            delete m_earth[x][y];
    
    // delete player
    delete m_player;
    
    // delete actors
    m_actors.clear();
}

