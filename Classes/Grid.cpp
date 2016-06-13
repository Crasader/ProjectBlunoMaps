//
//  Grid.cpp
//  ProjectBlunoMaps
//
//  Created by Aaraddhya Bhatalkar on 8/1/15.
//
//

#include "Grid.h"


Grid::Grid(Vector2 startingPoint, float xLength, float yLength)
:m_startingPoint(startingPoint), m_XLength(xLength), m_YLength(yLength)
{
    m_totalTiles = 0;
    
    for(int i=0; i < 8; ++i)
    {
        for(int j=0; j < 8; ++j)
        {
            m_grid[i][j] = m_totalTiles++;
        }
    }
}

/*
Vector2 Grid::getTileCoordCenterP(int tileNumber)
{
    int y = tileNumber / 8;
    int x = tileNumber % 8;

    return Vector2( m_startingPoint.x + (x * m_XLength) + (m_XLength/2) , m_startingPoint.y - (y * m_YLength) - (m_YLength/2) );
    
}
 
 Vector2 Grid::getTileCoordStartP(int tileNumber)
 {
 int y = tileNumber / 8;
 int x = tileNumber % 8;
 
 return Vector2(x * m_XLength , y * m_YLength);
 }
 
 Vector2 Grid::axisAlignedToIso(Vector2 position)
 {
    Vector2 isoPosition(0, 0);
    isoPosition.x = m_startingPoint.x + (2 * (m_startingPoint.y - position.y ) + (position.x - m_startingPoint.x ) ) / 2;
    isoPosition.y = m_startingPoint.y - (2 * (m_startingPoint.y - position.y) - (position.x - m_startingPoint.x) )/ 2;
    return isoPosition;
 }
 */

 Vector2 Grid::getTileCoordCenterIso(int tileNumber)
 {
     int y = tileNumber / 8;
     int x = tileNumber % 8;
     
     return Vector2( m_startingPoint.x + (x * m_XLength) +(y * m_XLength) + m_XLength, m_startingPoint.y +(x * m_YLength) - (y * m_YLength));
 }



std::set<int> Grid::getSurrondingTiles(int tileNumber, int radius)
{
    //use grid matrix to find out surronds
    std::set<int> surroundingTiles;
    surroundingTiles = getSurrondingTilesHelper(surroundingTiles, tileNumber, radius, false);
    
    //remove the tile
    surroundingTiles.erase(tileNumber);
    
    return surroundingTiles;
}

std::set<int> Grid::getSurrondingTilesHelper(std::set<int> &surroundingTiles, int tileNumber, int radius, bool updown)
{
    
    if(radius <= 0 && !updown)
        return surroundingTiles;
    
    if( (tileNumber % 8) ==  ((tileNumber + 1) % 8 ) -1)
    {
        surroundingTiles.insert(tileNumber+1);
        surroundingTiles = getSurrondingTilesHelper(surroundingTiles, tileNumber + 1, radius - 1, false);
    }
    
    if( (tileNumber -1) >= 0 && ((tileNumber % 8) ==  ((tileNumber - 1) % 8 ) +1) )
    {
        surroundingTiles.insert(tileNumber-1);
        surroundingTiles = getSurrondingTilesHelper(surroundingTiles, tileNumber - 1, radius - 1, false);
    }
    
    if(radius <= 0)
        return surroundingTiles;
    
    int down = tileNumber + 8;
    
    if( down >= 0 && down < m_totalTiles)
    {
        surroundingTiles.insert(down);
        surroundingTiles = getSurrondingTilesHelper(surroundingTiles, down, radius - 1, true);
    }
    
    int up = tileNumber - 8;
    
    if( up >= 0 && up < m_totalTiles)
    {
        surroundingTiles.insert(up);
        surroundingTiles = getSurrondingTilesHelper(surroundingTiles, up, radius - 1, true);
    }
    
    return surroundingTiles;
    
}

int Grid::GetTileNumber(Vector2 tileCoord)
{
    float xCoord = (tileCoord.x - m_startingPoint.x)/m_XLength;
    float yCoord = (tileCoord.y - m_startingPoint.y)/m_YLength;
    
    int y = (xCoord - yCoord)/2;
    int x = yCoord + y;
    
    return ((y * 8) + x);
}

void Grid::update()
{
    int t =0;
}

Grid::~Grid()
{
    
}