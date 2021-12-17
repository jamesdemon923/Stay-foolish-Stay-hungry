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

// accessors
Earth* StudentWorld::getEarthAt(int x, int y)
{
    return m_earth[x][y];
}

TunnelMan* StudentWorld::getPlayer()
{
    return m_player;
}

int StudentWorld::numTicks()
{
	return m_ticks;
}

int StudentWorld::numGold()
{
	return m_gold;
}

// mutators
void StudentWorld::getGold()
{
	m_gold++;
}

void StudentWorld::dropGold()
{
	m_gold--;
}

void StudentWorld::findBarrel()
{
	m_barrels--;
}

void StudentWorld::decreasePoints(int points)
{
	m_hitPoints = m_hitPoints - points;
}

void StudentWorld::protesterDies()
{
	m_aliveProtesters--;
}

// functions
void StudentWorld::setGameStat()
{
	int level = getLevel();
	int lives = getLives();
	int health = m_player->getHP() * 10;
	int squirts = m_player->numWater();
	int gold = m_gold;
	int barrelsLeft = m_barrels;
	int sonar = m_player->numSonar();
	int score = getScore();

	ostringstream oss;
    oss.fill('0');
    oss << "Scr: ";
    oss << setw(6) << score << " ";
	oss.fill(' ');
	oss << "Lvl: ";
	oss << setw(1) << level << " ";
	oss << "Lives: ";
	oss << setw(2) << lives << " ";
	oss << "Hlth: ";
	oss << setw(3) << health << "% ";
	oss << "Wtr: ";
	oss << setw(2) << squirts << " ";
	oss << "Gld: ";
	oss << setw(2) << gold << " ";
    oss << "Sonar: ";
    oss << setw(2) << sonar << " ";
    oss << "Oil left: ";
    oss << setw(2) << barrelsLeft << " ";

	string s = oss.str();
	setGameStatText(s);
}

void StudentWorld::addActor(Actor* a)
{
    m_actors.push_back(a);
}

void StudentWorld::hideEarthAt(int x, int y)
{
    m_earth[x][y]->setVisible(false);
    m_earth[x][y]->setDead();
}

void StudentWorld::hideEarthOverlap(int x, int y)
{
    for (int col = x; col < x+4; col++)
    {
        for (int row = y; row < y+4; row++)
        {
            if (col >=0 && col < VIEW_WIDTH && row>=0 && row < VIEW_HEIGHT-4
                && m_earth[col][row]->isAlive())
            {
                // remove overlap earth
                hideEarthAt(col, row);
                // dig sound
                playSound(SOUND_DIG);
            }
        }
    }
}

int StudentWorld::getRadius(int x1, int y1, int x2, int y2)
{
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

bool StudentWorld::checkPos(int x, int y)
{
    vector<Actor*>::iterator it = m_actors.begin();
    while (it != m_actors.end())
    {
        if (getRadius(x, y, (*it)->getX(), (*it)->getY()) <= 6.0) return false;
        it++;
    }
    return true;
}

bool StudentWorld::inEarth(int x, int y)
{
    for (int col = x; col < x+4; col++)
    {
        for (int row = y; row < y+4; row++)
        {
            if (row >= VIEW_HEIGHT-4 || !m_earth[col][row]->isAlive()) return false;
        }
    }
    return true;
}

bool StudentWorld::inBounds(int x, int y)
{
	for (int col = x; col < x + 4; col++)
	{
		for (int row = y; row < y + 4; row++)
		{
			if (!(x > -1 && x<VIEW_WIDTH && y>-1 && y < VIEW_HEIGHT)) return false;
		}
	}
	return true;
}

bool StudentWorld::overlapEarth(int x, int y)
{
    for (int col = x; col < x+4; col++)
    {
        for (int row = y; row < y+4; row++)
        {
            if (row < VIEW_HEIGHT-4 && col < VIEW_WIDTH && m_earth[col][row]->isAlive()) return true;
        }
    }
    return false;
}

bool StudentWorld::overlapBoulder(int x, int y)
{
    for (int i = 0; i < m_boulders; i++)
    {
        if (m_actors[i]->isAlive() && getRadius(x, y, m_actors[i]->getX(), m_actors[i]->getY()) <= 3.0) return true;
    }
    return false;
}

bool StudentWorld::runIntoEarth(int x, int y)
{
	if (y >= VIEW_HEIGHT - 4) return false;
	return m_earth[x][y]->isAlive();
}

bool StudentWorld::runIntoBoulder(int x, int y)
{
    for (int i = 0; i < m_boulders; i++)
    {
        if (m_actors[i]->isAlive() && x == m_actors[i]->getX() && y == m_actors[i]->getY()) return true;
    }
    return false;
}

void StudentWorld::illuminate()
{
    vector<Actor*>::iterator it = m_actors.begin();
    while (it != m_actors.end())
    {
        if (getRadius(getPlayer()->getX(), getPlayer()->getY(), (*it)->getX(), (*it)->getY()) <= 12.0 && (*it)->isAlive()) (*it)->setVisible(true);
        it++;
    }
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
            if (overlapEarth(x1, i) || overlapBoulder(x1, i)) return false;
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
            if (overlapEarth(i, y1) || overlapBoulder(i, y1)) return false;
        }
        return true;
    }
}

