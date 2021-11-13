#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include <vector>
using namespace std;

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
    int numTicks();
    int numGold();
    
    // mutators
	void getGold();
	void dropGold();
    void findBarrel();
	void decreasePoints(int points);
    void protesterDies();

	// functions
    void setGameStat();
    void addActor(Actor* a);
    void hideEarthAt(int x, int y);
    void hideEarthOverlap(int x, int y);
	int getRadius(int x1, int y1, int x2, int y2);
	bool checkPos(int x, int y);
	bool inEarth(int x, int y);
	bool inBounds(int x, int y);
    bool overlapEarth(int x, int y);
    bool overlapBoulder(int x, int y);
    bool runIntoEarth(int x, int y);
	bool runIntoBoulder(int x, int y);
    void illuminate();
    bool noObstacles(int x1, int y1, int x2, int y2);
    bool hitsProtester(Actor* a, int points);
    bool protesterPicksUpGold(Gold* g);

	virtual int init();
	virtual int move();
	virtual void cleanUp();

    // functions
	virtual ~StudentWorld();
    
private:
    Earth* m_earth[VIEW_WIDTH][VIEW_HEIGHT-4];
    TunnelMan* m_player;
    vector<Actor*> m_actors;
    int m_barrels;
    int m_ticks;
    int m_protesters;
    int m_boulders;
    int m_ticksToAddProtesters;
    int m_aliveProtesters;
    int m_probOfHardcore;
    int m_totalGold;
    int m_hitPoints;
    int m_sonar;
    int m_gold;

    Location setViableCoordinate(int Xmin, int Xmax, int Ymin, int Ymax);
};

#endif // STUDENTWORLD_H_
