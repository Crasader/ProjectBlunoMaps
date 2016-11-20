//
//  TouchGridWrapper.h
//  ProjectBlunoMaps
//
//  Created by Aaraddhya Bhatalkar on 11/17/16.
//
//

#ifndef TouchGridWrapper_h
#define TouchGridWrapper_h

#include "Defs.h"

class TouchGridWrapper
{

private:
    
    static TouchGridWrapper *m_instance;
    
    TouchGridWrapper() {}
    TouchGridWrapper(const TouchGridWrapper &){}
    TouchGridWrapper& operator=(const TouchGridWrapper &);
    
public:
    static TouchGridWrapper* getInstance()
    {
        if( m_instance == NULL)
            m_instance = new TouchGridWrapper();
        return m_instance;
    }
    
private:
    Vector2 m_startingPoint;
    //int m_totalTiles;
    //int m_grid[8][8];
    
    float m_XLength;
    float m_YLength;
    
public:
    
    Vector2 getTileCoordCenterIso(int tileNumber);
    int getTileNumber(Vector2 position);
    void setFactors(float, float, float, float);
};


#endif /* TouchGridWrapper_h */