bool StudentWorld::hitsProtester(Actor *a, int points)
{
    vector<Actor*>::iterator it = m_actors.begin();
    bool protestersAnnoyed = false;
    while (it != m_actors.end())
    {
        if ((*it)->isProtester() && getRadius(a->getX(), a->getY(), (*it)->getX(), (*it)->getY()) <= 3.0)
        {
            (*it)->getAnnoyed(points);
            protestersAnnoyed = true;
        }
        it++;
    }
    return protestersAnnoyed;
}

bool StudentWorld::protesterPicksUpGold(Gold* g)
{
    for (int i = 0; i < m_actors.size(); i++)
    {
        if (m_actors[i]->isProtester())
        {
            if (getRadius(g->getX(), g->getY(), m_actors[i]->getX(), m_actors[i]->getY()) <= 3.0)
            {
                g->setDead();
                playSound(SOUND_PROTESTER_FOUND_GOLD);

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

Location StudentWorld::setViableCoordinate(int Xmin, int Xmax, int Ymin, int Ymax)
{
    int Xa = Xmax-Xmin+1;
    int Xb = Xmin;
    
    int Ya = Ymax-Ymin+1;
    int Yb = Ymin;
    
    int x;
    int y;
    do 
	{
        x = rand() % Xa + Xb;
        y = rand() % Ya + Yb;
    } while (!checkPos(x, y) || !inEarth(x, y));
    
    return Location(x, y);
}

int StudentWorld::init()
{
    m_ticks = -1;
	m_protesters = min(15, static_cast<int>(2 + getLevel()*1.5));
	m_boulders = min(static_cast<int>(getLevel() / 2 + 2), 9);
	m_totalGold = max(static_cast<int>(5 - getLevel() / 2), 2);
	m_barrels = min(static_cast<int>(2 + getLevel()), 21);
    m_aliveProtesters = 0;
	m_probOfHardcore = min(90, static_cast<int>(getLevel() * 10 + 30));
    
    m_sonar = 1;
    m_gold = 0;
    
    // fill oil field with Earth objects
    for (int x = 0; x < VIEW_WIDTH; x++)
    {
        for (int y = 0; y < VIEW_HEIGHT-4; y++)
        {
            m_earth[x][y] = new Earth(x, y);
        }
    }

    for (int x = 30; x < 34; x++)
    {
        for (int y = 4; y < 60; y++)
        {
            hideEarthAt(x, y);
        }
    }

    // create player
    m_player = new TunnelMan(this);
    
    // Boulders
    for (int i = 0; i < m_boulders; i++)
    {
        Location loc = setViableCoordinate(0, 60, 20, 56);  

        // not close to other boulders and in earth
        m_actors.push_back(new Boulder(loc.m_col,loc.m_row, this));
        // clear out earth under current boulder
        hideEarthOverlap(loc.m_col, loc.m_row);
    }
    
    // Barrels
    for (int i = 0; i < m_barrels; i++)
    {
        Location loc = setViableCoordinate(0, 60, 0, 56);

        // not close to other boulders and in earth
        m_actors.push_back(new Barrel(loc.m_col, loc.m_row, this));
    }
    
    // Gold nuggets
    for (int i = 0; i < m_totalGold; i++)
    {
        Location loc = setViableCoordinate(0, 60, 0, 56);
        // not close to other boulders and within earth
        m_actors.push_back(new Gold(getPlayer(), loc.m_col, loc.m_row, this));
    }
    
    return GWSTATUS_CONTINUE_GAME;
}


int StudentWorld::move()
{
	setGameStat();
    
    // update ticks
    m_ticks++;
    m_ticksToAddProtesters--;
    
    // add new object
    int G = getLevel() * 25 + 300;

    if (rand() % G == 0)
    {
        // 20% possibility add sonar
        if (rand() % 5 == 0)
            m_actors.push_back(new Sonar(this));
        // 80% possibility add water pool
        else
        {
            int x;
            int y;
            do {
                x = rand() % VIEW_WIDTH;
                y = rand() % VIEW_HEIGHT-3;
            } while (overlapEarth(x, y) || overlapBoulder(x, y));
            m_actors.push_back(new Water(x, y, this));
        }
    }
    
    // add protester at first tick or if not enough protesters and waited at least T ticks
    if (m_ticks == 0 || (m_aliveProtesters < m_protesters && m_ticksToAddProtesters <= 0))
    {
        // add regular protester
        if (rand() % 99 > m_probOfHardcore)
        {
            m_actors.push_back(new RegularProtester(this));
        }
        // add hardcore protester
        else m_actors.push_back(new HardcoreProtester(this));

        // update number of alive protesters
        m_aliveProtesters++;
        // reset m_ticksToAddProtesters
        m_ticksToAddProtesters = max(25, static_cast<int>(200-getLevel()));
    }
    
    getPlayer()->doSomething();

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
            if (m_barrels == 0)
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

    // return the result
    // player died
    if (!m_player->isAlive())
    {
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    
    // level finished
    if (m_barrels == 0)
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

