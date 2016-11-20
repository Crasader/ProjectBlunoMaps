//
//  TouchGridWrapper.cpp
//  ProjectBlunoMaps
//
//  Created by Aaraddhya Bhatalkar on 11/17/16.
//
//

#include "TouchGridWrapper.h"

TouchGridWrapper* TouchGridWrapper::m_instance = NULL;

void TouchGridWrapper::setFactors(float startingPointX, float startingPointY, float xLength, float yLength)
{
    m_startingPoint.x = m_startingPoint.x + startingPointX;
    m_startingPoint.y = m_startingPoint.y + startingPointY;
    m_XLength = m_XLength + xLength;
    m_YLength = m_YLength + yLength;
}

Vector2 TouchGridWrapper::getTileCoordCenterIso(int tileNumber)
{
    int y = tileNumber / 8;
    int x = tileNumber % 8;
    
    return Vector2( m_startingPoint.x + (x * m_XLength) +(y * m_XLength) + m_XLength, m_startingPoint.y +(x * m_YLength) - (y * m_YLength));
}

int TouchGridWrapper::getTileNumber(Vector2 tileCoord)
{
    float xCoord = (tileCoord.x - m_startingPoint.x)/m_XLength;
    float yCoord = (tileCoord.y - m_startingPoint.y)/m_YLength;
    
    int y = ((xCoord - yCoord)/2.0f);
    int x = ((xCoord + yCoord)/2.0f);
    
    return ((y * 8) + x);
    
}
