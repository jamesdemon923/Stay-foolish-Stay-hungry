#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include <vector>

class Earth;
class TunnelMan;
class Actor;
class Squirt;
class Gold;
struct Location;

class StudentWorld : public GameWorld
{
public:
    // constructor
    StudentWorld(std::string assetDir);
    
    // accessors
    Earth* getEarthAt(int x, int y);
    TunnelMan* getPlayer();
    int getTicks();
    int numGold();
    
    // mutators
    void foundBarrel();
    void decreasePoints(int points);
    void playerFoundGold();
    void gotSonarKit();
    void protesterDied();
    void dropsGold();
    
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    void setDisplayText();
    void addActor(Actor* a);
    int calcRadius(int x1, int y1, int x2, int y2);
    void hideEarthAt(int x, int y);
    void hideEarthOverlap(int x, int y);
    bool overlapWithEarth(int x, int y);
    bool overlapWithBoulder(int x, int y);
    bool runIntoBoulder(int x, int y);
    bool withinBounds(int x, int y);
    bool runIntoEarth(int x, int y);
    void illuminate();
    bool noObstacles(int x1, int y1, int x2, int y2);
    bool hitsProtester(Actor* a, int points);
    bool protesterPicksUpGold(Gold* g);
    
    // destructor
    virtual ~StudentWorld();
    
private:
    Earth* m_earth[VIEW_WIDTH][VIEW_HEIGHT-4];
    TunnelMan* m_player;
    std::vector<Actor*> m_actors;
    int m_nBarrels;
    int m_ticksCount;
    int m_nProtesters;
    int m_nBoulders;
    int m_nTicksToAddProtesters;
    int m_nCurProtesters;
    int m_probHardcore;
    int m_nTotalGold;
    
    // inventory
    int m_hitPoints;
    int m_nSonar;
    int m_nGold;
    
    Location generateViableCoord(int Xmin, int Xmax, int Ymin, int Ymax);
    // no overlap with other goodies or boulders
    bool validPos(int x, int y);
    bool withinEarth(int x, int y);
};

#endif // STUDENTWORLD_H_
