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
#include "Defs.h"
#include "GameObject.h"
#include <set>

class Grid : public GameObject
{
private:
    Vector2 m_startingPoint;
    int m_totalTiles;
    int m_grid[8][8];
    
    float m_XLength;
    float m_YLength;
    
private:
     std::set<int> getSurrondingTilesHelper( std::set<int>  &, int tileNumber, int radius, bool updown);
    
public:
    
    Grid(Vector2 startingPoint, float xLength, float yLength);
    
    int     GetTileNumber(Vector2 position);
    
    /*
    Vector2 AxisAlignedToIso(Vector2 position);
    Vector2 GetTileCoordCenterP(int tileNumber);
    Vector2 GetTileCoordStartP(int tileNumber);
    */
    
    Vector2 getTileCoordCenterIso(int tileNumber);
    
    
    std::set<int> getSurrondingTiles(int tileNumber, int radius);
    
    virtual void update(Vector2);
    virtual ~Grid();
};

#endif /* defined(__ProjectBlunoMaps__Grid__) */
