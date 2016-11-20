//
//  Grid.h
//  ProjectBlunoMaps
//
//  Created by Aaraddhya Bhatalkar on 8/1/15.
//
//

#ifndef __ProjectBlunoMaps__Grid__
#define __ProjectBlunoMaps__Grid__

#include <stdio.h>
#include <set>
#include "Defs.h"
#include "GameObject.h"

struct Route
{
    std::vector<int> m_routeTiles;
    float m_gradient;
    float m_timer;
    bool m_carved;
    
    Route(float gradient, float timer):  m_timer(timer), m_carved(false)
    {
        m_gradient = (255/2)/gradient;
    }
    
    float getGradient()
    {
        float gradient = ((m_routeTiles.size() -1) * m_gradient) + m_gradient;
        return (255 - gradient);
    }
};

class Grid : public GameObject
{
private:
    Vector2 m_startingPoint;
    int m_totalTiles;
    int m_grid[8][8];
    
    float m_XLength;
    float m_YLength;
    
    std::set<int> m_surroundingTiles;
    std::map<int, GameObject *> m_allTiles;
    std::vector<Route *> m_routes;
    
public:
    std::vector<int> routingTiles;
    
public:
    
    Grid(Vector2 startingPoint, float xLength, float yLength);
    
    Vector2     getTileCoordCenterIso(int tileNumber);
    int         getTileNumber(Vector2 position);
    void        markSurrondingTiles(int tileNumber, int radius);
    void        clearSurrondingTiles();
    bool        confirmRoute(Vector2);
    void        stopRoute(Vector2);

    void        lockDown();
    void        cancelLockDown();
    
    int moveToUpTile(int currentTile, int byNumber);
    int moveToDownTile(int currentTile, int byNumber);
    int moveToLeftTile(int currentTile, int byNumber);
    int moveToRightTile(int currentTile, int byNumber);
    
    /*
     Vector2 AxisAlignedToIso(Vector2 position);
     Vector2 GetTileCoordCenterP(int tileNumber);
     Vector2 GetTileCoordStartP(int tileNumber);
     */

    virtual void update(float);
    virtual ~Grid();
    
private:
    std::set<int> getSurrondingTilesHelper( std::set<int>  &, int tileNumber, int radius, bool updown);
    std::set<int> getSurrondingTiles();
};

#endif /* defined(__ProjectBlunoMaps__Grid__) */
