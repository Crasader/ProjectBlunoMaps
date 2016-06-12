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
    int counter = 0;
    for(int i=0; i< 8; ++i)
    {
        for(int j=0; j<8; ++j)
        {
            m_grid[i][j] = counter++;
        }
    }
}

/*
Vector2 Grid::GetTileCoordCenterP(int tileNumber)
{
    int y = tileNumber / 8;
    int x = tileNumber % 8;

    return Vector2( m_startingPoint.x + (x * m_XLength) + (m_XLength/2) , m_startingPoint.y - (y * m_YLength) - (m_YLength/2) );
    
}
 
 Vector2 Grid::GetTileCoordStartP(int tileNumber)
 {
 int y = tileNumber / 8;
 int x = tileNumber % 8;
 
 return Vector2(x * m_XLength , y * m_YLength);
 }
 
 Vector2 Grid::AxisAlignedToIso(Vector2 position)
 {
    Vector2 isoPosition(0, 0);
    isoPosition.x = m_startingPoint.x + (2 * (m_startingPoint.y - position.y ) + (position.x - m_startingPoint.x ) ) / 2;
    isoPosition.y = m_startingPoint.y - (2 * (m_startingPoint.y - position.y) - (position.x - m_startingPoint.x) )/ 2;
    return isoPosition;
 }
 */

 Vector2 Grid::GetTileCoordCenterIso(int tileNumber)
 {
 int y = tileNumber / 8;
 int x = tileNumber % 8;
 
 return Vector2( m_startingPoint.x + (x * m_XLength) +(y * m_XLength) + m_XLength, m_startingPoint.y +(x * m_YLength) - (y * m_YLength));
 }

std::vector<int> Grid::GetSurrondingTiles(int tileNumber)
{
    //use grid matrix to find out surronds
    int i = tileNumber / 8;
    int j = tileNumber % 8;

}

int Grid::GetTileNumber(Vector2 tileCoord)
{
    

}

void Grid::update()
{
    int t =0;
}