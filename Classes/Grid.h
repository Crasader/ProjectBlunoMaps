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
#include <vector>

class Grid : public GameObject
{
private:
    Vector2 m_startingPoint;
    int m_totalTiles;
    int m_grid[8][8];
    float m_XLength;
    float m_YLength;
    
public:
    
    Grid(Vector2 startingPoint, float xLength, float yLength);
    
    Grid(Vector2 startingPoint, float xTransxLength, float xTransyLength, float yTransxLength, float yTransyLength);
    
    int     GetTileNumber(Vector2 position);
    
    /*
    Vector2 AxisAlignedToIso(Vector2 position);
    Vector2 GetTileCoordCenterP(int tileNumber);
    Vector2 GetTileCoordStartP(int tileNumber);
    */
    
    Vector2 GetTileCoordCenterIso(int tileNumber);
    
    
    std::vector<int> GetSurrondingTiles(int tileNumber);
    
    virtual void update();
    ~Grid();
};

#endif /* defined(__ProjectBlunoMaps__Grid__) */
